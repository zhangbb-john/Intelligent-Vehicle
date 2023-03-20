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
#include <assert.h>

#include "fsl_hsadc_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_StructInitUserConfigDefault
 * Description   : This function gets the default overall configuration structure.
 *
 *END**************************************************************************/ 
hsadc_status_t HSADC_DRV_StructInitUserConfigDefault(hsadc_user_config_t* configPtr)
{
    uint16_t i;
    hsadc_core_config_t* coreConfig;
    hsadc_conv_additional_config_t *convAConfig, *convBConfig;
    hsadc_chn_additional_config_t* chnConfig;
    hsadc_slot_additional_config_t* slotConfig;
    
    coreConfig = configPtr->coreConfig;
    convAConfig = configPtr->convConfig[kHSAdcConvA];
    convBConfig = configPtr->convConfig[kHSAdcConvB];
    chnConfig = configPtr->chnConfig;
    slotConfig = configPtr->slotConfig;
    
    if ((!configPtr) || (!coreConfig) || (!chnConfig) || (!slotConfig))
    {
        return kStatus_HSADC_InvalidArgument;
    }
    /* Core's configuration */
    coreConfig->scanMode = kHSAdcScanTriggeredParalled;
    coreConfig->parallelSimultModeEnable = true;
    coreConfig->dmaTriggerSrc = kHSAdcDmaTriggeredByEndOfScan;
    coreConfig->powerUpDelayCount = 0x12U;
    coreConfig->autoStandbyEnable = false;
    coreConfig->autoPowerDownEnable = false;
    coreConfig->convResolution = kHSAdcResolutionBitOf12;
    coreConfig->clkDivValue[kHSAdcConvA] = 0x04U;
    coreConfig->clkDivValue[kHSAdcConvB] = 0x04U;
    coreConfig->samplingTime[kHSAdcConvA] = 0U;
    coreConfig->samplingTime[kHSAdcConvB] = 0U;
    
    /* Converter's additional configuration */
    if (convAConfig)
    {
        convAConfig->convIntEnableMask = 0U;
        convAConfig->dmaEnable = 0U;
        convAConfig->syncInputEnable = true;
        convAConfig->calibrationBypassEnable = false;
        convAConfig->calibrateAtPowerUpEnable = false;
        convAConfig->calibrationModeAtPowerUp = kHSAdcCalibrationBoth;
    }   
    if (convBConfig)
    {
        convBConfig->convIntEnableMask = 0U;
        convBConfig->dmaEnable = 0U;
        convBConfig->syncInputEnable = true;
        convBConfig->calibrationBypassEnable = false;
        convBConfig->calibrateAtPowerUpEnable = false;
        convBConfig->calibrationModeAtPowerUp = kHSAdcCalibrationBoth;
    } 

    /* Channel's additional configuration */
    chnConfig->chnModeMask = 0U;
    chnConfig->chn67MuxSel[kHSAdcConvA] = kHSAdcChn67Mux6_7;
    chnConfig->chn67MuxSel[kHSAdcConvB] = kHSAdcChn67Mux6_7;
    
    /* Slot's additional configuration */
    slotConfig->slotIntEnableMask = 0U;
    for (i = 0; i < HSADC_SLOT_NUMBER; i++)
    {
        slotConfig->slotSampleChn[i] = kHSAdcSlotSampleANA0__ANA0_ANA1; 
        slotConfig->slotLowLimit[i] = 0U;
        slotConfig->slotHighLimit[i] = 0xFFFFU;
        slotConfig->slotOffset[i] = 0U; 
        slotConfig->slotZeroCrossMode[i] = kHSAdcZeroCrossDisable;
    }    
    slotConfig->slotEnableMask = 0U;
    slotConfig->slotWaitSyncEnableMask = 0U;
    slotConfig->slotScanIntEnableMask = 0U;  
    return kStatus_HSADC_Success; 
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_ConfigConv
 * Description   : This function configures the converter's additional part except 
 *   for the core part of the HSADC module.
 *
 *END**************************************************************************/
static hsadc_status_t HSADC_DRV_ConfigConv(uint32_t instance, hsadc_conv_id_t convId,
                                   hsadc_conv_additional_config_t* configPtr)
{
    HSADC_Type* base;   
    if (!configPtr)
    {
        return kStatus_HSADC_InvalidArgument;
    }
    base = g_hsadcBase[instance];
    /**********Converter related configuration***********/
    HSADC_HAL_SetConvIntCmd(base, convId, configPtr->convIntEnableMask, true);
    HSADC_HAL_SetConvDmaCmd(base, convId, configPtr->dmaEnable);   
    HSADC_HAL_SetConvEnableCmd(base, convId, kHSAdcConvSyncInputEnable, configPtr->syncInputEnable);
    /* Disable to stop converter. */
    HSADC_HAL_SetConvEnableCmd(base, convId, kHSAdcConvStopEnable, false);
    /* Calibrate the converter at power up period. */
    if (configPtr->calibrateAtPowerUpEnable)
    {
        /* Enable calibration request. */
        HSADC_HAL_SetCalibrationCmd(base, convId, configPtr->calibrationModeAtPowerUp, true);
    }
    /* Disable converter power down. */
    HSADC_HAL_SetConvEnableCmd(base, convId, kHSAdcConvPowerDownEnable, false);
    /* Waits converter to power up. */
    while (HSADC_HAL_GetConvFlag(base, convId, kHSAdcConvPowerStatusStable)){}
    if (configPtr->calibrateAtPowerUpEnable)
    {
        /* Wait until calibration complete. */
      while (!HSADC_HAL_GetConvFlag(base, convId, kHSAdcConvEndOfCalibrationIntHappened)){}
        /* Clear the end of calibration interrupt flag. */
        HSADC_HAL_ClearConvFlag(base, convId, kHSAdcConvEndOfCalibrationIntHappened);
        /* Disable calibration request. */
        HSADC_HAL_SetCalibrationCmd(base, convId, configPtr->calibrationModeAtPowerUp, false);
    }
    
    HSADC_HAL_SetConvEnableCmd(base, convId, kHSAdcConvCalibrationBypassEnable, 
                               configPtr->calibrationBypassEnable);
    return kStatus_HSADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_ConfigChn
 * Description   : This function configures the channel's additional part except 
 *   for the core part of the HSADC module.
 *
 *END**************************************************************************/
static hsadc_status_t HSADC_DRV_ConfigChn(uint32_t instance, hsadc_chn_additional_config_t* configPtr)
{
    HSADC_Type* base;    
    if (!configPtr)
    {
        return kStatus_HSADC_InvalidArgument;
    }
    base = g_hsadcBase[instance];
    
    HSADC_HAL_SetChnMode(base, configPtr->chnModeMask);
    HSADC_HAL_SetChn67MuxSel(base, kHSAdcConvA, configPtr->chn67MuxSel[kHSAdcConvA]);
    HSADC_HAL_SetChn67MuxSel(base, kHSAdcConvB, configPtr->chn67MuxSel[kHSAdcConvB]);
    return kStatus_HSADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_ConfigSlot
 * Description   : This function configures the slot's additional part except 
 *   for the core part of the HSADC module.
 *
 *END**************************************************************************/
static hsadc_status_t HSADC_DRV_ConfigSlot(uint32_t instance, hsadc_slot_additional_config_t* configPtr)
{
    uint8_t i;
    HSADC_Type* base;    
    if (!configPtr)
    {
        return kStatus_HSADC_InvalidArgument;
    }
    base = g_hsadcBase[instance];
    
    HSADC_HAL_SetSlotIntCmd(base, configPtr->slotIntEnableMask, true);
    for (i = 0; i < HSADC_SLOT_NUMBER; i++)
    {
        HSADC_HAL_SetSlotSampleChn(base, i, configPtr->slotSampleChn[i]);
        HSADC_HAL_SetSlotThreshold(base, i, configPtr->slotLowLimit[i], configPtr->slotHighLimit[i]);
        HSADC_HAL_SetSlotOffset(base, i, configPtr->slotOffset[i]);
        HSADC_HAL_SetSlotZeroCrossMode(base, i, configPtr->slotZeroCrossMode[i]);
    }
    HSADC_HAL_SetSlotEnableCmd(base, configPtr->slotEnableMask, kHSAdcSlotDisable, false);
    HSADC_HAL_SetSlotEnableCmd(base, ~(configPtr->slotEnableMask), kHSAdcSlotDisable, true);
    HSADC_HAL_SetSlotEnableCmd(base, configPtr->slotWaitSyncEnableMask, kHSAdcSlotWaitSyncEnable, true);
    HSADC_HAL_SetSlotEnableCmd(base, configPtr->slotScanIntEnableMask, kHSAdcSlotScanIntEnable, true); 
    return kStatus_HSADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_Config
 * Description   : This function configure this module overallly.
 *
 *END**************************************************************************/                      
static hsadc_status_t HSADC_DRV_Config(uint32_t instance, hsadc_user_config_t* configPtr)
{
    HSADC_Type* base;    
    hsadc_core_config_t* coreConfig;
    hsadc_conv_additional_config_t* convAConfig, *convBConfig;
    hsadc_chn_additional_config_t* chnConfig;
    hsadc_slot_additional_config_t* slotConfig;
    
    coreConfig = configPtr->coreConfig;
    convAConfig = configPtr->convConfig[kHSAdcConvA];
    convBConfig = configPtr->convConfig[kHSAdcConvB];
    chnConfig = configPtr->chnConfig;
    slotConfig = configPtr->slotConfig;
    
    if ((!configPtr) || (!coreConfig) || (!chnConfig) || (!slotConfig))
    {
        return kStatus_HSADC_InvalidArgument;
    }
    base = g_hsadcBase[instance];
    HSADC_HAL_Init(base);
    HSADC_HAL_Config(base, coreConfig);
    /* Configures the converter if its configuration pointer is not NULL. */
    if (convAConfig)
    {
        HSADC_DRV_ConfigConv(instance, kHSAdcConvA, convAConfig);
    }
    if (convBConfig)
    {
        /* User should not set simultaneous mode and calibration at power up period
        for converter B at the same time. When simultaneous mode is set, user should 
        only set the calibration at power up period for converter A. */
        if ((coreConfig->parallelSimultModeEnable) && (convBConfig->calibrateAtPowerUpEnable))
        {
            return kStatus_HSADC_InvalidArgument;
        }  
        HSADC_DRV_ConfigConv(instance, kHSAdcConvB, convBConfig);
    }    
    HSADC_DRV_ConfigChn(instance, chnConfig);   
    HSADC_DRV_ConfigSlot(instance, slotConfig); 
    return kStatus_HSADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_Init
 * Description   : This function initializes the HSADC module.
 *
 *END**************************************************************************/ 
hsadc_status_t HSADC_DRV_Init(uint32_t instance, hsadc_user_config_t* configPtr)
{  
    assert(instance < HSADC_INSTANCE_COUNT);    
    if(!configPtr)
    {
        return kStatus_HSADC_InvalidArgument;
    }
    
    CLOCK_SYS_EnableHSAdcClock(instance); 
    
    if (HSADC_DRV_Config(instance, configPtr) != kStatus_HSADC_Success)
    {
        return kStatus_HSADC_Failed;
    }
        
    INT_SYS_EnableIRQ(g_hsadcConvAIrqId[instance]); 
    INT_SYS_EnableIRQ(g_hsadcConvBIrqId[instance]);
    INT_SYS_EnableIRQ(g_hsadcErrIrqId[instance]);    
    return kStatus_HSADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_DeInit
 * Description   : This function deinitializes the HSADC module.
 *
 *END**************************************************************************/ 
hsadc_status_t HSADC_DRV_DeInit(uint32_t instance)
{
    assert(instance < HSADC_INSTANCE_COUNT);
    
    CLOCK_SYS_DisableHsadcClock(instance);
    
    INT_SYS_DisableIRQ(g_hsadcConvAIrqId[instance]);
    INT_SYS_DisableIRQ(g_hsadcConvBIrqId[instance]);
    INT_SYS_DisableIRQ(g_hsadcErrIrqId[instance]);    
    return kStatus_HSADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_SoftTriggerConv
 * Description   : Sets the converter A/B to start conversion.
 *
 *END**************************************************************************/
void HSADC_DRV_SoftTriggerConv(uint32_t instance, hsadc_conv_id_t convId)
{
    HSADC_Type* base;
    assert(instance < HSADC_INSTANCE_COUNT);
    base = g_hsadcBase[instance];
    HSADC_HAL_SoftTriggerConv(base, convId);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_GetConvFlag
 * Description   : Gets the status of the specific flag of the converter A/B.
 *
 *END**************************************************************************/
bool HSADC_DRV_GetConvFlag(uint32_t instance, hsadc_conv_id_t convId, 
                   hsadc_conv_flag_t flag)
{
    HSADC_Type* base;
    assert(instance < HSADC_INSTANCE_COUNT);
    base = g_hsadcBase[instance];
    return HSADC_HAL_GetConvFlag(base, convId, flag);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_ClearConvFlag
 * Description   : Clears the specific flag for the converter A/B.
 *
 *END**************************************************************************/
void HSADC_DRV_ClearConvFlag(uint32_t instance, hsadc_conv_id_t convId, 
                     hsadc_conv_flag_t flag)
{
    HSADC_Type* base;
    assert(instance < HSADC_INSTANCE_COUNT);
    base = g_hsadcBase[instance];
    HSADC_HAL_ClearConvFlag(base, convId, flag);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_GetGlobalSlotFlag
 * Description   : Gets the status of the global flag of all slots.
 *
 *END**************************************************************************/
bool HSADC_DRV_GetGlobalSlotFlag(uint32_t instance, hsadc_global_slot_flag_t flag)
{
    HSADC_Type* base;
    assert(instance < HSADC_INSTANCE_COUNT);
    base = g_hsadcBase[instance];
    return HSADC_HAL_GetGlobalSlotFlag(base, flag);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_ClearGlobalSlotFlag
 * Description   : Clears the global flag for all slots.
 *
 *END**************************************************************************/
void HSADC_DRV_ClearGlobalSlotFlag(uint32_t instance, hsadc_global_slot_flag_t flag)
{
    HSADC_Type* base;
    assert(instance < HSADC_INSTANCE_COUNT);
    base = g_hsadcBase[instance];
    HSADC_HAL_ClearGlobalSlotFlag(base, flag);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_GetSpecificSlotFlag
 * Description   : Gets the status of the specific flag of the sample slots.
 *
 *END**************************************************************************/
uint16_t HSADC_DRV_GetSpecificSlotFlag(uint32_t instance, uint16_t slotMask, 
                               hsadc_specific_slot_flag_t flag)
{
    HSADC_Type* base;
    assert(instance < HSADC_INSTANCE_COUNT);
    base = g_hsadcBase[instance];
    return HSADC_HAL_GetSpecificSlotFlag(base, slotMask, flag);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_ClearSpecificSlotFlag
 * Description   : This function clears the specific flag for the specific slots.
 *
 *END**************************************************************************/
void HSADC_DRV_ClearSpecificSlotFlag(uint32_t instance, uint16_t slotMask, 
                             hsadc_specific_slot_flag_t flag)
{
    HSADC_Type* base;
    assert(instance < HSADC_INSTANCE_COUNT);
    base = g_hsadcBase[instance];
    HSADC_HAL_ClearSpecificSlotFlag(base, slotMask, flag);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_GetSlotConvValue
 * Description   : Gets the conversion value of specific slot.
 *
 *END**************************************************************************/
uint16_t HSADC_DRV_GetSlotConvValue(uint32_t instance, uint16_t slotIdx)
{
    HSADC_Type* base;
    assert(instance < HSADC_INSTANCE_COUNT);
    base = g_hsadcBase[instance];
    return HSADC_HAL_GetSlotConvValue(base, slotIdx);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_ConvertBlocking
 * Description   : Converts the analog input in blocking mode.
 *
 *END**************************************************************************/
hsadc_status_t HSADC_DRV_ConvertBlocking(uint32_t instance, 
                                         hsadc_conv_id_t convId, 
                                         uint16_t* slotIdxArray, 
                                         uint16_t* slotValueArray, 
                                         uint8_t arraySize)
{
    uint8_t i;
    HSADC_Type* base;
    assert(instance < HSADC_INSTANCE_COUNT);
    base = g_hsadcBase[instance];
    
    switch (convId)
    {
        case kHSAdcConvA:
            /* Start Conversion. */
            HSADC_HAL_SoftTriggerConv(base, kHSAdcConvA);
            /* Wait until complete. */
            while (!HSADC_HAL_GetConvFlag(base, kHSAdcConvA, kHSAdcConvEndOfScanIntHappened)){} 
            /* Clear interrupt flag. */
            HSADC_HAL_ClearConvFlag(base, kHSAdcConvA, kHSAdcConvEndOfScanIntHappened);
            break;
        case kHSAdcConvB:
            /* Start Conversion. */
            HSADC_HAL_SoftTriggerConv(base, kHSAdcConvB);
            /* Wait until complete. */
            while (!HSADC_HAL_GetConvFlag(base, kHSAdcConvB, kHSAdcConvEndOfScanIntHappened)){}
            /* Clear interrupt flag. */
            HSADC_HAL_ClearConvFlag(base, kHSAdcConvB, kHSAdcConvEndOfScanIntHappened);
            break;
        default:
            return kStatus_HSADC_InvalidArgument;
    }
    
    /* Get the conversion result. */
    for (i = 0;i < arraySize;i++)
    {
        slotValueArray[i] = HSADC_HAL_GetSlotConvValue(base, slotIdxArray[i]);
    }
  
    return kStatus_HSADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_DRV_CalibrateBlocking
 * Description   : Calibrates the converter in blocking mode after power up period.
 *
 *END**************************************************************************/
uint16_t HSADC_DRV_CalibrateBlocking(uint32_t instance, hsadc_conv_id_t convId, 
                             hsadc_calibration_mode_t mode)
{
    HSADC_Type* base;
    assert(instance < HSADC_INSTANCE_COUNT);
    base = g_hsadcBase[instance];
    
    switch (convId)
    {
        case kHSAdcConvA:                    
            /* Enable calibration request. */
            HSADC_HAL_SetCalibrationCmd(base, kHSAdcConvA, mode, true);    
            /* Start Conversion. */
            HSADC_HAL_SoftTriggerConv(base, kHSAdcConvA);
            /* Wait until complete. */
            while (!HSADC_HAL_GetConvFlag(base, kHSAdcConvA, kHSAdcConvEndOfScanIntHappened)){}
            /* Wait until calibration complete. */
            while (!HSADC_HAL_GetConvFlag(base, kHSAdcConvA, kHSAdcConvEndOfCalibrationIntHappened)){}
            /* Clear the end of calibration flag. */
            HSADC_HAL_ClearConvFlag(base, kHSAdcConvA, kHSAdcConvEndOfCalibrationIntHappened);
            /* Clear the end of scan flag. */
            HSADC_HAL_ClearConvFlag(base, kHSAdcConvA, kHSAdcConvEndOfScanIntHappened);
            /* Disable calibration request. */
            HSADC_HAL_SetCalibrationCmd(base, kHSAdcConvA, mode, false);
            break;
        case kHSAdcConvB:
            /* Enable calibration request. */
            HSADC_HAL_SetCalibrationCmd(base, kHSAdcConvB, mode, true);    
            /* Start Conversion. */
            HSADC_HAL_SoftTriggerConv(base, kHSAdcConvB);
            /* Wait until complete. */
            while (!HSADC_HAL_GetConvFlag(base, kHSAdcConvB, kHSAdcConvEndOfScanIntHappened)){}
            /* Wait until calibration complete. */
            while (!HSADC_HAL_GetConvFlag(base, kHSAdcConvB, kHSAdcConvEndOfCalibrationIntHappened)){}
            /* Clear the end of calibration flag. */
            HSADC_HAL_ClearConvFlag(base, kHSAdcConvB, kHSAdcConvEndOfCalibrationIntHappened);
            /* Clear the end of scan flag. */
            HSADC_HAL_ClearConvFlag(base, kHSAdcConvB, kHSAdcConvEndOfScanIntHappened);
            /* Disable calibration request. */
            HSADC_HAL_SetCalibrationCmd(base, kHSAdcConvB, mode, false);
            break;
        default:
            return kStatus_HSADC_InvalidArgument;
    }
    
    return HSADC_HAL_GetCalibrationValue(base, convId, mode);
}
