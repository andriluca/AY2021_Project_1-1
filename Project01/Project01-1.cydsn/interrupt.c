/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#include "interrupt.h"

CY_ISR_PROTO(SW_ISR)
{
    // updating ODR.
    outputDataRate = (outputDataRate - EEPROM_INIT_VALUE + 1) % EEPROM_TOTAL_ODRS + EEPROM_INIT_VALUE;
    // setting flag to 1.
    onButtonPressed = 1;
}

CY_ISR(WTM_ISR)
{
    wtm = WTM_HIGH; //vedere se funziona
}

CY_ISR(TEMP_ISR)
{
    T_TIMER_ReadStatusRegister();
    t_isr = 1;
}

CY_ISR(COMM_GUI)
{
    comm_rec = 1;
}

CY_ISR_PROTO(BUTTON_RELEASE){

    // Settare flag del bottone rilasciato
    isButtonReleased = 1;
    // Controllo il tempo di pressione
    if(counted_seconds > TIMER_RESET_LOW_THRESHOLD && counted_seconds < TIMER_RESET_HIGH_THRESHOLD) 
        status = TOGGLE_DEVICE;
    else if(counted_seconds >= TIMER_RESET_HIGH_THRESHOLD)
        status = EMPTY_EEPROM;
    // Reset contatore
    counted_seconds = 0;
    TIMER_RESET_Stop();
}

CY_ISR_PROTO(COUNT_SEC){
    
    // Reset contatore timer
    TIMER_RESET_ReadStatusRegister();
    // Incrementare contatore
    counted_seconds++;

}

CY_ISR_PROTO(BUTTON_PRESS){
    TIMER_RESET_Start();
}


//CY_ISR(TIMER_ISR)
//{
//    TIMER_ReadStatusRegister();
//    temp ++;
//}
//