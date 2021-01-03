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

    if((settings & ESAV_STATUS) >> 5)
    {
        temp = 1;
        LED_Start();
        I2C_LIS3DH_Start(settings);
        ISR_T_StartEx(TEMP_ISR);
        ISR_ACC_StartEx(WTM_ISR);
    }
    else
    {
        temp = 0;
        ISR_ACC_Stop();
        LED_Stop();
    }

    TIMER_RESET_Start();

    ISR_TIMER_RESET_StartEx(COUNT_SEC);

    ISR_RX_StartEx(COMM_GUI);


    // Setup variables
    fifo_level = 0;     //
    outIndex = INT_EEPROM_ReadByte(INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_L) 
                | (INT_EEPROM_ReadByte(INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_H) << 8);       //usato in writeeeprom per tenere indirizzo attuale
    eeprom_index = 0;   // primo indirizzo eeprom disponibile
    eeprom_reset = 0;   // per resettare la eeprom
    pages = 1;          // da 0x00 a 0x80 è già una pagina scritta
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
    trigger = 1;
    
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
        if(onSaving())          doSaving(EXT_EEPROM_NO_RESETTING);
        
        // 3. Handshake character received
        if(onHandshake())       doHandshake();
        
        // 4. Configuration and Config Buffer characters received
        if(onChangeConfig())    doChangeConfig();
        
        // 5. Visualizing character received
        if(onVisualizing())     doVisualizing();
        
        // Reading the Temperature
        if (onTemperature())    doTemperature();
        
        // Reading the FIFO
        if (onWatermark())      doWatermark();
        
        // Writing the EEPROM
        if (onWriteEEPROM())    doWriteEEPROM();
        
        // Handling BUILT-IN LED blinking
        onFullEEPROM() ? LED_BlinkFast() : LED_BlinkSlow();

        // Handling Button releasing
        if (onButtonReleased()) doButtonReleased();
            
    }
    
}

// Conditions

_Bool onByteReceived(){
    
    return comm_rec;

}

_Bool onStopping(){

    return onByteReceived() && msg == 's';

}

_Bool onSaving(){

    return onByteReceived() && msg == 'b' && !full_eeprom;

}

_Bool onHandshake(){
    
    return onByteReceived() && msg == 'h';
    
}

_Bool onChangeConfig(){
    
    return onByteReceived() && msg == 'c';

}

_Bool onVisualizing(){
    
    return onByteReceived() && msg == 'v';

}

_Bool onTemperature(){
    
    return t_isr        // quando
    && temp             // enable
    // && !wtm 
    && !fifo_write 
    && !fifo_read;

}

_Bool onWatermark(){
    
    return wtm 
            && !fifo_write && !fifo_read;

}

_Bool onWriteEEPROM(){
    
    return !wtm && fifo_write && !full_eeprom;

}

_Bool onFullEEPROM(){
    
    return full_eeprom && !fifo_write;

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
    temp = 0;
    // Reading configuration byte
    settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
    // Saving bit toggle
    settings &= (0x1F);
    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte(settings, CONFIG_REGISTER);
    // Disabling acceleration reading ISR.
    ISR_ACC_Stop();
    wtm = WTM_LOW;
    LED_Stop();
    // Discarding old data
    if(resetting) I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS, pages);
    msg = ' ';
    comm_rec = 0;
}

void doSaving(uint8_t resetting){

    // Reading configuration byte
    settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
    // Saving bit toggle
    settings  |= (0x20);
    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte(settings, CONFIG_REGISTER);
    restart();
    // Discarding old data
    if(resetting) I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS, pages);
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

    msg=' ';
    comm_rec = 0;

}

void doChangeConfig(){

    // Waiting the Configuration Byte.
    comm_rec = 0;
    while(comm_rec == 0);

    // Reading settings
    settings = UART_ReadRxData();
    
    // Updating FSR Register
    switch(settings & FSR)
    {
        case LIS3DH_FS_02_CB:
            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                 LIS3DH_CTRL_REG4,
                 LIS3DH_SETUP_02_CTRL_REG4);
            break;
        case LIS3DH_FS_04_CB:
            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                 LIS3DH_CTRL_REG4,
                 LIS3DH_SETUP_04_CTRL_REG4);
            break;
        case LIS3DH_FS_08_CB:
            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                 LIS3DH_CTRL_REG4,
                 LIS3DH_SETUP_08_CTRL_REG4);
            break;
        case LIS3DH_FS_16_CB:
            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                 LIS3DH_CTRL_REG4,
                 LIS3DH_SETUP_16_CTRL_REG4);
            break;
        default:
            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                 LIS3DH_CTRL_REG4,
                 LIS3DH_SETUP_02_CTRL_REG4);
            break;
    }

    // Updating ODR Register
    switch((settings & ODR) >> 2)
    {
        case LIS3DH_ODR_01_CB:
            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                 LIS3DH_CTRL_REG1,
                 LIS3DH_SETUP_01_CTRL_REG1);
            break;
        case LIS3DH_ODR_10_CB:
            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                 LIS3DH_CTRL_REG1,
                 LIS3DH_SETUP_10_CTRL_REG1);
            break;
        case LIS3DH_ODR_25_CB:
            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                 LIS3DH_CTRL_REG1,
                 LIS3DH_SETUP_25_CTRL_REG1);
            break;
        case LIS3DH_ODR_50_CB:
            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                 LIS3DH_CTRL_REG1,
                 LIS3DH_SETUP_50_CTRL_REG1);
            break;
        default:
            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                 LIS3DH_CTRL_REG1,
                 LIS3DH_SETUP_01_CTRL_REG1);
            break;
    }
    
    // Updating Saving Status Bit
    (settings & ESAV_STATUS) >> 5 ? doSaving(EXT_EEPROM_RESETTING) : doStopping(EXT_EEPROM_RESETTING);
    msg=' ';
    comm_rec = 0;
}

