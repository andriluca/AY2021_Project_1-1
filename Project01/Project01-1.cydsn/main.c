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

volatile uint8_t wtm = WTM_LOW;
uint8_t raw_data_8bit[BYTE_TO_READ_PER_LEVEL];
uint16_t raw_data_16bit[3];



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    I2C_Peripheral_Start();
    CyDelay(5);
   
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, freq) //qui scriviamo la frequenza
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4, fsr); //qui scriviamo il full scale
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG5, LIS3DH_FIFO_EN_CTRL_REG5); //enable FIFO
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG3, LIS3DH_INT1_WTM_CTRL_REG3 ); //enable WTM INT
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_CTRL_REG, LIS3DH_STREAM_MODE_FIFO_CTRL_REG | LIS3DH_FTH_WTM_FIFO_CTRL_REG ); //select Stream mode and set WTM to 31 level

    
    for(;;)
    {
        switch(wtm)
        {
            case WTM_HIGH:
            for(uint8_t level = 0; level < LEVEL_TO_READ; level ++)
            {
                I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, 
                                                 LIS3DH_OUT_X_L, 
                                                 BYTE_TO_READ_PER_LEVEL,
                                                 raw_data_8bit);
                for (int i = 0; i < BYTE_TO_READ_PER_LEVEL; i ++)
                {
                    raw_data_16bit[i] = (int16)((raw_data_8bit[i] | (raw_data_8bit[i+1]<<8)))>>6;
                
                
                
            
        
    }
}

/* [] END OF FILE */
