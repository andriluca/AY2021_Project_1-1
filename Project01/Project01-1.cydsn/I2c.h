/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#ifndef __I2C_H
    #define __I2C_H
    #include "project.h"
    #include "cytypes.h"

    // This enum is encoding the error condition

    typedef enum
    {
        NO_ERROR,
        ERROR
    }ErrorCode;



/*****************************************************************************\
 * Function:    I2C_Peripheral_Start
 * Input:
 * Returns:     ErrorCode
 * Description:
 *     Initialization of the I2C master communication.
\*****************************************************************************/

    ErrorCode I2C_Peripheral_Start();

/*****************************************************************************\
 * Function:    I2C_Peripheral_Stop
 * Input:
 * Returns:     ErrorCode
 * Description:
 *     End of the I2C master communication.
\*****************************************************************************/

    ErrorCode I2C_Peripheral_Stop();

/*****************************************************************************\
 * Function:    I2C_Peripheral_ReadRegister
 * Input:       uint8_t device_address, uint8_t register_address,
 *              uint8_t* data
 * Returns:     ErrorCode
 * Description:
 *     Reading through I2C of a single register.
\*****************************************************************************/


    ErrorCode I2C_Peripheral_ReadRegister(uint8_t device_address,
                                            uint8_t register_address,
                                            uint8_t* data);

/*****************************************************************************\
 * Function:    I2C_Peripheral_ReadRegisterMulti
 * Input:       uint8_t device_address, uint8_t register_address
 *              uint8_t register_count, uint8_t* data
 * Returns:     ErrorCode
 * Description:
 *     Multiple reading through I2C of contiguous registers.
\*****************************************************************************/


    ErrorCode I2C_Peripheral_ReadRegisterMulti(uint8_t device_address,
                                                uint8_t register_address,
                                                uint8_t register_count,
                                                uint8_t* data);

/*****************************************************************************\
 * Function:    I2C_Peripheral_WriteRegister
 * Input:       uint8_t device_address, uint8_t register_address,
 *              uint8_t data
 * Returns:     ErrorCode
 * Description:
 *     Write through I2C at a given address.
\*****************************************************************************/

    ErrorCode I2C_Peripheral_WriteRegister(uint8_t device_address,
                                    uint8_t register_address,
                                    uint8_t data);




#endif
