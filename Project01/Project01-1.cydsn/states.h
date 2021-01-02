/* =========================================================================
 * Project01-1, Luca Andriotto, Matteo Cavicchioli, Alessandro Pirelli
 * =========================================================================
*/

#ifndef __STATES_H

    #define __STATES_H

    #include "accelerometer.h"
    #include "project.h"
    #include "cytypes.h"
    #include "define.h"
    #include "interrupt.h"
    #include "LED.h"
    #include "I2c.h"
    #include "EEPROM.h"
    #include "stdio.h"

    void init();
    void loop();
    
    // Flag
    volatile uint8_t temp;
    volatile uint8_t fifo_write;
    volatile uint8_t fifo_read;
    volatile uint8_t fifo_level;
    volatile uint16_t outIndex;
    volatile uint8_t full_eeprom;
    volatile uint8_t eeprom_reset;

    volatile uint16_t eeprom_index;

    uint8_t offset;
    int32_t temperature32;
    uint8_t temperature[(LEVEL_TO_READ + 1) * 2];
    uint8_t index_temp;
    uint8 settings;
    char msg;
    
    
#endif
