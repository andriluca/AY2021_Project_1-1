/* =========================================================================
 * Project01-1, Luca Andriotto, Matteo Cavicchioli, Alessandro Pirelli
 * =========================================================================
*/

#include "states.h"

// ================================= CONDITIONS =================================

/*****************************************************************************\
 * Function:    onByteReceived
 * Returns:     Boolean
 * Description: 
 *     True when byte from UART is received.
\*****************************************************************************/

_Bool onByteReceived();

/*****************************************************************************\
 * Function:    onStopping
 * Returns:     Boolean
 * Description: 
 *     True to abilitate doStopping state.
\*****************************************************************************/

_Bool onStopping();

/*****************************************************************************\
 * Function:    onSaving
 * Returns:     Boolean
 * Description: 
 *     True to abilitate doSaving state.
\*****************************************************************************/

_Bool onSaving();

/*****************************************************************************\
 * Function:    onHandshake
 * Returns:     Boolean
 * Description: 
 *     True to abilitate doHandshake state.
\*****************************************************************************/

_Bool onHandshake();

/*****************************************************************************\
 * Function:    onChangeConfig
 * Returns:     Boolean
 * Description: 
 *     True to abilitate doChangeConfig state.
\*****************************************************************************/

_Bool onChangeConfig();

/*****************************************************************************\
 * Function:    onVisualizing
 * Returns:     Boolean
 * Description: 
 *     True to abilitate doVisualizing state.
\*****************************************************************************/

_Bool onVisualizing();

/*****************************************************************************\
 * Function:    onTemperature
 * Returns:     Boolean
 * Description: 
 *     True to abilitate doTemperature state.
\*****************************************************************************/

_Bool onTemperature();

/*****************************************************************************\
 * Function:    onWatermark
 * Returns:     Boolean
 * Description: 
 *     True to abilitate doWatermark state.
\*****************************************************************************/

_Bool onWatermark();

/*****************************************************************************\
 * Function:    onWriteEEPROM
 * Returns:     Boolean
 * Description: 
 *     True to abilitate doWriteEEPROM state.
\*****************************************************************************/

_Bool onWriteEEPROM();

/*****************************************************************************\
 * Function:    onFullEEPROM
 * Returns:     Boolean
 * Description: 
 *     True to abilitate doFullEEPROM state.
\*****************************************************************************/

_Bool onFullEEPROM();

/*****************************************************************************\
 * Function:    onReadEEPROM
 * Returns:     Boolean
 * Description: 
 *     True to abilitate doReadEEPROM state.
\*****************************************************************************/

_Bool onReadEEPROM();

/*****************************************************************************\
 * Function:    onEEPROMReset
 * Returns:     Boolean
 * Description: 
 *     True to abilitate doEEPROMReset state.
\*****************************************************************************/

_Bool onEEPROMReset();

/*****************************************************************************\
 * Function:    onButtonReleased
 * Returns:     Boolean
 * Description: 
 *     True to abilitate doButtonReleased state.
\*****************************************************************************/

_Bool onButtonReleased();

// =============================== END CONDITIONS ===============================

// =================================== STATES ===================================

/*****************************************************************************\
 * Function:    doByteReceived
 * Returns:     Void
 * Description: 
 *     Reads command coming from GUI (UART).
\*****************************************************************************/

void doByteReceived();

/*****************************************************************************\
 * Function:    doStopping
 * Returns:     Void
 * Inputs: reading: True when EEPROM reading is required
 * Description: 
 *     Disabilitating data saving and acquisition.
\*****************************************************************************/

void doStopping(uint8_t reading);

/*****************************************************************************\
 * Function:    doSaving
 * Returns:     Void
 * Inputs: reading: True when EEPROM reading is required
 * Description: 
 *     Enabling data saving and acquisition.
\*****************************************************************************/

void doSaving(uint8_t reading);

/*****************************************************************************\
 * Function:    doToggle
 * Returns:     Void
 * Inputs: reading: True when EEPROM reading is required
 * Description: 
 *     Toggling data saving and acquisition.
\*****************************************************************************/

void doToggle();

/*****************************************************************************\
 * Function:    doHandshake
 * Returns:     Void
 * Description: 
 *     Upon receiving specific command from GUI, sends back custom strings and current settings.
\*****************************************************************************/

