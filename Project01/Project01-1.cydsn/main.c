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


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    init();
    
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