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
#include "project.h"
#include "I2c.h"
#include "define.h"
#include "accelerometer.h"
#include "states.h"
#include "stdio.h"
#include "EEPROM.h"



uint8_t comm_abilitate;
extern uint8 settings;
char msg;

extern uint8_t temp;
extern uint8_t fifo_write;
extern uint8_t fifo_read;
extern volatile uint8_t wtm;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
        
    init();
    comm_abilitate = 1;
       
    for(;;)
    {
        if (comm_rec && comm_abilitate)
        {
            msg = UART_ReadRxData();
            UART_ClearRxBuffer();
            switch(msg)
            {   
                case 's':
                    temp = 0;              
                    ISR_ACC_Stop(); 
                    wtm = WTM_LOW;
                    PWM_Stop();  
                    break;
                case 'b':
                    temp = 1;
                    I2C_LIS3DH_Start(settings);
                    ISR_ACC_StartEx(WTM_ISR); 
                    wtm = WTM_LOW;
                    PWM_Start();
                   // init();
                    break;
                case 'h':
                    UART_PutString("Accelerometer Hello $$$\n"); //important \n to stop ser.readline()                    
                    settings = INT_EEPROM_ReadByte(CONFIG_REGISTER);
                    switch(settings&FSR)
                    {            
                        case _2g:
                            UART_PutString("+-2g\n");
                            break;
                        case _4g:
                            UART_PutString("+-4g\n");
                            break; 
                        case _8g:
                            UART_PutString("+-8g\n");
                            break;
                        case _16g:
                            UART_PutString("+-16g\n");
                            break;
                        default:
                            break;
                    }
                    switch((settings&ODR)>>2)
                    {
                        case _1Hz:
                            UART_PutString("1Hz\n");
                            break;
                        case _10Hz:
                            UART_PutString("10Hz\n");
                            break; 
                        case _25Hz:
                            UART_PutString("25Hz\n");
                            break;
                        case _50Hz:
                            UART_PutString("50Hz\n");
                            break;
                        default:
                            break;
                    }
                    switch((settings&TEMP_FORMAT)>>4)
                    {
                        case CELSIUS:
                            UART_PutString("Celsius\n");
                            break;
                        case FAHRENHEIT:
                            UART_PutString("Fahrenheit\n");
                            break;
                        default:
                            break;
                    }
                    switch((settings&ESAV_STATUS)>>5)
                    {
                        case ESAV_OFF:
                        
                            UART_PutString("OFF\n");                       
                            break;
                        case ESAV_ON:
                            
                            UART_PutString("ON\n");
                            break;
                        default:
                            break;
                    }
                    break;
                case 'c':    
                    comm_abilitate = 0;
                    comm_rec = 0;                   
                    UART_ClearRxBuffer();
                    while(comm_rec == 0);
                    settings = UART_ReadRxData();   
                    UART_ClearRxBuffer();
                    switch(settings & FSR)
                    {
                        case _2g:
                            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG4,
                                 LIS3DH_SETUP_02_CTRL_REG4);        
                            break;
                        case _4g:
                            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG4,
                                 LIS3DH_SETUP_04_CTRL_REG4); 
                            break; 
                        case _8g:
                            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG4,
                                 LIS3DH_SETUP_08_CTRL_REG4); 
                            break;
                        case _16g:
                            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG4,
                                 LIS3DH_SETUP_16_CTRL_REG4); 
                            break;
                        default:
                            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG4,
                                 LIS3DH_SETUP_02_CTRL_REG4);   
                            break; 
                    }
                    
                    switch((settings&ODR)>>2)
                    {
                        case _1Hz:
                            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 LIS3DH_SETUP_01_CTRL_REG1);
                            break;
                        case _10Hz:
                            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 LIS3DH_SETUP_10_CTRL_REG1);
                            break; 
                        case _25Hz:
                            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 LIS3DH_SETUP_25_CTRL_REG1);
                            break;
                        case _50Hz:
                            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 LIS3DH_SETUP_50_CTRL_REG1);
                            break;
                        default:
                            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 LIS3DH_SETUP_01_CTRL_REG1);
                            break;
                    }
                        
                    if((settings & ESAV_STATUS)>>5)
                    {
                        temp = 1;
                        PWM_Start();
                        I2C_LIS3DH_Start(settings);
                        ISR_ACC_StartEx(WTM_ISR);
                    }       
                    else
                    {
                        temp = 0;            
                        ISR_ACC_Stop(); 
                        PWM_Stop();
                    }
                    
                    INT_EEPROM_UpdateTemperature();
                    INT_EEPROM_WriteByte(settings, CONFIG_REGISTER);
                    doEEPROMReset();
                    comm_abilitate = 1;
                    break;
                case 'v': 
                    temp = 0;              
                    ISR_ACC_Stop(); 
                    wtm = WTM_LOW;
                    PWM_Stop();  
                    doReadEEPROM();
                    doEEPROMReset();                 
                    break;
                default:
                    break;
            }
            comm_rec = 0;
        }
          
        
        // Reading the TEMPERATURE
        if (onTemperature())
            doTemperature();
        // Reading the FIFO
        if (onWatermark())
	        doWatermark();
        // Writing the EEPROM
        if (onWriteEEPROM())
            doWriteEEPROM();
        if (onFullEEPROM())
            doFullEEPROM();
        // Reading the EEPROM
        //if (onReadEEPROM())
        //    doReadEEPROM();
        // Resetting the EEPROM
        //if (onEEPROMReset())
        //    doEEPROMReset();
        
    }
}