void doHandshake();

/*****************************************************************************\
 * Function:    doChangeConfig
 * Returns:     Void
 * Description: 
 *     Updates Registers considering the Configuration Byte.
\*****************************************************************************/

void doChangeConfig();

/*****************************************************************************\
 * Function:    doVisualizing
 * Returns:     Void
 * Description: 
 *     Sends EXT EEPROM content through UART.
\*****************************************************************************/

void doVisualizing();

/*****************************************************************************\
 * Function:    doTemperature
 * Returns:     Void
 * Description: 
 *     Samples the temperature values with the same ODR.
\*****************************************************************************/

void doTemperature();

/*****************************************************************************\
 * Function:    doWatermark
 * Returns:     Void
 * Description: 
 *     Sampling acceleration when WTM ISR is received.
\*****************************************************************************/

void doWatermark();

/*****************************************************************************\
 * Function:    doWriteEEPROM
 * Returns:     Void
 * Description: 
 *     Writing EEPROM with the recorded words.
\*****************************************************************************/

void doWriteEEPROM();

/*****************************************************************************\
 * Function:    doFullEEPROM
 * Returns:     Void
 * Description: 
 *     Stopping acquisition and changing built-in LED blinking pattern.
\*****************************************************************************/

void doFullEEPROM();

/*****************************************************************************\
 * Function:    doReadEEPROM
 * Returns:     Void
 * Description: 
 *     Sending EEPROM content through UART.
\*****************************************************************************/

void doReadEEPROM();

/*****************************************************************************\
 * Function:    doEEPROMReset
 * Returns:     Void
 * Description: 
 *     Erasing EEPROM content and resetting indexes.
\*****************************************************************************/

void doEEPROMReset();

/*****************************************************************************\
 * Function:    doButtonReleased
 * Returns:     Void
 * Description: 
 *     Checks pressure duration.
\*****************************************************************************/

void doButtonReleased();

// ================================= END STATES =================================


// =================================== UTILS ===================================

/*****************************************************************************\
 * Function:    getParam
 * Returns:     Void
 * Inputs: settings: Configuration byte, parameters: output vector.
 * Description: 
 *     Writes the configuration state in vector parameters.
\*****************************************************************************/

void restart();

/*****************************************************************************\
 * Function:    restart
 * Returns:     void
 * Description: 
 *     Brings the device in an IDLE state.
\*****************************************************************************/

void getParam(uint8_t settings, uint8_t* parameters);

/*****************************************************************************\
 * Function:    doManageData
 * Returns:     Void
 * Description: 
 *     Populating output data buffer with accelerations and temperatures.
\*****************************************************************************/

void doManageData();

/*****************************************************************************\
 * Function:    retrieve_pages
 * Returns:     pages
 * Description: 
 *     Calculates page in which to start to write data
\*****************************************************************************/

uint16_t retrieve_pages(uint16_t eeprom_index);

// ================================= END UTILS =================================


// Initialization

void init()
{
    CyGlobalIntEnable;
    // Setup peripherals
    UART_Start();
    T_TIMER_CLOCK_Start();
    T_TIMER_Start();
    ADC_Temp_Start();
    INT_EEPROM_Start();
    
    settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
    
    // Checking memory content's consistency
    if(settings & 0xC0)
    {
        settings =      LIS3DH_FS_02_CB 
                    | ( LIS3DH_ODR_01_CB        << ODR_LSB) 
                    | ( CELSIUS                 << TEMP_FORMAT_LSB) 
                    | ( ESAV_OFF                << ESAV_STATUS_LSB);               // "Reboot" starting from minimum sampling frequency
        INT_EEPROM_UpdateTemperature();
        INT_EEPROM_Write(&settings, CONFIG_REGISTER);
    }

    I2C_Peripheral_Start();
    CyDelay(5);                 // I2C Boot
    // Checking EEPROM Status
    uint8_t in[2];
    I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                    0xFF,
                                    0xFC,
                                    2,
                                    in);
    CyDelay(5);
