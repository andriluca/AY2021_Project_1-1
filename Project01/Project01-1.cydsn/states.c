/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "states.h"

volatile uint8_t wtm;
volatile uint8_t t_isr;
uint8_t raw_data_8bit[BYTE_TO_READ_PER_LEVEL];
uint16_t raw_data_16bit[3];
int16_t converted_acc[3];
uint32_t concatenated_Data;
uint8_t out      [(LEVEL_TO_READ + 1) * 6];
uint8_t outEEPROM[(LEVEL_TO_READ + 1) * 6 + 2];
uint8_t outUART [(LEVEL_TO_READ + 1) * 6];
uint8_t temp;
uint8_t offset;
uint8_t fifo_write;
uint8_t fifo_read;
uint8_t fifo_level;
uint16_t outIndex;
volatile uint8_t full_eeprom;
volatile uint8_t shiftIndex;
volatile uint16_t eeprom_index; //max 65535 se uint16
volatile uint8_t eeprom_reset;


uint8_t comm_abilitate;
uint8_t index_temp;
uint32_t temperature32 = 0;
uint8_t temperature[(LEVEL_TO_READ+1) * 2];
uint8 settings;

void init()
{
    UART_Start();
    T_TIMER_CLOCK_Start();
    T_TIMER_Start();
    ADC_Temp_Start();
    INT_EEPROM_Start();
    INT_EEPROM_UpdateTemperature();
    settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
    if((settings & 0xC0) != 0x00)           
    {
        settings = _2g|(_1Hz<<2)|(CELSIUS<<4)|(ESAV_OFF<<5);               //"Reboot" starting from minimum sampling frequency
        INT_EEPROM_Write(&settings, CONFIG_REGISTER);
    }
       
    I2C_Peripheral_Start();
    // I2C Boot
    CyDelay(5);
    I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS);
    
    if((settings & ESAV_STATUS)>>5)
    {
        temp = 1;
        PWM_Start();
        I2C_LIS3DH_Start(settings);
        ISR_ACC_StartEx(WTM_ISR);
    }       
    else
    {
        temp = 0;            
        ISR_ACC_Stop(); 
        PWM_Stop();
    }
    
    ISR_RX_StartEx(COMM_GUI);
    
    
    t_isr = 0;          //abilita isr timer
    fifo_level = 0;     //
    index_temp = 0;     //puntatore array temperatura
    outIndex = 0;       //usato in writeeeprom per tenere indirizzo attuale
    eeprom_index = 0;   //primo indirizzo eeprom disponibile
    eeprom_reset = 0;   // per resettare la eeprom
    offset = 0;         //per leggere fifo    
    pages = 1;          //da 0x00 a 0x80 è già una pagina scritta
    concatenated_Data = 0;      //pacchetto di dati per ogni livello  
    full_eeprom = 0;
    comm_rec = 0;
    comm_abilitate = 1;
    fifo_write = 0;     
    fifo_read = 0;
    wtm = WTM_LOW;
}

void restart()
{
    T_TIMER_CLOCK_Start();
    T_TIMER_Start();
 
    if((settings & 0xC0) != 0x00)           
        {
            settings = _2g|(_1Hz<<2)|(CELSIUS<<4)|(ESAV_OFF<<5);               //"Reboot" starting from minimum sampling frequency
            INT_EEPROM_Write(&settings, CONFIG_REGISTER);
        }
        
    if((settings & ESAV_STATUS)>>5)
        {
            temp = 1;
            PWM_Start();
            I2C_LIS3DH_Start(settings);
            ISR_ACC_StartEx(WTM_ISR);
        }       
    else
        {
            temp = 0;            
            ISR_ACC_Stop(); 
            PWM_Stop();
        }
    
    t_isr = 0;          //abilita isr timer
    fifo_level = 0;     //
    index_temp = 0;     //puntatore array temperatura
    outIndex = 0;       //usato in writeeeprom per tenere indirizzo attuale
    eeprom_index = 0;   //primo indirizzo eeprom disponibile
    eeprom_reset = 0;   // per resettare la eeprom
    offset = 0;         //per leggere fifo    
    pages = 1;          //da 0x00 a 0x80 è già una pagina scritta
    concatenated_Data = 0;      //pacchetto di dati per ogni livello  
    full_eeprom = 0;
    comm_rec = 0;
    comm_abilitate = 1;
    temp = 1;
    fifo_write = 0;     
    fifo_read = 0;
    wtm = WTM_LOW;
  
}


