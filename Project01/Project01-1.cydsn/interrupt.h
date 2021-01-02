/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#ifndef __INTERRUPT_H

    #define __INTERRUPT_H

    #include "cytypes.h"
    #include "define.h"
    #include "I2c.h"

    volatile uint8_t t_isr;
    volatile uint8_t wtm;
    volatile uint8_t comm_rec;
    volatile uint16_t counted_seconds;
    volatile uint8_t isButtonReleased;
    volatile uint8_t boot;
    volatile uint8_t trigger;

    
    CY_ISR_PROTO(WTM_ISR);

    CY_ISR_PROTO(TEMP_ISR);

    CY_ISR_PROTO(COMM_GUI);

    CY_ISR_PROTO(COUNT_SEC);

    CY_ISR_PROTO(BUTTON_PRESS);


#endif
