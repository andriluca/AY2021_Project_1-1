/* =========================================================================
 * Project01-1, Luca Andriotto, Matteo Cavicchioli, Alessandro Pirelli
 * =========================================================================
*/

#ifndef ACCELEROMETER_H

    #define ACCELEROMETER_H

    #include "I2c.h"
    #include "define.h"
    #include "interrupt.h"


/*****************************************************************************\
 * Function:    I2C_LIS3DH_Start
 * Input:
 * Returns:     ErrorCode
 * Description:
 *     Initialization of the LIS3DH Config Registers.
 *     It gathers ODR from EEPROM.
\*****************************************************************************/

    ErrorCode I2C_LIS3DH_Start(uint8 settings);

/*****************************************************************************\
 * Function:    I2C_LIS3DH_Get_Raw_Data
 * Input:       int16_t data
 * Returns:     ErrorCode
 * Description:
 *     Populates an int16_t array with right-aligned sensor data
\*****************************************************************************/

    ErrorCode I2C_LIS3DH_Get_Raw_Data(uint16_t* data);

    uint16_t I2C_LIS3DH_SetConfig(uint8 settings, uint8* config);

    uint8_t out[(LEVEL_TO_READ + 1) * 6];


#endif
