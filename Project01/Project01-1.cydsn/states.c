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
 * Returns:     Page index
 * Description: 
 *     Calculates page in which to start to write data
\*****************************************************************************/

uint16_t retrieve_pages(uint16_t eeprom_index);

// ================================= END UTILS =================================


// Initialization

void init()
{
    CyGlobalIntEnable;
    for (uint8_t i = 0; i < ((LEVEL_TO_READ + 1) * 5); i ++) temperature[i] = 0;
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
                                    EXT_EEPROM_INTEGRITY_MSB,
                                    EXT_EEPROM_INTEGRITY_LSB,
                                    2,
                                    in);
    CyDelay(5);
    
    if(!(in[0] == EXT_EEPROM_INTEGRITY_CHAR_1 && in[1] == EXT_EEPROM_INTEGRITY_CHAR_2))         // Check if EXT_EEPROM has been already used by this program
        doEEPROMReset();

    if(settings & ESAV_STATUS){                 // If status bit ON, start device
        
        temp = HIGH;
        LED_Start();
        I2C_LIS3DH_Start(settings);
        ISR_T_StartEx(TEMP_ISR);
        ISR_ACC_StartEx(WTM_ISR);
        
    }
    else{
        
        temp = LOW;
        ISR_ACC_Stop();
        LED_Stop();
        
    }

    TIMER_RESET_Start();

    ISR_TIMER_RESET_StartEx(COUNT_SEC);

    ISR_RX_StartEx(COMM_GUI);


    // Setup variables
    uint8_t eeprom_index_arr[2];
    
    I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,         // Retrieve first empty available EXT_EEPROM address 
                                EXT_EEPROM_FIRST_AV_ADDRESS_MSB,
                                EXT_EEPROM_FIRST_AV_ADDRESS_LSB,
                                2,
                                eeprom_index_arr);
    
    eeprom_index = (uint16_t)(eeprom_index_arr[1] << 8) | eeprom_index_arr[0];        
    pages = retrieve_pages(eeprom_index);
    offset = 0;
    index_temp = 0;
    counted_seconds = 0;
    
    eeprom_reset = LOW;                                                                               
    full_eeprom = LOW;
    comm_rec = LOW;
    fifo_write = LOW;
    fifo_read = LOW;    
    isButtonReleased = LOW;    
    wtm = LOW;
    t_isr = LOW;
       
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
    
}

void doStopping(uint8_t resetting){
    
    // Disabling temperature data saving.
    temp = LOW;
    // BETA VERSION
//    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
//                                 LIS3DH_CTRL_REG5,
//                                 LIS3DH_FIFO_DIS_CTRL_REG5);       // FIFO disable
    // Reading configuration byte
    settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
    // Saving toggled bit
    settings &= ~(1 << ESAV_STATUS_LSB);
    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte(settings, CONFIG_REGISTER);
    // Disabling acceleration reading ISR.
    ISR_ACC_Stop();
    wtm = LOW;
    LED_Stop();
    // Discarding old data
    if(resetting) doEEPROMReset();
    
    msg = ' ';
    comm_rec = LOW;
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
    
    msg = ' ';
    comm_rec = LOW;
}

void doToggle(){
    
    // Reading configuration byte
    uint8_t new_settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
    
    // Saving toggled bit
    new_settings ^= (1 << ESAV_STATUS_LSB);
    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte(new_settings, CONFIG_REGISTER);
    
    // Checking if saving or stopping
    (new_settings & ESAV_STATUS) >> ESAV_STATUS_LSB ? doSaving(EXT_EEPROM_NO_RESETTING) : doStopping(EXT_EEPROM_NO_RESETTING);
    
    msg = ' ';
    comm_rec = LOW;
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
    comm_rec = LOW;

}

void doChangeConfig(){
    
    uint8_t new_settings;
    // Waiting the Configuration Byte.
    comm_rec = LOW;
    while(!comm_rec);

    // Reading settings
    new_settings = UART_ReadRxData();

    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte(new_settings, CONFIG_REGISTER);
    
    // Updating Saving Status Bit
    (new_settings & ESAV_STATUS) >> ESAV_STATUS_LSB ? doSaving(EXT_EEPROM_RESETTING) : doStopping(EXT_EEPROM_RESETTING);
    
    msg = ' ';
    comm_rec = LOW;
}

void doVisualizing(){
    
    doStopping(EXT_EEPROM_NO_RESETTING);
    // BETA VERSION
//  doRetrieveIncompleteFIFO();
    doReadEEPROM();
    doEEPROMReset();
    
    msg = ' ';
    comm_rec = LOW;

    
}

void doTemperature(){
    
    t_isr = LOW;
    //trigger = LOW;
    
    // Sample temperature
    temperature32 = ADC_Temp_Read32();                                          
    
    // Over-Underflow check
    if (temperature32 > ADC_MAX) temperature32 = ADC_MAX;                       
    if (temperature32 < ADC_MIN) temperature32 = ADC_MIN;

    temperature[index_temp]     = (uint8_t)(temperature32 & 0xFF); 
    temperature[index_temp + 1] = (uint8_t)((temperature32 >> 8) & 0xFF);       
                 
    index_temp = index_temp + 2;
    
    
}

void doWatermark(){
    
    index_temp = 0;
    doManageData();
    index_temp = 0;         // Resetted again because in doManageData() it gets incremented
    offset = 0;
    fifo_write = HIGH;
    wtm = LOW;

}

