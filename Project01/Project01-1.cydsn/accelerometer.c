/* =========================================================================
 * Project01-1, Luca Andriotto, Matteo Cavicchioli, Alessandro Pirelli
 * =========================================================================
*/

#include "accelerometer.h"

extern uint8_t offset;
extern uint8_t index_temp;


ErrorCode I2C_LIS3DH_Start(uint8 setting)
{
    
    uint8 config[2];
    uint8_t period = I2C_LIS3DH_SetConfig(setting, config);
    // Setup control register 1
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 config[1]);    // ODR
    // Setup control register 3
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG3,
                                 LIS3DH_SETUP_CTRL_REG3);       // Interrupt on watermark
    // Setup control register 4
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG4,
                                 config[0]);     // FS
    // Setup control register 5
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG5,
                                 LIS3DH_SETUP_CTRL_REG5);       // FIFO enable
    // Setup FIFO control register (bypass to reset)
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_FIFO_CTRL_REG,
                                 LIS3DH_RESET_FIFO_CTRL_REG);   // Software reset of accelerometer mode.
    // Setup FIFO control register
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_FIFO_CTRL_REG,
                                 LIS3DH_SETUP_FIFO_CTRL_REG );  // select Stream mode and set WTM to 31 level
    T_TIMER_WritePeriod(period);
    return NO_ERROR;
}

ErrorCode I2C_LIS3DH_Get_Raw_Data(uint16_t* data)
{
    uint8_t sensorData[LIS3DH_OUT_N]; // This array is storing left-aligned bytes coming from accelerometer.

    //Storing data in temporary array.
    I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                    0x28,
                                    6,
                                    sensorData);


    // Re-arranging data to have them right-aligned as integers.
    for(int i = 0; i < LIS3DH_OUT_AXES; i++) data[i] = (uint16_t)((sensorData[2*i+1] << 8 | sensorData[2*i])) >> LIS3DH_RIGHT_SHIFT;

    return NO_ERROR;
}


uint16_t I2C_LIS3DH_SetConfig(uint8 settings, uint8* config)
{
    uint16_t temp_timer_period;
    switch(settings & FSR)
    {
        case _2g:
            config[0]=LIS3DH_SETUP_02_CTRL_REG4;
            break;
        case _4g:
            config[0]=LIS3DH_SETUP_04_CTRL_REG4;
            break;
        case _8g:
            config[0]=LIS3DH_SETUP_08_CTRL_REG4;
            break;
        case _16g:
            config[0]=LIS3DH_SETUP_16_CTRL_REG4;
            break;
        default:
            config[0]=LIS3DH_SETUP_02_CTRL_REG4;
            break;
    }

    switch((settings & ODR) >> 2)
    {
        case _1Hz:
            config[1] = LIS3DH_SETUP_01_CTRL_REG1;
            temp_timer_period = 500;
            break;
        case _10Hz:
            config[1] = LIS3DH_SETUP_10_CTRL_REG1;
            temp_timer_period = 50;
            break;
        case _25Hz:
            config[1] = LIS3DH_SETUP_25_CTRL_REG1;
            temp_timer_period = 20;
            break;
        case _50Hz:
            config[1] = LIS3DH_SETUP_50_CTRL_REG1;
            temp_timer_period = 10;
            break;
        default:
            config[1] = LIS3DH_SETUP_01_CTRL_REG1;
            temp_timer_period = 1000;
            break;
    }
    return temp_timer_period;
}