//    I2C_EXT_EEPROM_ReadRegister(EXT_EEPROM_DEVICE_ADDRESS,
//                                    0xFF,
//                                    0xFC,
//                                    in);
//    CyDelay(5);
//    I2C_EXT_EEPROM_ReadRegister(EXT_EEPROM_DEVICE_ADDRESS,
//                                    0xFF,
//                                    0xFC,
//                                    in + 1);
    
    if(!(in[0] == '%' && in[1] == '!')) 
        doEEPROMReset();

    if(settings & ESAV_STATUS){
        
        temp = 1;
        LED_Start();
        I2C_LIS3DH_Start(settings);
        ISR_T_StartEx(TEMP_ISR);
        ISR_ACC_StartEx(WTM_ISR);
        
    }
    else{
        
        temp = 0;
        ISR_ACC_Stop();
        LED_Stop();
        
    }

    TIMER_RESET_Start();

    ISR_TIMER_RESET_StartEx(COUNT_SEC);

    ISR_RX_StartEx(COMM_GUI);


    // Setup variables
    fifo_level = 0;
    uint8_t eeprom_index_arr[2];
    
    I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                0xFF,
                                0xFE,
                                2,
                                eeprom_index_arr);
//    I2C_EXT_EEPROM_ReadRegister(EXT_EEPROM_DEVICE_ADDRESS,
//                            0xFF,
//                            0xFE,
//                            eeprom_index_arr);
//    CyDelay(5);
//    I2C_EXT_EEPROM_ReadRegister(EXT_EEPROM_DEVICE_ADDRESS,
//                            0xFF,
//                            0xFF,
//                            eeprom_index_arr + 1);
    
    eeprom_index = (uint16_t)(eeprom_index_arr[1] << 8) | eeprom_index_arr[0];
//    outIndex = INT_EEPROM_ReadByte(INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_L) 
//                | (INT_EEPROM_ReadByte(INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_H) << 8);      // usato in writeeeprom per tenere indirizzo attuale
    // eeprom_index = 0;                                                                               // primo indirizzo eeprom disponibile
    eeprom_reset = 0;                                                                               // per resettare la eeprom
    pages = retrieve_pages(eeprom_index);
    full_eeprom = 0;
    comm_rec = 0;
    fifo_write = 0;
    fifo_read = 0;
    counted_seconds = 0;
    isButtonReleased = 0;
    offset = 0;
    index_temp = 0;
    boot = 1;
    wtm = WTM_LOW;
    t_isr = 0;
    trigger = 0;
    
}

void loop(){
    
    for(;;)
    {
        // Controlling the received byte
        if(onByteReceived())    
        doByteReceived();
        
        // Controlling each case
        // 1. Stopping character received
        if(onStopping())        
        doStopping(EXT_EEPROM_NO_RESETTING);
        
        // 2. Saving character received
        if(onSaving())          
        doSaving(EXT_EEPROM_NO_RESETTING);
        
        // 3. Handshake character received
        if(onHandshake())       
        doHandshake();
        
        // 4. Configuration and Config Buffer characters received
        if(onChangeConfig())    
        doChangeConfig();
        
        // 5. Visualizing character received
        if(onVisualizing())     
        doVisualizing();
        
        // Reading the Temperature
        if (onTemperature())    
        doTemperature();
        
        // Reading the FIFO
        if (onWatermark())      
        doWatermark();
        
        // Writing the EEPROM
        if (onWriteEEPROM())   
        doWriteEEPROM();
        
        // Handling BUILT-IN LED blinking
        if(onFullEEPROM())      
        doFullEEPROM();

        // Handling Button releasing
        if (onButtonReleased()) 
        doButtonReleased();
            
    }
    
}

// Conditions

_Bool onByteReceived(){
    
    return comm_rec;

}

_Bool onStopping(){

    return onByteReceived() 
    && msg == 's';

}

_Bool onSaving(){

    return onByteReceived() 
    && msg == 'b'
    && !full_eeprom;

}

_Bool onHandshake(){
    
    return onByteReceived() 
    && msg == 'h';
    
}

_Bool onChangeConfig(){
    
    return onByteReceived() 
    && msg == 'c';

}

_Bool onVisualizing(){
    
    return onByteReceived() 
    && msg == 'v';

}

_Bool onTemperature(){
    
    return t_isr        // When ISR is triggered
    && temp             // Enable control
    && !fifo_write 
    && !fifo_read
    && !full_eeprom;

}

_Bool onWatermark(){
    
    return wtm 
    && !fifo_write 
    && !fifo_read
    && !full_eeprom;

}

