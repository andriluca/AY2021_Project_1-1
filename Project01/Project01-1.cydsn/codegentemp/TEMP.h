/*******************************************************************************
* File Name: TEMP.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_TEMP_H) /* Pins TEMP_H */
#define CY_PINS_TEMP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TEMP_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TEMP__PORT == 15 && ((TEMP__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TEMP_Write(uint8 value);
void    TEMP_SetDriveMode(uint8 mode);
uint8   TEMP_ReadDataReg(void);
uint8   TEMP_Read(void);
void    TEMP_SetInterruptMode(uint16 position, uint16 mode);
uint8   TEMP_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TEMP_SetDriveMode() function.
     *  @{
     */
        #define TEMP_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TEMP_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TEMP_DM_RES_UP          PIN_DM_RES_UP
        #define TEMP_DM_RES_DWN         PIN_DM_RES_DWN
        #define TEMP_DM_OD_LO           PIN_DM_OD_LO
        #define TEMP_DM_OD_HI           PIN_DM_OD_HI
        #define TEMP_DM_STRONG          PIN_DM_STRONG
        #define TEMP_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TEMP_MASK               TEMP__MASK
#define TEMP_SHIFT              TEMP__SHIFT
#define TEMP_WIDTH              1u

/* Interrupt constants */
#if defined(TEMP__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TEMP_SetInterruptMode() function.
     *  @{
     */
        #define TEMP_INTR_NONE      (uint16)(0x0000u)
        #define TEMP_INTR_RISING    (uint16)(0x0001u)
        #define TEMP_INTR_FALLING   (uint16)(0x0002u)
        #define TEMP_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TEMP_INTR_MASK      (0x01u) 
#endif /* (TEMP__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TEMP_PS                     (* (reg8 *) TEMP__PS)
/* Data Register */
#define TEMP_DR                     (* (reg8 *) TEMP__DR)
/* Port Number */
#define TEMP_PRT_NUM                (* (reg8 *) TEMP__PRT) 
/* Connect to Analog Globals */                                                  
#define TEMP_AG                     (* (reg8 *) TEMP__AG)                       
/* Analog MUX bux enable */
#define TEMP_AMUX                   (* (reg8 *) TEMP__AMUX) 
/* Bidirectional Enable */                                                        
#define TEMP_BIE                    (* (reg8 *) TEMP__BIE)
/* Bit-mask for Aliased Register Access */
#define TEMP_BIT_MASK               (* (reg8 *) TEMP__BIT_MASK)
/* Bypass Enable */
#define TEMP_BYP                    (* (reg8 *) TEMP__BYP)
/* Port wide control signals */                                                   
#define TEMP_CTL                    (* (reg8 *) TEMP__CTL)
/* Drive Modes */
#define TEMP_DM0                    (* (reg8 *) TEMP__DM0) 
#define TEMP_DM1                    (* (reg8 *) TEMP__DM1)
#define TEMP_DM2                    (* (reg8 *) TEMP__DM2) 
/* Input Buffer Disable Override */
#define TEMP_INP_DIS                (* (reg8 *) TEMP__INP_DIS)
/* LCD Common or Segment Drive */
#define TEMP_LCD_COM_SEG            (* (reg8 *) TEMP__LCD_COM_SEG)
/* Enable Segment LCD */
#define TEMP_LCD_EN                 (* (reg8 *) TEMP__LCD_EN)
/* Slew Rate Control */
#define TEMP_SLW                    (* (reg8 *) TEMP__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TEMP_PRTDSI__CAPS_SEL       (* (reg8 *) TEMP__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TEMP_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TEMP__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TEMP_PRTDSI__OE_SEL0        (* (reg8 *) TEMP__PRTDSI__OE_SEL0) 
#define TEMP_PRTDSI__OE_SEL1        (* (reg8 *) TEMP__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TEMP_PRTDSI__OUT_SEL0       (* (reg8 *) TEMP__PRTDSI__OUT_SEL0) 
#define TEMP_PRTDSI__OUT_SEL1       (* (reg8 *) TEMP__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TEMP_PRTDSI__SYNC_OUT       (* (reg8 *) TEMP__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TEMP__SIO_CFG)
    #define TEMP_SIO_HYST_EN        (* (reg8 *) TEMP__SIO_HYST_EN)
    #define TEMP_SIO_REG_HIFREQ     (* (reg8 *) TEMP__SIO_REG_HIFREQ)
    #define TEMP_SIO_CFG            (* (reg8 *) TEMP__SIO_CFG)
    #define TEMP_SIO_DIFF           (* (reg8 *) TEMP__SIO_DIFF)
#endif /* (TEMP__SIO_CFG) */

/* Interrupt Registers */
#if defined(TEMP__INTSTAT)
    #define TEMP_INTSTAT            (* (reg8 *) TEMP__INTSTAT)
    #define TEMP_SNAP               (* (reg8 *) TEMP__SNAP)
    
	#define TEMP_0_INTTYPE_REG 		(* (reg8 *) TEMP__0__INTTYPE)
#endif /* (TEMP__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TEMP_H */


/* [] END OF FILE */
