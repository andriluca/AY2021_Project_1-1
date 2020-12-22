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
#include "EEPROM.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    uint8_t arr1[126] = {
        1,2,3,4,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        
        
    };
    uint8_t arr2[126] = {
        1,2,3,4,0,0,
        1,2,3,4,0,0,
        1,2,3,4,0,0,
        1,2,3,4,0,0,
        1,2,3,4,0,0,
        1,2,3,4,0,0,
        1,2,3,4,0,0,
        1,2,3,4,0,0,
        1,2,3,4,0,0,
        1,2,3,4,0,0,
        1,2,3,4,0,0,
        1,2,3,4,0,0,
        0,0,0,0,0,1,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        0,0,0,0,0,0,
        
        
    };
    
    uint8_t array[126] = {1,2,3};
    
    init();
    
//    for (uint8_t i = 0; i<4;i++){
//        I2C_EXT_EEPROM_WriteWord(arr1);
//    }
//    for (uint8_t i = 0; i<2;i++){
//        I2C_EXT_EEPROM_WriteWord(arr2);
//    }
    
    //I2C_EXT_EEPROM_WriteWord(array);
    //CyDelay(5);
//    I2C_EXT_EEPROM_PrintWord(0);
    
    //I2C_EXT_EEPROM_WriteRegisterMulti(EXT_EEPROM_DEVICE_ADDRESS, (6>>8) & 0xff, 6 & 0xff, 3, array);
    //I2C_EXT_EEPROM_PrintWord(1);
    // I2C_EXT_EEPROM_PrintWord(2);
    
//    for(uint16_t i=0; i<128; i++){
//        I2C_EXT_EEPROM_SendWord(i);
//    }
    
    //char message[10];
    //sprintf(message, "%d\r\n", index);
    //UART_PutString(message);
        
    for(;;)
    {
        
        // Reading the TEMPERATURE
        if(onTemperature())
            doTemperature();
        // Reading the FIFO
        if(onWatermark())
	        doWatermark();
        // Writing the EEPROM
        if (onWriteEEPROM())
            doWriteEEPROM();
        // Reading the EEPROM
        if (onReadEEPROM())
            doReadEEPROM();
        // Resetting the EEPROM
        if(onEEPROMReset())
            doEEPROMReset();

    }
}