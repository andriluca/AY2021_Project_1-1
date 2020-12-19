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



_Bool onWaterMark();

void doWatermark();

void init()
{
    UART_Start();
    I2C_Peripheral_Start();
    I2C_LIS3DH_Start();
    ISR_ACC_StartEx(WTM_ISR);
    //shiftIndex = 0;
    CyDelay(5);
    ADC_Temp_Start();
}

//_Bool onWatermark(){
//    return wtm && !fifo_read;
//}
//
//_Bool onReadEEPROM(){
//    return !wtm && fifo_read;
//}
//
//void doWatermark(){
//    for (int level = 0; level < LEVEL_TO_READ; level++){
//
//        // Receiving raw data
//    	I2C_LIS3DH_Get_Raw_Data(raw_data_16bit);
//    	// Converting data
//    	for (uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
//    	{
//    	    converted_acc[i] = (int16)(raw_data_16bit[i] * sensitivity * CONVERSION);
//    	}
//    	// Creating the data packets
//    	concatenated_Data = 0;
//    	uint8_t count = LIS3DH_OUT_AXES-1;
//    	for(uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
//    	{
//    	    concatenated_Data |= (uint32_t)((converted_acc[i] & 0x3FF) << 10*count);
//    	    count--;
//    	}
//    	
//    	// Populating the buffer with acceleration values.
//    	for(uint8_t i = 0; i < LIS3DH_RESOLUTION; i++)
//    	{
//    	    out[i + offset] = (uint8_t)((concatenated_Data >> 8*i) & 0xFF);
//    	}
//
//    	// Populating the buffer with acceleration values.
//    	for(uint8_t i = 4; i < LIS3DH_RESOLUTION + 2; i++)
//    	{
//    	    // In questo momento scrivo zero perchè non ci abbiamo ancora lavorato.
//    	    out[i + offset] = 0;
//    	}
//    	
//    	offset = offset + 6;
//	
//    }
//    
//    out[126] = 0;
//    out[127] = 0;
//    
//    fifo_read = 1;
//    wtm = 0;
//}
//
//void doReadEEPROM(){
//    I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
//				0x00,
//				0x00,
//				128,
//				out);
////    I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS);
//    CyDelay(5);
//    I2C_EXT_EEPROM_SequntialRead(EXT_EEPROM_DEVICE_ADDRESS,
//				126,
//				outEEPROM);
//    fifo_read = 0;
//}

/* [] END OF FILE */
