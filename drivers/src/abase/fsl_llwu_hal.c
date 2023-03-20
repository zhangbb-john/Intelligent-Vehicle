/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_llwu_hal.h"
#if FSL_FEATURE_SOC_LLWU_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/
// Has PIN0 ~ PIN3
#define LLWU_HAS_PIN_0_3 \
    (FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN0 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN1 | \
     FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN2 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN3)
// Has PIN4 ~ PIN7
#define LLWU_HAS_PIN_4_7 \
    (FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN4 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN5 | \
     FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN6 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN7)
// Has PIN8 ~ PIN11
#define LLWU_HAS_PIN_8_11 \
    (FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN8 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN9 | \
     FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN10 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN11)
// Has PIN12 ~ PIN15
#define LLWU_HAS_PIN_12_15 \
    (FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN12 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN13 | \
     FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN14 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN15)
// Has PIN16 ~ PIN19
#define LLWU_HAS_PIN_16_19 \
    (FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN16 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN17 | \
     FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN18 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN19)
// Has PIN20 ~ PIN23
#define LLWU_HAS_PIN_20_23 \
    (FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN20 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN21 | \
     FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN22 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN23)
// Has PIN24 ~ PIN27
#define LLWU_HAS_PIN_24_27 \
    (FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN24 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN25 | \
     FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN26 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN27)
// Has PIN28 ~ PIN31
#define LLWU_HAS_PIN_28_31 \
    (FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN28 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN29 | \
     FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN30 | FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN31)

// Has PIN0 ~ PIN7
#define LLWU_HAS_PIN_0_7   \
    (LLWU_HAS_PIN_0_3   | LLWU_HAS_PIN_4_7)
// Has PIN8 ~ PIN15
#define LLWU_HAS_PIN_8_15  \
    (LLWU_HAS_PIN_8_11  | LLWU_HAS_PIN_12_15)
// Has PIN16 ~ PIN23
#define LLWU_HAS_PIN_16_23 \
    (LLWU_HAS_PIN_16_19 | LLWU_HAS_PIN_20_23)
// Has PIN24 ~ PIN31
#define LLWU_HAS_PIN_24_31 \
    (LLWU_HAS_PIN_24_27 | LLWU_HAS_PIN_28_31)

// Has PIN0 ~ PIN15
#define LLWU_HAS_PIN_0_15   \
    (LLWU_HAS_PIN_0_7   | LLWU_HAS_PIN_8_15)
// Has PIN16 ~ PIN31
#define LLWU_HAS_PIN_16_31 \
    (LLWU_HAS_PIN_16_23 | LLWU_HAS_PIN_24_31)

/*******************************************************************************
 * Code
 ******************************************************************************/

#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN
/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_SetExternalInputPinMode
 * Description   : Set external input pin source mode
 * This function will set the external input pin source mode that will be used
 * as wake up source.
 * 
 *END**************************************************************************/