// Condizioni

_Bool onTemperature(){
    return temp && !wtm && !fifo_write && !fifo_read;
}

_Bool onWatermark(){
    return wtm && !fifo_write && !fifo_read;
}

_Bool onWriteEEPROM(){
    return !wtm && fifo_write;
}

_Bool onFullEEPROM(){
    return full_eeprom && !fifo_write;
}

_Bool onReadEEPROM(){
    return fifo_read; //eventuale condizione del pulsante
}

_Bool onEEPROMReset(){
    return eeprom_reset;
}

// Stati

void doTemperature(){
    uint8_t actual_level;

    if(fifo_level == 0) ISR_T_StartEx(TEMP_ISR);

    if(fifo_level <= LEVEL_TO_READ)
    {
        if(t_isr)
        {
        I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_SRC_REG, &actual_level);
        t_isr = 0;
        }

        if((actual_level & 0x1F) == fifo_level)
        {

            temperature32 = ADC_Temp_Read32();

            if (temperature32 > ADC_MAX)
            temperature32 = ADC_MAX;
            if (temperature32 < ADC_MIN)
            temperature32 = ADC_MIN;


            temperature[index_temp + 1] = (uint8_t)((temperature32 >>8) & 0xFF); //msb
            temperature[index_temp] = (uint8_t)(temperature32 & 0xFF); //lsb

            index_temp = index_temp + 2;
            fifo_level ++;
        }
    }
    else
    {
        ISR_T_Stop();
        temp = 0;
        index_temp = 0;
        fifo_level = 0;
    }
}


void doWatermark(){
    for (int level = 0; level < LEVEL_TO_READ + 1; level++){

        // Receiving raw data
    	I2C_LIS3DH_Get_Raw_Data(raw_data_16bit);
    	// Converting data
//    	for (uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
//    	{
//    	    converted_acc[i] = (int16)(raw_data_16bit[i] * sensitivity * CONVERSION);
//    	}
        CyDelayUs(200);
    	// Creating the data packets
    	concatenated_Data = 0;
    	uint8_t count = LIS3DH_OUT_AXES-1;
    	for(uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
    	{
    	    concatenated_Data |= (uint32_t)((raw_data_16bit[i] & 0x3FF) << 10*count);
    	    count--;
    	}

    	// Populating the buffer with acceleration values.
    	for(uint8_t i = 0; i < LIS3DH_RESOLUTION; i++)
    	{
    	    out[i + offset] = (uint8_t)((concatenated_Data >> 8*i) & 0xFF);
    	}

        out[4 + offset] = temperature[index_temp];
        out[5 + offset] = temperature[index_temp + 1];

        index_temp = index_temp + 2;
    	offset = offset + 6;

    }

    index_temp = 0;
    offset = 0;
    fifo_write = 1;
    wtm = 0;

}

void doWriteEEPROM(){

    I2C_EXT_EEPROM_WriteWord(out);

    outIndex = outIndex + 126;

    if (//outIndex == 5*EEPROM_WORD_SIZE
        //I2C_EXT_EEPROM_Last_Index(out) < 126 || outIndex == 110
        outIndex == 110
    ) //overflow
    {
        full_eeprom = 1;
    }

    temp = 1;
    fifo_write = 0;

}

void doFullEEPROM(){
    
    LED_BlinkFast();
    full_eeprom = 0;
    
}

void doReadEEPROM(){
    
    EXT_LED_Write(EXT_LED_ON);
    
    CyDelay(5);
    uint8_t header[] = {0xA0};
    uint8_t tail[] = {0xC0, 0xC0};

    uint16_t outIndex_read = 0;

    UART_PutArray(header, 1);
    for (uint16_t i = 0; i<pages; i++)
    {

//        I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
//                                        (outIndex_read >> 8) & 0xFF,
//                                        outIndex_read & 0xFF,
//                                        128,
//                                        outEEPROM);
//        outIndex_read = outIndex_read + 128;
        I2C_EXT_EEPROM_PrintWord(i);


        UART_PutArray(outEEPROM, 128);
    }
    UART_PutArray(tail, 2);
    
    pages = 1;
    fifo_read = 0;
    eeprom_reset = 1;
    
    EXT_LED_Write(EXT_LED_OFF);

}

void doEEPROMReset(){
    
    I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS);
    eeprom_reset = 0;
    
}