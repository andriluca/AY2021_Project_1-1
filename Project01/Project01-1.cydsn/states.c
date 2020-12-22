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
#include "accelerometer.h"
#include "I2c.h"
#include "EEPROM.h"

uint8 sensitivity;
volatile uint8_t wtm;
uint8_t raw_data_8bit[BYTE_TO_READ_PER_LEVEL];
int16_t raw_data_16bit[3];
int16_t converted_acc[3];
uint32_t concatenated_Data;
uint8_t out      [(LEVEL_TO_READ + 1) * 6];
uint8_t outEEPROM[(LEVEL_TO_READ + 1) * 6 + 2];
uint8_t outUART [(LEVEL_TO_READ + 1) * 6];
uint8_t j;
uint8_t temp;
uint8_t offset;
uint8_t fifo_write;
uint8_t fifo_read;
uint8_t fifo_level;
uint8_t word_sizes[EEPROM_TOTAL_WORDS] = {};
uint16_t written_pages;
uint16_t outIndex;
volatile uint8_t shiftIndex;
volatile uint16_t eeprom_index; //max 65535 se uint16
volatile uint8_t eeprom_reset;



uint8_t index_temp;
uint32_t temperature32 = 0;
uint8_t temperature[(LEVEL_TO_READ+1) * 2];

void init()
{
    UART_Start();
    I2C_Peripheral_Start();
    I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS);
    I2C_LIS3DH_Start();
    ISR_ACC_StartEx(WTM_ISR);
    
    wtm = WTM_LOW;
    temp = 1;
    fifo_level = 0;
    index_temp = 0;
    shiftIndex = 0;
    outIndex = 0;
    eeprom_index = 0;
    eeprom_reset = 0;   // per resettare la eeprom
    offset = 0;
    fifo_write = 0;
    fifo_read = 0;
    written_pages = 0;
    concatenated_Data = 0;
    sensitivity = 4;
    CyDelay(5);
    ADC_Temp_Start();
}

_Bool onTemperature(){
    return temp && !wtm && !fifo_write && !fifo_read;
}

//_Bool onTemperature(){
//    return (temp < LEVEL_TO_READ + 1) && !wtm && !fifo_write && !fifo_read;
//}

_Bool onWatermark(){
    return wtm && !fifo_write && !fifo_read;
}

_Bool onWriteEEPROM(){
    return !wtm && fifo_write;
}

_Bool onReadEEPROM(){
    return fifo_read && !fifo_write; //eventuale condizione del pulsante
}
    
_Bool onEEPROMReset(){
    return eeprom_reset;
}

void doTemperature(){
    uint8_t actual_level;
    while(fifo_level <= LEVEL_TO_READ){
        do{
        I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_SRC_REG, &actual_level);
        }
        while((actual_level & 0x1F) == fifo_level);

        temperature32 = ADC_Temp_Read32();
                    
        if (temperature32 > ADC_MAX)    
        temperature32 = ADC_MAX;
        if (temperature32 < ADC_MIN)
        temperature32 = ADC_MIN;
              

        temperature[index_temp] = (uint8_t)((temperature32 >>8) & 0xFF); //msb
        temperature[index_temp + 1] = (uint8_t)(temperature32 & 0xFF); //lsb

        index_temp = index_temp + 2;
        fifo_level ++;
    }
    temp = 0;
    index_temp = 0;
    fifo_level = 0;
}

