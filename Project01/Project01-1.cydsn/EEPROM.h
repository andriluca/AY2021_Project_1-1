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

    ErrorCode I2C_EXT_EEPROM_ReadRegister(uint8_t device_address,
                                            uint8_t register_address_high,
                                            uint8_t register_address_low,
                                            uint8_t* data);

    ErrorCode I2C_EXT_EEPROM_WriteRegister(uint8_t device_address,
                                        uint8_t register_address_high,
                                        uint8_t register_address_low,
                                        uint8_t data);

    ErrorCode I2C_EXT_EEPROM_WriteRegisterMulti(uint8_t device_address,
                                        uint8_t register_address_high,
                                        uint8_t register_address_low,
                                        uint8_t register_count,
                                        uint8_t* data);
    
    ErrorCode I2C_EXT_EEPROM_ReadRegisterMulti(uint8_t device_address,
                                        uint8_t register_address_high,
                                        uint8_t register_address_low,
                                        uint8_t register_count,
                                        uint8_t* data);
    
    ErrorCode I2C_EXT_EEPROM_SequntialRead(uint8_t device_address,
                                        uint8_t register_count,
                                        uint8_t* data);
    
    ErrorCode I2C_EXT_EEPROM_Reset(uint8_t device_address, uint8_t pages);

    ErrorCode I2C_EXT_EEPROM_WriteWord(uint8_t* word);

    uint8_t I2C_EXT_EEPROM_Last_Index(uint8_t* word);
    
// =============================== DEBUG UART ===============================
    
    
    void I2C_EXT_EEPROM_PrintAll();

    void I2C_EXT_EEPROM_PrintWord(uint16_t word);

    extern volatile uint16_t eeprom_index;
    
    uint16_t pages;
    
#endif

/* [] END OF FILE */
