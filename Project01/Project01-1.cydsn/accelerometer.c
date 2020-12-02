/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#include "accelerometer.h"

/*****************************************************************************\
 * Function:    I2C_LIS3DH_Get_Raw_Data
 * Input:       int16_t data
 * Returns:     ErrorCode
 * Description: 
 *     Populates an int16_t array with right-aligned sensor data
\*****************************************************************************/


ErrorCode I2C_LIS3DH_Get_Raw_Data(int16_t* data);

ErrorCode I2C_LIS3DH_Start()
{
    // Reading EEPROM register dedicated to startup ODR.
    // Checking if the memorized value is in allowed range.
    // if the value is out of range --> ODR is set to the default initial value.
    
    if(EEPROM_ReadByte(EEPROM_REGISTER) < EEPROM_INIT_VALUE 
    || EEPROM_ReadByte(EEPROM_REGISTER) > EEPROM_FINAL_VALUE)
    {
        // Updating temperature before writing the initial value.
		EEPROM_UpdateTemperature();
		// Initialization of the EEPROM register
        EEPROM_WriteByte(EEPROM_INIT_VALUE, EEPROM_REGISTER);
    }
    
    // init CTRL_REG1
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                LIS3DH_CTRL_REG1,
                                // writing the 4 MSb of the register 1 (related to ODR)
                                (EEPROM_ReadByte(EEPROM_REGISTER) << 4 | LIS3DH_NORMAL_CTRL_REG1));
    
    // init CTRL_REG4
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                LIS3DH_CTRL_REG4,
                                LIS3DH_NORMAL_CTRL_REG4_0);
    
    return NO_ERROR;
}

ErrorCode I2C_LIS3DH_Manage_Data(int16_t* array)
{
    // Initializing the data buffer
    uint8_t out[BYTE_TO_TRANSFER];
    out[0] = 0xA0;                      // --> HEADER
    out[BYTE_TO_TRANSFER - 1] = 0xC0;   // --> TAIL
    
    // Array dedicated to save accelerometer data in digit.
    int16_t sensorData[3];
    
    // Data acquisition
    I2C_LIS3DH_Get_Raw_Data(sensorData);
    
    // Data conversion
    for(uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)  
	    array[i] = (int16_t)(sensorData[i] * sensitivity * CONVERSION); // populating the array's float data.
    
    // Counters
    uint8_t arrayIndex=0,    	// arrayIndex is used to browse the array cells. 
			shiftIndex=0;   	// shiftIndex is used in order to perform the right shift operation on the data.
        
    uint32_t reconstructedData = 0;
    
    for(uint8_t count = 1; count < BYTE_TO_TRANSFER - 1; count++){
        reconstructedData = array[arrayIndex+2] | array[arrayIndex + 1] << 10 | array[arrayIndex] << 20;
    }
    
    for(uint8_t count = 1; count < BYTE_TO_TRANSFER - 1; count++) 
    {
        
        out[count] = array[arrayIndex] >> 8 * shiftIndex & 0xff;        // populating the buffer with binary translated float properly masked.
        shiftIndex = (shiftIndex+1) % BYTES_PER_AXIS;                 	// updating the shift index.
        if(!(count % BYTES_PER_AXIS)) arrayIndex++;                 	// updating the array index, once all the data related to one axis are gathered.
    }
    
    // Sending data buffer
    UART_PutArray(out, BYTE_TO_TRANSFER);
    
    return NO_ERROR;
}

ErrorCode I2C_LIS3DH_Get_Raw_Data(int16_t* data)
{
    uint8_t sensorData[LIS3DH_OUT_N]; // This array is storing left-aligned bytes coming from accelerometer.
    
    // Storing data in temporary array.
    I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                    LIS3DH_OUT_X_L,
                                    LIS3DH_OUT_N,
                                    sensorData);
    
    // Re-arranging data to have them right-aligned as integers.
    for(int i = 0; i < LIS3DH_OUT_AXES; i++) data[i] = (int16_t)((sensorData[2*i+1] << 8 | sensorData[2*i])) >> LIS3DH_RIGHT_SHIFT;   
    
    return NO_ERROR;
}