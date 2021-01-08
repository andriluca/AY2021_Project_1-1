/* =========================================================================
 * Project01-1, Luca Andriotto, Matteo Cavicchioli, Alessandro Pirelli
 * =========================================================================
*/

#include "interrupt.h"

CY_ISR(WTM_ISR){
    
    wtm = HIGH;

}

CY_ISR(TEMP_ISR){
    
    T_TIMER_ReadStatusRegister();
    t_isr = HIGH;

}

CY_ISR(COMM_GUI){

    // Setting flag
    comm_rec = HIGH;
    
}

CY_ISR_PROTO(COUNT_SEC){

    // Reset timer counter
    counted_seconds = TIMER_RESET_ReadCapture();
    // Setting flag
    isButtonReleased = HIGH;

}