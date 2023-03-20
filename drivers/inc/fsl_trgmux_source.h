/*
** ###################################################################
**     Version:             rev. 1.0, 2015-06-04
**     Build:               b150605
**
**     Abstract:
**         Enumeration value mapping header.
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2015-06-04)
**         Initial Version.
**
** ###################################################################
*/

#if !defined(__FSL_TRGMUX_SOURCE_H__)
#define __FSL_TRGMUX_SOURCE_H__

/*!
 * @addtogroup trgmux_source
 * @{ */

/*******************************************************************************
 * Definitions
*******************************************************************************/

/*!
 * @brief Structure for the TRGMUX source
 *
 * Defines the structure for the TRGMUX source collections.
 */
typedef enum _trgmux_source {
#if defined(CPU_MKL28Z512VDC7) || defined(CPU_MKL28Z512VLH7) || defined(CPU_MKL28Z512VLL7) || defined(CPU_MKL28Z512VMP7)
    kTrgmuxSrcDisabled = 0U, /*!< Trigger function is disabled */
    kTrgmuxSrcPortPin = 1U, /*!< Port pin trigger intput is selected */
    kTrgmuxSrcFlexIOTimer0 = 2U, /*!< FlexIO Timer 0 input is selected */
    kTrgmuxSrcFlexIOTimer1 = 3U, /*!< FlexIO Timer 1 input is selected */
    kTrgmuxSrcFlexIOTimer2 = 4U, /*!< FlexIO Timer 2 input is selected */
    kTrgmuxSrcFlexIOTimer3 = 5U, /*!< FlexIO Timer 3 input is selected */
    kTrgmuxSrcFlexIOTimer4 = 6U, /*!< FlexIO Timer 4 input is selected */
    kTrgmuxSrcFlexIOTimer5 = 7U, /*!< FlexIO Timer 5 input is selected */
    kTrgmuxSrcFlexIOTimer6 = 8U, /*!< FlexIO Timer 6 input is selected */
    kTrgmuxSrcFlexIOTimer7 = 9U, /*!< FlexIO Timer 7 input is selected */
    kTrgmuxSrcTpm0Overflow = 10U, /*!< TPM0 Overflow is selected */
    kTrgmuxSrcTpm0Ch0 = 11U, /*!< TPM0 Channel 0 is selected */
    kTrgmuxSrcTpm0Ch1 = 12U, /*!< TPM0 Channel 1 is selected */
    kTrgmuxSrcTpm1Overflow = 13U, /*!< TPM1 Overflow is selected */
    kTrgmuxSrcTpm1Ch0 = 14U, /*!< TPM1 Channel 0 is selected */
    kTrgmuxSrcTpm1Ch1 = 15U, /*!< TPM1 Channel 1 is selected */
    kTrgmuxSrcLpit1Ch0 = 16U, /*!< LPIT1 Channel 0 is selected */
    kTrgmuxSrcLpit1Ch1 = 17U, /*!< LPIT1 Channel 1 is selected */
    kTrgmuxSrcLpit1Ch2 = 18U, /*!< LPIT1 Channel 2 is selected */
    kTrgmuxSrcLpit1Ch3 = 19U, /*!< LPIT1 Channel 3 is selected */
    kTrgmuxSrcLpuart0RxData = 20U, /*!< LPUART0 RX Data is selected */
    kTrgmuxSrcLpuart0TxData = 21U, /*!< LPUART0 TX Data is selected */
    kTrgmuxSrcLpuart0RxIdle = 22U, /*!< LPUART0 RX Idle is selected */
    kTrgmuxSrcLpuart1RxData = 23U, /*!< LPUART1 RX Data is selected */
    kTrgmuxSrcLpuart1TxData = 24U, /*!< LPUART1 TX Data is selected */
    kTrgmuxSrcLpuart1RxIdle = 25U, /*!< LPUART1 RX Idle is selected */
    kTrgmuxSrcLpi2c0MasterStop = 26U, /*!< LPI2C0 Master STOP is selected */
    kTrgmuxSrcLpi2c0SlaveStop = 27U, /*!< LPI2C0 Slave STOP is selected */
    kTrgmuxSrcLpi2c1MasterStop = 28U, /*!< LPI2C1 Master STOP is selected */
    kTrgmuxSrcLpi2c1SlaveStop = 29U, /*!< LPI2C1 Slave STOP is selected */
    kTrgmuxSrcLpspi0Frame = 30U, /*!< LPSPI0 Frame is selected */
    kTrgmuxSrcLpspi0RxData = 31U, /*!< LPSPI0 RX Data is selected */
    kTrgmuxSrcLpspi1Frame = 32U, /*!< LPSPI1 Frame is selected */
    kTrgmuxSrcLpspi1RxData = 33U, /*!< LPSPI1 RX Data is selected */
    kTrgmuxSrcRtcSecCount = 34U, /*!< RTC Seconds Counter is selected */
    kTrgmuxSrcRtcAlarm = 35U, /*!< RTC Alarm is selected */
    kTrgmuxSrcLptmr0Trg = 36U, /*!< LPTMR0 Trigger is selected */
    kTrgmuxSrcLptmr1Trg = 37U, /*!< LPTMR1 Trigger is selected */
    kTrgmuxSrcCmp0Output = 38U, /*!< CMP0 Output is selected */
    kTrgmuxSrcCmp1Output = 39U, /*!< CMP1 Output is selected */
    kTrgmuxSrcAdc0ConvAComplete = 40U, /*!< ADC0 Conversion A Complete is selected */
    kTrgmuxSrcAdc0ConvBComplete = 41U, /*!< ADC0 Conversion B Complete is selected */
    kTrgmuxSrcPortAPinTrg = 42U, /*!< Port A Pin Trigger is selected */
    kTrgmuxSrcPortBPinTrg = 43U, /*!< Port B Pin Trigger is selected */
    kTrgmuxSrcPortCPinTrg = 44U, /*!< Port C Pin Trigger is selected */
    kTrgmuxSrcPortDPinTrg = 45U, /*!< Port D Pin Trigger is selected */
    kTrgmuxSrcPortEPinTrg = 46U, /*!< Port E Pin Trigger is selected */
    kTrgmuxSrcTpm2Overflow = 47U, /*!< TPM2 Overflow is selected */
    kTrgmuxSrcTpm2Ch0 = 48U, /*!< TPM2 Channel 0 is selected */
    kTrgmuxSrcTpm2Ch1 = 49U, /*!< TPM2 Channel 1 is selected */
    kTrgmuxSrcLpit0Ch0 = 50U, /*!< LPIT0 Channel 0 is selected */
    kTrgmuxSrcLpit0Ch1 = 51U, /*!< LPIT0 Channel 1 is selected */
    kTrgmuxSrcLpit0Ch2 = 52U, /*!< LPIT0 Channel 2 is selected */
    kTrgmuxSrcLpit0Ch3 = 53U, /*!< LPIT0 Channel 3 is selected */
    kTrgmuxSrcUsbSof = 54U, /*!< USB Start-of-Frame is selected */
    kTrgmuxSrcLpuart2RxData = 55U, /*!< LPUART2 RX Data is selected */
    kTrgmuxSrcLpuart2TxData = 56U, /*!< LPUART2 TX Data is selected */
    kTrgmuxSrcLpuart2RxIdle = 57U, /*!< LPUART2 RX Idle is selected */
    kTrgmuxSrcLpi2c2MasterStop = 58U, /*!< LPI2C2 Master STOP is selected */
    kTrgmuxSrcLpi2c2SlaveStop = 59U, /*!< LPI2C2 Slave STOP is selected */
    kTrgmuxSrcLpspi2Frame = 60U, /*!< LPSPI2 Frame is selected */
    kTrgmuxSrcLpspi2RxData = 61U, /*!< LPSPI2 RX Data is selected */
    kTrgmuxSrcI2c0TxFrameSync = 62U, /*!< I2C0 TX Frame Sync is selected */
    kTrgmuxSrcI2c0RxFrameSync = 63U, /*!< I2C0 RX Frame Sync is selected */
#else
    #error "No valid CPU defined!"
#endif
} trgmux_source_t;

/* @} */

#endif /* __FSL_TRGMUX_SOURCE_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/

