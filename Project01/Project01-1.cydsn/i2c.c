/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#include "I2c.h"


ErrorCode I2C_Peripheral_Start()
    {
        I2C_Master_Start();
        return NO_ERROR;
    }

ErrorCode I2C_Peripheral_Stop()
    {
        I2C_Master_Stop();
        return NO_ERROR;
    }

ErrorCode I2C_Peripheral_ReadRegister(uint8_t device_address,
                                            uint8_t register_address,
                                            uint8_t* data)
    {
        // Send start condition
        uint8_t error = I2C_Master_MasterSendStart(device_address,I2C_Master_WRITE_XFER_MODE);
        if (error == I2C_Master_MSTR_NO_ERROR)
        {
            // Write address of register to be read
            error = I2C_Master_MasterWriteByte(register_address);
            if (error == I2C_Master_MSTR_NO_ERROR)
            {
                // Send restart condition
                error = I2C_Master_MasterSendRestart(device_address, I2C_Master_READ_XFER_MODE);
                if (error == I2C_Master_MSTR_NO_ERROR)
                {
                    // Read data without acknowledgement
                    *data = I2C_Master_MasterReadByte(I2C_Master_NAK_DATA);
                }
            }
        }
        // Send stop condition
        I2C_Master_MasterSendStop();
        // Return error code
        return error ? ERROR : NO_ERROR;
    }

ErrorCode I2C_EXT_EEPROM_ReadRegister(uint8_t device_address,
                                            uint8_t register_address_high,
                                            uint8_t register_address_low,
                                            uint8_t* data)
    {
        // Send start condition
        uint8_t error = I2C_Master_MasterSendStart(device_address,I2C_Master_WRITE_XFER_MODE);
        if (error == I2C_Master_MSTR_NO_ERROR)
        {
            // Write address of register to be read
            error = I2C_Master_MasterWriteByte(register_address_high);
            if (error == I2C_Master_MSTR_NO_ERROR)
            {
                // Send address LSB
                error = I2C_Master_MasterWriteByte(register_address_low);
                if(error == I2C_Master_MSTR_NO_ERROR)
                {
                    error = I2C_Master_MasterSendRestart(device_address, I2C_Master_READ_XFER_MODE);
                    if (error == I2C_Master_MSTR_NO_ERROR)
                    {
                        // Read data without acknowledgement
                        *data = I2C_Master_MasterReadByte(I2C_Master_NAK_DATA);
                    }
                }
            }
        }
        // Send stop condition
        I2C_Master_MasterSendStop();
        // Return error code
        return error ? ERROR : NO_ERROR;
    }

ErrorCode I2C_Peripheral_ReadRegisterMulti(uint8_t device_address,
                                        uint8_t register_address,
                                        uint8_t register_count,
                                        uint8_t* data)
    {
        // Start condition
        uint8_t error = I2C_Master_MasterSendStart(device_address,I2C_Master_WRITE_XFER_MODE);
        if(error == I2C_Master_MSTR_NO_ERROR)
        {
            // modifying the register address in order to automatically read multiple values
            register_address |= 0x80;
            // writing the register address
            error = I2C_Master_MasterWriteByte(register_address);

            if(error == I2C_Master_MSTR_NO_ERROR)
            {
                // Send restart
                error = I2C_Master_MasterSendRestart(device_address,I2C_Master_READ_XFER_MODE);

                if(error == I2C_Master_MSTR_NO_ERROR)
                {
                    // send a number of data equal to register_count
                    uint8_t count = register_count;
                    while(count>1)
                    {
                        data[register_count-count] = I2C_Master_MasterReadByte(I2C_Master_ACK_DATA);
                        count--;
                    }

                    data[register_count - 1] = I2C_Master_MasterReadByte(I2C_Master_NAK_DATA);
                }
            }
        }
        // Stop condition
        error = I2C_Master_MasterSendStop();

        return error ? ERROR : NO_ERROR;

    }

ErrorCode I2C_Peripheral_WriteRegister(uint8_t device_address,
                                    uint8_t register_address,
                                    uint8_t data)
    {
        // Send start condition
        uint8_t error = I2C_Master_MasterSendStart(device_address, I2C_Master_WRITE_XFER_MODE);
        if (error == I2C_Master_MSTR_NO_ERROR)
        {
            // Write register address
            error = I2C_Master_MasterWriteByte(register_address);
            if (error == I2C_Master_MSTR_NO_ERROR)
            {
                // Write byte of interest
                error = I2C_Master_MasterWriteByte(data);
            }
        }
        // Send stop condition
        I2C_Master_MasterSendStop();
        // Return error code
        return error ? ERROR : NO_ERROR;
    }

