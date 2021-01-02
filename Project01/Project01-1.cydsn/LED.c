#include "LED.h"

void LED_Start(){
    PWM_Start();
}

void LED_Stop(){
    PWM_Stop();
}

void LED_BlinkSlow(){
    // Blinking with T=1s, DC=50%
    PWM_WritePeriod(BUILT_IN_LED_PERIOD_SLOW);
    PWM_WriteCompare(BUILT_IN_LED_COMPARE_SLOW);
}

void LED_BlinkFast(){
    // Blinking with T=250ms, DC=50%
    PWM_WritePeriod(BUILT_IN_LED_PERIOD_FAST);
    PWM_WriteCompare(BUILT_IN_LED_COMPARE_FAST);
}