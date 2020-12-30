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



uint8_t comm_abilitate;
extern uint8 settings;

extern uint8_t temp;
extern uint8_t fifo_write;
extern uint8_t fifo_read;
extern volatile uint8_t wtm;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
        
    init();
    comm_abilitate = 1;
       
    for(;;)
    {
        
        if(onByteReceived())
            doByteReceived();
        
        if(onStopping())
            doStopping();
        
        if(onSaving())
            doSaving();
        
        if(onHandshake())
            doHandshake();
        
        
        if(onChangeConfig())
            doChangeConfig();
            
        if(onVisualizing())
            doVisualizing();
        
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
        
        if (onButtonReleased())
            doButtonReleased();
        
        
    }
}