ErrorCode I2C_EXT_EEPROM_WriteRegister(uint8_t device_address,
                                    uint8_t register_address_high,
                                    uint8_t register_address_low,
                                    uint8_t data)
    {
        // Send start condition
        uint8_t error = I2C_Master_MasterSendStart(device_address, I2C_Master_WRITE_XFER_MODE);
        if (error == I2C_Master_MSTR_NO_ERROR)
        {
            // Write register address high
            error = I2C_Master_MasterWriteByte(register_address_high);
            if(error == I2C_Master_MSTR_NO_ERROR)
            {
                error = I2C_Master_MasterWriteByte(register_address_low);
                if (error == I2C_Master_MSTR_NO_ERROR)
                {
                    // Write byte of interest
                    error = I2C_Master_MasterWriteByte(data);
                }
            }
        }
        // Send stop condition
        I2C_Master_MasterSendStop();
        // Return error code
        return error ? ERROR : NO_ERROR;
    }


ErrorCode I2C_EXT_EEPROM_WriteRegisterMulti(uint8_t device_address,
                                        uint8_t register_address_high,
                                        uint8_t register_address_low,
                                        uint8_t register_count,
                                        uint8_t* data)
    {
        // Send start condition
        uint8_t error = I2C_Master_MasterSendStart(device_address, I2C_Master_WRITE_XFER_MODE);
        if (error == I2C_Master_MSTR_NO_ERROR)
        {
            // Write address of register to be written with the MSB equal to 1
            error = I2C_Master_MasterWriteByte(register_address_high);
            if (error == I2C_Master_MSTR_NO_ERROR)
            {
                error = I2C_Master_MasterWriteByte(register_address_low);
                if (error == I2C_Master_MSTR_NO_ERROR)
                {
                    // Continue writing until we have data to write
                    uint8_t counter = register_count;
                    while(counter > 0)
                    {
                         error = I2C_Master_MasterWriteByte(data[register_count-counter]);
                        if (error != I2C_Master_MSTR_NO_ERROR)
                        {
                            // Send stop condition
                            I2C_Master_MasterSendStop();
                            // Return error code
                            return ERROR;
                        }
                        counter--;
                    }
                }
            }
        }
        // Send stop condition in case something didn't work out correctly
        I2C_Master_MasterSendStop();
        // Return error code
        return error ? ERROR : NO_ERROR;
    }

ErrorCode I2C_EXT_EEPROM_ReadRegisterMulti(uint8_t device_address,
                                        uint8_t register_address_high,
                                        uint8_t register_address_low,
                                        uint8_t register_count,
                                        uint8_t* data)
    {
        // Start condition
        uint8_t error = I2C_Master_MasterSendStart(device_address,I2C_Master_WRITE_XFER_MODE);
        if(error == I2C_Master_MSTR_NO_ERROR)
        {
            // modifying the register address in order to automatically read multiple values
            // writing the register address
            error = I2C_Master_MasterWriteByte(register_address_high);

            if(error == I2C_Master_MSTR_NO_ERROR)
            {
                error = I2C_Master_MasterWriteByte(register_address_low);
                if(error == I2C_Master_MSTR_NO_ERROR)
                {
                    // Send restart
                    error = I2C_Master_MasterSendRestart(device_address,I2C_Master_READ_XFER_MODE);

                    if(error == I2C_Master_MSTR_NO_ERROR)
                    {
                        // send a number of data equal to register_count
                        uint8_t count = register_count;
                        while(count>1)
                        {
                            data[register_count-count] = I2C_Master_MasterReadByte(I2C_Master_ACK_DATA);
                            count--;
                        }

                        data[register_count - 1] = I2C_Master_MasterReadByte(I2C_Master_NAK_DATA);
                    }
                }

            }
        }
        // Stop condition
        error = I2C_Master_MasterSendStop();

        return error ? ERROR : NO_ERROR;

    }

ErrorCode I2C_EXT_EEPROM_SequntialRead(uint8_t device_address,
                                        uint8_t register_count,
                                        uint8_t* data)
    {
        // Start condition
        uint8_t error = I2C_Master_MasterSendStart(device_address,I2C_Master_READ_XFER_MODE);
        if(error == I2C_Master_MSTR_NO_ERROR)
        {
            // modifying the register address in order to automatically read multiple values
            // writing the register address

            //error = I2C_Master_MasterSendRestart(device_address,I2C_Master_READ_XFER_MODE);

            uint8_t count = register_count;
            while(count>1)
            {
                data[register_count-count] = I2C_Master_MasterReadByte(I2C_Master_ACK_DATA);
                count--;
            }

            data[register_count - 1] = I2C_Master_MasterReadByte(I2C_Master_NAK_DATA);

        // Stop condition
        error = I2C_Master_MasterSendStop();

        }

        return error ? ERROR : NO_ERROR;

    }
ErrorCode I2C_EXT_EEPROM_Reset(uint8_t device_address)
    {
        uint8_t error = I2C_Master_MasterSendStart(device_address, I2C_Master_WRITE_XFER_MODE);
        if (error == I2C_Master_MSTR_NO_ERROR){
            // Sending ones
            error = I2C_Master_MasterWriteByte(0xFF);
            if(error == I2C_Master_MSTR_NO_ERROR){
                error = I2C_Master_MasterSendStart(device_address,I2C_Master_READ_XFER_MODE);
                if(error == I2C_Master_MSTR_NO_ERROR){
                    error = I2C_Master_MasterSendStop();
                }
            }
        }
        return error ? ERROR : NO_ERROR;
    }


