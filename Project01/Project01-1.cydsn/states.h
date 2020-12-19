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
#include "cytypes.h"
#include "define.h"
#include "interrupt.h"

#ifndef __STATES_H
    #define __STATES_H
    #include "project.h"
    
    _Bool onWatermark();
    _Bool onReadEEPROM();

    void doWatermark();
    void doReadEEPROM();

    void init();
#endif


/* [] END OF FILE */
