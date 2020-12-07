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
int16 raw_data_16bit[3];
int32 converted_acc[3];
uint32_t concatenated_Data = 0;
uint8_t out[BYTE_TO_EEPROM*LEVEL_TO_READ];
uint8_t j = 0;
uint8_t offset = 0;

ErrorCode error;



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    init();
    
    uint8 sensitivity = 4;
    uint8 freq = EEPROM_ODR_25;
    uint8 fsr = LIS3DH_NORMAL_CTRL_REG4_FS0;
    
    //da definire freq e fsr 
   
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, 0x37); //qui scriviamo la frequenza
    if (error == NO_ERROR)
    {
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4, fsr | LIS3DH_NR_CTRL_REG4); //qui scriviamo il full scale
        if (error == NO_ERROR) 
        {
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG5, LIS3DH_FIFO_EN_CTRL_REG5); //enable FIFO
            if (error == NO_ERROR) 
            {
                error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG3, LIS3DH_WM_CTRL_REG3 ); //enable WTM INT
                if (error == NO_ERROR) 
                {
                    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_CTRL_REG, LIS3DH_STREAM_MODE_FIFO_CTRL_REG | LIS3DH_FTH_WTM_FIFO_CTRL_REG ); //select Stream mode and set WTM to 31 level
                }
            }
        }
    }
    
//    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, 0x47); //qui scriviamo la frequenza
//    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4, 0x00); //qui scriviamo il full scale
//    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG5, LIS3DH_FIFO_EN_CTRL_REG5); //enable FIFO
//    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG3, 0x04 ); //enable WTM INT
//    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_CTRL_REG, 0x5E ); //select Stream mode and set WTM to 31 level
    
    
    
    ISR_ACC_StartEx(WTM_ISR);
    //uint8 pin = 1;
    
    for(;;)
    {
        
        if (wtm)
        {
            for(uint8_t level = 0; level < LEVEL_TO_READ; level ++)
            {
                I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, 
                                                 LIS3DH_OUT_X_L, 
                                                 BYTE_TO_READ_PER_LEVEL,
                                                 raw_data_8bit);
                
                // Casting 10 bits per sample into an int16 array
                for (int i = 0; i < BYTE_TO_READ_PER_LEVEL/2; i ++)
                {
                    raw_data_16bit[i] = (int16)((raw_data_8bit[j] | (raw_data_8bit[j+1]<<8)))>>6;
                    converted_acc[i] = (int16)(raw_data_16bit[i] * sensitivity * CONVERSION); 
                    j = j+2;
                }
                
            concatenated_Data = converted_acc[A_Z] | (converted_acc[A_Y] << 10) | (converted_acc[A_X] << 20);
            
            out[0 + offset] = (uint8_t)(concatenated_Data & 0xFF);
            out[1 + offset] = (uint8_t)((concatenated_Data >> 8) & 0xFF);
            out[2 + offset] = (uint8_t)((concatenated_Data >> 16) & 0xFF);
            out[3 + offset] = (uint8_t)((concatenated_Data >> 24) & 0xFF);
            
            //inviamo out[4]; 
            
            offset = offset + 4;
            }
        wtm = WTM_LOW;
        }
            
            
            
                
                
            
               
                
                
                
                
                
                
            
        
    }
}

/* [] END OF FILE */
