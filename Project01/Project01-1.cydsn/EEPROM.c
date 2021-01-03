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

ErrorCode I2C_EXT_EEPROM_Reset(uint8_t device_address, uint8_t pages)
    {
        uint8_t in[512] = {};

        for (uint16_t word = 0; word < pages; word++)
        {
            I2C_EXT_EEPROM_WriteRegisterMulti(device_address,
                                                (word * EXT_EEPROM_WORD_SIZE) >> 8,
                                                word * EXT_EEPROM_WORD_SIZE & 0xFF,
                                                EXT_EEPROM_WORD_SIZE,
                                                in);
            CyDelay(5);
        }

        return NO_ERROR;

    }



void I2C_EXT_EEPROM_PrintAll(){
    UART_PutString("Memory content:\r\n");
    for (uint16_t i = 0; i < EXT_EEPROM_TOTAL_WORDS; i++)
        I2C_EXT_EEPROM_PrintWord(i);
}

void I2C_EXT_EEPROM_PrintWord(uint16_t word){
    char message[10];
    uint8_t bytes_per_row = 6;
    uint8_t out[EXT_EEPROM_WORD_SIZE];

    // Reading the word
    UART_PutString("Word: ");
    sprintf(message, "%d", word);
    UART_PutString(message);
    UART_PutString("\r\n");
    I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                        ((word*EXT_EEPROM_WORD_SIZE) >> 8) & 0xFF,
                                        ((word*EXT_EEPROM_WORD_SIZE)) & 0xFF,
                                        EXT_EEPROM_WORD_SIZE,
                                        out);
    for (uint8_t i = 0; i < EXT_EEPROM_WORD_SIZE; i++){

        sprintf(message,"%.2X", out[i]);
        UART_PutString(message);
        UART_PutString("  ");
        if(!((i+1)%bytes_per_row)) UART_PutString("\n");
    }
    UART_PutString("\r\n");

}

ErrorCode I2C_EXT_EEPROM_WriteWord(uint8_t* word){

    uint8_t word_index = I2C_EXT_EEPROM_First_Index(word); // index of the first available empty cell.

    uint8_t potential_bytes = EXT_EEPROM_WORD_SIZE - (eeprom_index % EXT_EEPROM_WORD_SIZE);

    // Controllo che la parola possa essere scritta sulla pagina
    if (eeprom_index != 0xFFF0)
    {
        if(potential_bytes > word_index){
            I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                                (eeprom_index >> 8) & 0xff,
                                                (eeprom_index) & 0xff,
                                                word_index,
                                                word);
            eeprom_index += word_index;

        }
        else{
            I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                                (eeprom_index >> 8) & 0xff,
                                                (eeprom_index) & 0xff,
                                                potential_bytes,
                                                word);
            eeprom_index += potential_bytes;
            pages++;
            CyDelay(5);
            I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                                (eeprom_index >> 8) & 0xff,
                                                (eeprom_index) & 0xff,
                                                word_index - potential_bytes,
                                                &word[potential_bytes]);
            eeprom_index += word_index - potential_bytes;
        }
    }
    else
    {
        I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                                                (eeprom_index >> 8) & 0xff,
                                                (eeprom_index) & 0xff,
                                                potential_bytes - (potential_bytes % BYTE_TO_READ_PER_LEVEL),
                                                word);
        eeprom_index += potential_bytes;
    }

    CyDelay(5);

    return NO_ERROR;
}

uint8_t I2C_EXT_EEPROM_First_Index(uint8_t* word){
    
    uint8_t count = 0;
    
    uint8_t i;
    // Ciclo per tutta la dimensione della parola
    for (i = 20; i > 0; i--){
        for (uint8_t j = 0; j < BYTE_TO_TRANSFER; j++){
            // Modificare il parametro sulla base di cosa viene restituito dall'accelerometro quando incompleto.
            if (word[j+i*6] == 0) count ++;
        }
        if (count < BYTE_TO_TRANSFER) return (i + 1)*BYTE_TO_TRANSFER;
        else count = 0;
    }
    return BYTE_TO_TRANSFER;
    
}