_Bool onWriteEEPROM(){
    
    return !wtm 
    && fifo_write 
    && !full_eeprom;

}

_Bool onFullEEPROM(){
    
    return full_eeprom; 
    //&& !fifo_write;

}

_Bool onReadEEPROM(){
    
    return fifo_read;

}

_Bool onEEPROMReset(){
    
    return eeprom_reset;

}

_Bool onButtonReleased(){
    
    return isButtonReleased;

}


// States

void doByteReceived(){
    
    msg = UART_ReadRxData();
    //UART_ClearRxBuffer();
    
}

void doStopping(uint8_t resetting){
    
    // Disabling temperature data saving.
    temp = 0;
    // Reading configuration byte
    settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
    // Saving toggled bit
    settings &= ~(1 << ESAV_STATUS_LSB);
    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte(settings, CONFIG_REGISTER);
    // Disabling acceleration reading ISR.
    ISR_ACC_Stop();
    wtm = WTM_LOW;
    LED_Stop();
    // Discarding old data
    if(resetting) doEEPROMReset();
    //if(resetting) I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS, pages);
    
    msg = ' ';
    comm_rec = 0;
}

void doSaving(uint8_t resetting){
    
    // Reading configuration byte
    settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
    // Saving toggled bit
    settings  |= (1 << ESAV_STATUS_LSB);
    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte(settings, CONFIG_REGISTER);
    // Discarding old data
    if(resetting) doEEPROMReset();
    restart();
    
    //    if(resetting) I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS, pages);
    
    msg = ' ';
    comm_rec = 0;
}

void doToggle(){
    
    // Reading configuration byte
    uint8_t new_settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
    
    // Saving toggled bit
    new_settings ^= (1 << ESAV_STATUS_LSB);
    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte(new_settings, CONFIG_REGISTER);
    
    // Checking if saving or stopping
    if (new_settings & (1 << ESAV_STATUS_LSB)) restart();
    else {
        // Disabling temperature data saving.
        temp = 0;
        // Disabling acceleration reading ISR.
        ISR_ACC_Stop();
        wtm = WTM_LOW;
        LED_Stop();
    }
    
    msg = ' ';
    comm_rec = 0;
}

void doHandshake(){

    uint8_t parameters[4];
    // Sending handshake passphrase.
    UART_PutString("Accelerometer Hello $$$\n");
    // Reading stored Configuration byte.
    settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
    
    // Preparing messages to send through UART.
    char tosend[10];
    getParam(settings, parameters);

    // Sending FSR
    sprintf(tosend, "+-%dg\n", parameters[0]);
    UART_PutString(tosend);

    // Sending ODR
    sprintf(tosend, "%dHz\n", parameters[1]);
    UART_PutString(tosend);

    // Sending Temperature Format
    parameters[2] ? UART_PutString("Fahrenheit\n") : UART_PutString("Celsius\n");

    // Sending Saving Status
    
    parameters[3] ? UART_PutString("ON\n") : UART_PutString("OFF\n");

    msg = ' ';
    comm_rec = 0;

}

void doChangeConfig(){
    
    uint8_t new_settings;
    // Waiting the Configuration Byte.
    comm_rec = 0;
    while(!comm_rec);

    // Reading settings
    new_settings = UART_ReadRxData();
    //UART_ClearRxBuffer();

    // Initializing accelerometer with new settings
    I2C_LIS3DH_Start(new_settings);
    
    // Updating Saving Status Bit
    (new_settings & ESAV_STATUS) >> ESAV_STATUS_LSB ? doSaving(EXT_EEPROM_RESETTING) : doStopping(EXT_EEPROM_RESETTING);
    
    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte(new_settings, CONFIG_REGISTER);
    
    msg = ' ';
    comm_rec = 0;
}

void doVisualizing(){
    
    doStopping(EXT_EEPROM_NO_RESETTING);
    doReadEEPROM();
    doEEPROMReset();
    // Check if memory was Full
    if(full_eeprom) full_eeprom = !full_eeprom;
    
    msg = ' ';
    comm_rec = 0;
    
}