void LLWU_HAL_SetExternalInputPinMode(LLWU_Type * base,
                                      llwu_external_pin_modes_t pinMode,
                                      llwu_wakeup_pin_t pinNumber)
{
#if (FSL_FEATURE_LLWU_REG_BITWIDTH == 8) // Register bit width is 8.
    /*-------------------------------------------------------------------------
      In 8-bit control register, every 2-bit controls one external pin. To set
      the proper register bit field, need to calculate the register and shift in
      register base on pinNumber.

                  X   X   X   X   X   X | X   X           <-- pinNumber
                  ----------------------|------
                  Used to get register  | Used to get shift in register

      Register: pinNumber>>2;
      Shift in register: (pinNumber & 0b11) << 1;

      For example, if pinNumber=1 (WUPE1), register and shift are like this
      -------------------------------------------------
      |   WUPE3   |   WUPE2   |   WUPE1   |   WUPE0   |   <-- Register
      -------------------------------------------------
                                          ^
                                          | Shift in register.

          0    0      0    0      1    1      0    0      <-- Bit mask.

    --------------------------------------------------------------------------*/
    uint32_t shiftInReg = (((uint8_t)pinNumber)&0x03U) << 1U;
    uint32_t bitMask    = 0x03U << shiftInReg;

    switch ((uint8_t)pinNumber >> 2U) // Which register to write to.
    {
#if (LLWU_HAS_PIN_0_3)
        case 0:
            LLWU_WR_PE1(base,
                    ((LLWU_RD_PE1(base) & ~bitMask) | ((uint32_t)pinMode << shiftInReg)));
            break;
#endif
#if (LLWU_HAS_PIN_4_7)
        case 1:
            LLWU_WR_PE2(base,
                    ((LLWU_RD_PE2(base) & ~bitMask) | ((uint32_t)pinMode << shiftInReg)));
            break;
#endif
#if (LLWU_HAS_PIN_8_11)
        case 2:
            LLWU_WR_PE3(base,
                    ((LLWU_RD_PE3(base) & ~bitMask) | ((uint32_t)pinMode << shiftInReg)));
            break;
#endif
#if (LLWU_HAS_PIN_12_15)
        case 3:
            LLWU_WR_PE4(base,
                    ((LLWU_RD_PE4(base) & ~bitMask) | ((uint32_t)pinMode << shiftInReg)));
            break;
#endif
#if (LLWU_HAS_PIN_16_19)
        case 4:
            LLWU_WR_PE5(base,
                    ((LLWU_RD_PE5(base) & ~bitMask) | ((uint32_t)pinMode << shiftInReg)));
            break;
#endif
#if (LLWU_HAS_PIN_20_23)
        case 5:
            LLWU_WR_PE6(base,
                    ((LLWU_RD_PE6(base) & ~bitMask) | ((uint32_t)pinMode << shiftInReg)));
            break;
#endif
#if (LLWU_HAS_PIN_24_27)
        case 6:
            LLWU_WR_PE7(base,
                    ((LLWU_RD_PE7(base) & ~bitMask) | ((uint32_t)pinMode << shiftInReg)));
            break;
#endif
#if (LLWU_HAS_PIN_28_31)
        case 7:
            LLWU_WR_PE8(base,
                    ((LLWU_RD_PE8(base) & ~bitMask) | ((uint32_t)pinMode << shiftInReg)));
            break;
#endif
        default:
            break;
    }
#else // Register bit width is 32.
    /*-------------------------------------------------------------------------
      In 32-bit control register, every 2-bit controls one external pin. To set
      the proper register bit field, need to calculate the register and shift in
      register base on pinNumber.
                  X   X   X   X | X   X   X   X           <-- pinNumber
                  -----------------------------
           Used to get register |  Used to get shift in register

      Register: pinNumber>>4;
      Shift in register: (pinNumber & 0b1111) << 1;

      For example, if pinNumber=1 (WUPE1), register and shift are like this
      -------------------------------------------------
      |   WUPE3   |   WUPE2   |   WUPE1   |   WUPE0   |   <-- Register
      -------------------------------------------------
                                          ^
                                          | Shift in register.

          0    0      0    0      1    1      0    0      <-- Bit mask.

    --------------------------------------------------------------------------*/
    uint32_t shiftInReg = (((uint8_t)pinNumber)&0x0FU) << 1U;
    uint32_t bitMask    = 0x03U << shiftInReg;

    switch ((uint8_t)pinNumber >> 4U) // Which register to write to.
    {
#if (LLWU_HAS_PIN_0_15)
        case 0:
            LLWU_WR_PE1(base,
                    ((LLWU_RD_PE1(base) & ~bitMask) | ((uint32_t)pinMode << shiftInReg)));
            break;
#endif
#if (LLWU_HAS_PIN_16_31)
        case 1:
            LLWU_WR_PE2(base,
                    ((LLWU_RD_PE2(base) & ~bitMask) | ((uint32_t)pinMode << shiftInReg)));
            break;
#endif
        default:
            break;
    }
#endif
}
#endif

#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE
/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_SetInternalModuleCmd
 * Description   : Enable/disable internal module source
 * This function will enable/disable the internal module source mode that will 
 * be used as wake up source. 
 * 
 *END**************************************************************************/
void LLWU_HAL_SetInternalModuleCmd(LLWU_Type * base, llwu_wakeup_module_t moduleNumber, bool enable)
{
    uint32_t bitMask = 1U << (uint8_t)moduleNumber;

    if (enable)
    {
        LLWU_WR_ME(base, (LLWU_RD_ME(base) | bitMask));
    }
    else
    {
        LLWU_WR_ME(base, (LLWU_RD_ME(base) & ~bitMask));
    }
}
#endif

