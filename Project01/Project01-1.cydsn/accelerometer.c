/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#include "accelerometer.h"

void I2C_LIS3DH_SetConfig(uint8 settings, uint8* config)
{
    switch(settings & FSR)
    {
        case _2g:
            config[0]=LIS3DH_SETUP_02_CTRL_REG4;           
            break;
        case _4g:
            config[0]=LIS3DH_SETUP_04_CTRL_REG4; 
            break; 
        case _8g:
            config[0]=LIS3DH_SETUP_08_CTRL_REG4; 
            break;
        case _16g:
            config[0]=LIS3DH_SETUP_16_CTRL_REG4; 
            break;
        default:
            config[0]=LIS3DH_SETUP_02_CTRL_REG4;  
            break; 
    }
    
    switch((settings&ODR)>>2)
    {
        case _1Hz:
            config[1]=LIS3DH_SETUP_01_CTRL_REG1;
            break;
        case _10Hz:
            config[1]=LIS3DH_SETUP_10_CTRL_REG1;
            break; 
        case _25Hz:
            config[1]=LIS3DH_SETUP_25_CTRL_REG1;
            break;
        case _50Hz:
            config[1]=LIS3DH_SETUP_50_CTRL_REG1;
            break;
        default:
            config[1]=LIS3DH_SETUP_01_CTRL_REG1;
            break;
    }
    
}



ErrorCode I2C_LIS3DH_Start(uint8 setting)
{
    // Reading EEPROM register dedicated to startup ODR.
    // Checking if the memorized value is in allowed range.
    // if the value is out of range --> ODR is set to the default initial value.
    
//    if(EEPROM_ReadByte(EEPROM_REGISTER) < EEPROM_INIT_VALUE 
//    || EEPROM_ReadByte(EEPROM_REGISTER) > EEPROM_FINAL_VALUE)
//    {
//        // Updating temperature before writing the initial value.
//		EEPROM_UpdateTemperature();
//		// Initialization of the EEPROM register
//        EEPROM_WriteByte(EEPROM_INIT_VALUE, EEPROM_REGISTER);
//    }
    uint8 config[2];
    I2C_LIS3DH_SetConfig(setting, config);
    // Setup control register 1
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 config[1]);    // ODR
    // Setup control register 3
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG3,
                                 LIS3DH_SETUP_CTRL_REG3);       // Interrupt on watermark
    // Setup control register 4
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG4,
                                 config[0]);     // FS
    // Setup control register 5
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG5,
                                 LIS3DH_SETUP_CTRL_REG5);       // FIFO enable
    // Setup FIFO control register (bypass to reset)
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_FIFO_CTRL_REG,
                                 LIS3DH_RESET_FIFO_CTRL_REG);   // Software reset of accelerometer mode.
    // Setup FIFO control register
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_FIFO_CTRL_REG,
                                 LIS3DH_SETUP_FIFO_CTRL_REG );  // select Stream mode and set WTM to 31 level

//    I2C_Peripheral_WriteRegister(0x18, 0x2E,0x00);//FIFO
//    I2C_Peripheral_WriteRegister(0x18, 0x20,0x47);//1
//    I2C_Peripheral_WriteRegister(0x18, 0x22,0x04);//3
//    I2C_Peripheral_WriteRegister(0x18, 0x23,0x00);//4
//    I2C_Peripheral_WriteRegister(0x18, 0x24,0x40);//5
//    I2C_Peripheral_WriteRegister(0x18, 0x2E,0x9E);//FIFO


    
    
    // init CTRL_REG1
//    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
//                                LIS3DH_CTRL_REG1,
//                                // writing the 4 MSb of the register 1 (related to ODR)
//                                (EEPROM_ReadByte(EEPROM_REGISTER) << 4 | LIS3DH_NORMAL_CTRL_REG1));
//    
    // init CTRL_REG4
//    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
//                                LIS3DH_CTRL_REG4,
//                                LIS3DH_NORMAL_CTRL_REG4_0);
//    
    return NO_ERROR;
}

ErrorCode I2C_LIS3DH_Manage_Data(int16 * array, uint8 sensitivity)
{
    // Initializing the data buffer
    uint8_t out[BYTE_TO_EEPROM];
    
    uint32_t concatenated_Data = 0;
    
    // Array dedicated to save accelerometer data in digit.
    int16 converted_acc[3];
    
    // Data acquisition
    //I2C_LIS3DH_Get_Raw_Data(sensorData);
    
    // Data conversion
    for(uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)  
	    converted_acc[i] = (int16_t)(array[i] * sensitivity * CONVERSION); //make conversion using array raw values
    
    // Counters
    uint8_t arrayIndex=0,    	// arrayIndex is used to browse the array cells. 
			shiftIndex=0;   	// shiftIndex is used in order to perform the right shift operation on the data.
        
    
    concatenated_Data = converted_acc[A_Z] | converted_acc[A_Y] << 10 | converted_acc[A_X] << 20;
    
    out[0] = concatenated_Data & 0xFF;
    out[1] = (concatenated_Data >> 8) & 0xFF;
    out[2] = (concatenated_Data >> 16) & 0xFF;
    out[3] = (concatenated_Data >> 24) & 0xFF;
    
    return NO_ERROR;
}

ErrorCode I2C_LIS3DH_Get_Raw_Data(uint16_t* data)
{
    uint8_t sensorData[LIS3DH_OUT_N]; // This array is storing left-aligned bytes coming from accelerometer.
    
    //Storing data in temporary array.
    I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                    0x28,
                                    6,
                                    sensorData);
    
    
    // Re-arranging data to have them right-aligned as integers.
    for(int i = 0; i < LIS3DH_OUT_AXES; i++) data[i] = (uint16_t)((sensorData[2*i+1] << 8 | sensorData[2*i])) >> LIS3DH_RIGHT_SHIFT;   
    
    return NO_ERROR;
}