/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#ifndef __FSL_HSADC_HAL_H__
#define __FSL_HSADC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup hsadc_hal
 * @{
 */

/******************************************************************************
 * Enumerations.
 *****************************************************************************/

/*! @brief Defines the type to enumerate ADC converter's scan mode. */
typedef enum _hsadc_scan_mode
{
    kHSAdcScanOnceSequential      = 0U, /*!< Once (single) sequential. @internal gui name="Once sequential" */
    kHSAdcScanOnceParallel        = 1U, /*!< Once parallel. @internal gui name="Once parallel" */
    kHSAdcScanLoopSequential      = 2U, /*!< Loop sequential. @internal gui name="Loop sequential" */
    kHSAdcScanLoopParallel        = 3U, /*!< Loop parallel. @internal gui name="Loop parallel" */
    kHSAdcScanTriggeredSequential = 4U, /*!< Triggered sequential. @internal gui name="Triggered sequential" */
    kHSAdcScanTriggeredParalled   = 5U  /*!< Triggered parallel (default). @internal gui name="Triggered parallel" */
} hsadc_scan_mode_t;

/*!
 * @brief Defines the type of DMA trigger source for each converter.
 *
 * During sequential and simultaneous parallel scan modes CTRL3[DMASRC] selects 
 * between EOSIA and RDY bits as the DMA source. During non-simultaneous parallel 
 * scan mode CTRL3[DMASRC] selects between EOSIA/EOSIB for converters A and B, 
 * and the RDY bits as the DMA source. 
 */
typedef enum _hsadc_dma_trigger_src
{
    kHSAdcDmaTriggeredByEndOfScan = 0U, /*!< DMA trigger source is end of scan interrupt. @internal gui name="End of scan" */
    kHSAdcDmaTriggeredByConvReady = 1U  /*!< DMA trigger source is RDY status. @internal gui name="Conversion ready" */
} hsadc_dma_trigger_src_t;

/*!
 * @breif Defines the type of ADC conversion resolution.
 *
 * Selects the conversion result resolution for the converter A and B. 
 */
typedef enum _hsadc_resolution_mode
{
    kHSAdcResolutionBitOf6  = 0U, /*!< 6-bit mode @internal gui name="6-bit" */
    kHSAdcResolutionBitOf8  = 1U, /*!< 8-bit mode @internal gui name="8-bit" */
    kHSAdcResolutionBitOf10 = 2U, /*!< 10-bit mode @internal gui name="10-bit" */
    kHSAdcResolutionBitOf12 = 3U  /*!< 12-bit mode @internal gui name="12-bit" */
} hsadc_resolution_mode_t;

/*! @brief Defines the converter number */
#define HSADC_CONV_NUMBER 2U

/*! @brief Defines the identifier for converter A and B. */ 
typedef enum _hsadc_conv_id
{
    kHSAdcConvA = 0U,  /*!< Converter A's identifier. @internal gui name="Converter A" */
    kHSAdcConvB = 1U   /*!< Converter B's identifier. @internal gui name="Converter B" */
} hsadc_conv_id_t;

/*!
 * @brief Defines the bit mask to represent the working mode of a specific channel pair.
 *
 * Following const value represents the bit mask to configure the working mode of 
 * the channel pair. If the bit mask is set, the channel pair work as differential mode. 
 * Otherwise they both work as single-ended mode. If channel is selected in differential 
 * mode for example HSADC_DIFF_MODE_ANA0_ANA1_MASK is set, the first channel for 
 * example ANA0 is positive electrode and the second channel for example ANA1 is 
 * negetive electrode. The bit mask is set in the parameter "mode" of the API "HSADC_HAL_SetChnMode".
 */
#define HSADC_DIFF_MODE_ANA0_ANA1_MASK 0x01U/*!< Working mode of channels ANA0 and ANA1 */
#define HSADC_DIFF_MODE_ANA2_ANA3_MASK 0x02U/*!< Working mode of channels ANA2 and ANA3 */
#define HSADC_DIFF_MODE_ANB0_ANB1_MASK 0x04U/*!< Working mode of channels ANB0 and ANB1 */
#define HSADC_DIFF_MODE_ANB2_ANB3_MASK 0x08U/*!< Working mode of channels ANB2 and ANB3 */
#define HSADC_DIFF_MODE_ANA4_ANA5_MASK 0x10U/*!< Working mode of channels ANA4 and ANA5 */
#define HSADC_DIFF_MODE_ANA6_ANA7_MASK 0x20U/*!< Working mode of channels ANA6 and ANA7 */
#define HSADC_DIFF_MODE_ANB4_ANB5_MASK 0x40U/*!< Working mode of channels ANB4 and ANB5 */
#define HSADC_DIFF_MODE_ANB6_ANB7_MASK 0x80U/*!< Working mode of channels ANB6 and ANB7 */

/*!
 * @brief Defines the channel 6/7's input multiplex.
 *
 * Control the 8-1 MUX to select an input to the channel 6/7 for converter A and B.
 */
typedef enum _hsadc_chn67_mux_sel
{
    kHSAdcChn67Mux6_7     = 0U,/*!< Select the input pin as ANA6-ANA7 or ANB6-ANB7 @internal gui name="Mux6_7" */
    kHSAdcChn67Mux8_9     = 1U,/*!< Select the input pin as ANA8-ANA9 or ANB8-ANB9 @internal gui name="Mux8_9" */
    kHSAdcChn67Mux10_11   = 2U,/*!< Select the input pin as ANA10-ANA11 or ANB10-ANB11 @internal gui name="Mux10_11" */
    kHSAdcChn67Mux12_13   = 3U,/*!< Select the input pin as ANA12-ANA13 or ANB12-ANB13 @internal gui name="Mux12_13" */
    kHSAdcChn67Mux14_15   = 4U,/*!< Select the input pin as ANA14-ANA15 or ANB14-ANB15 @internal gui name="Mux14_15" */
    kHSAdcChn67Mux16_17   = 5U,/*!< Select the input pin as ANA16-ANA17 or ANB16-ANB17 @internal gui name="Mux16_17" */
    kHSAdcChn67Mux18_vref = 6U /*!< Select the input pin as ANA18-VREF or ANB18-VREF @internal gui name="Mux18_vref" */
} hsadc_chn67_mux_sel_t;

/*! @brief Defines the slot number. */
#define HSADC_SLOT_NUMBER 16U

/*! @brief Defines the channel which is sampled by a specific slot. If channel is
 * selected in differential mode for example kHSAdcSampleANA0__ANA0_ANA1 is select
 * and ANA0_ANA1 is in differential mode which is set by HSADC_HAL_SetChnMode, 
 * the first channel for example ANA0 is positive electrode and the second channel
 * for example ANA1 is negetive electrode.
 */
typedef enum _hsadc_slot_sample_chn
{
    kHSAdcSlotSampleANA0__ANA0_ANA1 = 0U, /*!< The slot samples ANA0 in single 
                                 ended mode or ANA0_ANA1 in differential mode @internal gui name="ANA0__ANA0_ANA1" */
    kHSAdcSlotSampleANA1__ANA0_ANA1 = 1U, /*!< The slot samples ANA1 in single 
                                 ended mode or ANA0_ANA1 in differential mode @internal gui name="ANA1__ANA0_ANA1" */
    kHSAdcSlotSampleANA2__ANA2_ANA3 = 2U, /*!< The slot samples ANA2 in single 
                                 ended mode or ANA2_ANA3 in differential mode @internal gui name="ANA2__ANA2_ANA3" */
    kHSAdcSlotSampleANA3__ANA2_ANA3 = 3U, /*!< The slot samples ANA3 in single 
                                 ended mode or ANA2_ANA3 in differential mode @internal gui name="ANA3__ANA2_ANA3" */
    kHSAdcSlotSampleANA4__ANA4_ANA5 = 4U, /*!< The slot samples ANA4 in single 
                                 ended mode or ANA4_ANA5 in differential mode @internal gui name="ANA4__ANA4_ANA5" */
    kHSAdcSlotSampleANA5__ANA4_ANA5 = 5U, /*!< The slot samples ANA5 in single 
                                 ended mode or ANA4_ANA5 in differential mode @internal gui name="ANA5__ANA4_ANA5" */
    kHSAdcSlotSampleANA6__ANA6_ANA7 = 6U, /*!< The slot samples ANA6 in single 
                                 ended mode or ANA6_ANA7 in differential mode @internal gui name="ANA6__ANA6_ANA7" */
    kHSAdcSlotSampleANA7__ANA6_ANA7 = 7U, /*!< The slot samples ANA7 in single 
                                 ended mode or ANA6_ANA7 in differential mode @internal gui name="ANA7__ANA6_ANA7" */
    kHSAdcSlotSampleANB0__ANB0_ANB1 = 8U, /*!< The slot samples ANB0 in single 
                                 ended mode or ANB0_ANB1 in differential mode @internal gui name="ANB0__ANB0_ANB1" */
    kHSAdcSlotSampleANB1__ANB0_ANB1 = 9U, /*!< The slot samples ANB1 in single 
                                 ended mode or ANB0_ANB1 in differential mode @internal gui name="ANB1__ANB0_ANB1" */
    kHSAdcSlotSampleANB2__ANB2_ANB3 = 10U, /*!< The slot samples ANB2 in single 
                                 ended mode or ANB2_ANB3 in differential mode @internal gui name="ANB2__ANB2_ANB3" */
    kHSAdcSlotSampleANB3__ANB2_ANB3 = 11U, /*!< The slot samples ANB3 in single 
                                 ended mode or ANB2_ANB3 in differential mode @internal gui name="ANB3__ANB2_ANB3" */
    kHSAdcSlotSampleANB4__ANB4_ANB5 = 12U, /*!< The slot samples ANB4 in single 
                                 ended mode or ANB4_ANB5 in differential mode @internal gui name="ANB4__ANB4_ANB5" */
    kHSAdcSlotSampleANB5__ANB4_ANB5 = 13U, /*!< The slot samples ANB5 in single 
                                 ended mode or ANB4_ANB5 in differential mode @internal gui name="ANB5__ANB4_ANB5" */
    kHSAdcSlotSampleANB6__ANB6_ANB7 = 14U, /*!< The slot samples ANB6 in single 
                                 ended mode or ANB6_ANB7 in differential mode @internal gui name="ANB6__ANB6_ANB7" */
    kHSAdcSlotSampleANB7__ANB6_ANB7 = 15U  /*!< The slot samples ANB7 in single 
                                 ended mode or ANB6_ANB7 in differential mode @internal gui name="ANB7__ANB6_ANB7" */
} hsadc_slot_sample_chn_t;

/*! @brief Defines the type to enumerate the zero crossing detection mode for each slot. */
typedef enum _hsadc_zero_cross_mode
{
    kHSAdcZeroCrossDisable        = 0U,/*!< Zero crossing detection disabled. @internal gui name="Disable" */
    kHSAdcZeroCrossAtFallingEdge  = 1U,/*!< Enable for positive to negative sign change. @internal gui name="Falling edge" */
    kHSAdcZeroCrossAtRisingEdge   = 2U,/*!< Enable for negative to positive sign change. @internal gui name="Rising edge" */
    kHSAdcZeroCrossAtBothEdge     = 3U /*!< Enable for any sign change. @internal gui name="Both edges" */
} hsadc_zero_cross_mode_t;

/*! @brief Defines the interrupt source enablement bit mask for converter A and B. */ 
typedef enum _hsadc_conv_int_src
{
    kHSAdcConvEndOfScanInt        = 0x01U, /*!< End of scan interrupt */
    kHSAdcConvEndOfCalibrationInt = 0x02U, /*!< End of calibration interrupt */
    kHSAdcConvAllInt              = 0x03U  /*!< All interrupts */
} hsadc_conv_int_src_t;

/*! @brief Defines the interrupt source enablement bit mask for all slots */
typedef enum _hsadc_slot_int_src
{
    kHSAdcSlotZeroCrossInt = 0x01U,   /*!< Global zero crossing interrupt */ 
    kHSAdcSlotLowLimitInt  = 0x02U,   /*!< Global low limit interrupt */
    kHSAdcSlotHighLimitInt = 0x04U,   /*!< Global high limit interrupt */
    kHSAdcSlotAllInt       = 0x07U    /*!< All global interrupts */
} hsadc_slot_int_src_t;

/*! @brief Defines the enablement command for converter A and B. */
typedef enum _hsadc_conv_enable_cmd
{
    kHSAdcConvSyncInputEnable          = 0U,/*!< Enable or disable hardware trigger */
    kHSAdcConvStopEnable               = 1U,/*!< Enable or disable to stop converter */
    kHSAdcConvPowerDownEnable          = 2U,/*!< Enable or disable to power down converter */
    kHSAdcConvCalibrationBypassEnable  = 3U /*!< Enable or disable to bypass calibration block */
} hsadc_conv_enable_cmd_t;

/*! @brief Defines the enablement command for specific slot. */
typedef enum _hsadc_slot_enable_cmd
{
    kHSAdcSlotDisable        = 0U, /*!< Disable or Enable some slots */
    kHSAdcSlotWaitSyncEnable = 1U, /*!< Enable or disable the specific slot to 
               delay until a new sync input occurs when it samples completely */
    kHSAdcSlotScanIntEnable  = 2U  /*!< Enable or disable the specific slot to 
                               trigger interrupt when it scans complete */
} hsadc_slot_enable_cmd_t;

/*!
 * @brief Defines the ADC converter's flags.
 *
 * This type defines all kinds of flags for ADC converter.
 */ 
typedef enum _hsadc_conv_flag
{
    kHSAdcConvCalibrationRunning          = 0U,/*!< Calibration is running */
    kHSAdcConvDummyConversionRunning      = 1U,/*!< Dummy Conversion is running */
    kHSAdcConvEndOfCalibrationIntHappened = 2U,/*!< End of calibration interrupt has happened */
    kHSAdcConvEndOfScanIntHappened        = 3U,/*!< End of scan interrupt has happened */
    kHSAdcConvConversionInProgress        = 4U,/*!< Converter's scan is in progress */
    kHSAdcConvPowerStatusStable           = 5U /*!< Converter is currently power down */
} hsadc_conv_flag_t;

/*!
 * @brief Defines the global flags for all slots.
 *
 * This type defines the global flag for all slots. The detail flag for each slot
 * can be found in hsadc_specific_slot_flag_t.
 */
typedef enum _hsadc_global_slot_flag
{
    kHSAdcGlobalSlotHighLimitIntHappened = 0U,/*!< Global high limit interrupt happened */
    kHSAdcGlobalSlotLowLimitIntHappened  = 1U,/*!< Global low limit interrupt happened */
    kHSAdcGlobalSlotZeroCrossIntHappened = 2U /*!< Global zero crossing interrupt happened */
} hsadc_global_slot_flag_t;

 /*!
  * @brief Defines the flag for specific slot.
  *
  * This type defines all kinds of flags for specific slot.
  */
typedef enum _hsadc_specific_slot_flag
{             
    kHSAdcSpecificSlotHighLimitIntHappened = 0U,/*!< Specific high limit interrupt happened */
    kHSAdcSpecificSlotLowLimitIntHappened  = 1U,/*!< Specific low limit interrupt happened */
    kHSAdcSpecificSlotZeroCrossIntHappened = 2U,/*!< Specific zero crossing interrupt happened */
    kHSAdcSpecificSlotResultReady          = 3U /*!< Conversion result has generated */
} hsadc_specific_slot_flag_t;

/*! @brief Defines the calibration type for converter A/B */
typedef enum _hsadc_calibration_mode
{
    kHSAdcCalibrationSingleEnded  = 0U,       /*!< Single ended mode calibration @internal gui name="Single ended" */
    kHSAdcCalibrationDifferential = 1U,       /*!< Differential mode calibration @internal gui name="Differential" */
    kHSAdcCalibrationBoth         = 2U        /*!< Single and differential calibration @internal gui name="Both" */
} hsadc_calibration_mode_t;


/******************************************************************************
 * Definitions.
 *****************************************************************************/

/*! 
 * @brief Defines the core configuration structure for HSADC module. 
 *
 * It mainly has two parts: Common configuration between converter A and B/
 * Individual configuration for converter A and B. If below configuration item is an 
 * array, it represents that the first one is for converter A and the second one is 
 * for converter B.
 * @internal gui name="Core configuration" id="hsadcCoreCfg"
 */
typedef struct HSAdcCoreConfig
{
    /* Common configuration between converter A and converter B. */
    hsadc_scan_mode_t scanMode;    /*!< ADC scan mode control. @internal gui name="Scan mode" id="ScanMode" */
    bool parallelSimultModeEnable; /*!< Parallel scans done simultaneously enable. @internal gui name="Parallel simultaneous mode" id="ParallelSimultModeEnable" */
    hsadc_dma_trigger_src_t dmaTriggerSrc;/*!< DMA trigger source. @internal gui name="DMA trigger" id="DmaTriggerSrc" */
    bool autoStandbyEnable;        /*!< Auto standby mode enable. @internal gui name="Auto standby " id="AutoStandbyEnable" */
    uint16_t powerUpDelayCount;    /*!< Power up delay. @internal gui name="Power up delay count" id="PowerUpDelayCount" */
    bool autoPowerDownEnable;      /*!< Auto power down mode enable. @internal gui name="Auto power down" id="AutoPowerDownEnable" */
    hsadc_resolution_mode_t convResolution;/*!< Selects the converter's resolution. @internal gui name="Resolution" id="ConvResolution" */
    
    
    /* Configuration of individual converter. */
    uint16_t clkDivValue[HSADC_CONV_NUMBER];    /*!< Clock divider from the bus clock. @internal gui name="Clock divider" id="ClkDivValue" range="0..63" */
    uint16_t samplingTime[HSADC_CONV_NUMBER];   /*!< Sampling time. @internal gui name="Sampling time" id="SamplingTime" range="0..255" */     
} hsadc_core_config_t;


#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/* Reset and init functions. */
/*!
 * @brief Resets the HSADC module. 
 * 
 * This function resets the HSADC module to the default value. The reset state is:
 * 1. Disable all DMA/Interrupt/hardware trigger.
 * 2. Set all channels work in single ended mode.
 * 3. Default working mode of converter A and B is triggered parallel.
 * 4. Enable hardware trigger/simultanious mode for converter A and B.
 * 5. Enable stop mode for converter A/B.
 * 6. Default clock divisor for converter A and B is 5.
 * 7. Disable the zero cross mode of all slots.
 * 8. Set all slots to sample ANA0 in single ended mode or ANA0_ANA1 in differential mode.
 * 9. Enable all slots.
 * 10. Clear all flags.
 * 11. Set the low limit value of all slots to 0.
 * 12. Set the high limit value of all slots to 0xFFFF.
 * 13. Power down converter A/B.
 * 14. Disable every slot to delay until a new sync input occurs.
 * 15. Select 12 bit resolution. 
 * 16. Select DMA trigger source as end of scan interrupt.
 * 17. Scan interrupt is not enabled for every slot.
 * 18. Set sample time of converter A and B to 0
 * 19. Disable calibration bypass for converter A/B.
 * 20. Set single ended mode and differential mode calibration result to 0.
 * 21. Set the mux selector of channel 67 of converter A/B to ANA6-ANA7/ANB6-ANB7.
 * 
 * @param base Register base address for the module.
 */
void HSADC_HAL_Init(HSADC_Type * base);

/*!
 * @brief Configures the HSADC module.
 *
 * This function configures the HSADC module according to the user input.
 *
 * @param base Register base address for the module.
 * @param configPtr The configuration structure which contains the user's configuration.
 */
void HSADC_HAL_Config(HSADC_Type* base, const hsadc_core_config_t* configPtr);

/* Dynamically set/get functions. */
/*!
 * @brief Sets the working mode for all the channels from ANA0 to ANB7.
 *
 * This function sets all the channels to work at single ended mode or differential
 * mode by using the logical or of bit mask from HSADC_DIFF_MODE_ANA0_ANA1_MASK to
 * HSADC_DIFF_MODE_ANB6_ANB7_MASK.
 *
 * @param base Register base address for the module.
 * @param modeMask The logical or of the bit mask of channels' working mode.
 */
static inline void HSADC_HAL_SetChnMode(HSADC_Type* base, uint16_t modeMask)
{
    /* The low half byte of modeMask is for CHNCFG_L, 
    the high half byte of modeMask is for CHNCFG_H. */
    HSADC_WR_CTRL1_CHNCFG_L(base, (modeMask & 0x0FU));
    HSADC_WR_CTRL2_CHNCFG_H(base, ((modeMask & 0xF0U)>>4U));
}

/*!
 * @brief Sets the multiplex channel of channel 6/7 for converter A/B.
 *
 * This function sets the multiplex channel of the channel 6/7 for converter A/B.
 *
 * @param base Register base address for the module.
 * @param convId Converter identifier, channel 6/7's mux of which will be select.
 * @param muxSel The multiplex channel's number.
 */
void HSADC_HAL_SetChn67MuxSel(HSADC_Type* base, hsadc_conv_id_t convId, 
                      hsadc_chn67_mux_sel_t muxSel);

/*!
 * @brief Sets the sample channel for specific slots.
 *
 * This function sets the sample channel for specific slots numbered from 0 ~ 15.
 * In differernt scan mode, the channel which can be sampled by the slot is different.
 * In sequential mode, any slot can sample any channel of converter A(ANA0 to ANA7)
 * at a certain time. Any slot also can sample any channel of converter B(ANB0 to
 * ANB7) in other time. The converter A and B can't work parallelly. The scan starts
 * from slot 0(CLIST1[SAMPLE0]) until the first disabled slot is encountered.
 * In parallel none simultaneous mode, slot(0 to 7) can reference only the channel 
 * of converter A(ANA0 to ANA7). slot(8 to 15) can reference only the channel of
 * converter B(ANB0 to ANB7). The two converter A/B can work parallelly. The scan 
 * in both converters terminates when either converter encounters a disabled sample slot.
 * In parallel simultaneous mode, slot(0 to 7) can reference only the channel 
 * of converter A(ANA0 to ANA7). slot(8 to 15) can reference only the channel of
 * converter B(ANB0 to ANB7). The two converter A/B can work parallelly.  Each 
 * converter's scan completes when a disabled sample is encountered in that converter's 
 * sample list only.
 *
 * @param base Register base address for the module.
 * @param slotIdx The specific slot numbered from 0 ~ 15.
 * @param channel The analog input channel.
 */
void HSADC_HAL_SetSlotSampleChn(HSADC_Type* base, uint16_t slotIdx, 
                        hsadc_slot_sample_chn_t channel);

/*!
 * @brief Sets the threshold value for specific slot.
 *
 * This function sets the low limit value and high limit value of conversion 
 * result for specific slot. The value can be used to trigger low limit interrupt
 * and high limit interrupt.
 *
 * @param base Register base address for the module.
 * @param slotIdx The specific slot numbered from 0 to 15.
 * @param lowLimit The low limit value.
 * @param highLimit The high limit value.
 */
static inline void HSADC_HAL_SetSlotThreshold(HSADC_Type* base, 
                                      uint16_t slotIdx, 
                                      uint16_t lowLimit, 
                                      uint16_t highLimit)
{
    HSADC_WR_LOLIM(base, slotIdx, lowLimit);
    HSADC_WR_HILIM(base, slotIdx, highLimit);
}
 
/*!
 * @brief Sets the offset value for conversion result.
 *
 * This function sets the offset value for the conversion result. The final result
 * in the result register is got by using conversion result to subtract this offset.
 *
 * @param base Register base address for the module.
 * @param slotIdx The specific slot numbered from 0 to 15.
 * @param offset The offset value.
 */
static inline void HSADC_HAL_SetSlotOffset(HSADC_Type* base, uint16_t slotIdx, 
                                   uint16_t offset)
{
    HSADC_WR_OFFST(base, slotIdx, offset);
}

/*!
 * @brief Ses the zero crossing mode for the specific slot.
 *
 * This function sets the zero crossing mode for all the slots numbered from
 * 0 to 15. ZeroCrossing mode for each slot can be used to trigger zero crossing
 * interrupt to detect the sign of the conversion result change. User only need to
 * pass in logical or of some bit mask as the definition of HSADC_ZERO_CROSS_MODE_MASK.
 *
 * @param base Register base address for the module.
 * @param slotIdx The specific slot numbered from 0 to 15.
 * @param zeroCrossMode Bits mask of zero crossing mode for each slot.
 */
void HSADC_HAL_SetSlotZeroCrossMode(HSADC_Type* base, uint16_t slotIdx, 
                            hsadc_zero_cross_mode_t zeroCrossMode);

/*!
 * @brief Sets to enable or disable the specific interrupt for converter.
 *
 * This function sets to enable or disable the specific interrupt which is defined 
 * in hsadc_conv_int_src_t.
 *
 * @param base Register base address for the module.
 * @param convId The converter identifier.
 * @param intMask The mask contains the interrupt which will be enabled/disabled.
 * @param enable True to enable the interrupt. False to disable the interrupt.
 */
void HSADC_HAL_SetConvIntCmd(HSADC_Type* base, 
                     hsadc_conv_id_t convId, 
                     uint32_t intMask, 
                     bool enable);

/*!
 * @brief Sets to enable or disable the specific interrupt for all slots.
 *
 * This function sets to enable or disable the specific interrupt which is defined
 * in hsadc_slot_int_src_t.
 *
 * @param base Register base address for the module.
 * @param intMask The mask used to contain the interrupt which will be enabled/disabled.
 * @param enable True to enable the interrupt. False to disable the interrupt.
 */
void HSADC_HAL_SetSlotIntCmd(HSADC_Type* base, uint32_t intMask, bool enable);

/*!
 * @brief Sets to enable or disable the DMA for converter A/B.
 *
 * This function sets to enable or disable the DMA for specific converter.
 *
 * @param base Register base address for the module.
 * @param convId The converter identifier.
 * @param enable True to enable the dma. False to disable the dma.
 */
void HSADC_HAL_SetConvDmaCmd(HSADC_Type* base, hsadc_conv_id_t convId, bool enable);

/*!
 * @brief Sets the enablement command for converter A/B.
 *
 * This function sets to enable or disable the enablement command which is defined 
 * in hsadc_conv_enable_cmd_t.
 * 
 * @param base Register base address for the module.
 * @param convId The converter identifier.
 * @param cmd The specific command of converter A/B.
 * @param enable True to enable the specific command. False to disable the specific command.
 */
void HSADC_HAL_SetConvEnableCmd(HSADC_Type* base, 
                        hsadc_conv_id_t convId, 
                        hsadc_conv_enable_cmd_t cmd, 
                        bool enable);

/*!
 * @brief Sets to enable or disable the enablement command for specific slots.
 *
 * This function sets to enable or disable the specific command which is defined 
 * in hsadc_slot_enable_cmd_t. The slots is defined in slotMask in the following 
 * parameters. Bit 0 in the slotMask represents slot numbered 0. Bit 15 in the 
 * slotMask represents slot numbered 15.  
 * 
 * @param base Register base address for the module.
 * @param slotMask Bit 0~bit 15 represent the slot 0~slot 15.       
 * @param cmd The specific command .
 * @param enable True to enable above command. False to disable above command.
 */
void HSADC_HAL_SetSlotEnableCmd(HSADC_Type* base, 
                        uint16_t slotMask, 
                        hsadc_slot_enable_cmd_t cmd, 
                        bool enable);

/*!
 * @brief Sets to start the conversion for the converter.
 *
 * This function sets to start the conversion for the converter.
 *
 * @param base Register base address for the module.
 * @param convId The converter identifier.
 */
void HSADC_HAL_SoftTriggerConv(HSADC_Type* base, hsadc_conv_id_t convId);

/*!
 * @brief Gets the status of the converter A/B's flag.
 *
 * This function gets the status of the converter A/B's flag which is defined
 * in hsadc_conv_flag_t.
 * 
 * @param base Register base address for the module.
 * @param convId The converter identifier.
 * @param flag The specific flag.
 * @return Current status of the specific flag.
 *      -true: The flag is asserted.
 *      -false: The flag is not asserted.
 */
bool HSADC_HAL_GetConvFlag(HSADC_Type* base, hsadc_conv_id_t convId, 
                   hsadc_conv_flag_t flag);

/*!
 * @brief Clears the flag for the converter A/B.
 *
 * This function clears the flag for the converter A/B. The flag is 
 * defined in hsadc_conv_flag_t.
 *
 * @param base Register base address for the module.
 * @param convId The converter identifier.
 * @param flag The specific flag.
 */
void HSADC_HAL_ClearConvFlag(HSADC_Type* base, hsadc_conv_id_t convId, 
                     hsadc_conv_flag_t flag);

/*!
 * @brief Gets the status of global flag of all slots.
 *
 * This function gets the status of the global flag of all slots. The flag status 
 * of each slot can be got from HSADC_GetSpecificSlotFlag.
 *
 * @param base Register base address for the module.
 * @param flag The global flag of all the slots.
 * @return Current status of the specific flag.
 *      -true: The flag is asserted.
 *      -false: The flag is not asserted.
 */
bool HSADC_HAL_GetGlobalSlotFlag(HSADC_Type* base, hsadc_global_slot_flag_t flag);

/*!
 * @brief Clears the global flag for all slots.
 *
 * This function clears the global flag for all slots from 0 to 15.
 *
 * @param base Register base address for the module.
 * @param flag The global flag of all the slots.
 */
void HSADC_HAL_ClearGlobalSlotFlag(HSADC_Type* base, hsadc_global_slot_flag_t flag);

/*!
 * @brief Gets the status of the specific slots' flag.
 *
 * This function gets the status of the specific slots' flag which is defined
 * in hsadc_specific_slot_flag_t.
 *
 * @param base Register base address for the module.
 * @param slotMask Bit 0 to bit 15 represent the slot 0 to slot 15.
 * @param flag The specific flag.
 * @return The status bits mask of specific slots' flag. 
 */
uint16_t HSADC_HAL_GetSpecificSlotFlag(HSADC_Type* base, uint16_t slotMask, 
                               hsadc_specific_slot_flag_t flag);
  
/*!
 * @brief Clears the flag for the specific slots.
 *
 * This function clears the flag for the specific slots. The flag is
 * defined in hsadc_specific_slot_flag_t.
 *
 * @param base Register base address for the module.
 * @param slotMask Bit 0 to bit 15 represent the slot 0 to slot 15.
 * @param flag The specific flag.
 */
void HSADC_HAL_ClearSpecificSlotFlag(HSADC_Type* base, uint16_t slotMask, 
                             hsadc_specific_slot_flag_t flag);

/*!
 * @brief Sets to start the calibration for converter A/B.
 *
 * This function sets to start the single ended mode calibration or differential
 * mode calibration as the definition of hsadc_calibration_mode_t.
 *
 * @param base Register base address for the module.
 * @param convId The converter identifier.
 * @param mode The calibration mode.
 * @param enable Enable or disable the calibration.
 */
void HSADC_HAL_SetCalibrationCmd(HSADC_Type* base, 
                         hsadc_conv_id_t convId, 
                         hsadc_calibration_mode_t mode, 
                         bool enable);

/*!
 * @brief Gets the calibration value of converter A/B.
 *
 * This funtion gets the single ended mode calibration value or differential mode
 * calibration value.
 *
 * @param base Register base address for the module.
 * @param convId The converter identifier.
 * @param mode The calibration mode.
 * @return The calibration value.
 */
uint16_t HSADC_HAL_GetCalibrationValue(HSADC_Type* base, hsadc_conv_id_t convId, 
                               hsadc_calibration_mode_t mode);

/*!
 * @brief Gets the sample value of the specific slot.
 *
 * This function gets the conversion result of specific slot.
 *
 * @param base Register base address for the module.
 * @param slotIdx The specific slot number.
 * @return The conversion result.
 */
static inline uint16_t HSADC_HAL_GetSlotConvValue(HSADC_Type * base, uint16_t slotIdx)
{
    return HSADC_RD_RSLT(base, slotIdx);
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* __FAL_HSADC_HAL_H__ */
/******************************************************************************
 * EOF
 *****************************************************************************/

