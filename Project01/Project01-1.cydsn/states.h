#include "project.h"
#include "cytypes.h"
#include "define.h"
#include "interrupt.h"
#include "LED.h"
#include "accelerometer.h"
#include "I2c.h"
#include "EEPROM.h"


#ifndef __STATES_H
    #define __STATES_H
    #include "project.h"
    
    _Bool onTemperature();
    _Bool onWatermark();
    _Bool onWriteEEPROM();
    _Bool onFullEEPROM();
    _Bool onReadEEPROM();
    _Bool onEEPROMReset();

    void doTemperature();
    void doWatermark();
    void doWriteEEPROM();
    void doFullEEPROM();
    void doReadEEPROM();
    void doEEPROMReset();


    void init();
    void restart();
#endif
