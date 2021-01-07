/* =========================================================================
 * Project01-1, Luca Andriotto, Matteo Cavicchioli, Alessandro Pirelli
 * =========================================================================
*/

#ifndef __DEFINE_H

    #define __DEFINE_H

    // ======================================================================== Accelerometer ========================================================================
    
    // ************************************************************************** addresses **************************************************************************
    
    #define LIS3DH_DEVICE_ADDRESS       0x18                                    // Accelerometer's slave address (SAD).
    #define LIS3DH_CTRL_REG1            0x20                                    // Register 1       --> setup Hi Res Mode (ODRs' selection happens in interrupt).
    #define LIS3DH_CTRL_REG3            0x22                                    // Register 3       --> setup ISR type (WTM/OVR).
    #define LIS3DH_CTRL_REG4            0x23                                    // Register 4       --> setup FS[1:0].
    #define LIS3DH_CTRL_REG5            0x24                                    // Register 5       --> setup FIFO Enable.
    #define LIS3DH_FIFO_CTRL_REG        0x2e                                    // FIFO Register    --> setup FIFO Mode.
    #define LIS3DH_OUT_X_L              0x28                                    // First output register.
    #define LIS3DH_OUT_Z_H              0x2d                                    // Last output register.
    #define LIS3DH_OUT_N                (LIS3DH_OUT_Z_H - LIS3DH_OUT_X_L + 1)   // Number of output registers (6).
    #define LIS3DH_OUT_AXES             (uint8_t)(LIS3DH_OUT_N / 2)             // Accelerometer's number of axes (3).
    
    // ***************************************************************************************************************************************************************
    
    // *********************************************************************** registers masks ***********************************************************************
    
    // Control Register 1
    #define LIS3DH_ENABLE_CTRL_REG1             0x07    // Partial mask: enabling the 3 axes.
    // GUI encode ODRs in 2 bits, so it's needed to add '+ 1' to the data coming from it.
    #define LIS3DH_ODR_01                       0x01    //   1Hz
    #define LIS3DH_ODR_10                       0x02    //  10Hz
    #define LIS3DH_ODR_25                       0x03    //  25Hz
    #define LIS3DH_ODR_50                       0x04    //  50Hz

    // Control Register 3
    #define LIS3DH_WM_CTRL_REG3                 0x04
    #define LIS3DH_OVR_CTRL_REG3                0x02
    #define LIS3DH_I1_ZYXDA_CTRL_REG3           0x10

    // Control Register 4
    #define LIS3DH_NR_CTRL_REG4                 0x00
    #define LIS3DH_BDU_CTRL_REG4                0x80
    
    // Normal mode Full Scales
    #define LIS3DH_FS_02                        0x00    // FS = [-2, +2]g   --> So =  4
    #define LIS3DH_FS_04                        0x01    // FS = [-4, +4]g   --> So =  8
    #define LIS3DH_FS_08                        0x02    // FS = [-8, +8]g   --> So = 16
    #define LIS3DH_FS_16                        0x03    // FS = [-16, +16]g --> So = 48
        
    // Control Register 5
    #define LIS3DH_FIFO_EN_CTRL_REG5            0x40    // Enable the FIFO register.

    // FIFO Control Register
	// Modes
    #define LIS3DH_STREAM_MODE_FIFO_CTRL_REG    0x80
    #define LIS3DH_FIFO_MODE_FIFO_CTRL_REG      0x40
    #define LIS3DH_STF_MODE_FIFO_CTRL_REG       0xC0
    #define LIS3DH_BYPASS_FIFO_CTRL_REG         0x00

    // Number of levels
    #define LIS3DH_FTH_WTM_FIFO_CTRL_REG        0x14

    // ***************************************************************************************************************************************************************

    // ************************************************************************* setup masks *************************************************************************

    // Use these masks on Accelerometer startup.
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

    // ***************************************************************************************************************************************************************

    // *************************************************************************** encoding **************************************************************************
    //Flags values
    #define LOW                     0
    #define HIGH                    1
    // Accelerations bytes
    #define X_LSB                       0
    #define X_MSB                       1
    #define Y_LSB                       2
    #define Y_MSB                       3
    #define Z_LSB                       4
    #define Z_MSB                       5
    // FIFO levels to read
    #define LEVEL_TO_READ               LIS3DH_FTH_WTM_FIFO_CTRL_REG
    
    // ***************************************************************************************************************************************************************
    
    // ===============================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // ======================================================================= Internal EEPROM =======================================================================
    
    // Addresses
    #define CONFIG_REGISTER                                     0x00                // EEPROM register for config initialization.
    #define INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_L     0x01                // EEPROM registers for restoring first address.
    #define INT_EEPROM_EXT_EEPROM_FIRST_AVAILABLE_ADDRESS_H     0x02
    // Addresses (Configuration Byte)
    #define ODR_LSB                                             0x02
    #define TEMP_FORMAT_LSB                                     0x04
    #define ESAV_STATUS_LSB                                     0x05
    
    // Masks (Configuration Byte)
    #define FSR                                                 0x03
    #define ODR                                                 0x0C
    #define TEMP_FORMAT                                         0x10
    #define ESAV_STATUS                                         0x20
    
    // Encoding
    // FSR
    #define LIS3DH_FS_02_CB                                     LIS3DH_FS_02
    #define LIS3DH_FS_04_CB                                     LIS3DH_FS_04
    #define LIS3DH_FS_08_CB                                     LIS3DH_FS_08
    #define LIS3DH_FS_16_CB                                     LIS3DH_FS_16
    // ODR 
    #define LIS3DH_ODR_01_CB                                    0x00
    #define LIS3DH_ODR_10_CB                                    0x01
    #define LIS3DH_ODR_25_CB                                    0x02
    #define LIS3DH_ODR_50_CB                                    0x03
    // Saving status
    #define ESAV_OFF                                            0x00
    #define ESAV_ON                                             0x01
    // Temperature
    #define CELSIUS                                             0x00
    #define FAHRENHEIT                                          0x01
    
    // Values
    // FSR
    #define FS_02_CB                                            2
    #define FS_04_CB                                            4
    #define FS_08_CB                                            8
    #define FS_16_CB                                            16
    // ODR
    #define ODR_01_CB                                           1
    #define ODR_10_CB                                           10
    #define ODR_25_CB                                           25
    #define ODR_50_CB                                           50
    
    // ===============================================================================================================================================================
    
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    // ======================================================================= External EEPROM =======================================================================
    
    #define EXT_EEPROM_DEVICE_ADDRESS                           0x50
    #define EXT_EEPROM_WORD_SIZE                                0x80                // Number of bytes per word.
    #define EXT_EEPROM_TOTAL_WORDS                              512
    #define EXT_EEPROM_OVERFLOW                                 110
    #define EXT_EEPROM_NO_RESETTING                             0
    #define EXT_EEPROM_RESETTING                                1
    #define BYTE_TO_READ_PER_LEVEL                              6
    #define BYTE_TO_EEPROM                                      4
    
    // ===============================================================================================================================================================
    
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    // ======================================================================== Built-in LED =========================================================================

    #define BUILT_IN_LED_PERIOD_FAST        127
    #define BUILT_IN_LED_PERIOD_SLOW        511
    #define BUILT_IN_LED_COMPARE_FAST       64
    #define BUILT_IN_LED_COMPARE_SLOW       256
    
    // ===============================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    // ======================================================================== External LED =========================================================================
    
    #define EXT_LED_ON                      1
    #define EXT_LED_OFF                     0
    
    // ===============================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    // ============================================================================= ADC =============================================================================
    
    #define ADC_MAX                     65535
    #define ADC_MIN                     0

    // ===============================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    // ======================================================================== TIMER (Switch) =======================================================================
    
    #define TIMER_RESET_PERIOD          5120
    #define TOGGLE_DEVICE               TIMER_RESET_PERIOD - 256
    #define EMPTY_EEPROM                TIMER_RESET_PERIOD - 2560
    
    // ===============================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    // ============================================================================= UART ============================================================================
    
    #define LIS3DH_RESOLUTION           4                                           // Hi Res in bits.
    #define LIS3DH_TOTAL_BITS           10                                          // Bits to memorize raw data (in digit).
    #define LIS3DH_RIGHT_SHIFT          (LIS3DH_TOTAL_BITS - LIS3DH_RESOLUTION)     // to perform right shift.
    #define BYTES_PER_AXIS              (uint8_t)(LIS3DH_RESOLUTION/LIS3DH_OUT_AXES)
    #define BYTE_TO_TRANSFER            (1 + LIS3DH_RESOLUTION + 1)
    
    // ===============================================================================================================================================================

#endif
