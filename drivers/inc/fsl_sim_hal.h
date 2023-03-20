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

#if !defined(__FSL_SIM_HAL_H__)
#define __FSL_SIM_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"

/*! @addtogroup sim_hal*/
/*! @{*/

/*! @file*/

/*******************************************************************************
* Definitions
******************************************************************************/

/*! @brief SIM HAL API return status*/
typedef enum _sim_hal_status {
    kSimHalSuccess,  /*!< Success.      */
    kSimHalFail,     /*!< Error occurs. */
} sim_hal_status_t;

/*******************************************************************************
* API
******************************************************************************/

/*
* Include the CPU-specific clock API header files.
*/

#include "fsl_sim_hal_MKV58F24.h"


  #if FSL_FEATURE_SOC_SIM_COUNT
  #else
  #error "No valid CPU defined!"
  #endif

/*! @}*/

#endif /* __FSL_SIM_HAL_H__*/
/*******************************************************************************
* EOF
******************************************************************************/

