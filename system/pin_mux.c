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
** @file pin_mux.c
** @version 1.1
** @brief
**
*/
/*!
**  @addtogroup pin_mux_module pin_mux module documentation
**  @{
*/

/* MODULE pin_mux. */

#include "fsl_device_registers.h"
#include "fsl_port_hal.h"
#include "pin_mux.h"

void configure_enet_pins(uint32_t instance)
{
    /* ENET0_1588_TMR0 PORTC_PCR16 */
    PORT_HAL_SetMuxMode(PORTC,16u,kPortMuxAlt4);
    /* ENET0_1588_TMR1 PORTC_PCR17 */
    PORT_HAL_SetMuxMode(PORTC,17u,kPortMuxAlt4);
    /* ENET0_1588_TMR2 PORTC_PCR18 */
    PORT_HAL_SetMuxMode(PORTC,18u,kPortMuxAlt4);
    /* ENET0_1588_TMR3 PORTC_PCR19 */
    PORT_HAL_SetMuxMode(PORTC,19u,kPortMuxAlt4);

    /* MII0_COL                --- ETH_COL   --- B12 --- PTA29a5 */
    PORT_HAL_SetMuxMode(PORTA,29u,kPortMuxAlt5);
    /* MII0_CRS                --- ETH_CRS   --- A12 --- PTA27a5 */
    PORT_HAL_SetMuxMode(PORTA,27u,kPortMuxAlt5);
    /* RMII0_MDC/MII0_MDC      --- ETH_MDC   --- A13 --- PTA8a5  */
    PORT_HAL_SetMuxMode(PORTA,8u,kPortMuxAlt5);
    /* RMII0_MDIO/MII0_MDIO    --- ETH_MDIO  --- A14 --- PTA7a5  */
    PORT_HAL_SetMuxMode(PORTA,7u,kPortMuxAlt5);
    PORT_HAL_SetOpenDrainCmd(PORTA,7u,true);
    /* MII0_RXCLK              --- ETH_RXCLK --- A15 --- PTA11a5 */
    PORT_HAL_SetMuxMode(PORTA,11u,kPortMuxAlt5);
    /* RMII0_RXD0/MII0_RXD0    --- ETH_RXD0  --- A20 --- PTA13a5 */
    PORT_HAL_SetMuxMode(PORTA,13u,kPortMuxAlt5);
    /* RMII0_RXD1/MII0_RXD1    --- ETH_RXD1  --- A19 --- PTA12a5 */
    PORT_HAL_SetMuxMode(PORTA,12u,kPortMuxAlt5);
    /* MII0_RXD2               --- ETH_RXD2  --- A18 --- PTA10a5 */
    PORT_HAL_SetMuxMode(PORTA,10u,kPortMuxAlt5);
    /* MII0_RXD3               --- ETH_RXD3  --- A17 --- PTA9a5  */
    PORT_HAL_SetMuxMode(PORTA,9u,kPortMuxAlt5);
    /* RMII0_CRS_DV/MII0_RXDV  --- ETH_RXDV  --- A16 --- PTA14a5 */
    PORT_HAL_SetMuxMode(PORTA,14u,kPortMuxAlt5);
    /* RMII0_RXER/MII0_RXER    --- ETH_RXER  --- B13 --- PTA5a4  */
    PORT_HAL_SetMuxMode(PORTA,5u,kPortMuxAlt4);
    /* MII0_TXCLK              --- ETH_TXCLK --- B14 --- PTA25a5 */
    PORT_HAL_SetMuxMode(PORTA,25u,kPortMuxAlt5);
    /* RMII0_TXD0/MII0_TXD0    --- ETH_TXD0  --- B20 --- PTA16a5 */
    PORT_HAL_SetMuxMode(PORTA,16u,kPortMuxAlt5);
    /* RMII0_TXD1/MII0_TXD1    --- ETH_TXD1  --- B19 --- PTA17a5 */
    PORT_HAL_SetMuxMode(PORTA,17u,kPortMuxAlt5);
    /* MII0_TXD2               ---  ETH_TXD2 --- B18 --- PTA24a5 */
    PORT_HAL_SetMuxMode(PORTA,24u,kPortMuxAlt5);
    /* MII0_TXD3               --- ETH_TXD3  --- B17 --- PTA26a5 */
    PORT_HAL_SetMuxMode(PORTA,26u,kPortMuxAlt5);
    /* RMII0_TXEN/MII0_TXEN    --- ETH_TXEN  --- B15 --- PTA15a5 */
    PORT_HAL_SetMuxMode(PORTA,15u,kPortMuxAlt5);

    /* MII0_TXER               --- ETH_TXER  --- B16 --- PORTA_PCR28 */
    PORT_HAL_SetMuxMode(PORTA,28u,kPortMuxAlt5);
}

