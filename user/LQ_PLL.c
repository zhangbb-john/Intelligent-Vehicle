/*******************************************************************************
��ƽ    ̨������KV58F24���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��2��2��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4�����ϰ汾
��Target  ��MKV58F1M0VLQ24
��Crystal �� 50.000Mhz
��busclock��137.500MHz
��pllclock��275.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

uint32 core_clk_M;//��λMHZ
uint32 bus_clk_M;//��λMHZ

/* Configuration for enter RUN mode. Core clock = 150MHz. */
const clock_manager_user_config_t PLL150MHz =
{
  .mcgConfig =
  {
    .mcg_mode           = kMcgModePEE,   // Work in PEE mode.
    .irclkEnable        = true,  // MCGIRCLK enable.
    .irclkEnableInStop  = false, // MCGIRCLK disable in STOP mode.
    .ircs               = kMcgIrcSlow, // Select IRC32k.
    .fcrdiv             = 0U,    // FCRDIV is 0.
    
    .frdiv   = 6U,
    .drs     = kMcgDcoRangeSelLow,  // Low frequency range
    .dmx32   = kMcgDmx32Default,    // DCO has a default range of 25%
    
    .pll0EnableInFllMode    = false,  // PLL0 disable
    .pll0EnableInStop       = false,  // PLL0 disable in STOP mode
    .prdiv0                 = 0x3U,
    .vdiv0                  = 0x8U,
  },
  .simConfig =
  {
    .er32kSrc  = kClockEr32kSrcLpo,     // ERCLK32K selection, use LPO.
    .outdiv1   = 0U,
    .outdiv2   = 1U,
    .outdiv3   = 1U,
    .outdiv4   = 5U
  },
  .oscerConfig =
  {
    .enable       = true,  // OSCERCLK enable.
    .enableInStop = false, // OSCERCLK disable in STOP mode.
  }
};
const clock_manager_user_config_t PLL180MHz =
{
  .mcgConfig =
  {
    .mcg_mode           = kMcgModePEE,   // Work in PEE mode.
    .irclkEnable        = true,         // MCGIRCLK enable.
    .irclkEnableInStop  = false,        // MCGIRCLK disable in STOP mode.
    .ircs               = kMcgIrcSlow,  // Select IRC32k.
    .fcrdiv             = 0U,           // FCRDIV is 0.
    
    .frdiv   = 3U,
    .drs     = kMcgDcoRangeSelLow,      // Low frequency range
    .dmx32   = kMcgDmx32Default,        // DCO has a default range of 25%
    
    .pll0EnableInFllMode    = false,   // PLL0 disable
    .pll0EnableInStop       = false,   // PLL0 disable in STOP mode
    .prdiv0                 = 0x4U,
    .vdiv0                  = 20U,    //PLL =  50M * (pll_vdiv+16)/(prdiv+1)/2
  },
  .simConfig =
  {
    .er32kSrc  = kClockEr32kSrcLpo,     // ERCLK32K selection, use LPO.
    .outdiv1   = 0U,//system (CPU) clock= MCG
    .outdiv2   = 1U,//Fast Peripheral clock = MCG/2
    .outdiv3   = 2U,//FlexBus    = MCG/(2+1)
    .outdiv4   = 7U//Bus /Flash clock= MCG/8
  },
  .oscerConfig =
  {
    .enable       = true,              // OSCERCLK enable.
    .enableInStop = false,             // OSCERCLK disable in STOP mode.
  }
};
/* Configuration for HSRUN mode. Core clock = 200MHz. */
const clock_manager_user_config_t PLL200MHz =
{
  .mcgConfig =
  {
    .mcg_mode           = kMcgModePEE,   // Work in PEE mode.
    .irclkEnable        = true,         // MCGIRCLK enable.
    .irclkEnableInStop  = false,        // MCGIRCLK disable in STOP mode.
    .ircs               = kMcgIrcSlow,  // Select IRC32k.
    .fcrdiv             = 0U,           // FCRDIV is 0.
    
    .frdiv   = 3U,
    .drs     = kMcgDcoRangeSelLow,      // Low frequency range
    .dmx32   = kMcgDmx32Default,        // DCO has a default range of 25%
    
    .pll0EnableInFllMode    = false,   // PLL0 disable
    .pll0EnableInStop       = false,   // PLL0 disable in STOP mode
    .prdiv0                 = 0x4U,
    .vdiv0                  = 24U,    //PLL =  50M * (pll_vdiv+16)/(prdiv+1)/2
  },
  .simConfig =
  {
    .er32kSrc  = kClockEr32kSrcLpo,     // ERCLK32K selection, use LPO.
    .outdiv1   = 0U,//system (CPU) clock= MCG
    .outdiv2   = 1U,//Fast Peripheral clock = MCG/2
    .outdiv3   = 2U,//FlexBus    = MCG/(2+1)
    .outdiv4   = 7U//Bus /Flash clock= MCG/8
  },
  .oscerConfig =
  {
    .enable       = true,              // OSCERCLK enable.
    .enableInStop = false,             // OSCERCLK disable in STOP mode.
  }
};
const clock_manager_user_config_t PLL235MHz =
{
  .mcgConfig =
  {
    .mcg_mode           = kMcgModePEE,   // Work in PEE mode.
    .irclkEnable        = true,         // MCGIRCLK enable.
    .irclkEnableInStop  = false,        // MCGIRCLK disable in STOP mode.
    .ircs               = kMcgIrcSlow,  // Select IRC32k.
    .fcrdiv             = 0U,           // FCRDIV is 0.
    
    .frdiv   = 3U,
    .drs     = kMcgDcoRangeSelLow,      // Low frequency range
    .dmx32   = kMcgDmx32Default,        // DCO has a default range of 25%
    
    .pll0EnableInFllMode    = false,   // PLL0 disable
    .pll0EnableInStop       = false,   // PLL0 disable in STOP mode
    .prdiv0                 = 0x4U,
    .vdiv0                  = 31,    //PLL =  50M * (pll_vdiv+16)/(prdiv+1)/2
  },
  .simConfig =
  {
    .er32kSrc  = kClockEr32kSrcLpo,     // ERCLK32K selection, use LPO.
    .outdiv1   = 0U,//system (CPU) clock= MCG
    .outdiv2   = 1U,//Fast Peripheral clock = MCG/2
    .outdiv3   = 3U,//FlexBus    = MCG/(2+1)
    .outdiv4   = 9U//Bus /Flash clock= MCG/8
  },
  .oscerConfig =
  {
    .enable       = true,              // OSCERCLK enable.
    .enableInStop = false,             // OSCERCLK disable in STOP mode.
  }
};
const clock_manager_user_config_t PLL250MHz =
{
  .mcgConfig =
  {
    .mcg_mode           = kMcgModePEE,   // Work in PEE mode.
    .irclkEnable        = true,         // MCGIRCLK enable.
    .irclkEnableInStop  = false,        // MCGIRCLK disable in STOP mode.
    .ircs               = kMcgIrcSlow,  // Select IRC32k.
    .fcrdiv             = 0U,           // FCRDIV is 0.
    
    .frdiv   = 3U,
    .drs     = kMcgDcoRangeSelLow,      // Low frequency range
    .dmx32   = kMcgDmx32Default,        // DCO has a default range of 25%
    
    .pll0EnableInFllMode    = false,   // PLL0 disable
    .pll0EnableInStop       = false,   // PLL0 disable in STOP mode
    .prdiv0                 = 0x3U,
    .vdiv0                  = 24U,    //PLL =  50M * (pll_vdiv+16)/(prdiv+1)/2
  },
  .simConfig =
  {
    .er32kSrc  = kClockEr32kSrcLpo,     // ERCLK32K selection, use LPO.
    .outdiv1   = 0U,//system (CPU) clock= MCG
    .outdiv2   = 1U,//Fast Peripheral clock = MCG/2
    .outdiv3   = 3U,//FlexBus    = MCG/(2+1)
    .outdiv4   = 9U//Bus /Flash clock= MCG/8
  },
  .oscerConfig =
  {
    .enable       = true,              // OSCERCLK enable.
    .enableInStop = false,             // OSCERCLK disable in STOP mode.
  }
};
const clock_manager_user_config_t PLL275MHz =
{
  .mcgConfig =
  {
    .mcg_mode           = kMcgModePEE,   // Work in PEE mode.
    .irclkEnable        = true,         // MCGIRCLK enable.
    .irclkEnableInStop  = false,        // MCGIRCLK disable in STOP mode.
    .ircs               = kMcgIrcSlow,  // Select IRC32k.
    .fcrdiv             = 0U,           // FCRDIV is 0.
    
    .frdiv   = 6U,
    .drs     = kMcgDcoRangeSelLow,      // Low frequency range
    .dmx32   = kMcgDmx32Default,        // DCO has a default range of 25%
    
    .pll0EnableInFllMode    = false,   // PLL0 disable
    .pll0EnableInStop       = false,   // PLL0 disable in STOP mode
    .prdiv0                 = 0x3U,
    .vdiv0                  = 28U,    //PLL =  50M * (pll_vdiv+16)/(prdiv+1)/2
  },
  .simConfig =
  {
    .er32kSrc  = kClockEr32kSrcLpo,     // ERCLK32K selection, use LPO.
    .outdiv1   = 0U,//system (CPU) clock= MCG
    .outdiv2   = 1U,//Fast Peripheral clock = MCG/2
    .outdiv3   = 3U,//FlexBus   = MCG/(2+1)
    .outdiv4   = 9U//Bus /Flash clock= MCG/8
  },
  .oscerConfig =
  {
    .enable       = true,              // OSCERCLK enable.
    .enableInStop = false,             // OSCERCLK disable in STOP mode.
  }
};

