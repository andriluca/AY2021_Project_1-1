/* =========================================================================
 * Project01-1, Luca Andriotto, Matteo Cavicchioli, Alessandro Pirelli
 * =========================================================================
*/

#ifndef _EEPROM_H
    
    #define _EEPROM_H
    
    #include "define.h"
    #include "project.h"
    #include "cytypes.h"
    #include "I2c.h"
    #include "stdio.h"

/*****************************************************************************\
 * Function:    I2C_EXT_EEPROM_ReadRegister
 * Inputs:
 * Returns:     ErrorCode
 * Description: 
 *     Reading EEPROM cell with specific address.
\*****************************************************************************/

    
    ErrorCode I2C_EXT_EEPROM_ReadRegister(uint8_t device_address,
                                            uint8_t register_address_high,
                                            uint8_t register_address_low,
                                            uint8_t* data);
/*****************************************************************************\
 * Function:    I2C_EXT_EEPROM_WriteRegister
 * Inputs:
 * Returns:     ErrorCode
 * Description: 
 *     Writing EEPROM cell with specific address.
\*****************************************************************************/

    ErrorCode I2C_EXT_EEPROM_WriteRegister(uint8_t device_address,
                                        uint8_t register_address_high,
                                        uint8_t register_address_low,
                                        uint8_t data);

/*****************************************************************************\
 * Function:    I2C_EXT_EEPROM_WriteRegisterMulti
 * Inputs:
 * Returns:     ErrorCode
 * Description: 
 *     Writing multiple EEPROM cells starting at a specific address.
\*****************************************************************************/

    ErrorCode I2C_EXT_EEPROM_WriteRegisterMulti(uint8_t device_address,
                                        uint8_t register_address_high,
                                        uint8_t register_address_low,
                                        uint8_t register_count,
                                        uint8_t* data);
    
/*****************************************************************************\
 * Function:    I2C_EXT_EEPROM_ReadRegisterMulti
 * Inputs:
 * Returns:     ErrorCode
 * Description: 
 *     Reading multiple EEPROM cells starting at a specific address.
\*****************************************************************************/

    ErrorCode I2C_EXT_EEPROM_ReadRegisterMulti(uint8_t device_address,
                                        uint8_t register_address_high,
                                        uint8_t register_address_low,
                                        uint8_t register_count,
                                        uint8_t* data);
    
/*****************************************************************************\
 * Function:    I2C_EXT_EEPROM_Reset
 * Inputs:
 * Returns:     ErrorCode
 * Description: 
 *     Erasing EEPROM content from first to indicated page.
\*****************************************************************************/

    ErrorCode I2C_EXT_EEPROM_Reset(uint8_t device_address, uint8_t pages);

/*****************************************************************************\
 * Function:    I2C_EXT_EEPROM_WriteWord
 * Inputs:
 * Returns:     ErrorCode
 * Description: 
 *     Writing EEPROM pages linearly.
\*****************************************************************************/

    ErrorCode I2C_EXT_EEPROM_WriteWord(uint8_t* word);

/*****************************************************************************\
 * Function:    I2C_EXT_EEPROM_First_Index
 * Inputs:
 * Returns:     uint8_t
 * Description: 
 *     Returning index of the first available EEPROM empty cell.
\*****************************************************************************/

    uint8_t I2C_EXT_EEPROM_First_Index(uint8_t* word);
    
// =============================== DEBUG UART ===============================
    
/*****************************************************************************\
 * Function:    I2C_EXT_EEPROM_PrintAll
 * Inputs:
 * Returns:     void
 * Description: 
 *     Printing all the memory content through UART (using PutString for debug).
\*****************************************************************************/

    
    void I2C_EXT_EEPROM_PrintAll();

/*****************************************************************************\
 * Function:    I2C_EXT_EEPROM_PrintWord
 * Inputs:
 * Returns:     void
 * Description: 
 *     Printing a specific EEPROM page through UART (using PutString for debug).
\*****************************************************************************/

    void I2C_EXT_EEPROM_PrintWord(uint16_t word);

    extern volatile uint16_t eeprom_index;
    uint16_t pages;
    
#endif