void doVisualizing(){
    
    doStopping(EXT_EEPROM_NO_RESETTING);
    doReadEEPROM();
    doEEPROMReset();
    // Check if memory is Full
    if(full_eeprom) full_eeprom = 0;
    msg=' ';
    comm_rec = 0;
    
}

void doTemperature(){
    
    temperature32 = ADC_Temp_Read32();                      

    if (temperature32 > ADC_MAX) temperature32 = ADC_MAX;
    if (temperature32 < ADC_MIN) temperature32 = ADC_MIN;


    temperature[index_temp + 1] = (uint8_t)((temperature32 >> 8) & 0xFF); //msb
    temperature[index_temp]     = (uint8_t)(temperature32 & 0xFF); //lsb

    index_temp = index_temp + 2;
    fifo_level ++;
    t_isr = 0;

}

void doWatermark(){
    
    index_temp = 0;
    doManageData();
    index_temp = 0;
    offset = 0;
    fifo_write = 1;
    wtm = 0;

}

void doWriteEEPROM(){
    
    I2C_EXT_EEPROM_WriteWord(out);

    outIndex = outIndex + EXT_EEPROM_WORD_SIZE - 2;

    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte((outIndex & 0xFF),
                        INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_L);
    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte(((outIndex >> 8) & 0xFF),
                        INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_H);
    
    if (outIndex == 110) full_eeprom = 1;

    fifo_level = 0;
    temp = 1;
    fifo_write = 0;

}

void doFullEEPROM(){

    doStopping(EXT_EEPROM_NO_RESETTING);
    LED_Start();
    LED_BlinkFast();

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
        outIndex_read = outIndex_read + 128;
        UART_PutArray(outEEPROM, 128);
        
    }
    UART_PutArray(tail, 2);

    fifo_read = 0;
    eeprom_reset = 1;

    EXT_LED_Write(EXT_LED_OFF);

}

void doEEPROMReset(){

    I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS, pages);
    pages = 1;
    eeprom_index = 0;
    outIndex = 0;
    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte(outIndex, INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_L);
    INT_EEPROM_UpdateTemperature();
    INT_EEPROM_WriteByte(outIndex >> 8, INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_H);
    
}

void doButtonReleased(){

    if(counted_seconds <  TOGGLE_DEVICE && counted_seconds > EMPTY_EEPROM){
        // B o S
        // lettura della configurazione attuale
        settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
        // Se siamo in saving
        if (settings & 0x20){
            temp = 0;
            settings &= (0x1F);
            INT_EEPROM_UpdateTemperature();
            INT_EEPROM_WriteByte(settings, CONFIG_REGISTER);
            ISR_ACC_Stop();
            wtm = WTM_LOW;
            LED_Stop();
        }
        else{
            settings |= (0x20);
            INT_EEPROM_UpdateTemperature();
            INT_EEPROM_WriteByte(settings, CONFIG_REGISTER);
            restart();
        }
    }
    else if(counted_seconds < EMPTY_EEPROM){
        // reset eeprom
        I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS, pages);
        eeprom_index = 0;
        outIndex = 0;
        INT_EEPROM_UpdateTemperature();
        INT_EEPROM_WriteByte(outIndex, INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_L);
        INT_EEPROM_UpdateTemperature();
        INT_EEPROM_WriteByte(outIndex >> 8, INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_H);
        pages = 1;
    }

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
    

    LED_Start();
    I2C_LIS3DH_Start(settings);
    ISR_T_StartEx(TEMP_ISR);
    ISR_ACC_StartEx(WTM_ISR);
  
    t_isr = 0;                  // abilita isr timer
    fifo_level = 0;             //
    index_temp = 0;
    outIndex = INT_EEPROM_ReadByte(INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_L) 
                | (INT_EEPROM_ReadByte(INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_H) << 8);       //usato in writeeeprom per tenere indirizzo attuale
    eeprom_reset = 0;           // per resettare la eeprom
    full_eeprom = 0;
    temp = 1;
    fifo_write = 0;
    fifo_read = 0;
    boot = 1;
    wtm = WTM_LOW;
    trigger = 1;

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
    	for(uint8_t i = 0; i < LIS3DH_RESOLUTION; i++){
            
    	    out[i + offset] = (uint8_t)((concatenated_Data >> 8*i) & 0xFF);
    	
        }

        // Populating the buffer with temperature values
        out[4 + offset] = temperature[index_temp];
        out[5 + offset] = temperature[index_temp + 1];

        index_temp = index_temp + 2;
    	offset = offset + 6;

    }
    
}
