/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#ifndef __INTERRUPT_H

    #define __INTERRUPT_H

    #include "cytypes.h"
    #include "define.h"
    #include "I2c.h"

    uint8_t outputDataRate;                         // keeps track of ODR changes.
    volatile uint8_t onButtonPressed;               // keeps track of button states.
    uint8_t zyxda;                                  // keeps track of the zyxda bit of status register.

    volatile uint8_t wtm;
    volatile uint8_t t_isr;
    volatile uint16_t counted_seconds;
    volatile uint8_t isButtonReleased;
    volatile uint8_t status;

    CY_ISR_PROTO(SW_ISR);

    CY_ISR_PROTO(WTM_ISR);

    CY_ISR_PROTO(TEMP_ISR);

    CY_ISR_PROTO(COMM_GUI);

    CY_ISR_PROTO(BUTTON_RELEASE);

    CY_ISR_PROTO(COUNT_SEC);

    CY_ISR_PROTO(BUTTON_PRESS);

    volatile uint8_t comm_rec;



#endif