#if FSL_FEATURE_LLWU_HAS_DMA_ENABLE_REG
/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_SetDmaCmd
 * Description   : Enable/disable DMA source.
 * This function will enable/disable the DMA that will be used as wake up source.
 *
 *END**************************************************************************/
void LLWU_HAL_SetDmaCmd(LLWU_Type * base, llwu_wakeup_dma_t dmaNumber, bool enable)
{
    uint32_t value = LLWU_RD_DE(base);
    uint32_t bit = 1U << (uint32_t)dmaNumber;

    if (enable)
    {
        value |= bit;
    }
    else
    {
        value &= ~bit;
    }

    LLWU_WR_DE(base, value);
}
#endif

#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN

/* For some platforms register LLWU_PF is used instead of LLWU_F. */
#if defined(LLWU_BRD_PF1_WUF0)
#define LLWU_RD_PINFLAG(reg) LLWU_RD_PF##reg
#else
#define LLWU_RD_PINFLAG(reg) LLWU_RD_F##reg
#endif

#if defined(LLWU_BWR_PF1_WUF0)
#define LLWU_WR_PINFLAG(reg) LLWU_WR_PF##reg
#else
#define LLWU_WR_PINFLAG(reg) LLWU_WR_F##reg
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_GetExternalPinWakeupFlag
 * Description   : Get external wakeup source flag
 * This function will get the external wakeup source flag for specific pin. 
 * 
 *END**************************************************************************/
bool LLWU_HAL_GetExternalPinWakeupFlag(LLWU_Type * base, llwu_wakeup_pin_t pinNumber)
{
#if (FSL_FEATURE_LLWU_REG_BITWIDTH == 8) // Register bit width is 8.
    uint8_t bitMask  = 0U;
    uint8_t bitInReg = 1U << ((uint8_t)pinNumber & 0x07U); // Which bit to check.

    switch (((uint32_t)pinNumber) >> 3U) // Which register to check.
    {
#if (LLWU_HAS_PIN_0_7)
        case 0: // PIN0 ~ PIN7
            bitMask = LLWU_RD_PINFLAG(1)(base);
            break;
#endif
#if (LLWU_HAS_PIN_8_15)
        case 1: // PIN8 ~ PIN15
            bitMask = LLWU_RD_PINFLAG(2)(base);
            break;
#endif
#if (LLWU_HAS_PIN_16_23)
        case 2: // PIN16 ~ PIN23
            bitMask = LLWU_RD_PINFLAG(3)(base);
            break;
#endif
#if (LLWU_HAS_PIN_24_31)
        case 3: // PIN24 ~ PIN31
            bitMask = LLWU_RD_PINFLAG(4)(base);
            break;
#endif
        default:
            break;
    }
    return (bitInReg & bitMask) ? true : false;
#else
    return (LLWU_RD_PF(base) & (1U<<((uint8_t)pinNumber))) ? true : false;
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_ClearExternalPinWakeupFlag
 * Description   : Clear external wakeup source flag
 * This function will clear the external wakeup source flag for specific pin.
 * 
 *END**************************************************************************/
void LLWU_HAL_ClearExternalPinWakeupFlag(LLWU_Type * base, llwu_wakeup_pin_t pinNumber)
{
#if (FSL_FEATURE_LLWU_REG_BITWIDTH == 8) // Register bit width is 8.
    uint8_t bitInReg = 1U << ((uint8_t)pinNumber & 0x07U); // Which bit to clear.

    switch (((uint32_t)pinNumber) >> 3U) // Which register to check.
    {
#if (LLWU_HAS_PIN_0_7)
        case 0: // PIN0 ~ PIN7
            LLWU_WR_PINFLAG(1)(base, bitInReg);
            break;
#endif
#if (LLWU_HAS_PIN_8_15)
        case 1: // PIN8 ~ PIN15
            LLWU_WR_PINFLAG(2)(base, bitInReg);
            break;
#endif
#if (LLWU_HAS_PIN_16_23)
        case 2: // PIN16 ~ PIN23
            LLWU_WR_PINFLAG(3)(base, bitInReg);
            break;
#endif
#if (LLWU_HAS_PIN_24_31)
        case 3: // PIN24 ~ PIN31
            LLWU_WR_PINFLAG(4)(base, bitInReg);
            break;
#endif
        default:
            break;
    }
#else
    LLWU_WR_PF(base, 1U<<(uint8_t)pinNumber);
#endif
}
#endif

#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE

#if (FSL_FEATURE_LLWU_REG_BITWIDTH == 8)

#if FSL_FEATURE_LLWU_HAS_MF
#define LLWU_RD_MODULE_FLAG LLWU_RD_MF5
#else
#define LLWU_RD_MODULE_FLAG LLWU_RD_F3
#endif

#else

#define LLWU_RD_MODULE_FLAG LLWU_RD_MF

#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_GetInternalModuleWakeupFlag
 * Description   : Get internal module wakeup source flag
 * This function will get the internal module wakeup source flag for specific 
 * module
 * 
 *END**************************************************************************/
bool LLWU_HAL_GetInternalModuleWakeupFlag(LLWU_Type * base, llwu_wakeup_module_t moduleNumber)
{
#if (FSL_FEATURE_LLWU_REG_BITWIDTH == 8)  // Bit width is 8
    uint8_t bitMask = (uint8_t)(1U << (uint8_t)moduleNumber);
#else // Bit width is 32.
    uint32_t bitMask = (uint32_t)(1U << (uint8_t)moduleNumber);
#endif

    return (LLWU_RD_MODULE_FLAG(base) & bitMask) ?  true : false;
}
#endif

#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN

#if (FSL_FEATURE_LLWU_REG_BITWIDTH == 32) // Register bit width is 32.
/* Mask for FILT[FILTFx]. */
#define LLWU_FILT_FILTFx_MASK (LLWU_FILT_FILTF1_MASK | \
                               LLWU_FILT_FILTF2_MASK | \
                               LLWU_FILT_FILTF3_MASK | \
                               LLWU_FILT_FILTF4_MASK)
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_SetPinFilterMode
 * Description   : Set pin filter configuration
 * This function will set the pin filter configuration.
 * 
 *END**************************************************************************/
