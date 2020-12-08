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
#include "states.h"
#include "accelerometer.h"
#include "I2c.h"

void init()
{
    UART_Start();
    I2C_Peripheral_Start();
    I2C_LIS3DH_Start();
    ISR_ACC_StartEx(WTM_ISR);
    CyDelay(5);
}

/* [] END OF FILE */