/*************************************************************************
* �������ܿƼ����޹�˾
*
*  �������ƣ�pll_init
*  ����˵����ʱ�ӳ�ʼ���������趨Ƶ�ʡ�
*  ����˵����PLL_?
*  �������أ���
*  �޸�ʱ�䣺2015-10-6
*  ��    ע���ں�ʱ�ӣ�ϵͳʱ�ӣ�=�ⲿʱ�ӣ�50M����Ƶ�ʣ�/ (pll_prdiv+1)*(pll_vdiv+16);
MCG=PLL, system (CPU) clock= MCG, bus = MCG/5, FlexBus = MCG/3, Bus /Flash clock= MCG/8
*  ��    �ӣ�pll_init(PLL180);
*************************************************************************/
void PLL_Init(clk_option opt)
{
  char pll_prdiv;
  char pll_vdiv;
  u32 temp_reg;
  
  // Set allowed power mode, allow all. 
  SMC_HAL_SetProtection(SMC, kAllowPowerModeAll);
  
  smc_power_mode_config_t powerModeConfig = 
  {
    .powerModeName = kPowerModeHsrun,
  };
  
  // Setup board clock source,Configure OSC0 pin mux.
  
  BOARD_InitOsc0();
  
  /* Set system clock configuration. */
  SMC_HAL_SetMode(SMC, &powerModeConfig);
  
  SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK
            | SIM_SCGC5_PORTB_MASK
            | SIM_SCGC5_PORTC_MASK
            | SIM_SCGC5_PORTD_MASK
            | SIM_SCGC5_PORTE_MASK );  
  
  if(opt!= PLLUNULL )
  {
    //����PLLʱ��
    switch(opt)
    {   
    case PLL150:
      pll_prdiv       = 4;
      pll_vdiv        = 14;
      CLOCK_SYS_SetConfiguration(&PLL150MHz);  
      break;   
    case PLL180:
      pll_prdiv       = 4;
      pll_vdiv        = 20;
      CLOCK_SYS_SetConfiguration(&PLL180MHz);  
      break;
    case PLL200:
      pll_prdiv       = 4;
      pll_vdiv        = 24;
      CLOCK_SYS_SetConfiguration(&PLL200MHz);  
      break; 
    case PLL235:
      pll_prdiv       = 4;
      pll_vdiv        = 31;
      CLOCK_SYS_SetConfiguration(&PLL235MHz);  
      break; 
    case PLL250:               
      pll_prdiv       = 3;
      pll_vdiv        = 24;
      CLOCK_SYS_SetConfiguration(&PLL250MHz);  
      break; 
    case PLL275:               //�ȶ�
      pll_prdiv       = 3;
      pll_vdiv        = 28;
      CLOCK_SYS_SetConfiguration(&PLL275MHz);  
      break;    
    default:   
      pll_prdiv       = 3;
      pll_vdiv        = 28;
      CLOCK_SYS_SetConfiguration(&PLL275MHz);
      break;//(��ʼ��δ�ɹ���ϵͳĬ��ϵͳʱ��Ϊ275M)
    }
  }
  core_clk_M= 50 * ( pll_vdiv+16 )/2/(pll_prdiv+1);
  bus_clk_M =core_clk_M/2;  
  
  MCG_C1 = MCG_C1_CLKS(2) ;//ѡ���ⲿʱ��
  MCG_C5 = MCG_C5_PRDIV(pll_prdiv);//����Ϊ50M����Ƶ�����ΧҪ��8M~16M ��ʱΪ 50/(prdiv+1)
  temp_reg = FMC_PFAPR;
  
  //ͨ��M&PFD��λM0PFD����ֹԤȡ����
  FMC_PFAPR |= FMC_PFAPR_M3PFD_MASK | FMC_PFAPR_M2PFD_MASK
    | FMC_PFAPR_M1PFD_MASK | FMC_PFAPR_M0PFD_MASK;
  //����ϵͳ��Ƶ��
  //MCG=PLL, system (CPU) clock= MCG,  
  SIM_CLKDIV1 =  SIM_CLKDIV1_OUTDIV1(0)    //system (CPU) clock= MCG/(0+1),����ƵΪ15
               | SIM_CLKDIV1_OUTDIV2(1)    //Fast Peripheral clock= MCG/(1+1),����ƵΪ15
               | SIM_CLKDIV1_OUTDIV3(3)    //Flexbus clock   = MCG/(3+1),����ƵΪ15
               | SIM_CLKDIV1_OUTDIV4(core_clk_M/30);   //Bus/Flash clock= MCG/9,����ƵΪ15,���Ϊ27.5M
  
