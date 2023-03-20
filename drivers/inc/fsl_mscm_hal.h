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
#ifndef __FSL_MSCM_HAL_H__
#define __FSL_MSCM_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_MSCM_COUNT


/*! 
 * @addtogroup mscm_hal
 * @{
 */
 
/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief Structure for processor infomations.*/
typedef struct MscmProcessorInfo
{
    uint8_t revision;       /*!< Processor Revision*/
    uint8_t number;         /*!< Processor Number*/
    uint8_t port;           /*!< Processor Port*/
    uint8_t count;          /*!< Processor Count*/
    uint32_t personality;   /*!< Processor Personality*/      
} mscm_processor_info_t;

/*! @brief Structure for cache infomations.*/
typedef struct MscmCacheInfo
{
    uint8_t dataCacheWays;          /*!< Data Cache Ways*/
    uint8_t dataCacheSize;          /*!< Data Cache Size*/
    uint8_t instructCacheWays;      /*!< Instruction Cache Ways*/
    uint8_t instructCacheSize;      /*!< Instruction Cache Size*/     
} mscm_cache_info_t;

/*! @brief Structure for memory infomations.*/
typedef struct MscmMemInfo
{
    uint8_t memValid;           /*!< OCMEM Valid bit*/
    uint8_t memSizeHole;        /*!< OCMEM Size Hole*/
    uint8_t memSize;            /*!< OCMEM Size*/
    uint8_t memDataPathWidth;   /*!< OCMEM Data Path Width*/
    uint8_t memLock;            /*!< Read-Only*/
    uint8_t memType;            /*!< OCMEM Type*/
    uint8_t memProtect;         /*!< OCMEM Memory Protection Unit*/
} mscm_mem_info_t;
 
/*******************************************************************************
 * API
 *******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif


/*!
 * @brief Gets Processor x Revision.
 *
 * This function gets the revision of processor x. 
 *
 * @param base, MSCM base address
 * @return 0x00 corresponds to the r0p0 core release, 0x01 corresponds to the r0p1 core release.
 */
static inline uint8_t MSCM_HAL_GetRevisonX(MSCM_Type * base)
{
    return MSCM_BRD_CPxTYPE_RYPZ(base);
}


/*!
 * @brief Gets Processor x Personality.
 *
 * This function gets the Personality of processor x. 
 *
 * @param base, MSCM base address
 * @return if CPx = Cortex-M0, then PERSONALITY = 0x43_4D_30 ("CM0").
 */
static inline uint32_t MSCM_HAL_GetPersonalityX(MSCM_Type * base)
{
    return MSCM_BRD_CPxTYPE_PERSONALITY(base);
}


/*!
 * @brief Gets Processor x CPN.
 *
 * This function gets the CPN of processor x. 
 *
 * @param base, MSCM base address
 * @return if boot (primary) core, then CPN = 0, for secondary core, CPN = 1.
 */
static inline uint8_t MSCM_HAL_GetNumberX(MSCM_Type * base)
{
    return MSCM_BRD_CPxNUM_CPN(base);
}


/*!
 * @brief Gets Processor x PPN.
 *
 * This function gets the PPN of processor x. 
 *
 * @param base, MSCM base address
 * @return for core0, PPN = 0x00, for Core1, PPN = 0x24.
 */
static inline uint8_t MSCM_HAL_GetPortX(MSCM_Type * base)
{
    return MSCM_BRD_CPxMASTER_PPN(base);
}


/*!
 * @brief Gets Processor x PCNT.
 *
 * This function gets the PCNT of processor x. 
 *
 * @param base, MSCM base address
 * @return the processor count for the chip configuration.
 */
static inline uint8_t MSCM_HAL_GetCountX(MSCM_Type * base)
{
    return MSCM_BRD_CPxCOUNT_PCNT(base);
}


/*!
 * @brief Gets Processor x level n Data Cache Ways.
 *
 * This function gets the level n Data Cache Ways of processor x. 
 *
 * @param base, MSCM base address
 * @param index, level index
 * @return the number of cache ways for the data cache.
 */
static inline uint8_t MSCM_HAL_GetDataCacheWayX(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_CPxCFG_DCWY(base, index);
}


/*!
 * @brief Gets Processor x level n Data Cache Size.
 *
 * This function gets the level n Data Cache Size of processor x. 
 *
 * @param base, MSCM base address
 * @param index, level index
 * @return the number of cache size for the data cache.
 */
static inline uint8_t MSCM_HAL_GetDataCacheSizeX(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_CPxCFG_DCSZ(base, index);
}