void doTemperature(){
    
    t_isr = 0;
    temperature32 = ADC_Temp_Read32();                      

    if (temperature32 > ADC_MAX) temperature32 = ADC_MAX;
    if (temperature32 < ADC_MIN) temperature32 = ADC_MIN;


    temperature[index_temp + 1] = (uint8_t)((temperature32 >> 8) & 0xFF); //msb
    temperature[index_temp]     = (uint8_t)(temperature32 & 0xFF); //lsb

    index_temp = index_temp + 2;
    fifo_level++;


}

void doWatermark(){
    
    index_temp = 0;
    doManageData();
    index_temp = 0;
    offset = 0;
    fifo_write = 1;
    wtm = WTM_LOW;

}

void doWriteEEPROM(){
    
    I2C_EXT_EEPROM_WriteWord(out);

    // outIndex = outIndex + EXT_EEPROM_WORD_SIZE - 2;

    
//    INT_EEPROM_WriteByte(((outIndex >> 8) & 0xFF),
//                        INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_H);
    
    uint8_t eeprom_index_arr[2] = {0,0};
    
    if (
    //    outIndex == EXT_EEPROM_OVERFLOW
        eeprom_index == 0xFFFC
    ) {
        I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                    0xFF,
                                    0xFE,
                                    2,
                                    eeprom_index_arr);
        full_eeprom = 1;
        
    }
    else {
        eeprom_index_arr[0] = eeprom_index & 0xff;
        eeprom_index_arr[1] = (eeprom_index >> 8) & 0xff; 
        I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                    0xFF,
                                    0xFE,
                                    2,
                                    eeprom_index_arr);
    }

    CyDelay(5);
    fifo_level = 0;
    fifo_write = 0;
    //temp = 1;

}

void doFullEEPROM(){

    doStopping(EXT_EEPROM_NO_RESETTING);
    CyDelay(5);
    LED_Start();
    LED_BlinkFast();
    full_eeprom = 0;
}

void doReadEEPROM(){

    uint8_t outEEPROM[EXT_EEPROM_WORD_SIZE];
    
    EXT_LED_Write(EXT_LED_ON);

    CyDelay(5);
    uint8_t header[] = {0xA0};
    uint8_t tail[] = {0xC0, 0xC0};

    uint16_t outIndex_read = 0;

    UART_PutArray(header, 1);
    for (uint16_t i = 0; i < pages; i++){

        I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                        (outIndex_read >> 8) & 0xFF,
                                        outIndex_read & 0xFF,
                                        128,
                                        outEEPROM);
        outIndex_read += EXT_EEPROM_WORD_SIZE;
        
        i == EXT_EEPROM_TOTAL_WORDS - 1 ? UART_PutArray(outEEPROM, EXT_EEPROM_WORD_SIZE - 4) 
                                        : UART_PutArray(outEEPROM, EXT_EEPROM_WORD_SIZE);
        
    }
    UART_PutArray(tail, 2);

    fifo_read = 0;
    eeprom_reset = 1;

    EXT_LED_Write(EXT_LED_OFF);

}

void doEEPROMReset(){

    // Starting BUILT-IN LED
    LED_Start();

    // Changing BUILT-IN LED pattern
    LED_BlinkEEPROM();
    I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS, pages);
    
    // Stopping BUILT-IN LED
    LED_Stop();
    
    // Resetting variables
    pages = 1;
    eeprom_index = 0;
//    outIndex = 0;
    uint8_t eeprom_index_resetting[2];
    eeprom_index_resetting[0] = 0;
    eeprom_index_resetting[1] = 0;
    
    CyDelay(5);
    I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                0xFF,
                                0xFE,
                                2,
                                eeprom_index_resetting);
    CyDelay(5);
    
    
//    INT_EEPROM_UpdateTemperature();
//    INT_EEPROM_WriteByte(outIndex, INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_L);
//    INT_EEPROM_UpdateTemperature();
//    INT_EEPROM_WriteByte(outIndex >> 8, INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_H);
    
}

void doButtonReleased(){

    if (counted_seconds <  TOGGLE_DEVICE 
        && counted_seconds > EMPTY_EEPROM)      doToggle();

    else if (counted_seconds < EMPTY_EEPROM)    doEEPROMReset();

    counted_seconds = 0;
    isButtonReleased = 0;
}


// Utils

