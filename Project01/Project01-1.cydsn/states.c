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
#include "states.h"
#include "accelerometer.h"
#include "I2c.h"

uint8 sensitivity;
volatile uint8_t wtm = WTM_LOW;
uint8_t raw_data_8bit[BYTE_TO_READ_PER_LEVEL];
int16_t raw_data_16bit[3];
int16_t converted_acc[3];
uint32_t concatenated_Data;
uint8_t out      [(LEVEL_TO_READ + 1) * 6];
uint8_t outEEPROM[(LEVEL_TO_READ + 1) * 6 + 2];
uint8_t j;
uint8_t offset;
uint8_t fifo_read;
volatile uint8_t shiftIndex;
volatile uint16_t eeprom_index;
volatile uint8_t eeprom_reset;


void init()
{
    UART_Start();
    I2C_Peripheral_Start();
    I2C_LIS3DH_Start();
    ISR_ACC_StartEx(WTM_ISR);
    shiftIndex = 0;
    eeprom_index = 0;
    eeprom_reset = 0;   // per resettare la eeprom
    offset = 0;
    fifo_read = 0;
    concatenated_Data = 0;
    sensitivity = 4;
    CyDelay(5);
}

_Bool onWatermark(){
    return wtm && !fifo_read;
}

_Bool onReadEEPROM(){
    return !wtm && fifo_read;
}

_Bool onEEPROMReset(){
    return eeprom_reset;
}

void doWatermark(){
    for (int level = 0; level < LEVEL_TO_READ + 1; level++){

        // Receiving raw data
    	I2C_LIS3DH_Get_Raw_Data(raw_data_16bit);
    	// Converting data
    	for (uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
    	{
    	    converted_acc[i] = (int16)(raw_data_16bit[i] * sensitivity * CONVERSION);
    	}
    	// Creating the data packets
    	concatenated_Data = 0;
    	uint8_t count = LIS3DH_OUT_AXES-1;
    	for(uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
    	{
    	    concatenated_Data |= (uint32_t)((converted_acc[i] & 0x3FF) << 10*count);
    	    count--;
    	}
    	
    	// Populating the buffer with acceleration values.
    	for(uint8_t i = 0; i < LIS3DH_RESOLUTION; i++)
    	{
    	    out[i + offset] = (uint8_t)((concatenated_Data >> 8*i) & 0xFF);
    	}

    	// Populating the buffer with temperature values.
    	for(uint8_t i = 4; i < LIS3DH_RESOLUTION + 2; i++)
    	{
    	    // In questo momento scrivo zero perchè non ci abbiamo ancora lavorato.
    	    out[i + offset] = 0;
    	}
    	
    	offset = offset + 6;
	
    }
    
    offset = 0;
    fifo_read = 1;
    wtm = 0;

}

void doReadEEPROM(){
    
    I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
                (eeprom_index >> 8) & 0xFF,
				eeprom_index & 0xFF,
				126,
				out);
//    I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS);
    CyDelay(5);
    
//    for (uint8_t i = 0; i<128; i++)
//        outEEPROM[i] = 0;
    
    I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS, 
                                        (eeprom_index >> 8) & 0xFF,
                                        eeprom_index & 0xFF,
                                        128,
                                        outEEPROM);
    eeprom_index = eeprom_index + 128;
    fifo_read = 0;
    
}

void doEEPROMReset(){
    I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS);
    eeprom_reset = 0;
}

/* [] END OF FILE */