/*!
 * @brief Gets Processor x level n Instruction Cache Ways.
 *
 * This function gets the level n Instruction Cache Ways of processor x. 
 *
 * @param base, MSCM base address
 * @param index, level index
 * @return the number of cache ways for the instruction cache.
 */
static inline uint8_t MSCM_HAL_GetInstructionCacheWayX(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_CPxCFG_ICWY(base, index);
}


/*!
 * @brief Gets Processor x level n Instruction Cache Size.
 *
 * This function gets the level n Instruction Cache Size of processor x. 
 *
 * @param base, MSCM base address
 * @param index, level index
 * @return the number of cache size for the instruction cache.
 */
static inline uint8_t MSCM_HAL_GetInstructionCacheSizeX(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_CPxCFG_ICSZ(base, index);
}


/*!
 * @brief Gets On-Chip Memory MPU information.
 *
 * This function gets on-chip memory MPU information. 
 *
 * @param base, MSCM base address
 * @param index, memory index
 * @return 0 means on-chip memory is not protected by an XRDC module.
 *         1 means on-chip memory is protected by an XRDC module.
 */
static inline uint8_t MSCM_HAL_GetMemProtectInfo(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_OCMDR_OCMPU(base, index);
}


/*!
 * @brief Gets On-Chip Memory Type.
 *
 * This function gets on-chip memory type. 
 *
 * @param base, MSCM base address
 * @param index, memory index
 * @return 
 *          - 0b000 - OCMEMn is a system RAM.
 *          - 0b001 - OCMEMn is a graphics RAM.
 *          - 0b010 - Reserved
 *          - 0b011 - OCMEMn is a ROM.
 *          - 0b100 - Reserved
 *          - 0b101 - Reserved
 *          - 0b110 - Reserved
 *          - 0b111 - Reserved
 */
static inline uint8_t MSCM_HAL_GetMemType(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_OCMDR_OCMT(base, index);
}


/*!
 * @brief Gets Read-Only information.
 *
 * This function gets Read-Only information. 
 *
 * @param base, MSCM base address
 * @param index, memory index
 * @return 0 means writes to the OCMDRn[11:0] are allowed.
 *         1 writes to the OCMDRn[11:0] are ignored.
 */
static inline uint8_t MSCM_HAL_GetReadOnlyInfo(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_OCMDR_RO(base, index);
}


/*!
 * @brief Gets On-Chip Memory Data Path Width.
 *
 * This function gets on-chip memory data path width. 
 *
 * @param base, MSCM base address
 * @param index, memory index
 * @return 
 *          - 0b010 - OCMEMn 32-bits wide
 *          - 0b011 - OCMEMn 64-bits wide
 */
static inline uint8_t MSCM_HAL_GetDataPathWidth(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_OCMDR_OCMW(base, index);
}


/*!
 * @brief Gets On-Chip Memory Size.
 *
 * This function gets on-chip memory size. 
 *
 * @param base, MSCM base address
 * @param index, memory index
 * @return 
 *          - 0b0000 - no OCMEMn
 *          - 0b0100 - 4KB OCMEMn
 *          - 0b0101 - 8KB OCMEMn
 *          - 0b0110 - 16KB OCMEMn
 *          - 0b0111 - 32KB OCMEMn
 *          - 0b1111 - 8192KB OCMEMn
 */
static inline uint8_t MSCM_HAL_GetMemSize(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_OCMDR_OCMSZ(base, index);
}


/*!
 * @brief Gets On-Chip Memory Size Hole.
 *
 * This function gets on-chip memory size hole. 
 *
 * @param base, MSCM base address
 * @param index, memory index
 * @return 
 *          - 0b0 - OCMEMn is a power-of-2 capacity.
 *          - 0b1 - OCMEMn is not a power-of-2, with a capacity is 0.75 * OCMSZ.
 */
static inline uint8_t MSCM_HAL_GetMemSizeHole(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_OCMDR_OCMSZH(base, index);
}


/*!
 * @brief Gets On-Chip Memory Valid Bit.
 *
 * This function gets on-chip memory valid bit. 
 *
 * @param base, MSCM base address
 * @param index, memory index
 * @return 
 *          - 0b0 - OCMEMn is not present.
 *          - 0b1 - OCMEMn is present.
 */
static inline uint8_t MSCM_HAL_GetMemValidBit(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_OCMDR_V(base, index);
}


/*!
 * @brief Gets Processor 0 Revision.
 *
 * This function gets the revision of processor 0. 
 *
 * @param base, MSCM base address
 * @return 0x00 corresponds to the r0p0 core release, 0x01 corresponds to the r0p1 core release.
 */
static inline uint8_t MSCM_HAL_GetRevison0(MSCM_Type * base)
{
    return MSCM_BRD_CP0TYPE_RYPZ(base);
} 