void configure_gpio_pins(uint32_t instance)
{
    switch(instance) {
        case PORTA_IDX:                             /* PTA */
            PORT_HAL_SetMuxMode(PORTA, 4, kPortMuxAsGpio);
            break;
        case PORTB_IDX:                             /* PTB */
            PORT_HAL_SetMuxMode(PORTB, 4, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTB, 5, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTB, 6, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTB, 7, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTB, 8, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTB, 9, kPortMuxAsGpio);
            break;
        case PORTC_IDX:                             /* PTC */
            PORT_HAL_SetMuxMode(PORTC, 18, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTC, 19, kPortMuxAsGpio);
            break;
        case PORTD_IDX:                             /* PTD */
            PORT_HAL_SetMuxMode(PORTD, 7, kPortMuxAsGpio);
            break;
        case PORTE_IDX:                             /* PTE */
            PORT_HAL_SetMuxMode(PORTE, 4, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTE, 11, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTE, 12, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTE, 13, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTE, 24, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTE, 27, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTE, 28, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTE, 29, kPortMuxAsGpio);
            PORT_HAL_SetMuxMode(PORTE, 30, kPortMuxAsGpio);
            break;
        default:
            break;
    }
}

void configure_jtag_pins(uint32_t instance)
{
    /* PORTA_PCR0 */
    PORT_HAL_SetMuxMode(PORTA,0u,kPortMuxAlt7);
    /* PORTA_PCR1 */
    PORT_HAL_SetMuxMode(PORTA,1u,kPortMuxAlt7);
    /* PORTA_PCR2 */
    PORT_HAL_SetMuxMode(PORTA,2u,kPortMuxAlt7);
    /* PORTA_PCR3 */
    PORT_HAL_SetMuxMode(PORTA,3u,kPortMuxAlt7);
}

void configure_scb_pins(uint32_t instance)
{
    /* PORTA_PCR4 */
    PORT_HAL_SetMuxMode(PORTA,4u,kPortMuxAlt7);
}

void configure_uart_pins(uint32_t instance)
{
    switch(instance) {
        case UART0_IDX:                      /* UART0 */
            /* PORTB_PCR0 */
            PORT_HAL_SetMuxMode(PORTB,0u,kPortMuxAlt7);
            /* PORTB_PCR1 */
            PORT_HAL_SetMuxMode(PORTB,1u,kPortMuxAlt7);
            break;
        default:
            break;
    }
}

void configure_i2c_pins(uint32_t instance)
{
    switch(instance) {
        case I2C0_IDX:                       /* I2C0 */
            /* Affects PORTB_PCR2 register */
            PORT_HAL_SetMuxMode(PORTB,2u,kPortMuxAlt2);
            PORT_HAL_SetPullCmd(PORTB, 2u, true);
            PORT_HAL_SetPullMode(PORTB, 2u, kPortPullUp);
            PORT_HAL_SetOpenDrainCmd(PORTB,2u,true);
            /* Affects PORTB_PCR3 register */
            PORT_HAL_SetMuxMode(PORTB,3u,kPortMuxAlt2);
            PORT_HAL_SetPullCmd(PORTB, 3u, true);
            PORT_HAL_SetPullMode(PORTB, 3u, kPortPullUp);
            PORT_HAL_SetOpenDrainCmd(PORTB,3u,true);
            break;
        case I2C1_IDX:                       /* I2C1 */
            /* Affects PORTD_PCR8 register */
            PORT_HAL_SetMuxMode(PORTD,8u,kPortMuxAlt2);
            PORT_HAL_SetPullCmd(PORTD, 8u, true);
            PORT_HAL_SetPullMode(PORTD, 8u, kPortPullUp);
            PORT_HAL_SetOpenDrainCmd(PORTD,8u,true);
            PORT_HAL_SetPassiveFilterCmd(PORTD,8u,false);
            /* Affects PORTD_PCR9 register */
            PORT_HAL_SetMuxMode(PORTD,9u,kPortMuxAlt2);
            PORT_HAL_SetPullCmd(PORTD, 9u, true);
            PORT_HAL_SetPullMode(PORTD, 9u, kPortPullUp);
            PORT_HAL_SetOpenDrainCmd(PORTD,9u,true);
            PORT_HAL_SetPassiveFilterCmd(PORTD, 9u, false);            
            break;
        default:
            break;
    }
}

void configure_spi_pins(uint32_t instance)
{
    switch(instance) {
        case SPI0_IDX:                       /* SPI0 */
            /* PORTE_PCR16 */
            PORT_HAL_SetMuxMode(PORTE, 16u,kPortMuxAlt2);
            /* PORTE_PCR19 */
            PORT_HAL_SetMuxMode(PORTE, 19u, kPortMuxAlt2);
            /* PORTE_PCR17 */
            PORT_HAL_SetMuxMode(PORTE, 17u, kPortMuxAlt2);
            /* PORTE_PCR18 */
            PORT_HAL_SetMuxMode(PORTE, 18u, kPortMuxAlt2);
            break;
        case SPI2_IDX:                       /* SPI2 */
            /* PORTB_PCR20 */
            PORT_HAL_SetMuxMode(PORTB, 20u,kPortMuxAlt2);
            /* PORTB_PCR23 */
            PORT_HAL_SetMuxMode(PORTB, 23u, kPortMuxAlt2);
            /* PORTB_PCR21 */
            PORT_HAL_SetMuxMode(PORTB, 21u, kPortMuxAlt2);
            /* PORTB_PCR22 */
            PORT_HAL_SetMuxMode(PORTB, 22u, kPortMuxAlt2);
            break;
        default:                             /* SPI1 */
            break;
    }
}