void LLWU_HAL_SetPinFilterMode(LLWU_Type * base,
                               uint32_t filterNumber,
                               llwu_external_pin_filter_mode_t pinFilterMode)
{
    /* check filter and pin number */
    assert(filterNumber < FSL_FEATURE_LLWU_HAS_PIN_FILTER);

#if (FSL_FEATURE_LLWU_REG_BITWIDTH == 8) // Register bit width is 8.
    /* branch to filter number */
    switch(filterNumber)
    {
#if (FSL_FEATURE_LLWU_HAS_PIN_FILTER >= 1)
    case 0:
        LLWU_BWR_FILT1_FILTSEL(base, pinFilterMode.pinNumber);
        LLWU_BWR_FILT1_FILTE(base, pinFilterMode.filterMode);
        break;
#endif
#if (FSL_FEATURE_LLWU_HAS_PIN_FILTER >= 2)
    case 1:
        LLWU_BWR_FILT2_FILTSEL(base, pinFilterMode.pinNumber);
        LLWU_BWR_FILT2_FILTE(base, pinFilterMode.filterMode);
        break;
#endif
#if (FSL_FEATURE_LLWU_HAS_PIN_FILTER >= 3)
    case 2:
        LLWU_BWR_FILT3_FILTSEL(base, pinFilterMode.pinNumber);
        LLWU_BWR_FILT3_FILTE(base, pinFilterMode.filterMode);
        break;
#endif
#if (FSL_FEATURE_LLWU_HAS_PIN_FILTER >= 4)
    case 3:
        LLWU_BWR_FILT4_FILTSEL(base, pinFilterMode.pinNumber);
        LLWU_BWR_FILT4_FILTE(base, pinFilterMode.filterMode);
        break;
#endif
    default:
        break;
    }
#else
    /* First, the pinNumber and the filterMode construct a 7-bit data.

                   7-bit data = (filterMode << 5) | pinNumber;

       Then the data left shift and set to the right place according to
       parameter filterNumber. For filterNumber 0/1/2/3, the left shift
       value is 0/8/16/24. */

    uint32_t shift = filterNumber << 3U; // Left shift value.

    uint32_t data = LLWU_FILT_FILTSEL1(pinFilterMode.pinNumber) |
                    LLWU_FILT_FILTE1(pinFilterMode.filterMode);

    uint32_t mask = LLWU_FILT_FILTFx_MASK |
        ((LLWU_FILT_FILTSEL1_MASK | LLWU_FILT_FILTE1_MASK) << shift);

    LLWU_WR_FILT(base, (LLWU_RD_FILT(base) & ~mask) | (data << shift));
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_GetFilterDetectFlag
 * Description   : Get filter detect flag
 * This function will get the filter detect flag.
 * 
 *END**************************************************************************/
bool LLWU_HAL_GetFilterDetectFlag(LLWU_Type * base, uint32_t filterNumber)
{
    bool retValue = false;

    /* check filter and pin number */
    assert(filterNumber < FSL_FEATURE_LLWU_HAS_PIN_FILTER);

#if (FSL_FEATURE_LLWU_REG_BITWIDTH == 8) // Register bit width is 8.
    /* branch to filter number */
    switch(filterNumber)
    {
#if (FSL_FEATURE_LLWU_HAS_PIN_FILTER >= 1)
    case 0:
        retValue = (bool)LLWU_BRD_FILT1_FILTF(base);
        break;
#endif
#if (FSL_FEATURE_LLWU_HAS_PIN_FILTER >= 2)
    case 1:
        retValue = (bool)LLWU_BRD_FILT2_FILTF(base);
        break;
#endif
#if (FSL_FEATURE_LLWU_HAS_PIN_FILTER >= 3)
    case 2:
        retValue = (bool)LLWU_BRD_FILT3_FILTF(base);
        break;
#endif
#if (FSL_FEATURE_LLWU_HAS_PIN_FILTER >= 4)
    case 3:
        retValue = (bool)LLWU_BRD_FILT4_FILTF(base);
        break;
#endif
    default:
        retValue = false;
        break;
    }
#else
    /* For flag 0, 1, 2, 3, check the bit 7, 15, 23, 31. */
    retValue = (LLWU_RD_FILT(base) & (1U << ((filterNumber << 3U) + 7U))) ? true : false;
#endif

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_ClearFilterDetectFlag
 * Description   : Clear filter detect flag
 * This function will clear the filter detect flag.
 * 
 *END**************************************************************************/
void LLWU_HAL_ClearFilterDetectFlag(LLWU_Type * base, uint32_t filterNumber)
{
    /* check filter and pin number */
    assert(filterNumber < FSL_FEATURE_LLWU_HAS_PIN_FILTER);

#if (FSL_FEATURE_LLWU_REG_BITWIDTH == 8) // Register bit width is 8.
    /* branch to filter number */
    switch(filterNumber)
    {
#if (FSL_FEATURE_LLWU_HAS_PIN_FILTER >= 1)
    case 0:
        LLWU_BWR_FILT1_FILTF(base, 1U);
        break;
#endif
#if (FSL_FEATURE_LLWU_HAS_PIN_FILTER >= 2)
    case 1:
        LLWU_BWR_FILT2_FILTF(base, 1U);
        break;
#endif
#if (FSL_FEATURE_LLWU_HAS_PIN_FILTER >= 3)
    case 2:
        LLWU_BWR_FILT3_FILTF(base, 1U);
        break;
#endif
#if (FSL_FEATURE_LLWU_HAS_PIN_FILTER >= 4)
    case 3:
        LLWU_BWR_FILT4_FILTF(base, 1U);
        break;
#endif
    default:
        break;
    }
#else
    /* For flag 0, 1, 2, 3, write 1 to the bit 7, 15, 23, 31. */
    LLWU_WR_FILT(base, (LLWU_RD_FILT(base) & ~LLWU_FILT_FILTFx_MASK)
                                           | (1U << ((filterNumber << 3U) + 7U)));
#endif
}
#endif

#if FSL_FEATURE_LLWU_HAS_RESET_ENABLE
/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_SetResetPinMode
 * Description   : Set RESET pin mode.
 * This function will set the RESET pin mode.
 * 
 *END**************************************************************************/
void LLWU_HAL_SetResetPinMode(LLWU_Type * base, llwu_reset_pin_mode_t resetPinMode)
{
    LLWU_WR_RST(base, LLWU_RST_RSTFILT(resetPinMode.filter) |
                      LLWU_RST_LLRSTE(resetPinMode.enable));
}
#endif
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

