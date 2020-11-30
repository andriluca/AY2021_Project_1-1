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
