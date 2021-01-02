/* =========================================================================
 * Project01-1, Luca Andriotto, Matteo Cavicchioli, Alessandro Pirelli
 * =========================================================================
*/

#include "interrupt.h"

CY_ISR(WTM_ISR){
    
    if(!boot) wtm = WTM_HIGH;
    boot = 0;
}

CY_ISR(TEMP_ISR){
    
    T_TIMER_ReadStatusRegister();
    if(trigger) t_isr = 1;
    trigger = !trigger;
}

CY_ISR(COMM_GUI){

    comm_rec = 1;
    
}

CY_ISR_PROTO(COUNT_SEC){

    // Reset contatore timer
    counted_seconds = TIMER_RESET_ReadCapture();
    // Incrementare contatore
    isButtonReleased = 1;

}