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

//CY_ISR(TIMER_ISR)
//{
//    TIMER_ReadStatusRegister();
//    temp ++;
//}
//