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
        
    init();
            
    for(;;)
    {
        
        // Reading the TEMPERATURE
        if (onTemperature())
            doTemperature();
        // Reading the FIFO
        if (onWatermark())
	        doWatermark();
        // Writing the EEPROM
        if (onWriteEEPROM())
            doWriteEEPROM();
        if (onFullEEPROM())
            doFullEEPROM();
        // Reading the EEPROM
        if (onReadEEPROM())
            doReadEEPROM();
        // Resetting the EEPROM
        if (onEEPROMReset())
            doEEPROMReset();

    }
}