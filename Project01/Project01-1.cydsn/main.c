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
#include "stdio.h"


uint8 sensitivity = 4;
volatile uint8_t wtm = WTM_LOW;
uint8_t raw_data_8bit[BYTE_TO_READ_PER_LEVEL];
int16_t raw_data_16bit[3];
int16_t converted_acc[3];
uint32_t concatenated_Data = 0;
uint8_t out      [(BYTE_TO_EEPROM)*LEVEL_TO_READ + 2];
uint8_t outEEPROM[(BYTE_TO_EEPROM)*LEVEL_TO_READ + 2];
//uint8_t out[BYTE_TO_EEPROM*LEVEL_TO_READ];
//uint8_t outEEPROM[BYTE_TO_EEPROM*LEVEL_TO_READ];
uint8_t j = 0;
uint8_t offset = 0;
uint8_t fifo_read = 0;
volatile uint8_t shiftIndex;
uint16_t ind = 0x0000;
uint8_t page = 0;
uint32_t temperature32 = 0;
//
//
//=======
//>>>>>>> d101645b9624087f0fc0c897c0e69a6aa765cd6d
//
//int main(void)
//{
//    CyGlobalIntEnable; /* Enable global interrupts. */
//    
//    init();
//    I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS);
//    
//<<<<<<< HEAD
//    uint8 sensitivity = 4;
//    //uint8 freq = EEPROM_ODR_25;
//    //uint8 fsr = LIS3DH_NORMAL_CTRL_REG4_FS0;
//    
//    //da definire freq e fsr 
//   
////    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, 0x30 | LIS3DH_NORMAL_CTRL_REG1); //qui scriviamo la frequenza
////    if (error == NO_ERROR)
////    {
////        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4, fsr | LIS3DH_NR_CTRL_REG4); //qui scriviamo il full scale
////        if (error == NO_ERROR) 
////        {
////            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG5, LIS3DH_FIFO_EN_CTRL_REG5); //enable FIFO
////            if (error == NO_ERROR) 
////            {
////                error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG3, LIS3DH_WM_CTRL_REG3 ); //enable WTM INT
////                if (error == NO_ERROR) 
////                {
////                    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_CTRL_REG, LIS3DH_STREAM_MODE_FIFO_CTRL_REG | LIS3DH_FTH_WTM_FIFO_CTRL_REG ); //select Stream mode and set WTM to 31 level
////                }
////            }
////        }
////    }
//    
//    //uint8 pin = 1;
//     
//    for(;;)
//    {
//        if(wtm && fifo_read == 0){
//            for (int level = 0; level < LEVEL_TO_READ; level++) //21
//            {
//                I2C_LIS3DH_Get_Raw_Data(raw_data_16bit);
//                for (uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
//                {
//                    converted_acc[i] = (int16)(raw_data_16bit[i] * sensitivity * CONVERSION);
//                }
//                
//                concatenated_Data = 0;
//                uint8_t count = LIS3DH_OUT_AXES-1;
//                for(uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
//                {
//                    concatenated_Data |= (uint32_t)((converted_acc[i] & 0x3FF) << 10*count);
//                    count--;
//                }
////                concatenated_Data = (uint32_t)(converted_acc[A_Z] | (converted_acc[A_Y] << 10) | (converted_acc[A_X] << 20));
//                
//                out[0 + offset] = (uint8_t)(concatenated_Data & 0xFF);
//                out[1 + offset] = (uint8_t)((concatenated_Data >> 8) & 0xFF);
//                out[2 + offset] = (uint8_t)((concatenated_Data >> 16) & 0xFF);
//                out[3 + offset] = (uint8_t)((concatenated_Data >> 24) & 0xFF);
//                
//                temperature32 = ADC_Temp_Read32();
//                
//                if (temperature32 > ADC_MAX)    
//                temperature32 = ADC_MAX;
//                if (temperature32 < ADC_MIN)
//                temperature32 = ADC_MIN;
//                      
//                out[4 + offset] = (uint8_t)(temperature32 & 0xFF); //lsb
//                out[5 + offset] = (uint8_t)((temperature32 >>8) & 0xFF); //msb
//                
//                
//                //inviamo out[4]; 
//                
//                offset = offset + 6;
//                
//            }
//            offset = 0;
//            
//            out[126] = 0xC0;
//            out[127] = 0xC0;
//            
////            for(uint8 i = 0; i <3; i++)
////            {    
////                char message[20];
////                sprintf(message, "raw_data_16: %u \n", (unsigned int) (raw_data_16bit[i]));
////                UART_PutString(message);
////            }
//            fifo_read = 1;
//            wtm = 0;
//        }
//        if (wtm ==0 && fifo_read)
//        {
//            //for (uint8_t i= 120; i<128; i++) out[i] = 0; 
//            I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
//                                        ind >> 8,
//                                        ind & 0xFF,
//                                        128,
//                                        out);
////            for(uint8_t i = 0; i < 128; i++)
////            {
////                I2C_EXT_EEPROM_WriteRegister(EXT_EEPROM_DEVICE_ADDRESS,ind >> 8, ind & 0xFF, out[i]);
////                ind = ind + 0x0001;
////            }
//            
//           
////            
////            I2C_EXT_EEPROM_ReadRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS,
////                                        ind >> 8,
////                                        ind & 0xFF,
////                                        120,
////                                        outEEPROM);
//            CyDelay(5);
//            //I2C_EXT_EEPROM_SequntialRead(EXT_EEPROM_DEVICE_ADDRESS,128,outEEPROM);
//            ind = ind + 0x0080;
//            page ++;
//            fifo_read = 0;
//        }
//        if (page == 1)
//        {
//            CyDelay(5);
//            for (uint8_t i = 0; i<128; i++)
//            {
//                I2C_EXT_EEPROM_ReadRegister(EXT_EEPROM_DEVICE_ADDRESS, (ind - 0x0080) >> 8, (ind - 0x0080) & 0xFF, &outEEPROM[i]);
//                ind ++;
//            }
//                                        
//            
//            page = 0;
//        }
//            
//            
//            
//            
//            
//        
//        
//        
//        
//        
//        
//        
//        
////        if (wtm)
////        {
////            wtm = WTM_LOW;
////            for(uint8_t level = 0; level < LEVEL_TO_READ + 1; level ++)
////            {
////                I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, 
////                                                 LIS3DH_OUT_X_L, 
////                                                 BYTE_TO_READ_PER_LEVEL,
////                                                 raw_data_8bit);
////                
////                
//////                I2C_LIS3DH_Get_Raw_Data(raw_data_16bit);
////                
////                // Casting 10 bits per sample into an int16 array
////                for (uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
////                {
////                    converted_acc[i] = (int16)(raw_data_16bit[i] * sensitivity * CONVERSION);
////                }
////                
////                concatenated_Data = 0;
////                uint8_t count = LIS3DH_OUT_AXES-1;
////                for(uint8_t i = 0; i < LIS3DH_OUT_AXES; i++)
////                {
////                    concatenated_Data |= (uint16_t)((converted_acc[i] & 0x3FF) << 10*count);
////                    count--;
////                }
//////                concatenated_Data = (uint32_t)(converted_acc[A_Z] | (converted_acc[A_Y] << 10) | (converted_acc[A_X] << 20));
////                
////                out[0 + offset] = (uint8_t)(concatenated_Data & 0xFF);
////                out[1 + offset] = (uint8_t)((concatenated_Data >> 8) & 0xFF);
////                out[2 + offset] = (uint8_t)((concatenated_Data >> 16) & 0xFF);
////                out[3 + offset] = (uint8_t)((concatenated_Data >> 24) & 0xFF);
////                
////                //inviamo out[4]; 
////                
////                offset = offset + 4;
////            }
////            // sensitivity = 1;
////            // UART_PutString("Sono dentro \r\n");
//////            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_CTRL_REG, 0); //select Stream mode and set WTM to 31 level
//////            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_CTRL_REG, LIS3DH_SETUP_FIFO_CTRL_REG ); //select Stream mode and set WTM to 31 level
////        }    
//

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    init();
    I2C_EXT_EEPROM_Reset(EXT_EEPROM_DEVICE_ADDRESS);
    for(;;)
    {
	    // Resetting the EEPROM
        if(onEEPROMReset())
            doEEPROMReset();
        // Reading the FIFO
        if(onWatermark())
	        doWatermark();
        // Writing the EEPROM
        if (onReadEEPROM())
            doReadEEPROM();
    }
}