/*!
 * @brief Gets Processor 0 Personality.
 *
 * This function gets the Personality of processor 0. 
 *
 * @param base, MSCM base address
 * @return if CPx = Cortex-M0, then PERSONALITY = 0x43_4D_30 ("CM0").
 */
static inline uint32_t MSCM_HAL_GetPersonality0(MSCM_Type * base)
{
    return MSCM_BRD_CP0TYPE_PERSONALITY(base);
}



/*!
 * @brief Gets Processor 0 CPN.
 *
 * This function gets the CPN of processor 0. 
 *
 * @param base, MSCM base address
 * @return if boot (primary) core, then CPN = 0, for secondary core, CPN = 1.
 */
static inline uint8_t MSCM_HAL_GetNumber0(MSCM_Type * base)
{
    return MSCM_BRD_CP0NUM_CPN(base);
}


/*!
 * @brief Gets Processor 0 PPN.
 *
 * This function gets the PPN of processor 0. 
 *
 * @param base, MSCM base address
 * @return for core0, PPN = 0x00, for Core1, PPN = 0x24.
 */
static inline uint8_t MSCM_HAL_GetPort0(MSCM_Type * base)
{
    return MSCM_BRD_CP0MASTER_PPN(base);
}


/*!
 * @brief Gets Processor 0 PCNT.
 *
 * This function gets the PCNT of processor 0. 
 *
 * @param base, MSCM base address
 * @return the processor count for the chip configuration.
 */
static inline uint8_t MSCM_HAL_GetCount0(MSCM_Type * base)
{
    return MSCM_BRD_CP0COUNT_PCNT(base);
}


 /*!
 * @brief Gets Processor 0 level n Data Cache Ways.
 *
 * This function gets the level n Data Cache Ways of processor 0. 
 *
 * @param base, MSCM base address
 * @param index, level index
 * @return the number of cache ways for the data cache.
 */
static inline uint8_t MSCM_HAL_GetDataCacheWay0(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_CP0CFG_DCWY(base, index);
}


/*!
 * @brief Gets Processor 0 level n Data Cache Size.
 *
 * This function gets the level n Data Cache Size of processor 0. 
 *
 * @param base, MSCM base address
 * @param index, level index
 * @return the number of cache size for the data cache.
 */
static inline uint8_t MSCM_HAL_GetDataCacheSize0(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_CP0CFG_DCSZ(base, index);
}


/*!
 * @brief Gets Processor 0 level n Instruction Cache Ways.
 *
 * This function gets the level n Instruction Cache Ways of processor 0. 
 *
 * @param base, MSCM base address
 * @param index, level index
 * @return the number of cache ways for the instruction cache.
 */
static inline uint8_t MSCM_HAL_GetInstructionCacheWay0(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_CP0CFG_ICWY(base, index);
}


/*!
 * @brief Gets Processor 0 level n Instruction Cache Size.
 *
 * This function gets the level n Instruction Cache Size of processor 0. 
 *
 * @param base, MSCM base address
 * @param index, level index
 * @return the number of cache size for the instruction cache.
 */
static inline uint8_t MSCM_HAL_GetInstructionCacheSize0(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_CP0CFG_ICSZ(base, index);
}


#if (FSL_FEATURE_MSCM_HAS_CP_COUNT > 1)

/*!
 * @brief Gets Processor 1 Revision.
 *
 * This function gets the revision of processor 1. 
 *
 * @param base, MSCM base address
 * @return 0x00 corresponds to the r0p0 core release, 0x01 corresponds to the r0p1 core release.
 */
static inline uint8_t MSCM_HAL_GetRevison1(MSCM_Type * base)
{
    return MSCM_BRD_CP1TYPE_RYPZ(base);
} 


/*!
 * @brief Gets Processor 1 Personality.
 *
 * This function gets the Personality of processor 1. 
 *
 * @param base, MSCM base address
 * @return if CPx = Cortex-M0, then PERSONALITY = 0x43_4D_30 ("CM0").
 */
static inline uint32_t MSCM_HAL_GetPersonality1(MSCM_Type * base)
{
    return MSCM_BRD_CP1TYPE_PERSONALITY(base);
}



/*!
 * @brief Gets Processor 1 CPN.
 *
 * This function gets the CPN of processor 1. 
 *
 * @param base, MSCM base address
 * @return if boot (primary) core, then CPN = 0, for secondary core, CPN = 1.
 */
static inline uint8_t MSCM_HAL_GetNumber1(MSCM_Type * base)
{
    return MSCM_BRD_CP1NUM_CPN(base);
}


