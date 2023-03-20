/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#include "fsl_ftm_hal.h"

#if FSL_FEATURE_SOC_FTM_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_Init
 * Description   : Initializes the FTM.
 *
 *END**************************************************************************/
void FTM_HAL_Init(FTM_Type *base)
{
    /* Use FTM mode */
    FTM_HAL_Enable(base, true);
    FTM_HAL_SetClockPs(base, kFtmDividedBy2);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_SetSyncMode
 * Description   : Sets the FTM register synchronization method.
 * This function will set the necessary bits for the synchronization mode that user wishes to use.
 *
 *END**************************************************************************/
void FTM_HAL_SetSyncMode(FTM_Type *base, uint32_t syncMethod)
{
    assert(syncMethod & (FTM_SYNC_TRIG0_MASK | FTM_SYNC_TRIG1_MASK | FTM_SYNC_TRIG2_MASK | FTM_SYNC_SWSYNC_MASK));

    uint32_t channel = 0;

    /* Use the Enhanced PWM synchronization method */
    FTM_HAL_SetPwmSyncModeCmd(base, true);

    FTM_HAL_SetCntinPwmSyncModeCmd(base, true);
    FTM_HAL_SetInvctrlPwmSyncModeCmd(base, true);
    FTM_HAL_SetSwoctrlPwmSyncModeCmd(base, true);
    FTM_HAL_SetOutmaskPwmSyncModeCmd(base, true);

    for (channel = 0; channel < (FSL_FEATURE_FTM_CHANNEL_COUNT / 2); channel++)
    {
        FTM_HAL_SetDualChnPwmSyncCmd(base, channel, true);
    }
    if (syncMethod & FTM_SYNC_SWSYNC_MASK)
    {
        /* Enable needed bits for software trigger to update registers with its buffer value */
        FTM_HAL_SetCounterSoftwareSyncModeCmd(base, true);
        FTM_HAL_SetModCntinCvSoftwareSyncModeCmd(base, true);
        FTM_HAL_SetInvctrlSoftwareSyncModeCmd(base, true);
        FTM_HAL_SetSwoctrlSoftwareSyncModeCmd(base, true);
        FTM_HAL_SetOutmaskSoftwareSyncModeCmd(base, true);
    }
    if (syncMethod & (FTM_SYNC_TRIG0_MASK | FTM_SYNC_TRIG1_MASK | FTM_SYNC_TRIG2_MASK))
    {
        /* Enable needed bits for hardware trigger to update registers with its buffer value */
        FTM_HAL_SetCounterHardwareSyncModeCmd(base, true);
        FTM_HAL_SetModCntinCvHardwareSyncModeCmd(base, true);
        FTM_HAL_SetInvctrlHardwareSyncModeCmd(base, true);
        FTM_HAL_SetSwoctrlHardwareSyncModeCmd(base, true);
        FTM_HAL_SetOutmaskHardwareSyncModeCmd(base, true);
        if (syncMethod & FTM_SYNC_TRIG0_MASK)
        {
            FTM_BWR_SYNC_TRIG0(base, 1);
        }

        if (syncMethod & FTM_SYNC_TRIG1_MASK)
        {
            FTM_BWR_SYNC_TRIG1(base, 1);
        }
        if (syncMethod & FTM_SYNC_TRIG2_MASK)
        {
            FTM_BWR_SYNC_TRIG2(base, 1);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_EnablePwmMode
 * Description   : Enables the FTM timer when it is PWM output mode
 *
 *END**************************************************************************/
void FTM_HAL_EnablePwmMode(FTM_Type *base, ftm_pwm_param_t *config, uint8_t channel)
{
    uint8_t chnlPairnum = FTM_HAL_GetChnPairIndex(channel);

    FTM_HAL_SetDualEdgeCaptureCmd(base, chnlPairnum, false);
    FTM_HAL_SetChnEdgeLevel(base, channel, config->edgeMode ? 1 : 2);
    switch(config->mode)
    {
        case kFtmEdgeAlignedPWM:
            FTM_HAL_SetDualChnCombineCmd(base, chnlPairnum, false);
            FTM_HAL_SetCpwms(base, 0);
            FTM_HAL_SetChnMSnBAMode(base, channel, 2);
            break;
        case kFtmCenterAlignedPWM:
            FTM_HAL_SetDualChnCombineCmd(base, chnlPairnum, false);
            FTM_HAL_SetCpwms(base, 1);
            break;
        case kFtmCombinedPWM:
            FTM_HAL_SetCpwms(base, 0);
            FTM_HAL_SetDualChnCombineCmd(base, chnlPairnum, true);
            break;
        default:
            assert(0);
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_DisablePwmMode
 * Description   : Disables the PWM output mode.
 *
 *END**************************************************************************/
void FTM_HAL_DisablePwmMode(FTM_Type *base, ftm_pwm_param_t *config, uint8_t channel)
{
    uint8_t chnlPairnum = FTM_HAL_GetChnPairIndex(channel);

    FTM_HAL_SetChnCountVal(base, channel, 0);
    FTM_HAL_SetChnEdgeLevel(base, channel, 0);
    FTM_HAL_SetChnMSnBAMode(base, channel, 0);
    FTM_HAL_SetCpwms(base, 0);
    FTM_HAL_SetDualChnCombineCmd(base, chnlPairnum, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_Reset
 * Description   : Resets the FTM registers
 *
 *END**************************************************************************/
void FTM_HAL_Reset(FTM_Type *base)
{
    FTM_WR_SC(base, 0);
    FTM_WR_CNT(base, 0);
    FTM_WR_MOD(base, 0);

    FTM_WR_CNTIN(base, 0);
    FTM_WR_STATUS(base, 0);
    FTM_WR_MODE(base, 0x00000004);
    FTM_WR_SYNC(base, 0);
    FTM_WR_OUTINIT(base, 0);
    FTM_WR_OUTMASK(base, 0);
    FTM_WR_COMBINE(base, 0);
    FTM_WR_DEADTIME(base, 0);
    FTM_WR_EXTTRIG(base, 0);
    FTM_WR_POL(base, 0);
    FTM_WR_FMS(base, 0);
    FTM_WR_FILTER(base, 0);
    FTM_WR_FLTCTRL(base, 0);
    FTM_WR_CONF(base, 0);
    FTM_WR_FLTPOL(base, 0);
    FTM_WR_SYNCONF(base, 0);
    FTM_WR_INVCTRL(base, 0);
    FTM_WR_SWOCTRL(base, 0);
    FTM_WR_PWMLOAD(base, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_SetHardwareSyncTriggerSrc
 * Description   : Sets the FTM peripheral timer hardware trigger.
 *
 *END**************************************************************************/
void FTM_HAL_SetHardwareSyncTriggerSrc(FTM_Type *base, uint32_t trigger_num, bool enable)
{
    switch(trigger_num)
    {
        case 0:
            FTM_BWR_SYNC_TRIG0(base, enable ? 1 : 0);
            break;
        case 1:
            FTM_BWR_SYNC_TRIG1(base, enable ? 1 : 0);
            break;
        case 2:
            FTM_BWR_SYNC_TRIG2(base, enable ? 1 : 0);
            break;
        default:
            assert(0);
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_SetChnTriggerCmd
 * Description   : Enables or disables the generation of the FTM peripheral timer channel trigger.
 * Enables or disables the generation of the FTM peripheral timer channel trigger when the
 * FTM counter is equal to its initial value. Channels 6 and 7 cannot be used as triggers.
 *
 *END**************************************************************************/
void FTM_HAL_SetChnTriggerCmd(FTM_Type *base, uint8_t channel, bool val)
{
    assert(channel < CHAN6_IDX);

    uint8_t bit = val ? 1 : 0;
    uint32_t value = (channel > 1U) ? (uint8_t)(bit << (channel - 2U)) : (uint8_t)(bit << (channel + 4U));

    val ? FTM_SET_EXTTRIG(base, value) : FTM_CLR_EXTTRIG(base, value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_SetChnInputCaptureFilter
 * Description   : Sets the FTM peripheral timer channel input capture filter value.
 *
 *END**************************************************************************/
void FTM_HAL_SetChnInputCaptureFilter(FTM_Type *base, uint8_t channel, uint8_t val)
{
    assert(channel < CHAN4_IDX);

    switch(channel)
    {
        case CHAN0_IDX:
            FTM_BWR_FILTER_CH0FVAL(base, val);
            break;
        case CHAN1_IDX:
            FTM_BWR_FILTER_CH1FVAL(base, val);
            break;
        case CHAN2_IDX:
            FTM_BWR_FILTER_CH2FVAL(base, val);
            break;
        case CHAN3_IDX:
            FTM_BWR_FILTER_CH3FVAL(base, val);
            break;
        default:
            assert(0);
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_GetChnPairIndex
 * Description   : Combines the channel control.
 * Returns an index for each channel pair.
 *
 *END**************************************************************************/
uint32_t FTM_HAL_GetChnPairIndex(uint8_t channel)
{
    if((channel == CHAN0_IDX) || (channel == CHAN1_IDX))
    {
        return 0;
    }
    else if((channel == CHAN2_IDX) || (channel == CHAN3_IDX))
    {
        return 1;
    }
    else if((channel == CHAN4_IDX) || (channel == CHAN5_IDX))
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

#endif /* FSL_FEATURE_SOC_FTM_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

