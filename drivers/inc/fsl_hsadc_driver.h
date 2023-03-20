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

#ifndef __FSL_HSADC_DRIVER_H__
#define __FSL_HSADC_DRIVER_H__
#include "fsl_hsadc_hal.h"

/*!
 * @addtogroup hsadc_driver
 * @{
 */
/******************************************************************************
 * Enumerations.
 *****************************************************************************/

/*! @brief Defines the high level API's running status. */
typedef enum _hsadc_status
{    
    kStatus_HSADC_Success         = 0U, /*!< Success */
    kStatus_HSADC_InvalidArgument = 1U, /*!< Invalid argument existed. */
    kStatus_HSADC_Failed          = 2U  /*!< Failed. */      
} hsadc_status_t;


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief The additional configuration structure of converters in HSADC module.
 *
 * This types defines the converter's additional configuration information except
 * for the core configuration information of HSADC module.
 */
typedef struct HSAdcConvAdditionalConfig
{
    /* Logic or of interrupt enablement bit mask as the definition of hsadc_conv_int_src_t. */
    uint32_t convIntEnableMask;/*!< Converter's interrupt enable mask @internal gui name="Conversion interrupt enable mask" id="ConvIntEnableMask" */
    bool dmaEnable;      /*!< Dma enable @internal gui name="Enable DMA" id="DmaEnable" */ 
    bool syncInputEnable;/*!< Hardware trigger enable @internal gui name="Enable synchronization input" id="SyncInputEnable" */ 
    bool calibrationBypassEnable;/*!< Calibration bypass enable @internal gui name="Bypass calibration" id="CalibrationBypassEnable" */
    bool calibrateAtPowerUpEnable;/*!< Calibrate at power up period enable @internal gui name="Calibrate at power-up" id="CalibrateAtPowerUpEnable" */
    hsadc_calibration_mode_t calibrationModeAtPowerUp;/*!< Calibration mode @internal gui name="Calibration mode at power-up" id="CalibrationModeAtPowerUp" */
} hsadc_conv_additional_config_t;

/*!
 * @brief The additional configuration structure of channels in HSADC module.
 *
 * This type defines the channel's additional configuration information except
 * for the core configuration information of HSADC module.
 */
typedef struct HSAdcChnAdditionalConfig
{
    /* Logic or of all channels' working mode bit mask as the definition from 
    HSADC_ANA0_ANA1_DIFF_MODE_MASK to HSADC_ANB6_ANB7_DIFF_MODE_MASK. */
    uint16_t chnModeMask;/*!< Working mode bit mask @internal gui name="Channels differential mode mask" id="ChnModeMask" */
    hsadc_chn67_mux_sel_t chn67MuxSel[HSADC_CONV_NUMBER];/*!< Channel 6/7 mux selector @internal gui name="Channel 67 mux" id="Chn67MuxSel" */
} hsadc_chn_additional_config_t;

/*!
 * @brief The additional configuration structure of slots in HSADC module.
 *
 * This type defines the slot's additional configuration information except for
 * the core configuration information of HSADC module.
 */
typedef struct HSAdcSlotAdditionalConfig
{
    /* Logic or of interrupt enablement bit mask as the definition of hsadc_slot_int_src_t */
    uint32_t slotIntEnableMask;/*!< Slot's interrupt enable mask @internal gui name="Slot interrupt (Limits &amp; ZX) enable mask" id="SlotIntEnableMask" */
    hsadc_slot_sample_chn_t slotSampleChn[HSADC_SLOT_NUMBER];/*!< Slot's sampled channels @internal gui name="Slot - channel select" id="SlotSampleChn" */
    uint16_t slotLowLimit[HSADC_SLOT_NUMBER]; /*!< Low limit value of conversion result @internal gui name="Slot low limit" id="SlotLowLimit" range="0..32760" */
    uint16_t slotHighLimit[HSADC_SLOT_NUMBER];/*!< High limit value of conversion result @internal gui name="Slot high limit" id="SlotHighLimit" range="0..32760" */
    uint16_t slotOffset[HSADC_SLOT_NUMBER];   /*!< Offset value of conversion result @internal gui name="Slot offset" id="SlotOffset" */    
    hsadc_zero_cross_mode_t slotZeroCrossMode[HSADC_SLOT_NUMBER]; /*!< Zero crossing mode @internal gui name="Slot zero cross mode" id="SlotZeroCrossMode" */
    uint16_t slotEnableMask;        /*!< Slot's enable mask @internal gui name="Slot enable mask" id="SlotEnableMask" */      
    uint16_t slotWaitSyncEnableMask;/*!< Wait sync input feature enable mask @internal gui name="Slot wait sync enable mask" id="SlotWaitSyncEnableMask" */
    uint16_t slotScanIntEnableMask; /*!< Scan complete interrupt enable mask @internal gui name="Slot scan interrupt enable mask" id="SlotScanIntEnableMask" */
} hsadc_slot_additional_config_t;