void configure_spi_cs0_pins(uint32_t instance)
{
    switch(instance) {
        case SPI0_IDX:                       /* SPI0 */
            PORT_HAL_SetMuxMode(PORTE, 16u, kPortMuxAsGpio);
            break;
            /* SPI1 */
            /* Not supported */
        case SPI2_IDX:                       /* SPI2 */
            PORT_HAL_SetMuxMode(PORTE, 26u, kPortMuxAsGpio);
            break;
        default:
            break;
    }
}

void configure_spi_cs1_pins(uint32_t instance)
{
    switch(instance) {
        case SPI0_IDX:                       /* SPI0 */
            PORT_HAL_SetMuxMode(PORTB, 20u, kPortMuxAsGpio);
            break;
        case SPI2_IDX:                       /* SPI2 */
            PORT_HAL_SetMuxMode(PORTC, 12u, kPortMuxAsGpio);
            break;
        default:                             /* SPI1 */
            break;
    }
}

#ifdef FTM_INSTANCE_COUNT
void configure_ftm_pins(uint32_t instance)
{
    switch(instance) {
        case FTM0_IDX:                       /* FTM0 */
            /* Affects PORTE_PCR30 register */
            PORT_HAL_SetDriveStrengthMode(PORTE,30u,kPortLowDriveStrength);
            PORT_HAL_SetMuxMode(PORTE,30u,kPortMuxAlt3);
            PORT_HAL_SetSlewRateMode(PORTE,30u,kPortSlowSlewRate);
            break;
        default:
            break;
    }
}
#endif

void configure_can_pins(uint32_t instance)
{
    switch(instance) {
        case CAN1_IDX:                       /* CAN1 */
            /* PORTC_PCR16 */
            PORT_HAL_SetMuxMode(PORTC,16u,kPortMuxAlt2);
            /* PORTC_PCR17 */
            PORT_HAL_SetMuxMode(PORTC,17u,kPortMuxAlt2);
            break;
        default:                             /* CAN0, CAN2 */
            break;
    }
}


void configure_pwm_pins(uint32_t instance)
{
    switch(instance)
    {
        case PWM0_IDX:
            PORT_HAL_SetMuxMode(PORTD, 0, kPortMuxAlt6);
            PORT_HAL_SetMuxMode(PORTD, 1, kPortMuxAlt6);
            PORT_HAL_SetMuxMode(PORTD, 2, kPortMuxAlt6);
            PORT_HAL_SetMuxMode(PORTD, 3, kPortMuxAlt6);
            PORT_HAL_SetMuxMode(PORTD, 4, kPortMuxAlt5);
            PORT_HAL_SetMuxMode(PORTD, 5, kPortMuxAlt5);
            PORT_HAL_SetMuxMode(PORTC, 1, kPortMuxAlt5);
            PORT_HAL_SetMuxMode(PORTC, 2, kPortMuxAlt5);
            break;
        default:
            break;
    }
}

void configure_enc_pins(uint32_t instance)
{
    switch(instance)
    {
        case ENC_IDX:
            PORT_HAL_SetMuxMode(PORTE, 24u, kPortMuxAlt4);
            PORT_HAL_SetMuxMode(PORTE, 25u, kPortMuxAlt4);
            PORT_HAL_SetMuxMode(PORTC, 1u, kPortMuxAlt6);
            PORT_HAL_SetMuxMode(PORTC, 2u, kPortMuxAlt6);
            break;
        default:
            break;
    }
}

void configure_cmp_pins(uint32_t instance)
{
    switch (instance)
    {
        case CMP0_IDX:
            PORT_HAL_SetMuxMode(PORTC, 5U, kPortPinDisabled); /* PTC5 - CMP0_OUT. */
            PORT_HAL_SetMuxMode(PORTC, 7U, kPortPinDisabled); /* PTC7 - CMP0_IN1. */
            PORT_HAL_SetMuxMode(PORTC, 8U, kPortPinDisabled); /* PTC8 - CMP0_IN2. */
            break;
        default:
            break;
    }
}

void configure_dac_pins(uint32_t instance)
{
    switch (instance)
    {
        case 0U:
            PORT_HAL_SetMuxMode(PORTE, 30U, kPortPinDisabled);
            break;
        default:
            break;
    }
}

void configure_xbarb_pins(uint32_t instance)
{
    switch (instance)
    {
        case 0U:
            PORT_HAL_SetMuxMode(PORTA, 4U, kPortMuxAlt4);
            break;
        default:
            break;
    }
}
/* END pin_mux. */
/*!
** @}
*/