void getParam(uint8_t settings, uint8_t* parameters){

    switch(settings & FSR){
        
        case LIS3DH_FS_02_CB:
            parameters[0] = FS_02_CB;
            break;
        case LIS3DH_FS_04_CB:
            parameters[0] = FS_04_CB;
            break;
        case LIS3DH_FS_08_CB:
            parameters[0] = FS_08_CB;
            break;
        case LIS3DH_FS_16_CB:
            parameters[0] = FS_16_CB;
            break;
        default:
            break;
    
    }

    switch((settings & ODR) >> ODR_LSB){
        
        case LIS3DH_ODR_01_CB:
            parameters[1] = ODR_01_CB;
            break;
        case LIS3DH_ODR_10_CB:
            parameters[1] = ODR_10_CB;
            break;
        case LIS3DH_ODR_25_CB:
            parameters[1] = ODR_25_CB;
            break;
        case LIS3DH_ODR_50_CB:
            parameters[1] = ODR_50_CB;
            break;
        default:
            break;
            
    }

    parameters[2] = (settings & TEMP_FORMAT) >> TEMP_FORMAT_LSB;

    parameters[3] = (settings & ESAV_STATUS) >> ESAV_STATUS_LSB;
}

void restart(){
    
    T_TIMER_CLOCK_Start();
    T_TIMER_Start();
    
    uint8_t new_settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
    

    LED_Start();
    I2C_LIS3DH_Start(new_settings);
    LED_BlinkSlow();
    ISR_T_StartEx(TEMP_ISR);
    ISR_ACC_StartEx(WTM_ISR);
  
    t_isr = 0;                  // abilita isr timer
    fifo_level = 0;             //
    index_temp = 0;
    uint8_t eeprom_index_arr[2];
    I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                0xFF,
                                0xFE,
                                2,
                                eeprom_index_arr);
    CyDelay(5);
    
//    I2C_EXT_EEPROM_ReadRegister(EXT_EEPROM_DEVICE_ADDRESS,
//                            0xFF,
//                            0xFE,
//                            eeprom_index_arr);
//    CyDelay(5);
//    I2C_EXT_EEPROM_ReadRegister(EXT_EEPROM_DEVICE_ADDRESS,
//                            0xFF,
//                            0xFF,
//                            eeprom_index_arr + 1);

    eeprom_index = (uint16_t)((eeprom_index_arr[1] << 8) | eeprom_index_arr[0]);
//    outIndex = INT_EEPROM_ReadByte(INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_L) 
//                | (INT_EEPROM_ReadByte(INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_H) << 8);       //usato in writeeeprom per tenere indirizzo attuale
    eeprom_reset = 0;           // per resettare la eeprom
    full_eeprom = 0;
    temp = 1;
    fifo_write = 0;
    fifo_read = 0;
    boot = 1;
    wtm = WTM_LOW;
    trigger = 0;

}

void doManageData(){

    uint32_t concatenated_Data;
    uint16_t raw_data_16bit[3];

    for (uint8_t level = 0; level <= LEVEL_TO_READ + 1; level++){

        // Receiving raw data
    	I2C_LIS3DH_Get_Raw_Data(raw_data_16bit);
    	concatenated_Data = 0;
        
        // Packing data into a 32 bit unsigned int
    	uint8_t count = LIS3DH_OUT_AXES - 1;
        for(uint8_t i = 0; i < LIS3DH_OUT_AXES; i++){
            
    	    concatenated_Data |= (uint32_t)((raw_data_16bit[i] & 0x3FF) << 10*count);
    	    count--;
    	
        }

    	// Populating the buffer with acceleration values.
    	for(uint8_t i = 0; i < LIS3DH_RESOLUTION; i++)     
    	    out[i + offset] = (uint8_t)((concatenated_Data >> 8*i) & 0xFF);

        // Populating the buffer with temperature values
        out[4 + offset] = temperature[index_temp];
        out[5 + offset] = temperature[index_temp + 1];

        index_temp = index_temp + 2;
    	offset = offset + 6;
        
        //if (level == LEVEL_TO_READ){
        //    out[4 + offset] = temperature[index_temp];
        //    out[5 + offset] = temperature[index_temp + 1];
        //}
    }
    
}

uint16_t retrieve_pages(uint16_t eeprom_index){
    uint16_t pages;
    pages = (uint16_t)((eeprom_index/EXT_EEPROM_WORD_SIZE)+1);
    return pages;
}

