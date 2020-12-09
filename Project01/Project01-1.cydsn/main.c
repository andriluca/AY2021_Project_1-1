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
#include "project.h"
#include "I2c.h"
#include "define.h"
#include "accelerometer.h"
#include "states.h"

volatile uint8_t wtm = WTM_LOW;
uint8_t raw_data_8bit[BYTE_TO_READ_PER_LEVEL];
int16_t raw_data_16bit[3];
int16_t converted_acc[3];
uint32_t concatenated_Data = 0;
uint8_t out[BYTE_TO_EEPROM*LEVEL_TO_READ];
uint8_t j = 0;
uint8_t offset = 0;



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    init();
    
    uint8 sensitivity = 4;
    //uint8 freq = EEPROM_ODR_25;
    //uint8 fsr = LIS3DH_NORMAL_CTRL_REG4_FS0;
    
    //da definire freq e fsr 
   
//    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, 0x30 | LIS3DH_NORMAL_CTRL_REG1); //qui scriviamo la frequenza
//    if (error == NO_ERROR)
//    {
//        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4, fsr | LIS3DH_NR_CTRL_REG4); //qui scriviamo il full scale
//        if (error == NO_ERROR) 
//        {
//            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG5, LIS3DH_FIFO_EN_CTRL_REG5); //enable FIFO
//            if (error == NO_ERROR) 
//            {
//                error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG3, LIS3DH_WM_CTRL_REG3 ); //enable WTM INT
//                if (error == NO_ERROR) 
//                {
//                    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_CTRL_REG, LIS3DH_STREAM_MODE_FIFO_CTRL_REG | LIS3DH_FTH_WTM_FIFO_CTRL_REG ); //select Stream mode and set WTM to 31 level
//                }
//            }
//        }
//    }
    
    //uint8 pin = 1;
    
    for(;;)
    {
        if(wtm){
            for (int level = 0; level < 31; level++){
                I2C_LIS3DH_Get_Raw_Data(raw_data_16bit);
            }
            wtm = 0;
        }
        
        
//        if (wtm)
//        {
//            wtm = WTM_LOW;
//            for(uint8_t level = 0; level < LEVEL_TO_READ + 1; level ++)
//            {
//                I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, 
//                                                 LIS3DH_OUT_X_L, 
//                                                 BYTE_TO_READ_PER_LEVEL,
//                                                 raw_data_8bit);
//                
//                
////                I2C_LIS3DH_Get_Raw_Data(raw_data_16bit);
//                
//                // Casting 10 bits per sample into an int16 array
//                for (uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
//                {
//                    converted_acc[i] = (int16)(raw_data_16bit[i] * sensitivity * CONVERSION);
//                }
//                
//                concatenated_Data = 0;
//                uint8_t count = LIS3DH_OUT_AXES-1;
//                for(uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
//                {
//                    concatenated_Data |= (uint16_t)((converted_acc[i] & 0x3FF) << 10*count);
//                    count--;
//                }
////                concatenated_Data = (uint32_t)(converted_acc[A_Z] | (converted_acc[A_Y] << 10) | (converted_acc[A_X] << 20));
//                
//                out[0 + offset] = (uint8_t)(concatenated_Data & 0xFF);
//                out[1 + offset] = (uint8_t)((concatenated_Data >> 8) & 0xFF);
//                out[2 + offset] = (uint8_t)((concatenated_Data >> 16) & 0xFF);
//                out[3 + offset] = (uint8_t)((concatenated_Data >> 24) & 0xFF);
//                
//                //inviamo out[4]; 
//                
//                offset = offset + 4;
//            }
//            // sensitivity = 1;
//            // UART_PutString("Sono dentro \r\n");
////            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_CTRL_REG, 0); //select Stream mode and set WTM to 31 level
////            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_CTRL_REG, LIS3DH_SETUP_FIFO_CTRL_REG ); //select Stream mode and set WTM to 31 level
//        }    
    }
}

/* [] END OF FILE */
