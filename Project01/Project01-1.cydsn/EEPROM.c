#include "EEPROM.h"

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
                    uint16_t counter = register_count;
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

ErrorCode I2C_EXT_EEPROM_Reset(uint8_t device_address)
    {
        for (uint16_t word = 0; word < 512; word++)
        {
            uint8_t in[512] = {};
            I2C_EXT_EEPROM_WriteRegisterMulti(device_address, (word*EEPROM_WORD_SIZE) >> 8, word*EEPROM_WORD_SIZE & 0xFF, 128, in);
            CyDelay(5);
        }
        return NO_ERROR;

//        uint8_t error = I2C_Master_MasterSendStart(device_address, I2C_Master_WRITE_XFER_MODE);
//        if (error == I2C_Master_MSTR_NO_ERROR){
//            // Sending ones
//            error = I2C_Master_MasterWriteByte(0xFF);
//            if(error == I2C_Master_MSTR_NO_ERROR){
//                error = I2C_Master_MasterSendStart(device_address,I2C_Master_READ_XFER_MODE);
//                if(error == I2C_Master_MSTR_NO_ERROR){
//                    error = I2C_Master_MasterSendStop();
//                }   
//            }
//        }
//        return error ? ERROR : NO_ERROR;

    }
    
   

void I2C_EXT_EEPROM_PrintAll(){
    UART_PutString("Memory content:\r\n");
    for (uint16_t i = 0; i < EEPROM_TOTAL_WORDS; i++)
        I2C_EXT_EEPROM_PrintWord(i);
}

void I2C_EXT_EEPROM_PrintWord(uint16_t word){
    char message[10];
    uint8_t bytes_per_row = 6;
    uint8_t out[EEPROM_WORD_SIZE];
    
    
    // Reading the word
    UART_PutString("Word: ");
    sprintf(message, "%d", word);
    UART_PutString(message);
    UART_PutString("\r\n");
    I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS, 
                                        ((word*EEPROM_WORD_SIZE) >> 8) & 0xFF,
                                        ((word*EEPROM_WORD_SIZE)) & 0xFF,
                                        EEPROM_WORD_SIZE,
                                        out);
    for (uint8_t i = 0; i < EEPROM_WORD_SIZE; i++){
            
        sprintf(message,"%.2X", out[i]);
        UART_PutString(message);
        UART_PutString("  ");
        if(!((i+1)%bytes_per_row)) UART_PutString("\n");
    }
    UART_PutString("\r\n");
    
}