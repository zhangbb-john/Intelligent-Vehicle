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

#include "fsl_mscm_hal.h"
#if FSL_FEATURE_SOC_MSCM_COUNT


/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : MSCM_HAL_GetCurrentProcessorInfo
 * Description   : Get the Current Processor Informations.
 *
 *END**************************************************************************/
void MSCM_HAL_GetCurrentProcessorInfo(MSCM_Type * base, mscm_processor_info_t * p_info)
{
    if (p_info)
    {
        p_info->revision = MSCM_HAL_GetRevisonX(base);
        p_info->number = MSCM_HAL_GetNumberX(base);
        p_info->port = MSCM_HAL_GetPortX(base);
        p_info->count = MSCM_HAL_GetCountX(base);
        p_info->personality = MSCM_HAL_GetPersonalityX(base);
    }    
}


/*FUNCTION**********************************************************************
 *
 * Function Name : MSCM_HAL_GetCurrentProcessorCacheInfo
 * Description   : Get the Curren Processor Cache Informations.
 *
 *END**************************************************************************/
void MSCM_HAL_GetCurrentCacheInfo(MSCM_Type * base, uint8_t index, mscm_cache_info_t * p_info)
{
    if (p_info)
    {
        p_info->dataCacheWays = MSCM_HAL_GetDataCacheWayX(base, index);
        p_info->dataCacheSize = MSCM_HAL_GetDataCacheSizeX(base, index);
        p_info->instructCacheWays = MSCM_HAL_GetInstructionCacheWayX(base, index);
        p_info->instructCacheSize = MSCM_HAL_GetInstructionCacheSizeX(base, index);
    }
    
}


/*FUNCTION**********************************************************************
 *
 * Function Name : MSCM_HAL_GetMemInfo
 * Description   : Get the specific Memory Informations.
 *
 *END**************************************************************************/
void MSCM_HAL_GetMemInfo(MSCM_Type * base, uint8_t index, mscm_mem_info_t * p_info)
{
    if (p_info)
    {
        p_info->memValid = MSCM_HAL_GetMemValidBit(base, index);
        p_info->memSizeHole = MSCM_HAL_GetMemSizeHole(base, index);
        p_info->memSize = MSCM_HAL_GetMemSize(base, index);
        p_info->memDataPathWidth = MSCM_HAL_GetDataPathWidth(base, index);
        p_info->memLock = MSCM_HAL_GetReadOnlyInfo(base, index);
        p_info->memType = MSCM_HAL_GetMemType(base, index);
        p_info->memProtect = MSCM_HAL_GetMemProtectInfo(base, index);
    }   
}


/*FUNCTION**********************************************************************
 *
 * Function Name : MSCM_HAL_GetProcessor0Info
 * Description   : Get the Processor0 Informations.
 *
 *END**************************************************************************/
void MSCM_HAL_GetProcessor0Info(MSCM_Type * base, mscm_processor_info_t * p_info)
{
    if (p_info)
    {
        p_info->revision = MSCM_HAL_GetRevison0(base);
        p_info->number = MSCM_HAL_GetNumber0(base);
        p_info->port = MSCM_HAL_GetPort0(base);
        p_info->count = MSCM_HAL_GetCount0(base);
        p_info->personality = MSCM_HAL_GetPersonality0(base);
    }
    
}


/*FUNCTION**********************************************************************
 *
 * Function Name : MSCM_HAL_GetProcessor0CacheInfo
 * Description   : Get the Specific Cache Informations of Processor0.
 *
 *END**************************************************************************/
void MSCM_HAL_GetProcessor0CacheInfo(MSCM_Type * base, uint8_t index, mscm_cache_info_t * p_info)
{
    if (p_info)
    {
        p_info->dataCacheWays = MSCM_HAL_GetDataCacheWay0(base, index);
        p_info->dataCacheSize = MSCM_HAL_GetDataCacheSize0(base, index);
        p_info->instructCacheWays = MSCM_HAL_GetInstructionCacheWay0(base, index);
        p_info->instructCacheSize = MSCM_HAL_GetInstructionCacheSize0(base, index);
    }
    
}


#if (FSL_FEATURE_MSCM_HAS_CP_COUNT > 1)
/*FUNCTION**********************************************************************
 *
 * Function Name : MSCM_HAL_GetProcessor1Info
 * Description   : Get the Processor1 Informations.
 *
 *END**************************************************************************/
void MSCM_HAL_GetProcessor1Info(MSCM_Type * base, mscm_processor_info_t * p_info)
{
    if (p_info)
    {
        p_info->revision = MSCM_HAL_GetRevison1(base);
        p_info->number = MSCM_HAL_GetNumber1(base);
        p_info->port = MSCM_HAL_GetPort1(base);
        p_info->count = MSCM_HAL_GetCount1(base);
        p_info->personality = MSCM_HAL_GetPersonality1(base);
    }
    
}


/*FUNCTION**********************************************************************
 *
 * Function Name : MSCM_HAL_GetProcessor1CacheInfo
 * Description   : Get the Specific Cache Informations of Processor1.
 *
 *END**************************************************************************/
void MSCM_HAL_GetProcessor1CacheInfo(MSCM_Type * base, uint8_t index, mscm_cache_info_t * p_info)
{
    if (p_info)
    {
        p_info->dataCacheWays = MSCM_HAL_GetDataCacheWay1(base, index);
        p_info->dataCacheSize = MSCM_HAL_GetDataCacheSize1(base, index);
        p_info->instructCacheWays = MSCM_HAL_GetInstructionCacheWay1(base, index);
        p_info->instructCacheSize = MSCM_HAL_GetInstructionCacheSize1(base, index);
    }
    
}

#endif

#endif
/*******************************************************************************
 * EOF
 *******************************************************************************/
