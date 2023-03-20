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

#include "fsl_hsadc_hal.h"
#include <assert.h>

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_Init
 * Description   : This function resets the HSADC module.
 *
 *END**************************************************************************/
void HSADC_HAL_Init(HSADC_Type * base)
{  
    uint8_t i;
    
    /* Disable all DMA/Interrupt. Enable hardware trigger. Enable stop mode for converter A/B. */
    HSADC_WR_CTRL1(base, 0x5005U);
    HSADC_WR_CTRL2(base, 0x5044U);
    /* Disable the zero cross mode for all slots. */
    HSADC_WR_ZXCTRL1(base, 0U);
    HSADC_WR_ZXCTRL2(base, 0U);
    /* Set all slots to sample ANA0 in single ended mode or ANA0_ANA1 in differential mode. */
    HSADC_WR_CLIST1(base, 0U);
    HSADC_WR_CLIST2(base, 0U);
    HSADC_WR_CLIST3(base, 0U);
    HSADC_WR_CLIST4(base, 0U);
    
    /* Enable all slots. */
    HSADC_WR_SDIS(base, 0U);
    /* Clear all flags. */
    HSADC_WR_STAT(base, 0x1830U);
    HSADC_WR_LOLIMSTAT(base, 0xFFFFU);
    HSADC_WR_HILIMSTAT(base, 0xFFFFU);    
    HSADC_WR_ZXSTAT(base, 0xFFFFU);
    for (i = 0; i < HSADC_SLOT_NUMBER; i++)
    {  
        /* Set the low limit value of all slots to 0. */
        HSADC_WR_LOLIM(base, i, 0x0000U);
        /* Set the high limit value of all slots to 0xFFFF. */
        HSADC_WR_HILIM(base, i, 0xFFFFU);
        HSADC_WR_OFFST(base, i, 0x0000U);
    }
    /* Power down converter A/B. */
    HSADC_WR_PWR(base, 0x1127U);
    /* Disable every slot to delay until a new sync input occurs. */
    HSADC_WR_SCTRL(base, 0U);
    HSADC_WR_PWR2(base, 0x0400U);
    /* Select 12 bit resolution. Select DMA trigger source is end of scan interrupt. */
    HSADC_WR_CTRL3(base, 0x0300U);
    /* Scan interrupt is disabled for every slot. */
    HSADC_WR_SCINTEN(base, 0U);
    /* Set sample time of converter A and B to 0 */
    HSADC_WR_SAMPTIM(base, 0U);
    /* Disable end of calibration interrupt for converter A and B. Disable 
    calibration bypass for converter A/B. */
    HSADC_WR_CALIB(base, 0U);
    /* Set single ended mode and differential mode calibration result to 0. */
    HSADC_WR_CALVAL_A(base, 0U);
    HSADC_WR_CALVAL_B(base, 0U);
    /* Set the mux selector of channel 67 of converter A/B to kHSAdcChn6a_7a. */
    HSADC_WR_MUX67_SEL(base, 0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_Config
 * Description   : This function initializes the HSADC module.
 *
 *END**************************************************************************/
void HSADC_HAL_Config(HSADC_Type * base, const hsadc_core_config_t* configPtr)
{
    assert(configPtr);
    
    uint16_t ctrl1, ctrl2, ctrl3, pwr, pwr2, samptim;
    
    HSADC_HAL_Init(base);
   
    /* Common configuration between converter A and converter B. */
    ctrl1 = HSADC_RD_CTRL1(base);
    ctrl2 = HSADC_RD_CTRL2(base);
    ctrl3 = HSADC_RD_CTRL3(base);
    pwr = HSADC_RD_PWR(base);
    pwr2 = HSADC_RD_PWR2(base);
    samptim = HSADC_RD_SAMPTIM(base);
    
    ctrl1 &= ~HSADC_CTRL1_SMODE_MASK;
    ctrl1 |= HSADC_CTRL1_SMODE(configPtr->scanMode);
    
    ctrl2 &= ~HSADC_CTRL2_SIMULT_MASK;
    if (configPtr->parallelSimultModeEnable)
    {
        ctrl2 |= HSADC_CTRL2_SIMULT_MASK;
    }
    
    ctrl3 &= ~HSADC_CTRL3_DMASRC_MASK;
    ctrl3 |= HSADC_CTRL3_DMASRC(configPtr->dmaTriggerSrc);
    
    pwr &= ~HSADC_PWR_ASB_MASK;
    if (configPtr->autoStandbyEnable)
    {
        pwr |= HSADC_PWR_ASB_MASK;
    }
    
    pwr &= ~HSADC_PWR_PUDELAY_MASK;
    pwr |= HSADC_PWR_PUDELAY(configPtr->powerUpDelayCount);
    
    pwr &= ~HSADC_PWR_APD_MASK;
    if (configPtr->autoPowerDownEnable)
    {
        pwr |= HSADC_PWR_APD_MASK;
    }
    
    ctrl3 &= ~HSADC_CTRL3_ADCRES_MASK;    
    ctrl3 |= HSADC_CTRL3_ADCRES(configPtr->convResolution);
    
    
    /* Configuration for individual converter. */          
    ctrl2 &= ~HSADC_CTRL2_DIVA_MASK;
    ctrl2 |= HSADC_CTRL2_DIVA(configPtr->clkDivValue[kHSAdcConvA]);
    
    pwr2 &= ~HSADC_PWR2_DIVB_MASK;
    pwr2 |= HSADC_PWR2_DIVB(configPtr->clkDivValue[kHSAdcConvB]);
    
    samptim &= ~HSADC_SAMPTIM_SAMPT_A_MASK;
    samptim |= HSADC_SAMPTIM_SAMPT_A(configPtr->samplingTime[kHSAdcConvA]);
    
    samptim &= ~HSADC_SAMPTIM_SAMPT_B_MASK;
    samptim |= HSADC_SAMPTIM_SAMPT_B(configPtr->samplingTime[kHSAdcConvB]);
      
    /* Write back the register value. */
    HSADC_WR_CTRL1(base, ctrl1);
    HSADC_WR_CTRL2(base, ctrl2);
    HSADC_WR_CTRL3(base, ctrl3);
    HSADC_WR_PWR(base, pwr);
    HSADC_WR_PWR2(base, pwr2);
    HSADC_WR_SAMPTIM(base, samptim);
}
  
/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_SetChn67MuxSel
 * Description   : Sets the mux channel of the channel 6 and channel 7 for converter A/B.
 *
 *END**************************************************************************/
void HSADC_HAL_SetChn67MuxSel(HSADC_Type* base, hsadc_conv_id_t convId, 
                      hsadc_chn67_mux_sel_t muxSel)
{
    switch (convId)
    {
        case kHSAdcConvA:
            HSADC_WR_MUX67_SEL_CH6_SELA(base, muxSel);
            HSADC_WR_MUX67_SEL_CH7_SELA(base, muxSel);
            break;
        case kHSAdcConvB:
            HSADC_WR_MUX67_SEL_CH6_SELB(base, muxSel);
            HSADC_WR_MUX67_SEL_CH7_SELB(base, muxSel);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_SetSlotSampleChn
 * Description   : Sets the specific slot to sample the specific channels.
 *
 *END**************************************************************************/
void HSADC_HAL_SetSlotSampleChn(HSADC_Type* base, uint16_t slotIdx, 
                        hsadc_slot_sample_chn_t channel)
{
    switch (slotIdx)
    {
        case 0U:
            HSADC_BWR_CLIST1_SAMPLE0(base, channel);
            break;
        case 1U:
            HSADC_BWR_CLIST1_SAMPLE1(base, channel);
            break;
        case 2U:
            HSADC_BWR_CLIST1_SAMPLE2(base, channel);
            break;
        case 3U:
            HSADC_BWR_CLIST1_SAMPLE3(base, channel);
            break;
        case 4U:
            HSADC_BWR_CLIST2_SAMPLE4(base, channel);
            break;
        case 5U:
            HSADC_BWR_CLIST2_SAMPLE5(base, channel);
            break;
        case 6U:
            HSADC_BWR_CLIST2_SAMPLE6(base, channel);
            break;
        case 7U:
            HSADC_BWR_CLIST2_SAMPLE7(base, channel);
            break;
        case 8U:
            HSADC_BWR_CLIST3_SAMPLE8(base, channel);
            break;
        case 9U:
            HSADC_BWR_CLIST3_SAMPLE9(base, channel);
            break;
        case 10U:
            HSADC_BWR_CLIST3_SAMPLE10(base, channel);
            break;
        case 11U:
            HSADC_BWR_CLIST3_SAMPLE11(base, channel);
            break;
        case 12U:
            HSADC_BWR_CLIST4_SAMPLE12(base, channel);
            break;
        case 13U:
            HSADC_BWR_CLIST4_SAMPLE13(base, channel);
            break;
        case 14U:
            HSADC_BWR_CLIST4_SAMPLE14(base, channel);
            break;
        case 15U:
            HSADC_BWR_CLIST4_SAMPLE15(base, channel);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSAdc_HAL_SetSlotZeroCrossMode
 * Description   : Sets the zero crossing mode for specific slot.
 *
 *END**************************************************************************/
void HSADC_HAL_SetSlotZeroCrossMode(HSADC_Type* base, uint16_t slotIdx, 
                            hsadc_zero_cross_mode_t zeroCrossMode)
{
    switch (slotIdx)
    {
        case 0U:
            HSADC_BWR_ZXCTRL1_ZCE0(base, zeroCrossMode);
            break;
        case 1U:
            HSADC_BWR_ZXCTRL1_ZCE1(base, zeroCrossMode);
            break;
        case 2U:
            HSADC_BWR_ZXCTRL1_ZCE2(base, zeroCrossMode);
            break;
        case 3U:
            HSADC_BWR_ZXCTRL1_ZCE3(base, zeroCrossMode);
            break;
        case 4U:
            HSADC_BWR_ZXCTRL1_ZCE4(base, zeroCrossMode);
            break;
        case 5U:
            HSADC_BWR_ZXCTRL1_ZCE5(base, zeroCrossMode);
            break;
        case 6U:
            HSADC_BWR_ZXCTRL1_ZCE6(base, zeroCrossMode);
            break;
        case 7U:
            HSADC_BWR_ZXCTRL1_ZCE7(base, zeroCrossMode);
            break;
        case 8U:
            HSADC_BWR_ZXCTRL2_ZCE8(base, zeroCrossMode);
            break;
        case 9U:
            HSADC_BWR_ZXCTRL2_ZCE9(base, zeroCrossMode);
            break;
        case 10U:
            HSADC_BWR_ZXCTRL2_ZCE10(base, zeroCrossMode);
            break;
        case 11U:
            HSADC_BWR_ZXCTRL2_ZCE11(base, zeroCrossMode);
            break;
        case 12U:
            HSADC_BWR_ZXCTRL2_ZCE12(base, zeroCrossMode);
            break;
        case 13U:
            HSADC_BWR_ZXCTRL2_ZCE13(base, zeroCrossMode);
            break;
        case 14U:
            HSADC_BWR_ZXCTRL2_ZCE14(base, zeroCrossMode);
            break;
        case 15U:
            HSADC_BWR_ZXCTRL2_ZCE15(base, zeroCrossMode);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_SetConvIntCmd
 * Description   : Sets if enable the specific interrupt for converter A/B.
 *
 *END**************************************************************************/
void HSADC_HAL_SetConvIntCmd(HSADC_Type* base, 
                     hsadc_conv_id_t convId, 
                     uint32_t intMask, 
                     bool enable)
{
    uint16_t ctrl1, ctrl2, calib;
    
    ctrl1 = HSADC_RD_CTRL1(base);
    ctrl2 = HSADC_RD_CTRL2(base);
    calib = HSADC_RD_CALIB(base);
    switch (convId)
    {
        case kHSAdcConvA:
            if (intMask & kHSAdcConvAllInt)/* Enable all the interrupts. */
            {
                ctrl1 &= ~HSADC_CTRL1_EOSIEA_MASK;
                calib &= ~HSADC_CALIB_EOCALIEA_MASK;
                if (enable)
                {
                    ctrl1 |= HSADC_CTRL1_EOSIEA_MASK;
                    calib |= HSADC_CALIB_EOCALIEA_MASK;
                }        
            }
            else /* Enable specific interrupt according to the bit mask. */
            {
                if (intMask & kHSAdcConvEndOfScanInt)
                {
                    ctrl1 &= ~HSADC_CTRL1_EOSIEA_MASK;
                    if (enable)
                    {
                        ctrl1 |= HSADC_CTRL1_EOSIEA_MASK;
                    }
                }
                if (intMask & kHSAdcConvEndOfCalibrationInt)
                {
                    calib &= ~HSADC_CALIB_EOCALIEA_MASK;
                    if (enable)
                    {
                        calib |= HSADC_CALIB_EOCALIEA_MASK;
                    }
                }                
            }
            break;
        case kHSAdcConvB:
            if (intMask & kHSAdcConvAllInt)/* Enable all the interrupts. */
            {
                ctrl2 &= ~HSADC_CTRL2_EOSIEB_MASK;
                calib &= ~HSADC_CALIB_EOCALIEB_MASK;
                if (enable)
                {
                    ctrl2 |= HSADC_CTRL2_EOSIEB_MASK;
                    calib |= HSADC_CALIB_EOCALIEB_MASK;
                }    
            }
            else /* Enable specific interrupt according to the bit mask. */
            {
                if (intMask & kHSAdcConvEndOfScanInt)
                {
                    ctrl2 &= ~HSADC_CTRL2_EOSIEB_MASK;
                    if (enable)
                    {
                        ctrl2 |= HSADC_CTRL2_EOSIEB_MASK;
                    }
                }
                if (intMask & kHSAdcConvEndOfCalibrationInt)
                {
                    calib &= ~HSADC_CALIB_EOCALIEB_MASK;
                    if (enable)
                    {
                        calib |= HSADC_CALIB_EOCALIEB_MASK;
                    }
                }                
            }
            break;
        default:
            break;
    }
    
    HSADC_WR_CTRL1(base, ctrl1);
    HSADC_WR_CTRL2(base, ctrl2);
    HSADC_WR_CALIB(base, calib);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_SetSlotIntCmd
 * Description   : This function sets if enable the interrupt for all slots.
 *
 *END**************************************************************************/
void HSADC_HAL_SetSlotIntCmd(HSADC_Type* base, uint32_t intMask, bool enable)
{
    uint16_t ctrl1;
    
    ctrl1 = HSADC_RD_CTRL1(base);
    
    if (intMask & kHSAdcSlotAllInt)/* Enable all the interrupts. */
    {
        ctrl1 &= ~(HSADC_CTRL1_ZCIE_MASK | HSADC_CTRL1_LLMTIE_MASK | 
                   HSADC_CTRL1_HLMTIE_MASK);
        if (enable)
        {
            ctrl1 |= (HSADC_CTRL1_ZCIE_MASK | HSADC_CTRL1_LLMTIE_MASK | 
                      HSADC_CTRL1_HLMTIE_MASK);
        }   
    }
    else /* Enable specific interrupt according to the bit mask. */
    {
        if (intMask & kHSAdcSlotZeroCrossInt)
        {
            ctrl1 &= ~HSADC_CTRL1_ZCIE_MASK;
            if (enable)
            {
                ctrl1 |= HSADC_CTRL1_ZCIE_MASK;
            }
        }
        if (intMask & kHSAdcSlotLowLimitInt)
        {
            ctrl1 &= ~HSADC_CTRL1_LLMTIE_MASK;
            if (enable)
            {
                ctrl1 |= HSADC_CTRL1_LLMTIE_MASK;
            }
        }
        if (intMask & kHSAdcSlotHighLimitInt)
        {
            ctrl1 &= ~HSADC_CTRL1_HLMTIE_MASK;
            if (enable)
            {
                ctrl1 |= HSADC_CTRL1_HLMTIE_MASK;
            }
        }        
    }
    
    HSADC_WR_CTRL1(base, ctrl1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_SetConvDmaCmd
 * Description   : This function sets if enable the DMA for converter A/B.
 *
 *END**************************************************************************/
void HSADC_HAL_SetConvDmaCmd(HSADC_Type* base, hsadc_conv_id_t convId, bool enable)
{
    switch (convId)
    {
        case kHSAdcConvA:
            if (enable)
            {
                HSADC_SET_CTRL1(base, HSADC_CTRL1_DMAENA_MASK);
            }
            else
            {
                HSADC_CLR_CTRL1(base, HSADC_CTRL1_DMAENA_MASK);
            }
            
            break;
        case kHSAdcConvB:
            if (enable)
            {
                HSADC_SET_CTRL2(base, HSADC_CTRL2_DMAENB_MASK);
            }
            else
            {
                HSADC_CLR_CTRL2(base, HSADC_CTRL2_DMAENB_MASK);
            }
            
            break;
        default:
            break;
    }    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_SetConvEnableCmd
 * Description   : Sets the enablement command for converter A/B.
 *
 *END**************************************************************************/
void HSADC_HAL_SetConvEnableCmd(HSADC_Type* base, 
                        hsadc_conv_id_t convId, 
                        hsadc_conv_enable_cmd_t cmd, 
                        bool enable)
{
    switch (convId)
    {
        case kHSAdcConvA:
            if (cmd == kHSAdcConvSyncInputEnable)
            {
                if (enable)
                {
                    HSADC_SET_CTRL1(base, HSADC_CTRL1_SYNCA_MASK);
                }
                else
                {
                    HSADC_CLR_CTRL1(base, HSADC_CTRL1_SYNCA_MASK);
                }
            }
            else if (cmd == kHSAdcConvStopEnable)
            {
                if (enable)
                {
                    HSADC_SET_CTRL1(base, HSADC_CTRL1_STOPA_MASK);
                }
                else
                {
                    HSADC_CLR_CTRL1(base, HSADC_CTRL1_STOPA_MASK);
                }
            }
            else if (cmd == kHSAdcConvPowerDownEnable)
            {
                if (enable)
                {
                    HSADC_SET_PWR(base, HSADC_PWR_PDA_MASK);
                }
                else
                {
                    HSADC_CLR_PWR(base, HSADC_PWR_PDA_MASK);
                }
            }
            else if (cmd == kHSAdcConvCalibrationBypassEnable)
            {
                if (enable)
                {
                    HSADC_SET_CALIB(base, HSADC_CALIB_BYPA_MASK);
                }
                else
                {
                    HSADC_CLR_CALIB(base, HSADC_CALIB_BYPA_MASK);
                }
            }          
            break;
        case kHSAdcConvB:
            if (cmd == kHSAdcConvSyncInputEnable)
            {
                if (enable)
                {
                    HSADC_SET_CTRL2(base, HSADC_CTRL2_SYNCB_MASK);
                }
                else
                {
                    HSADC_CLR_CTRL2(base, HSADC_CTRL2_SYNCB_MASK);
                }
            }
            else if (cmd == kHSAdcConvStopEnable)
            {
                if (enable)
                {
                    HSADC_SET_CTRL2(base, HSADC_CTRL2_STOPB_MASK);
                }
                else
                {
                    HSADC_CLR_CTRL2(base, HSADC_CTRL2_STOPB_MASK);
                }
            }
            else if (cmd == kHSAdcConvPowerDownEnable)
            {
                if (enable)
                {
                    HSADC_SET_PWR(base, HSADC_PWR_PDB_MASK);
                }
                else
                {
                    HSADC_CLR_PWR(base, HSADC_PWR_PDB_MASK);
                }
            }
            else if (cmd == kHSAdcConvCalibrationBypassEnable)
            {
                if (enable)
                {
                    HSADC_SET_CALIB(base, HSADC_CALIB_BYPB_MASK);
                }
                else
                {
                    HSADC_CLR_CALIB(base, HSADC_CALIB_BYPB_MASK);
                }
            }
            break;
        default:
            break;
    }  
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_SetSlotEnableCmd
 * Description   : Sets the enablement command for the specific slots.
 *
 *END**************************************************************************/
void HSADC_HAL_SetSlotEnableCmd(HSADC_Type* base, 
                        uint16_t slotMask,
                        hsadc_slot_enable_cmd_t cmd, 
                        bool enable)
{
    switch (cmd)
    {
        case kHSAdcSlotDisable:
            if (enable)
            {
                HSADC_SET_SDIS(base, slotMask);
            }
            else
            {
                HSADC_CLR_SDIS(base, slotMask);
            }
            break;
        case kHSAdcSlotWaitSyncEnable:
            if (enable)
            {
                HSADC_SET_SCTRL(base, slotMask);
            }
            else
            {
                HSADC_CLR_SCTRL(base, slotMask);
            }
            break;
        case kHSAdcSlotScanIntEnable:
            if (enable)
            {
                HSADC_SET_SCINTEN(base, slotMask);
            }
            else
            {
                HSADC_CLR_SCINTEN(base, slotMask);
            }
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_SoftTriggerConv
 * Description   : Sets the converter A/B to start conversion.
 *
 *END**************************************************************************/
void HSADC_HAL_SoftTriggerConv(HSADC_Type* base, hsadc_conv_id_t convId)
{
    switch (convId)
    {
        case kHSAdcConvA:
            HSADC_SET_CTRL1(base, HSADC_CTRL1_STARTA_MASK);
            break;
        case kHSAdcConvB:
            HSADC_SET_CTRL2(base, HSADC_CTRL2_STARTB_MASK);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_GetConvFlag
 * Description   : Gets the status of the specific flag of the converter A/B.
 *
 *END**************************************************************************/
bool HSADC_HAL_GetConvFlag(HSADC_Type* base, hsadc_conv_id_t convId, 
                   hsadc_conv_flag_t flag)
{
    switch (convId)
    {
        case kHSAdcConvA:
            if (flag == kHSAdcConvCalibrationRunning)
            {
                return HSADC_BRD_STAT_CALONA(base);
            }
            else if (flag == kHSAdcConvDummyConversionRunning)
            {
                return HSADC_BRD_STAT_DUMMYA(base);
            }
            else if (flag == kHSAdcConvEndOfCalibrationIntHappened)
            {
                return HSADC_BRD_STAT_EOCALIA(base);
            }
            else if (flag == kHSAdcConvEndOfScanIntHappened)
            {
                return HSADC_BRD_STAT_EOSIA(base);
            }
            else if (flag == kHSAdcConvConversionInProgress)
            {
                return HSADC_BRD_STAT_CIPA(base);
            }
            else if (flag == kHSAdcConvPowerStatusStable)
            {
                return HSADC_BRD_PWR_PSTSA(base);
            }
            break;
        case kHSAdcConvB:
            if (flag == kHSAdcConvCalibrationRunning)
            {
                return HSADC_BRD_STAT_CALONB(base);
            }
            else if (flag == kHSAdcConvDummyConversionRunning)
            {
                return HSADC_BRD_STAT_DUMMYB(base);
            }
            else if (flag == kHSAdcConvEndOfCalibrationIntHappened)
            {
                return HSADC_BRD_STAT_EOCALIB(base);
            }
            else if (flag == kHSAdcConvEndOfScanIntHappened)
            {
                return HSADC_BRD_STAT_EOSIB(base);
            }
            else if (flag == kHSAdcConvConversionInProgress)
            {
                return HSADC_BRD_STAT_CIPB(base);
            }
            else if (flag == kHSAdcConvPowerStatusStable)
            {
                return HSADC_BRD_PWR_PSTSB(base);
            }
            break;
        default:
            break;
    }
    return false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_ClearConvFlag
 * Description   : Clears the specific flag for the converter A/B.
 *
 *END**************************************************************************/
void HSADC_HAL_ClearConvFlag(HSADC_Type* base, hsadc_conv_id_t convId, 
                     hsadc_conv_flag_t flag)
{ 
    switch (convId)
    {
        case kHSAdcConvA:            
            if (flag == kHSAdcConvEndOfCalibrationIntHappened)
            {
                HSADC_SET_STAT(base, HSADC_STAT_EOCALIA_MASK);
            }
            else if (flag == kHSAdcConvEndOfScanIntHappened)
            {
                HSADC_SET_STAT(base, HSADC_STAT_EOSIA_MASK);
            }
            break;
        case kHSAdcConvB:
            if (flag == kHSAdcConvEndOfCalibrationIntHappened)
            {
                HSADC_SET_STAT(base, HSADC_STAT_EOCALIB_MASK);
            }
            else if (flag == kHSAdcConvEndOfScanIntHappened)
            {
                HSADC_SET_STAT(base, HSADC_STAT_EOSIB_MASK);
            }
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_GetGlobalSlotFlag
 * Description   : Gets the status of the global flag of all slots.
 *
 *END**************************************************************************/
bool HSADC_HAL_GetGlobalSlotFlag(HSADC_Type* base, hsadc_global_slot_flag_t flag)
{
    bool result = false;
    switch (flag)
    {
        case kHSAdcGlobalSlotHighLimitIntHappened:
            result = HSADC_BRD_STAT_HLMTI(base);
            break;
        case kHSAdcGlobalSlotLowLimitIntHappened:
            result = HSADC_BRD_STAT_LLMTI(base);
            break;
        case kHSAdcGlobalSlotZeroCrossIntHappened:
            result = HSADC_BRD_STAT_ZCI(base);
            break;
        default:
            break;
    }
    return result;     
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_ClearGlobalSlotFlag
 * Description   : Clears the global flag for all slots.
 *
 *END**************************************************************************/
void HSADC_HAL_ClearGlobalSlotFlag(HSADC_Type* base, hsadc_global_slot_flag_t flag)
{
    uint16_t slotMask = 0xFFFFU;
    
    switch (flag)
    {
        case kHSAdcGlobalSlotHighLimitIntHappened:
            HSADC_WR_HILIMSTAT(base, slotMask);
            break;
        case kHSAdcGlobalSlotLowLimitIntHappened:
            HSADC_WR_LOLIMSTAT(base, slotMask);
            break;
        case kHSAdcGlobalSlotZeroCrossIntHappened:
            HSADC_WR_ZXSTAT(base, slotMask);
            break;
        default:
            break;
    } 
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_GetSpecificSlotFlag
 * Description   : Gets the status of the specific flag of the sample slots.
 *
 *END**************************************************************************/
uint16_t HSADC_HAL_GetSpecificSlotFlag(HSADC_Type* base, uint16_t slotMask, 
                               hsadc_specific_slot_flag_t flag)
{
    uint16_t result = 0U;
    switch (flag)
    {
        case kHSAdcSpecificSlotHighLimitIntHappened:
            result = (HSADC_RD_HILIMSTAT(base) & slotMask);
            break;
        case kHSAdcSpecificSlotLowLimitIntHappened:
            result = (HSADC_RD_LOLIMSTAT(base) & slotMask);
            break;
        case kHSAdcSpecificSlotZeroCrossIntHappened:
            result = (HSADC_RD_ZXSTAT(base) & slotMask);
            break;
        case kHSAdcSpecificSlotResultReady:
            result = (HSADC_RD_RDY(base) & slotMask);
            break;
        default:
            break;
    }
    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_ClearSpecificSlotFlag
 * Description   : This function clears the specific flag for the specific slots.
 *
 *END**************************************************************************/
void HSADC_HAL_ClearSpecificSlotFlag(HSADC_Type* base, uint16_t slotMask, 
                             hsadc_specific_slot_flag_t flag)
{
    switch (flag)
    {     
        case kHSAdcSpecificSlotHighLimitIntHappened:
            HSADC_WR_HILIMSTAT(base, slotMask);
            break;
        case kHSAdcSpecificSlotLowLimitIntHappened:
            HSADC_WR_LOLIMSTAT(base, slotMask);
            break;
        case kHSAdcSpecificSlotZeroCrossIntHappened:
            HSADC_WR_ZXSTAT(base, slotMask);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_SetCalibrationCmd
 * Description   : Sets to enable or disable the calibration request for converter A/B.
 *
 *END**************************************************************************/
void HSADC_HAL_SetCalibrationCmd(HSADC_Type* base, 
                         hsadc_conv_id_t convId, 
                         hsadc_calibration_mode_t mode,
                         bool enable)
{
    switch (convId)
    {
        case kHSAdcConvA:
            if (enable)
            {
                if (mode == kHSAdcCalibrationSingleEnded)
                {
                    HSADC_SET_CALIB(base, HSADC_CALIB_REQSINGA_MASK);
                    HSADC_SET_CALIB(base, HSADC_CALIB_CAL_REQA_MASK);
                }
                else if (mode == kHSAdcCalibrationDifferential)
                {
                    HSADC_SET_CALIB(base, HSADC_CALIB_REQDIFA_MASK);
                    HSADC_SET_CALIB(base, HSADC_CALIB_CAL_REQA_MASK);                    
                }
                else
                {
                    HSADC_SET_CALIB(base, HSADC_CALIB_REQSINGA_MASK);
                    HSADC_SET_CALIB(base, HSADC_CALIB_REQDIFA_MASK);
                    HSADC_SET_CALIB(base, HSADC_CALIB_CAL_REQA_MASK); 
                }
            }
            else
            {
                if (mode == kHSAdcCalibrationSingleEnded)
                {
                    HSADC_CLR_CALIB(base, HSADC_CALIB_REQSINGA_MASK);
                }
                else if (mode == kHSAdcCalibrationDifferential)
                {
                    HSADC_CLR_CALIB(base, HSADC_CALIB_REQDIFA_MASK);
                }
                else
                {
                    HSADC_CLR_CALIB(base, HSADC_CALIB_REQSINGA_MASK);
                    HSADC_CLR_CALIB(base, HSADC_CALIB_REQDIFA_MASK);
                }
            }            
            break;
        case kHSAdcConvB:
            if (enable)
            {
                if (mode == kHSAdcCalibrationSingleEnded)
                {
                    HSADC_SET_CALIB(base, HSADC_CALIB_REQSINGB_MASK);
                    HSADC_SET_CALIB(base, HSADC_CALIB_CAL_REQB_MASK);                    
                }
                else if (mode == kHSAdcCalibrationDifferential)
                {
                    HSADC_SET_CALIB(base, HSADC_CALIB_REQDIFB_MASK);
                    HSADC_SET_CALIB(base, HSADC_CALIB_CAL_REQB_MASK);                    
                }
                else
                {
                    HSADC_SET_CALIB(base, HSADC_CALIB_REQSINGB_MASK);
                    HSADC_SET_CALIB(base, HSADC_CALIB_REQDIFB_MASK);
                    HSADC_SET_CALIB(base, HSADC_CALIB_CAL_REQB_MASK);    
                }
            }
            else
            {
                if (mode == kHSAdcCalibrationSingleEnded)
                {
                    HSADC_CLR_CALIB(base, HSADC_CALIB_REQSINGB_MASK);
                }
                else if (mode == kHSAdcCalibrationDifferential)
                {
                    HSADC_CLR_CALIB(base, HSADC_CALIB_REQDIFB_MASK);
                }
                else
                {
                    HSADC_CLR_CALIB(base, HSADC_CALIB_REQSINGB_MASK);
                    HSADC_CLR_CALIB(base, HSADC_CALIB_REQDIFB_MASK);
                }
            }
            
            break;
        default:
            break; 
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : HSADC_HAL_GetCalibrationValue
 * Description   : Gets the calibration value of converter A/B.
 *
 *END**************************************************************************/
uint16_t HSADC_HAL_GetCalibrationValue(HSADC_Type* base, hsadc_conv_id_t convId, 
                               hsadc_calibration_mode_t mode)
{
    uint16_t result = 0U;
    switch (convId)
    {
        case kHSAdcConvA:
            if (mode == kHSAdcCalibrationSingleEnded)
            {
                result = HSADC_RD_CALVAL_A_CALVSING(base);
            }
            else
            {
                result = HSADC_RD_CALVAL_A_CALVDIF(base);
            }
            break;
        case kHSAdcConvB:
            if (mode == kHSAdcCalibrationSingleEnded)
            {
                result = HSADC_RD_CALVAL_B_CALVSING(base);
            }
            else
            {
                result = HSADC_RD_CALVAL_B_CALVDIF(base);
            }
            break;
        default:
            break; 
    }
    return result;
}