/*!
 * @brief The overall configuration structure of HSADC module.
 *
 * This type defines all the configuration items when use HSADC module. User can
 * fill this structure one time to configure all aspects of HSADC module. Then user 
 * can convert the analog input constantly in the simplest situation.
 * The memory of this structure may not be acceptable to the user. So user can 
 * only use the core configuration structure to configure the core part of HSADC 
 * module by using HAL layer's configuration API. Then they can call other HAL 
 * APIs to configure other aspects of HSADC module.
 */
typedef struct HSAdcUserConfig
{
    hsadc_core_config_t* coreConfig;           /*!< Core configuration */
    /* If sets the item in the array "convConfig" to NULL, means not to use this converter. */
    hsadc_conv_additional_config_t* convConfig[HSADC_CONV_NUMBER];/*!< All converters' additional configuration */
    hsadc_chn_additional_config_t* chnConfig;  /*!< All channels' additional configuration */ 
    hsadc_slot_additional_config_t* slotConfig;/*!< All slots' additional configuration */
} hsadc_user_config_t;

extern HSADC_Type * g_hsadcBase[];

extern IRQn_Type g_hsadcConvAIrqId[HSADC_INSTANCE_COUNT];
extern IRQn_Type g_hsadcConvBIrqId[HSADC_INSTANCE_COUNT];
extern IRQn_Type g_hsadcErrIrqId[HSADC_INSTANCE_COUNT];

