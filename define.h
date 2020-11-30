/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#ifndef __DEFINE_H

    #define __DEFINE_H
    
    /* === Changeable values === */
    // Persistent memory
    #define EEPROM_REGISTER             0x0000            // EEPROM register for initialization.
    #define EEPROM_INIT_VALUE           EEPROM_ODR_1      // Initial ODR if cell content was incosistent (< EEPROM_FINAL_VALUE).
    #define EEPROM_FINAL_VALUE          EEPROM_ODR_200    // Final encoded ODR value (> EEPROM_FINAL_VALUE).
    
    // FSR
    #define FS0                                           // Full Scale Range.
    
    /*  FS      RANGE       SENSITIVITY *\
     *  ------------------------------- *
     *  FS0     [-2, +2]g            1  *
     *  FS1     [-4, +4]g            2  *
     *  FS2     [-8, +8]g            4  *
     *  FS3     [-16, +16]g         12  *
    \*  ------------------------------- */
    
    
    /* === End changeable values === */
    
    // addresses
    #define LIS3DH_DEVICE_ADDRESS       0x18                                    // Accelerometer's slave address (SAD).
    #define LIS3DH_CTRL_REG1            0x20                                    // Register 1 --> setup Hi Res Mode (ODRs' selection happens in interrupt).
    #define LIS3DH_CTRL_REG4            0x23                                    // Register 4 --> setup FS[1:0] + LIS3DH_SENSITIVITY (use masks below).
    #define LIS3DH_STATUS_REG           0x27                                    // Status Register.
    #define LIS3DH_OUT_X_L              0x28                                    // First output register.
    #define LIS3DH_OUT_Z_H              0x2d                                    // Last output register.
    #define LIS3DH_OUT_N                (LIS3DH_OUT_Z_H - LIS3DH_OUT_X_L + 1)   // Number of output registers.
    #define LIS3DH_OUT_AXES             (uint8_t)(LIS3DH_OUT_N / 2)             // Accelerometer's number of axes.
    
    // register masks
    #define LIS3DH_HI_RES_CTRL_REG1     0x07    // Partial mask: the rest is initialized and modified by the interrupt.
    #define LIS3DH_ZYXDA_STATUS_REG     0x08    // New available data incoming from the register.
    #define LIS3DH_HR_CTRL_REG4         0x08    // Partial mask: the rest is modified by the if defined.
        
    #define LIS3DH_HI_RES_CTRL_REG4_FS0 0x00    // FS = [-2, +2]g   --> So =  1     CHOSEN
    #define LIS3DH_HI_RES_CTRL_REG4_FS1 0x10    // FS = [-4, +4]g   --> So =  2
    #define LIS3DH_HI_RES_CTRL_REG4_FS2 0x20    // FS = [-8, +8]g   --> So =  4   
    #define LIS3DH_HI_RES_CTRL_REG4_FS3 0x30    // FS = [-16, +16]g --> So = 12
    #define LIS3DH_SENSITIVITY_0        1       // mg/digit                         CHOSEN
    #define LIS3DH_SENSITIVITY_1        2       // mg/digit
    #define LIS3DH_SENSITIVITY_2        4       // mg/digit
    #define LIS3DH_SENSITIVITY_3        12      // mg/digit

    // Automatic definitions according to the FS choice
    #if defined(FS0)
        #define LIS3DH_HI_RES_CTRL_REG4     LIS3DH_HI_RES_CTRL_REG4_FS0 | LIS3DH_HR_CTRL_REG4
        #define LIS3DH_SENSITIVITY          LIS3DH_SENSITIVITY_0
    #elif defined(FS1)
        #define LIS3DH_HI_RES_CTRL_REG4     LIS3DH_HI_RES_CTRL_REG4_FS1 | LIS3DH_HR_CTRL_REG4
        #define LIS3DH_SENSITIVITY          LIS3DH_SENSITIVITY_1
    #elif defined(FS2)
        #define LIS3DH_HI_RES_CTRL_REG4     LIS3DH_HI_RES_CTRL_REG4_FS2 | LIS3DH_HR_CTRL_REG4
        #define LIS3DH_SENSITIVITY          LIS3DH_SENSITIVITY_2
    #elif defined(FS3)
        #define LIS3DH_HI_RES_CTRL_REG4     LIS3DH_HI_RES_CTRL_REG4_FS3 | LIS3DH_HR_CTRL_REG4
        #define LIS3DH_SENSITIVITY          LIS3DH_SENSITIVITY_3
    #endif 
    
    // Data buffer
    #define LIS3DH_RESOLUTION           10                                          // Hi Res in bits.
    #define LIS3DH_TOTAL_BITS           30                                          // Bits to memorize data (in digit).
    #define LIS3DH_RIGHT_SHIFT          (LIS3DH_TOTAL_BITS - LIS3DH_RESOLUTION)     // to perform right shift.
    #define BYTES_PER_AXIS              (uint8_t)(LIS3DH_RESOLUTION/LIS3DH_OUT_AXES)
    #define BYTE_TO_TRANSFER            1 + LIS3DH_RESOLUTION + 1
    
    // Conversion
    #define GRAVITY                     9.81                                // ms^-2
    #define CONVERSION                  LIS3DH_SENSITIVITY*0.001*GRAVITY    // ms^-2*digit^-1
    
    // EEPROM
    #define EEPROM_TOTAL_ODRS           (EEPROM_FINAL_VALUE - EEPROM_INIT_VALUE + 1)    // Number of ODR to be cycled.
    #define EEPROM_ODR_1                0x01                                            //   1Hz    CHOSEN
    #define EEPROM_ODR_10               0x02                                            //  10Hz
    #define EEPROM_ODR_25               0x03                                            //  25Hz
    #define EEPROM_ODR_50               0x04                                            //  50Hz
    #define EEPROM_ODR_100              0x05                                            // 100Hz
    #define EEPROM_ODR_200              0x06                                            // 200Hz    CHOSEN
    #define EEPROM_ODR_400              0x07                                            // 400Hz

#endif
