/*
 * Copyright (c) 2013-2014, Freescale Semiconductor, Inc.
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
/*!
** @file pin_mux.h
** @version 1.1
** @brief
**
*/         
/*!
**  @addtogroup pin_mux_module pin_mux module documentation
**  @{
*/         

#ifndef pin_mux_H_
#define pin_mux_H_

/* MODULE pin_mux. */


/*
** ===================================================================
**     Method      :  pin_mux_ENET (component PinSettings)
*/
/*!
**     @brief
**         ENET method sets registers according routing settings. Call
**         this method code to route desired pins into ENET periphery.
**     @param
**         uint32_t instance - ENET instance number (0 is expected)
*/
/* ===================================================================*/
void configure_enet_pins(uint32_t instance);
/*
** ===================================================================
**     Method      :  pin_mux_JTAG (component PinSettings)
*/
/*!
**     @brief
**         JTAG method sets registers according routing settings. Call
**         this method code to route desired pins into JTAG periphery.
**     @param
**         uint32_t instance - JTAG instance number (0 is expected)
*/
/* ===================================================================*/
void configure_jtag_pins(uint32_t instance);
/*
** ===================================================================
**     Method      :  pin_mux_SCB (component PinSettings)
*/
/*!
**     @brief
**         SCB method sets registers according routing settings. Call
**         this method code to route desired pins into SystemControl periphery.
**     @param
**         uint32_t instance - SCB instance number (0 is expected)
*/
/* ===================================================================*/
void configure_scb_pins(uint32_t instance);
/*
** ===================================================================
**     Method      :  pin_mux_UART (component PinSettings)
*/
/*!
**     @brief
**         UART method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         UART0, UART1
**         peripherals.
**     @param
**         uint32_t instance - UART instance number 0..1
*/
/* ===================================================================*/
void configure_uart_pins(uint32_t instance);

/*
** ===================================================================
**     Method      :  pin_mux_I2C (component PinSettings)
*/
/*!
**     @brief
**         I2C method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         I2C0, I2C1, I2C2
**         peripherals.
**     @param
**         uint32_t instance - I2C instance number 0..2
*/
/* ===================================================================*/
void configure_i2c_pins(uint32_t instance);
/*
** ===================================================================
**     Method      :  pin_mux_FTM (component PinSettings)
*/
/*!
**     @brief
**         FTM method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         FTM0, FTM1, FTM2, FTM3
**         peripherals.
**     @param
**         uint32_t instance - FTM instance number 0..3
*/
/* ===================================================================*/
void configure_ftm_pins(uint32_t instance);
/*
** ===================================================================
**     Method      :  pin_mux_CAN (component PinSettings)
*/
/*!
**     @brief
**         CAN method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         CAN0,CAN1
**         peripherals.
**     @param
**         uint32_t instance - CAN instance number 0,1
*/
/* ===================================================================*/
void configure_can_pins(uint32_t instance);


void configure_spi_pins(uint32_t instance);

/*
** ===================================================================
**     Method      :  pin_mux_PWM (component PinSettings)
*/
/*!
**     @brief
**         PWM method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         ENC
**         peripherals.
**     @param
**         uint32_t instance - PWM instance number 0..1
*/
/* ===================================================================*/

void configure_pwm_pins(uint32_t instance);
/*
** ===================================================================
**     Method      :  pin_mux_ENC (component PinSettings)
*/
/*!
**     @brief
**         ENC method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         ENC
**         peripherals.
**     @param
**         uint32_t instance - ENC instance number 0..1
*/
/* ===================================================================*/
void configure_enc_pins(uint32_t instance);

void configure_cmp_pins(uint32_t instance);

/*
** ===================================================================
**     Method      :  configure_gpio_pins (component PinSettings)
*/
/*!
**     @brief
**         gpio_pin_mux method configures the various ports pins mux settings
**         This method sets the mux settings of all LED and switch pins.
*/
/* ===================================================================*/
void configure_gpio_pins(uint32_t instance);

void configure_dac_pins(uint32_t instance);

/*
** ===================================================================
**     Method      :  configure_xbarb_pins (component PinSettings)
*/
/*!
**     @brief
**         configure_xbarb_pins method sets registers according routing
**         settings. Call this method code to route desired pins into:
**         XBARB peripheral.
**         
**     @param
**         uint32_t instance - XBARB instance number 0
*/
/* ===================================================================*/
void configure_xbarb_pins(uint32_t instance);
/* END pin_mux. */
#endif /* #ifndef __pin_mux_H_ */
/*!
** @}
*/