//void doTemperature(){
//    
//    
//    if (temp == 0){
//        uint8_t start_XDA;
//        do{
//            I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_STATUS_REG, &start_XDA);
//        }while(start_XDA == 1);
//        
//        TIMER_CLOCK_Start();
//        TIMER_Start();
//        TIMER_WritePeriod(20);
//        ISR_TIMER_StartEx(TIMER_ISR);
//        
//        
//        temperature32 = ADC_Temp_Read32();
//                
//        if (temperature32 > ADC_MAX)    
//        temperature32 = ADC_MAX;
//        if (temperature32 < ADC_MIN)
//        temperature32 = ADC_MIN;
//              
//
//        temperature[index_temp] = (uint8_t)((temperature32 >>8) & 0xFF); //msb
//        temperature[index_temp + 1] = (uint8_t)(temperature32 & 0xFF); //lsb
//
//        index_temp = index_temp + 2;
//    }
//    else
//    {
//        temperature32 = ADC_Temp_Read32();
//                
//        if (temperature32 > ADC_MAX)    
//        temperature32 = ADC_MAX;
//        if (temperature32 < ADC_MIN)
//        temperature32 = ADC_MIN;
//              
//
//        temperature[index_temp] = (uint8_t)((temperature32 >>8) & 0xFF); //msb
//        temperature[index_temp + 1] = (uint8_t)(temperature32 & 0xFF); //lsb
//
//        index_temp = index_temp + 2;
//    }
//    if (temp == LEVEL_TO_READ)
//    {
//        TIMER_Stop();
//        index_temp = 0;
//    }
//}

void doWatermark(){
    for (int level = 0; level < LEVEL_TO_READ + 1; level++){

        // Receiving raw data
    	I2C_LIS3DH_Get_Raw_Data(raw_data_16bit);
    	// Converting data
    	for (uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
    	{
    	    converted_acc[i] = (int16)(raw_data_16bit[i] * sensitivity * CONVERSION);
    	}
    	// Creating the data packets
    	concatenated_Data = 0;
    	uint8_t count = LIS3DH_OUT_AXES-1;
    	for(uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
    	{
    	    concatenated_Data |= (uint32_t)((converted_acc[i] & 0x3FF) << 10*count);
    	    count--;
    	}

    	// Populating the buffer with acceleration values.
    	for(uint8_t i = 0; i < LIS3DH_RESOLUTION; i++)
    	{
    	    out[i + offset] = (uint8_t)((concatenated_Data >> 8*i) & 0xFF);
    	}

    	// Populating the buffer with temperature values.
//    	for(uint8_t i = 4; i < LIS3DH_RESOLUTION + 2; i++)
//    	{
//    	    // In questo momento scrivo zero perchè non ci abbiamo ancora lavorato.
//    	    out[i + offset] = 0;
//    	}
        
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
    
//    I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
//                (eeprom_index >> 8) & 0xFF,
//				eeprom_index & 0xFF,
//				126,
//				out);
////    I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS);
//    CyDelay(5);
//
////    for (uint8_t i = 0; i<128; i++)
////        outEEPROM[i] = 0;
//
//    I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
//                                        (eeprom_index >> 8) & 0xFF,
//                                        eeprom_index & 0xFF,
//                                        128,
//                                        outEEPROM);
    outIndex = outIndex + 128;
    temp = 1;
    fifo_write = 0;
    
    
    
    if (outIndex == 10*EEPROM_WORD_SIZE
//        I2C_EXT_EEPROM_Last_Index(out) < 126 || outIndex == 0
    ) //overflow
    {
        fifo_read = 1;
    }

}

void doReadEEPROM(){
    
    CyDelay(5);
    uint8_t header[] = {0xA0};
    uint8_t tail[] = {0xC0};
    
    uint16_t outIndex = 0;
    
    UART_PutArray(header, 1);
    for (uint16_t i = 0; i<(int)(eeprom_index/EEPROM_WORD_SIZE); i++)
    {
        
        I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                        (outIndex >> 8) & 0xFF,
                                        outIndex & 0xFF,
                                        128,
                                        outEEPROM);
        outIndex = outIndex + 128;
        
        
        UART_PutArray(outEEPROM, 128);
    }
    UART_PutArray(tail, 1);
    fifo_read = 0;
    eeprom_reset = 1;
    
}

void doEEPROMReset(){
    I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS);
    eeprom_reset = 0;
}


/* [] END OF FILE */
