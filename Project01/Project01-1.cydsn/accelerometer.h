/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#ifndef ACCELEROMETER_H

    #define ACCELEROMETER_H

    #include "I2c.h"
    #include "define.h"
    #include "interrupt.h"

    // The union is the trick to decompose a float into its constituting bytes.
    // It behaves like a "binary translator" for floats.
    // By storing in its float32 argument the data and then masking its uint32_t
    // argument it's possible to send floating point data as bytes.
    // This normally isn't possible when handling floating point data.

    typedef union
    {
        float32 data;
        uint32_t mask;
    } outtype;

    // Array collecting the float to send
    outtype outarray[LIS3DH_OUT_AXES];
    
    
/*****************************************************************************\
 * Function:    I2C_LIS3DH_Start
 * Input:       
 * Returns:     ErrorCode
 * Description: 
 *     Initialization of the LIS3DH Config Registers. 
 *     It gathers ODR from EEPROM.
\*****************************************************************************/
   
    ErrorCode I2C_LIS3DH_Start();
    
/*****************************************************************************\
 * Function:    I2C_LIS3DH_Manage_Data
 * Input:       outtype* array
 * Returns:     ErrorCode
 * Description: 
 *     Gathers LIS3DH data and sends them through UART
\*****************************************************************************/
    
    ErrorCode I2C_LIS3DH_Manage_Data(int16_t* array);
    
#endif