void doWriteEEPROM(){
    
    I2C_EXT_EEPROM_WriteWord(out);
    
    uint8_t eeprom_index_arr[2] = {0,0};
    
    // Check if EXT_EEPROM is full, if so reset first available address in EXT_EEPROM and sets dedicated flag
    // otherwise update eeprom_index value in EXT_EEPROM
    if ( eeprom_index == EXT_EEPROM_LAST_ADDRESS_USABLE){
        
        I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                    EXT_EEPROM_FIRST_AV_ADDRESS_MSB,
                                    EXT_EEPROM_FIRST_AV_ADDRESS_LSB,
                                    2,
                                    eeprom_index_arr);
        full_eeprom = HIGH;
        
    }
    else {
        eeprom_index_arr[0] = eeprom_index & 0xff;
        eeprom_index_arr[1] = (eeprom_index >> 8) & 0xff; 
        I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                    EXT_EEPROM_FIRST_AV_ADDRESS_MSB,
                                    EXT_EEPROM_FIRST_AV_ADDRESS_LSB,
                                    2,
                                    eeprom_index_arr);
    }

    CyDelay(5);
    fifo_write = LOW;
    // BETA VERSION
//    for(uint8_t i = 0; i<126; i++) out[i] = 0;
//    for(uint8_t i = 0; i<(LEVEL_TO_READ + 1) * 3; i++) temperature[i] = 0;

}

void doFullEEPROM(){

    doStopping(EXT_EEPROM_NO_RESETTING);
    CyDelay(5);
    LED_Start();
    LED_BlinkFast();
    full_eeprom = LOW;
    
}

void doReadEEPROM(){

    // External LED notifies the user communication with GUI has started
    EXT_LED_Write(EXT_LED_ON);
    
    // Building array to send
    uint8_t header[] = {0xA0};
    uint8_t outEEPROM[EXT_EEPROM_WORD_SIZE];                
    uint8_t tail[] = {0xC0, 0xC0};

    uint16_t outIndex_read = 0;
    
    // Send header
    UART_PutArray(header, 1);
    
    // Send data
    for (uint16_t i = 0; i < pages; i++){

        I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                        (outIndex_read >> 8) & 0xFF,
                                        outIndex_read & 0xFF,
                                        128,
                                        outEEPROM);
        outIndex_read += EXT_EEPROM_WORD_SIZE;
        
        // If last page has data, send everything but integrity bytes and EXT_EEPROM index
        i == EXT_EEPROM_TOTAL_WORDS - 1 ? UART_PutArray(outEEPROM, EXT_EEPROM_WORD_SIZE - 4)    
                                        : UART_PutArray(outEEPROM, EXT_EEPROM_WORD_SIZE);
        
    }
    
    // Send tail
    UART_PutArray(tail, 2);

    fifo_read = LOW;
    eeprom_reset = HIGH;

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
    
    // Resetting EXT_EEPROM index
    uint8_t eeprom_index_resetting[2];
    eeprom_index_resetting[0] = 0;
    eeprom_index_resetting[1] = 0;
    
    CyDelay(5);
    I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                EXT_EEPROM_FIRST_AV_ADDRESS_MSB,
                                EXT_EEPROM_FIRST_AV_ADDRESS_LSB,
                                2,
                                eeprom_index_resetting);
    CyDelay(5);
    
}

void doButtonReleased(){

    if (counted_seconds <  TOGGLE_DEVICE && counted_seconds > EMPTY_EEPROM)      
        doToggle();

    else if (counted_seconds < EMPTY_EEPROM){
        
        uint8_t new_settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
        (new_settings & ESAV_STATUS) >> ESAV_STATUS_LSB ? doSaving(EXT_EEPROM_RESETTING) : doStopping(EXT_EEPROM_RESETTING);
        
    }
    
    counted_seconds = 0;
    isButtonReleased = LOW;
    
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
      
    uint8_t eeprom_index_arr[2];
    I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                0xFF,
                                0xFE,
                                2,
                                eeprom_index_arr);
    CyDelay(5);
    
    eeprom_index = (uint16_t)((eeprom_index_arr[1] << 8) | eeprom_index_arr[0]);
    
    uint8_t new_settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
    
    LED_Start();
    I2C_LIS3DH_Start(new_settings);
    LED_BlinkSlow();
    ISR_T_StartEx(TEMP_ISR);
    ISR_ACC_StartEx(WTM_ISR);
    index_temp = 0;
    
    t_isr = LOW;  
    eeprom_reset = LOW;           
    full_eeprom = LOW;
    temp = HIGH;
    fifo_write = LOW;
    fifo_read = LOW;
    wtm = LOW;

}

void doManageData(){

    uint32_t concatenated_Data;
    uint16_t raw_data_16bit[3];

    for (uint8_t level = 0; level < LEVEL_TO_READ + 1; level++){

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
        
    }
    
}

uint16_t retrieve_pages(uint16_t eeprom_index){
    
    uint16_t pages;
    pages = (uint16_t)((eeprom_index/EXT_EEPROM_WORD_SIZE)+1);
    return pages;
    
}


/*
=========================================== BETA FUNTION ===========================================
*/
void doRetrieveIncompleteFIFO(){

 

    uint32_t concatenated_Data;
    uint16_t raw_data_16bit[3];
    uint8_t last_level;
    I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, 0x2f, &last_level);
    last_level = (last_level & 0x1F);
    index_temp = 0;
    
    if (last_level && !full_eeprom ){

 

        for (uint8_t level = 0; level < last_level; level++){

 

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
        
        }
        
        index_temp = 0;
        offset = 0;
        
        CyDelay(5);
        doWriteEEPROM();
        
        for(uint8_t i = 0; i<126; i++) out[i] = 0;
        for(uint8_t i = 0; i<(LEVEL_TO_READ + 1) * 3; i++) temperature[i] = 0;
    
    }
    
}
 
