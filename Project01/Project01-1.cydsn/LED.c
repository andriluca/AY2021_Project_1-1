#include "LED.h"

void LED_BlinkSlow(){
    // Blinking with T=1s, DC=50%
    PWM_WritePeriod(LED_PERIOD_SLOW);
    PWM_WriteCompare(LED_COMPARE_SLOW);
}

void LED_BlinkFast(){
    // Blinking with T=250ms, DC=50%
    PWM_WritePeriod(LED_PERIOD_FAST);
    PWM_WriteCompare(LED_COMPARE_FAST);
}