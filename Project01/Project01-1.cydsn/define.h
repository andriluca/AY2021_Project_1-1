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
    #define EEPROM_FINAL_VALUE          EEPROM_ODR_50     // Final encoded ODR value (> EEPROM_FINAL_VALUE).
    
    // FSR
    
    /*  FS      RANGE       SENSITIVITY *\
     *  ------------------------------- *
     *  FS0     [-2, +2]g            1  *
     *  FS1     [-4, +4]g            2  *
     *  FS2     [-8, +8]g            4  *
     *  FS3     [-16, +16]g         12  *
    \*  ------------------------------- */
    
    
    /* === End changeable values === */
    
    // addresses
    #define EXT_EEPROM_DEVICE_ADDRESS   0x50 
    #define LIS3DH_DEVICE_ADDRESS       0x18                                    // Accelerometer's slave address (SAD).
    #define LIS3DH_CTRL_REG1            0x20                                    // Register 1 --> setup Hi Res Mode (ODRs' selection happens in interrupt).
    #define LIS3DH_CTRL_REG3            0x22
    #define LIS3DH_CTRL_REG4            0x23                                    // Register 4 --> setup FS[1:0] + LIS3DH_SENSITIVITY (use masks below).
    #define LIS3DH_CTRL_REG5            0x24
    #define LIS3DH_FIFO_CTRL_REG        0x2e
    #define LIS3DH_STATUS_REG           0x27                                    // Status Register.
    #define LIS3DH_OUT_X_L              0x28                                    // First output register.
    #define LIS3DH_OUT_Z_H              0x2d                                    // Last output register.
    #define LIS3DH_OUT_N                (LIS3DH_OUT_Z_H - LIS3DH_OUT_X_L + 1)   // Number of output registers (6).
    #define LIS3DH_OUT_AXES             (uint8_t)(LIS3DH_OUT_N / 2)             // Accelerometer's number of axes (3).
    
    // === REGISTER MASKS ===

    // Status Register
    #define LIS3DH_ZYXDA_STATUS_REG     0x08    // New available data incoming from the register.

    // Control Register 1
    #define LIS3DH_ENABLE_CTRL_REG1     0x07    // Partial mask: enabling the 3 axes.
    // GUI encode ODRs in 2 bits, so it's needed to add '+ 1' to the data coming from it.
    #define LIS3DH_ODR_01               0x01    //   1Hz
    #define LIS3DH_ODR_10               0x02    //  10Hz
    #define LIS3DH_ODR_25               0x03    //  25Hz
    #define LIS3DH_ODR_50               0x04    //  50Hz
    // Use these masks in order to setup Control Register 1.

    // Control Register 3
    #define LIS3DH_WM_CTRL_REG3         0x04
    #define LIS3DH_OVR_CTRL_REG3        0x02

    // Control Register 4
    #define LIS3DH_NR_CTRL_REG4         0x00    // Partial mask: the rest is modified by the if defined.
    // Normal mode Full Scales
    #define LIS3DH_FS_02                  0x00    // FS = [-2, +2]g   --> So =  4
    #define LIS3DH_FS_04                  0x01    // FS = [-4, +4]g   --> So =  8
    #define LIS3DH_FS_08                  0x02    // FS = [-8, +8]g   --> So = 16   
    #define LIS3DH_FS_16                  0x03    // FS = [-16, +16]g --> So = 48
    // Use these masks to setup the Control Register 4
    
    // Control Register 5
    #define LIS3DH_FIFO_EN_CTRL_REG5       0x40    // Enable the FIFO register

    // FIFO Control Register
	// Modes
    #define LIS3DH_STREAM_MODE_FIFO_CTRL_REG    0x80
    #define LIS3DH_FIFO_MODE_FIFO_CTRL_REG      0x40
    #define LIS3DH_STF_MODE_FIFO_CTRL_REG       0xc0
    #define LIS3DH_BYPASS_FIFO_CTRL_REG         0x00
    
    // Number of levels
    #define LIS3DH_FTH_WTM_FIFO_CTRL_REG        0x15
    
    // ===== SETUP MASKS =====
    #define LIS3DH_SETUP_01_CTRL_REG1	(LIS3DH_ODR_01 << 4) | LIS3DH_ENABLE_CTRL_REG1  // Setup mask varying with odr
    #define LIS3DH_SETUP_10_CTRL_REG1	(LIS3DH_ODR_10 << 4) | LIS3DH_ENABLE_CTRL_REG1
    #define LIS3DH_SETUP_25_CTRL_REG1	(LIS3DH_ODR_25 << 4) | LIS3DH_ENABLE_CTRL_REG1
    #define LIS3DH_SETUP_50_CTRL_REG1	(LIS3DH_ODR_50 << 4) | LIS3DH_ENABLE_CTRL_REG1

    #define LIS3DH_SETUP_CTRL_REG3		LIS3DH_WM_CTRL_REG3                             // Choose between WM and OVR
    
    #define LIS3DH_SETUP_02_CTRL_REG4   (LIS3DH_FS_02 << 4) | LIS3DH_NR_CTRL_REG4       // Setup mask varying with fs
    #define LIS3DH_SETUP_04_CTRL_REG4   (LIS3DH_FS_04 << 4) | LIS3DH_NR_CTRL_REG4
    #define LIS3DH_SETUP_08_CTRL_REG4   (LIS3DH_FS_08 << 4) | LIS3DH_NR_CTRL_REG4
    #define LIS3DH_SETUP_16_CTRL_REG4   (LIS3DH_FS_16 << 4) | LIS3DH_NR_CTRL_REG4

    #define LIS3DH_SETUP_CTRL_REG5      LIS3DH_FIFO_EN_CTRL_REG5
    
    #define LIS3DH_RESET_FIFO_CTRL_REG  LIS3DH_BYPASS_FIFO_CTRL_REG
    #define LIS3DH_MODE_FIFO_CTRL_REG   LIS3DH_STREAM_MODE_FIFO_CTRL_REG                // Choose between Stream and FIFO mode
    #define LIS3DH_SETUP_FIFO_CTRL_REG  LIS3DH_MODE_FIFO_CTRL_REG | LIS3DH_FTH_WTM_FIFO_CTRL_REG 
    
    //--------------------------------------------//
    //        NORMAL MODE IS SET BY DEFAULT       //
    //--------------------------------------------//
    

    // Normal mode sensitivities
    #define LIS3DH_SENSITIVITY_0        4       // mg/digit
    #define LIS3DH_SENSITIVITY_1        8       // mg/digit
    #define LIS3DH_SENSITIVITY_2        16      // mg/digit
    #define LIS3DH_SENSITIVITY_3        48      // mg/digit

    
    // Data buffer
    #define LIS3DH_RESOLUTION            4                                          // Hi Res in bits.
    #define LIS3DH_TOTAL_BITS           10                                          // Bits to memorize raw data (in digit).
    #define LIS3DH_RIGHT_SHIFT          (LIS3DH_TOTAL_BITS - LIS3DH_RESOLUTION)     // to perform right shift.
    #define BYTES_PER_AXIS              (uint8_t)(LIS3DH_RESOLUTION/LIS3DH_OUT_AXES)
    #define BYTE_TO_TRANSFER            1 + LIS3DH_RESOLUTION + 1
    
    // Conversion
    #define GRAVITY                     9.81                                // ms^-2
    // Modify in a variable
    #define CONVERSION                  0.001*GRAVITY*100    // ms^-2*digit^-1
    
    // EEPROM
    #define EEPROM_TOTAL_ODRS           (EEPROM_FINAL_VALUE - EEPROM_INIT_VALUE + 1)    // Number of ODR to be cycled.
    #define EEPROM_ODR_1                0x01                                            //   1Hz    CHOSEN
    #define EEPROM_ODR_10               0x02                                            //  10Hz
    #define EEPROM_ODR_25               0x03                                            //  25Hz
    #define EEPROM_ODR_50               0x04                                            //  50Hz    CHOSEN
    #define EEPROM_ODR_100              0x05                                            // 100Hz
    #define EEPROM_ODR_200              0x06                                            // 200Hz    
    #define EEPROM_ODR_400              0x07                                            // 400Hz
    
    // Status
    #define WTM_LOW                     0
    #define WTM_HIGH                    1
    #define BYTE_TO_READ_PER_LEVEL      6
    #define LEVEL_TO_READ               LIS3DH_FTH_WTM_FIFO_CTRL_REG
    #define BYTE_TO_EEPROM              4
    #define X_LSB   0
    #define X_MSB   1
    #define Y_LSB   2
    #define Y_MSB   3
    #define Z_LSB   4
    #define Z_MSB   5
    #define A_Z     2
    #define A_Y     1
    #define A_X     0

#endif
