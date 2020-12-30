/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef _EEPROM_H
    #define _EEPROM_H
    #include "define.h"
    #include "project.h"
    #include "cytypes.h"
    #include "I2c.h"
    #include "stdio.h"
    
    uint16_t counter_pages;
    uint16_t pages;
    
    
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
    ErrorCode I2C_EXT_EEPROM_Reset(uint8_t device_address);
    ErrorCode I2C_EXT_EEPROM_Partial_Reset(uint8_t device_address, uint8_t pages);
    
    void I2C_EXT_EEPROM_PrintAll();
    
    void I2C_EXT_EEPROM_PrintWord(uint16_t word);

    ErrorCode I2C_EXT_EEPROM_WriteWord(uint8_t* word);
    
    ErrorCode I2C_EXT_EEPROM_SendWord();
    
    uint8_t I2C_EXT_EEPROM_Last_Index(uint8_t* word);

#endif

/* [] END OF FILE */