/*!
 * @brief Gets Processor 1 PPN.
 *
 * This function gets the PPN of processor 1. 
 *
 * @param base, MSCM base address
 * @return for core0, PPN = 0x00, for Core1, PPN = 0x24.
 */
static inline uint8_t MSCM_HAL_GetPort1(MSCM_Type * base)
{
    return MSCM_BRD_CP1MASTER_PPN(base);
}


/*!
 * @brief Gets Processor 1 PCNT.
 *
 * This function gets the PCNT of processor 1. 
 *
 * @param base, MSCM base address
 * @return the processor count for the chip configuration.
 */
static inline uint8_t MSCM_HAL_GetCount1(MSCM_Type * base)
{
    return MSCM_BRD_CP1COUNT_PCNT(base);
}


 /*!
 * @brief Gets Processor 1 level n Data Cache Ways.
 *
 * This function gets the level n Data Cache Ways of processor 1. 
 *
 * @param base, MSCM base address
 * @param index, level index
 * @return the number of cache ways for the data cache.
 */
static inline uint8_t MSCM_HAL_GetDataCacheWay1(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_CP1CFG_DCWY(base, index);
}


/*!
 * @brief Gets Processor 1 level n Data Cache Size.
 *
 * This function gets the level n Data Cache Size of processor 1. 
 *
 * @param base, MSCM base address
 * @param index, level index
 * @return the number of cache size for the data cache.
 */
static inline uint8_t MSCM_HAL_GetDataCacheSize1(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_CP1CFG_DCSZ(base, index);
}


/*!
 * @brief Gets Processor 1 level n Instruction Cache Ways.
 *
 * This function gets the level n Instruction Cache Ways of processor 1. 
 *
 * @param base, MSCM base address
 * @param index, level index
 * @return the number of cache ways for the instruction cache.
 */
static inline uint8_t MSCM_HAL_GetInstructionCacheWay1(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_CP1CFG_ICWY(base, index);
}


/*!
 * @brief Gets Processor 1 level n Instruction Cache Size.
 *
 * This function gets the level n Instruction Cache Size of processor 1. 
 *
 * @param base, MSCM base address
 * @param index, level index
 * @return the number of cache size for the instruction cache.
 */
static inline uint8_t MSCM_HAL_GetInstructionCacheSize1(MSCM_Type * base, uint8_t index)
{
    return MSCM_BRD_CP1CFG_ICSZ(base, index);
}

#endif


/*!
 * @brief  Get the Current Processor Informations.
 *
 * @param base MSCM base pointer
 * @param p_info The Current Processor Informations of type mscm_processor_info_t
 */
void MSCM_HAL_GetCurrentProcessorInfo(MSCM_Type * base, mscm_processor_info_t * p_info);


/*!
 * @brief  Get the Specific Cache Informations of Current Processor .
 *
 * @param base MSCM base pointer
 * @param index cache index
 * @param p_info The Current Processor Informations of type mscm_cache_info_t
 */
void MSCM_HAL_GetCurrentCacheInfo(MSCM_Type * base, uint8_t index, mscm_cache_info_t * p_info);


/*!
 * @brief  Get the Specific Memory Informations.
 *
 * @param base MSCM base pointer
 * @param index Memory index
 * @param p_info The Current Processor Informations of type mscm_mem_info_t
 */
void MSCM_HAL_GetMemInfo(MSCM_Type * base, uint8_t index, mscm_mem_info_t * p_info);


/*!
 * @brief  Get the Processor0 Informations.
 *
 * @param base MSCM base pointer
 * @param p_info The Current Processor Informations of type mscm_processor_info_t
 */
void MSCM_HAL_GetProcessor0Info(MSCM_Type * base, mscm_processor_info_t * p_info);


/*!
 * @brief  Get the Specific Cache Informations of Processor0.
 *
 * @param base MSCM base pointer
 * @param index cache index
 * @param p_info The Processor0 Informations of type mscm_cache_info_t
 */
void MSCM_HAL_GetProcessor0CacheInfo(MSCM_Type * base, uint8_t index, mscm_cache_info_t * p_info);


/*!
 * @brief  Get the Processor1 Informations.
 *
 * @param base MSCM base pointer
 * @param p_info The Current Processor Informations of type mscm_processor_info_t
 */
void MSCM_HAL_GetProcessor1Info(MSCM_Type * base, mscm_processor_info_t * p_info);


/*!
 * @brief  Get the Specific Cache Informations of Processor1.
 *
 * @param base MSCM base pointer
 * @param index cache index
 * @param p_info The Processor1 Informations of type mscm_cache_info_t
 */
void MSCM_HAL_GetProcessor1CacheInfo(MSCM_Type * base, uint8_t index, mscm_cache_info_t * p_info);


#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_MSCM_HAL_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/ 
