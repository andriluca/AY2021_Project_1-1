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
    
    _Bool onByteReceived();
    _Bool onStopping();
    _Bool onSaving();
    _Bool onHandshake();
    _Bool onVisualizing();
    _Bool onChangeConfig();
    _Bool onTemperature();
    _Bool onWatermark();
    _Bool onWriteEEPROM();
    _Bool onFullEEPROM();
    _Bool onReadEEPROM();
    _Bool onEEPROMReset();
    _Bool onButtonReleased();

    void doByteReceived();
    void doStopping();
    void doSaving();
    void doHandshake();
    void doVisualizing();
    void doChangeConfig();
    void doTemperature();
    void doWatermark();
    void doWriteEEPROM();
    void doFullEEPROM();
    void doReadEEPROM();
    void doEEPROMReset();
    void doButtonReleased();

    void init();
    void restart();
#endif