//  SIM_CLKDIV1 =  SIM_CLKDIV1_OUTDIV1(0)    //system (CPU) clock= MCG/(0+1),����ƵΪ15
//               | SIM_CLKDIV1_OUTDIV2(1)    //Fast Peripheral clock= MCG/(1+1),����ƵΪ15
//               | SIM_CLKDIV1_OUTDIV3(3)    //Flexbus clock   = MCG/(3+1),����ƵΪ15
//               | SIM_CLKDIV1_OUTDIV4(core_clk_M/30);   //Bus/Flash clock= MCG/9,����ƵΪ15,���Ϊ27.5M
  
  //���´�FMC_PFAPR��ԭʼֵ
  FMC_PFAPR = temp_reg;
  
  MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(pll_vdiv);//PLL =  50M* (pll_vdiv+16)/(prdiv+1) /2
  
  while (!(MCG_S & MCG_S_PLLST_MASK)){}; // wait for PLL status bit to set
  while (!(MCG_S & MCG_S_LOCK0_MASK)){}; // Wait for LOCK bit to set
  
  MCG_C1=0x00;
  
  //�ȴ�ʱ��״̬λ����
  while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3){};  
}
 
/* OSC0 configuration. */
#define OSC0_XTAL_FREQ 50000000U
#define OSC0_SC2P_ENABLE_CONFIG  false
#define OSC0_SC4P_ENABLE_CONFIG  false
#define OSC0_SC8P_ENABLE_CONFIG  false
#define OSC0_SC16P_ENABLE_CONFIG false
#define MCG_HGO0   kOscGainLow
#define MCG_RANGE0 kOscRangeVeryHigh
#define MCG_EREFS0 kOscSrcExt

/* Function to initialize OSC0 base on board configuration. */
void BOARD_InitOsc0(void)
{
  // OSC0 configuration.
  osc_user_config_t osc0Config =
  {
    .freq                = OSC0_XTAL_FREQ,
    .hgo                 = MCG_HGO0,
    .range               = MCG_RANGE0,
    .erefs               = MCG_EREFS0,
    .enableCapacitor2p   = OSC0_SC2P_ENABLE_CONFIG,
    .enableCapacitor4p   = OSC0_SC4P_ENABLE_CONFIG,
    .enableCapacitor8p   = OSC0_SC8P_ENABLE_CONFIG,
    .enableCapacitor16p  = OSC0_SC16P_ENABLE_CONFIG,
  };
  CLOCK_SYS_OscInit(0U, &osc0Config);
}