#if defined(__cplusplus)
extern "C" {
#endif
  
/******************************************************************************
 * API
 *****************************************************************************/

/* Init/DeInit functions. */
/*!
 * @brief Gets the default HSADC module configuration structure.
 *
 * This function fill the default value for the configuration items in the overall
 * configuration structure to examplify the simplest usage of HSADC module. User 
 * can directly use the result of this function and do some modification to get 
 * the customized configuration structure.
 *
 * @param configPtr The structure to save the default configuration information.
 * @return kStatus_HSADC_Success means success. Otherwise means failed.
 */
hsadc_status_t HSADC_DRV_StructInitUserConfigDefault(hsadc_user_config_t* configPtr);

/*!
 * @brief Initializes the HSADC module.
 *
 * This function initializes the HSADC module according to the user input.
 *
 * @param instance Instance ID number.
 * @param userConfig The structure contains the configuration information.
 * @return kStatus_HSADC_Success means success. Otherwise means failed.
 */
hsadc_status_t HSADC_DRV_Init(uint32_t instance, hsadc_user_config_t* configPtr);

/*!
 * @brief Disables the HSADC module.
 *
 * This function Disables the clock and interrupt for HSADC module.
 *
 * @param instance Instance ID number.
 * @return kStatus_HSADC_Success means success. Otherwise means failed.
 */
hsadc_status_t HSADC_DRV_DeInit(uint32_t instance);

/* Dynamical get/set functions. */
/*!
 * @brief Sets to start the conversion for the converter.
 *
 * This function sets to start the conversion for the converter.
 *
 * @param instance Instance ID number.
 * @param convId The converter identifier.
 */
void HSADC_DRV_SoftTriggerConv(uint32_t instance, hsadc_conv_id_t convId);

/*!
 * @brief Gets the status of the converter A/B's flag.
 *
 * This function gets the status of the converter A/B's flag which is defined
 * in hsadc_conv_flag_t.
 * 
 * @param instance Instance ID number.
 * @param convId The converter identifier.
 * @param flag The specific flag.
 * @return Current status of the specific flag.
 *      -true: The flag is asserted.
 *      -false: The flag is not asserted.
 */
bool HSADC_DRV_GetConvFlag(uint32_t instance, hsadc_conv_id_t convId, 
                   hsadc_conv_flag_t flag);

/*!
 * @brief Clears the flag for the converter A/B.
 *
 * This function clears the flag of the converter A/B. The flag is 
 * defined in hsadc_conv_flag_t.
 *
 * @param instance Instance ID number.
 * @param convId The converter identifier.
 * @param flag The specific flag.
 */
void HSADC_DRV_ClearConvFlag(uint32_t instance, hsadc_conv_id_t convId, 
                     hsadc_conv_flag_t flag);

/*!
 * @brief Gets the status of global flag of all slots.
 *
 * This function gets the status of the global flag of all slots. The flag status 
 * of each slot can be got from HSADC_GetSpecificSlotFlag.
 *
 * @param instance Instance ID number.
 * @param flag The global flag of all the slots.
 * @return Current status of the specific flag.
 *      -true: The flag is asserted.
 *      -false: The flag is not asserted.
 */
bool HSADC_DRV_GetGlobalSlotFlag(uint32_t instance, hsadc_global_slot_flag_t flag);

/*!
 * @brief Clears the global flag for all slots.
 *
 * This function clears the global flag of all slots from 0 to 15.
 *
 * @param instance Instance ID number.
 * @param flag The global flag of all the slots.
 */
void HSADC_DRV_ClearGlobalSlotFlag(uint32_t instance, hsadc_global_slot_flag_t flag);
/*!
 * @brief Gets the status for the specific slots' flag.
 *
 * This function gets the status of the specific slots' flag which is defined
 * in hsadc_specific_slot_flag_t.
 *
 * @param instance Instance ID number.
 * @param slotMask Bit 0 to bit 15 represent the slot 0 to slot 15.
 * @param flag The specific flag.
 * @return The status bits mask of specific slots' flag. 
 */
uint16_t HSADC_DRV_GetSpecificSlotFlag(uint32_t instance, uint16_t slotMask, 
                               hsadc_specific_slot_flag_t flag);

/*!
 * @brief Clears the flag for the specific slots.
 *
 * This function clears the flag of the specific slots. The flag is
 * defined in hsadc_specific_slot_flag_t.
 *
 * @param instance Instance ID number.
 * @param slotMask Bit 0 to bit 15 represent the slot 0 to slot 15.
 * @param flag The specific flag.
 */
void HSADC_DRV_ClearSpecificSlotFlag(uint32_t instance, uint16_t slotMask, 
                             hsadc_specific_slot_flag_t flag);

/*!
 * @brief Gets the sample value of the specific slot.
 *
 * This function gets the conversion result of specific slot.
 *
 * @param instance Instance ID number.
 * @param slotIdx The specific slot number.
 * @return The conversion result.
 */
uint16_t HSADC_DRV_GetSlotConvValue(uint32_t instance, uint16_t slotIdx);

/*!
 * @brief Executes conversion in blocking mode.
 *
 * This function executes conversion of the specific converter in the blocking mode.
 *
 * @param instance Instance ID number.
 * @param convId The converter identifier.
 * @param slotIdxArray The array contains the slot, the conversion result of which will be got.
 * @param slotValueArray The array saves the conversion result of slotIdxArray.
 * @param arraySize The slot array size.
 * @return kStatus_HSADC_Success means success. Otherwise means failed.
 */
hsadc_status_t HSADC_DRV_ConvertBlocking(uint32_t instance, 
                                 hsadc_conv_id_t convId, 
                                 uint16_t* slotIdxArray, 
                                 uint16_t* slotValueArray, 
                                 uint8_t arraySize);

/*!
 * @brief Executes the calibration process in the blocking mode.
 *
 * This function calibrates the converter in the blocking mode after the power up 
 * period. 
 *
 * @param instance Instance ID number.
 * @param convId The converter identifier.
 * @param mode The calibration mode.
 * @return The calibration value for the converter.
 */
uint16_t HSADC_DRV_CalibrateBlocking(uint32_t instance, hsadc_conv_id_t convId, 
                             hsadc_calibration_mode_t mode);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */
#endif /* __FSL_HSADC_DRIVER_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/
