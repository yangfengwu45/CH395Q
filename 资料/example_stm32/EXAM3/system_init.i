#line 1 "..\\SYSTEM\\System_Init.c"






 
#line 1 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"







































 



 



 
    






  


 
  


 

#line 75 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"


















 










 
   








            
#line 122 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"





 






 
#line 143 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 



 



 
#line 162 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"




 
typedef enum IRQn
{
 
  NonMaskableInt_IRQn         = -14,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVCall_IRQn                 = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      

 
  WWDG_IRQn                   = 0,       
  PVD_IRQn                    = 1,       
  TAMPER_IRQn                 = 2,       
  RTC_IRQn                    = 3,       
  FLASH_IRQn                  = 4,       
  RCC_IRQn                    = 5,       
  EXTI0_IRQn                  = 6,       
  EXTI1_IRQn                  = 7,       
  EXTI2_IRQn                  = 8,       
  EXTI3_IRQn                  = 9,       
  EXTI4_IRQn                  = 10,      
  DMA1_Channel1_IRQn          = 11,      
  DMA1_Channel2_IRQn          = 12,      
  DMA1_Channel3_IRQn          = 13,      
  DMA1_Channel4_IRQn          = 14,      
  DMA1_Channel5_IRQn          = 15,      
  DMA1_Channel6_IRQn          = 16,      
  DMA1_Channel7_IRQn          = 17,      

#line 221 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 242 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 270 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 296 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"


  ADC1_2_IRQn                 = 18,      
  USB_HP_CAN1_TX_IRQn         = 19,      
  USB_LP_CAN1_RX0_IRQn        = 20,      
  CAN1_RX1_IRQn               = 21,      
  CAN1_SCE_IRQn               = 22,      
  EXTI9_5_IRQn                = 23,      
  TIM1_BRK_IRQn               = 24,      
  TIM1_UP_IRQn                = 25,      
  TIM1_TRG_COM_IRQn           = 26,      
  TIM1_CC_IRQn                = 27,      
  TIM2_IRQn                   = 28,      
  TIM3_IRQn                   = 29,      
  TIM4_IRQn                   = 30,      
  I2C1_EV_IRQn                = 31,      
  I2C1_ER_IRQn                = 32,      
  I2C2_EV_IRQn                = 33,      
  I2C2_ER_IRQn                = 34,      
  SPI1_IRQn                   = 35,      
  SPI2_IRQn                   = 36,      
  USART1_IRQn                 = 37,      
  USART2_IRQn                 = 38,      
  USART3_IRQn                 = 39,      
  EXTI15_10_IRQn              = 40,      
  RTCAlarm_IRQn               = 41,      
  USBWakeUp_IRQn              = 42,      
  TIM8_BRK_IRQn               = 43,      
  TIM8_UP_IRQn                = 44,      
  TIM8_TRG_COM_IRQn           = 45,      
  TIM8_CC_IRQn                = 46,      
  ADC3_IRQn                   = 47,      
  FSMC_IRQn                   = 48,      
  SDIO_IRQn                   = 49,      
  TIM5_IRQn                   = 50,      
  SPI3_IRQn                   = 51,      
  UART4_IRQn                  = 52,      
  UART5_IRQn                  = 53,      
  TIM6_IRQn                   = 54,      
  TIM7_IRQn                   = 55,      
  DMA2_Channel1_IRQn          = 56,      
  DMA2_Channel2_IRQn          = 57,      
  DMA2_Channel3_IRQn          = 58,      
  DMA2_Channel4_5_IRQn        = 59       


#line 381 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 426 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 472 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"
} IRQn_Type;



 

#line 1 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cm3.h"
 







 

























 
























 




 


 

 













#line 110 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cm3.h"


 







#line 145 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cm3.h"

#line 1 "E:\\MDK5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
 
 





 









     
#line 27 "E:\\MDK5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
     











#line 46 "E:\\MDK5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
#line 216 "E:\\MDK5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     



     






     
    
 



#line 241 "E:\\MDK5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     







     










     











#line 305 "E:\\MDK5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"






 
#line 147 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cm3.h"
#line 1 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cmInstr.h"
 







 

























 






 



 


 









 







 







 






 








 







 







 









 









 

__attribute__((section(".rev16_text"))) static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 

__attribute__((section(".revsh_text"))) static __inline __asm int32_t __REVSH(int32_t value)
{
  revsh r0, r0
  bx lr
}










 










 











 









 









 









 











 











 











 







 










 










 









 





#line 684 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cmInstr.h"

   

#line 148 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cm3.h"
#line 1 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cmFunc.h"
 







 

























 






 



 


 





 
 






 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}







 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}







 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}







 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}







 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}







 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}







 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}







 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}







 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}







 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}







 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}








 







 








 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}







 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xff);
}







 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}







 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & (uint32_t)1);
}




#line 307 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cmFunc.h"


#line 634 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cmFunc.h"

 

#line 149 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cm3.h"








 
#line 179 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cm3.h"

 






 
#line 195 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cm3.h"

 












 


 





 


 
typedef union
{
  struct
  {

    uint32_t _reserved0:27;               





    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       

    uint32_t _reserved0:15;               





    uint32_t T:1;                         
    uint32_t IT:2;                        
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t FPCA:1;                      
    uint32_t _reserved0:29;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 






 


 
typedef struct
{
  volatile uint32_t ISER[8];                  
       uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];                  
       uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];                  
       uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];                  
       uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];                  
       uint32_t RESERVED4[56];
  volatile uint8_t  IP[240];                  
       uint32_t RESERVED5[644];
  volatile  uint32_t STIR;                     
}  NVIC_Type;

 



 






 


 
typedef struct
{
  volatile const  uint32_t CPUID;                    
  volatile uint32_t ICSR;                     
  volatile uint32_t VTOR;                     
  volatile uint32_t AIRCR;                    
  volatile uint32_t SCR;                      
  volatile uint32_t CCR;                      
  volatile uint8_t  SHP[12];                  
  volatile uint32_t SHCSR;                    
  volatile uint32_t CFSR;                     
  volatile uint32_t HFSR;                     
  volatile uint32_t DFSR;                     
  volatile uint32_t MMFAR;                    
  volatile uint32_t BFAR;                     
  volatile uint32_t AFSR;                     
  volatile const  uint32_t PFR[2];                   
  volatile const  uint32_t DFR;                      
  volatile const  uint32_t ADR;                      
  volatile const  uint32_t MMFR[4];                  
  volatile const  uint32_t ISAR[5];                  
       uint32_t RESERVED0[5];
  volatile uint32_t CPACR;                    
} SCB_Type;

 















 






























 




#line 422 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cm3.h"

 





















 









 


















 










































 









 









 















 






 


 
typedef struct
{
       uint32_t RESERVED0[1];
  volatile const  uint32_t ICTR;                     



       uint32_t RESERVED1[1];

} SCnSCB_Type;

 



 










 






 


 
typedef struct
{
  volatile uint32_t CTRL;                     
  volatile uint32_t LOAD;                     
  volatile uint32_t VAL;                      
  volatile const  uint32_t CALIB;                    
} SysTick_Type;

 












 



 



 









 






 


 
typedef struct
{
  volatile  union
  {
    volatile  uint8_t    u8;                   
    volatile  uint16_t   u16;                  
    volatile  uint32_t   u32;                  
  }  PORT [32];                           
       uint32_t RESERVED0[864];
  volatile uint32_t TER;                      
       uint32_t RESERVED1[15];
  volatile uint32_t TPR;                      
       uint32_t RESERVED2[15];
  volatile uint32_t TCR;                      
       uint32_t RESERVED3[29];
  volatile  uint32_t IWR;                      
  volatile const  uint32_t IRR;                      
  volatile uint32_t IMCR;                     
       uint32_t RESERVED4[43];
  volatile  uint32_t LAR;                      
  volatile const  uint32_t LSR;                      
       uint32_t RESERVED5[6];
  volatile const  uint32_t PID4;                     
  volatile const  uint32_t PID5;                     
  volatile const  uint32_t PID6;                     
  volatile const  uint32_t PID7;                     
  volatile const  uint32_t PID0;                     
  volatile const  uint32_t PID1;                     
  volatile const  uint32_t PID2;                     
  volatile const  uint32_t PID3;                     
  volatile const  uint32_t CID0;                     
  volatile const  uint32_t CID1;                     
  volatile const  uint32_t CID2;                     
  volatile const  uint32_t CID3;                     
} ITM_Type;

 



 



























 



 



 



 









   






 


 
typedef struct
{
  volatile uint32_t CTRL;                     
  volatile uint32_t CYCCNT;                   
  volatile uint32_t CPICNT;                   
  volatile uint32_t EXCCNT;                   
  volatile uint32_t SLEEPCNT;                 
  volatile uint32_t LSUCNT;                   
  volatile uint32_t FOLDCNT;                  
  volatile const  uint32_t PCSR;                     
  volatile uint32_t COMP0;                    
  volatile uint32_t MASK0;                    
  volatile uint32_t FUNCTION0;                
       uint32_t RESERVED0[1];
  volatile uint32_t COMP1;                    
  volatile uint32_t MASK1;                    
  volatile uint32_t FUNCTION1;                
       uint32_t RESERVED1[1];
  volatile uint32_t COMP2;                    
  volatile uint32_t MASK2;                    
  volatile uint32_t FUNCTION2;                
       uint32_t RESERVED2[1];
  volatile uint32_t COMP3;                    
  volatile uint32_t MASK3;                    
  volatile uint32_t FUNCTION3;                
} DWT_Type;

 






















































 



 



 



 



 



 



 



























   






 


 
typedef struct
{
  volatile uint32_t SSPSR;                    
  volatile uint32_t CSPSR;                    
       uint32_t RESERVED0[2];
  volatile uint32_t ACPR;                     
       uint32_t RESERVED1[55];
  volatile uint32_t SPPR;                     
       uint32_t RESERVED2[131];
  volatile const  uint32_t FFSR;                     
  volatile uint32_t FFCR;                     
  volatile const  uint32_t FSCR;                     
       uint32_t RESERVED3[759];
  volatile const  uint32_t TRIGGER;                  
  volatile const  uint32_t FIFO0;                    
  volatile const  uint32_t ITATBCTR2;                
       uint32_t RESERVED4[1];
  volatile const  uint32_t ITATBCTR0;                
  volatile const  uint32_t FIFO1;                    
  volatile uint32_t ITCTRL;                   
       uint32_t RESERVED5[39];
  volatile uint32_t CLAIMSET;                 
  volatile uint32_t CLAIMCLR;                 
       uint32_t RESERVED7[8];
  volatile const  uint32_t DEVID;                    
  volatile const  uint32_t DEVTYPE;                  
} TPI_Type;

 



 



 












 






 



 





















 



 





















 



 



 


















 






   


#line 1133 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cm3.h"






 


 
typedef struct
{
  volatile uint32_t DHCSR;                    
  volatile  uint32_t DCRSR;                    
  volatile uint32_t DCRDR;                    
  volatile uint32_t DEMCR;                    
} CoreDebug_Type;

 




































 






 







































 






 

 
#line 1253 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cm3.h"

#line 1262 "E:\\MDK5\\ARM\\CMSIS\\Include\\core_cm3.h"






 










 

 



 




 










 
static __inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07);                

  reg_value  =  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;                                                    
  reg_value &= ~((0xFFFFUL << 16) | (7UL << 8));              
  reg_value  =  (reg_value                                 |
                ((uint32_t)0x5FA << 16) |
                (PriorityGroupTmp << 8));                                      
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR =  reg_value;
}







 
static __inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) >> 8);    
}







 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}







 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}











 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}







 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}







 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}










 
static __inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}










 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 4)) & 0xff); }  
  else {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)] = ((priority << (8 - 4)) & 0xff);    }         
}












 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 4)));  }  
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)]           >> (8 - 4)));  }  
}













 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 4) ? 4 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 4) < 7) ? 0 : PriorityGroupTmp - 7 + 4;

  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}













 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 4) ? 4 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 4) < 7) ? 0 : PriorityGroupTmp - 7 + 4;

  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}





 
static __inline void NVIC_SystemReset(void)
{
  __dsb(0xF);                                                     
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = ((0x5FA << 16)      |
                 (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) |
                 (1UL << 2));                    
  __dsb(0xF);                                                      
  while(1);                                                     
}

 



 




 

















 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1) > (0xFFFFFFUL << 0))  return (1);       

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = ticks - 1;                                   
  NVIC_SetPriority (SysTick_IRQn, (1<<4) - 1);   
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0;                                           
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2) |
                   (1UL << 1)   |
                   (1UL << 0);                     
  return (0);                                                   
}



 



 




 

extern volatile int32_t ITM_RxBuffer;                     












 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if ((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL << 0))                  &&       
      (((ITM_Type *) (0xE0000000UL) )->TER & (1UL << 0)        )                    )      
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000UL) )->PORT[0].u8 = (uint8_t) ch;
  }
  return (ch);
}








 
static __inline int32_t ITM_ReceiveChar (void) {
  int32_t ch = -1;                            

  if (ITM_RxBuffer != 0x5AA55AA5) {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = 0x5AA55AA5;        
  }

  return (ch);
}








 
static __inline int32_t ITM_CheckChar (void) {

  if (ITM_RxBuffer == 0x5AA55AA5) {
    return (0);                                  
  } else {
    return (1);                                  
  }
}

 





#line 479 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"
#line 1 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\system_stm32f10x.h"



















 



 



   
  


 









 



 




 

extern uint32_t SystemCoreClock;           



 



 



 



 



 



 
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


 









 
  


   
 
#line 480 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"
#line 481 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



   

 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;   
typedef const int16_t sc16;   
typedef const int8_t sc8;    

typedef volatile int32_t  vs32;
typedef volatile int16_t  vs16;
typedef volatile int8_t   vs8;

typedef volatile const int32_t vsc32;   
typedef volatile const int16_t vsc16;   
typedef volatile const int8_t vsc8;    

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;   
typedef const uint16_t uc16;   
typedef const uint8_t uc8;    

typedef volatile uint32_t  vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t  vu8;

typedef volatile const uint32_t vuc32;   
typedef volatile const uint16_t vuc16;   
typedef volatile const uint8_t vuc8;    

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

 





 



    



 

typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
  volatile uint32_t JOFR1;
  volatile uint32_t JOFR2;
  volatile uint32_t JOFR3;
  volatile uint32_t JOFR4;
  volatile uint32_t HTR;
  volatile uint32_t LTR;
  volatile uint32_t SQR1;
  volatile uint32_t SQR2;
  volatile uint32_t SQR3;
  volatile uint32_t JSQR;
  volatile uint32_t JDR1;
  volatile uint32_t JDR2;
  volatile uint32_t JDR3;
  volatile uint32_t JDR4;
  volatile uint32_t DR;
} ADC_TypeDef;



 

typedef struct
{
  uint32_t  RESERVED0;
  volatile uint16_t DR1;
  uint16_t  RESERVED1;
  volatile uint16_t DR2;
  uint16_t  RESERVED2;
  volatile uint16_t DR3;
  uint16_t  RESERVED3;
  volatile uint16_t DR4;
  uint16_t  RESERVED4;
  volatile uint16_t DR5;
  uint16_t  RESERVED5;
  volatile uint16_t DR6;
  uint16_t  RESERVED6;
  volatile uint16_t DR7;
  uint16_t  RESERVED7;
  volatile uint16_t DR8;
  uint16_t  RESERVED8;
  volatile uint16_t DR9;
  uint16_t  RESERVED9;
  volatile uint16_t DR10;
  uint16_t  RESERVED10; 
  volatile uint16_t RTCCR;
  uint16_t  RESERVED11;
  volatile uint16_t CR;
  uint16_t  RESERVED12;
  volatile uint16_t CSR;
  uint16_t  RESERVED13[5];
  volatile uint16_t DR11;
  uint16_t  RESERVED14;
  volatile uint16_t DR12;
  uint16_t  RESERVED15;
  volatile uint16_t DR13;
  uint16_t  RESERVED16;
  volatile uint16_t DR14;
  uint16_t  RESERVED17;
  volatile uint16_t DR15;
  uint16_t  RESERVED18;
  volatile uint16_t DR16;
  uint16_t  RESERVED19;
  volatile uint16_t DR17;
  uint16_t  RESERVED20;
  volatile uint16_t DR18;
  uint16_t  RESERVED21;
  volatile uint16_t DR19;
  uint16_t  RESERVED22;
  volatile uint16_t DR20;
  uint16_t  RESERVED23;
  volatile uint16_t DR21;
  uint16_t  RESERVED24;
  volatile uint16_t DR22;
  uint16_t  RESERVED25;
  volatile uint16_t DR23;
  uint16_t  RESERVED26;
  volatile uint16_t DR24;
  uint16_t  RESERVED27;
  volatile uint16_t DR25;
  uint16_t  RESERVED28;
  volatile uint16_t DR26;
  uint16_t  RESERVED29;
  volatile uint16_t DR27;
  uint16_t  RESERVED30;
  volatile uint16_t DR28;
  uint16_t  RESERVED31;
  volatile uint16_t DR29;
  uint16_t  RESERVED32;
  volatile uint16_t DR30;
  uint16_t  RESERVED33; 
  volatile uint16_t DR31;
  uint16_t  RESERVED34;
  volatile uint16_t DR32;
  uint16_t  RESERVED35;
  volatile uint16_t DR33;
  uint16_t  RESERVED36;
  volatile uint16_t DR34;
  uint16_t  RESERVED37;
  volatile uint16_t DR35;
  uint16_t  RESERVED38;
  volatile uint16_t DR36;
  uint16_t  RESERVED39;
  volatile uint16_t DR37;
  uint16_t  RESERVED40;
  volatile uint16_t DR38;
  uint16_t  RESERVED41;
  volatile uint16_t DR39;
  uint16_t  RESERVED42;
  volatile uint16_t DR40;
  uint16_t  RESERVED43;
  volatile uint16_t DR41;
  uint16_t  RESERVED44;
  volatile uint16_t DR42;
  uint16_t  RESERVED45;    
} BKP_TypeDef;
  


 

typedef struct
{
  volatile uint32_t TIR;
  volatile uint32_t TDTR;
  volatile uint32_t TDLR;
  volatile uint32_t TDHR;
} CAN_TxMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t RIR;
  volatile uint32_t RDTR;
  volatile uint32_t RDLR;
  volatile uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t FR1;
  volatile uint32_t FR2;
} CAN_FilterRegister_TypeDef;



 
  
typedef struct
{
  volatile uint32_t MCR;
  volatile uint32_t MSR;
  volatile uint32_t TSR;
  volatile uint32_t RF0R;
  volatile uint32_t RF1R;
  volatile uint32_t IER;
  volatile uint32_t ESR;
  volatile uint32_t BTR;
  uint32_t  RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  uint32_t  RESERVED1[12];
  volatile uint32_t FMR;
  volatile uint32_t FM1R;
  uint32_t  RESERVED2;
  volatile uint32_t FS1R;
  uint32_t  RESERVED3;
  volatile uint32_t FFA1R;
  uint32_t  RESERVED4;
  volatile uint32_t FA1R;
  uint32_t  RESERVED5[8];

  CAN_FilterRegister_TypeDef sFilterRegister[14];



} CAN_TypeDef;



 
typedef struct
{
  volatile uint32_t CFGR;
  volatile uint32_t OAR;
  volatile uint32_t PRES;
  volatile uint32_t ESR;
  volatile uint32_t CSR;
  volatile uint32_t TXD;
  volatile uint32_t RXD;  
} CEC_TypeDef;



 

typedef struct
{
  volatile uint32_t DR;
  volatile uint8_t  IDR;
  uint8_t   RESERVED0;
  uint16_t  RESERVED1;
  volatile uint32_t CR;
} CRC_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SWTRIGR;
  volatile uint32_t DHR12R1;
  volatile uint32_t DHR12L1;
  volatile uint32_t DHR8R1;
  volatile uint32_t DHR12R2;
  volatile uint32_t DHR12L2;
  volatile uint32_t DHR8R2;
  volatile uint32_t DHR12RD;
  volatile uint32_t DHR12LD;
  volatile uint32_t DHR8RD;
  volatile uint32_t DOR1;
  volatile uint32_t DOR2;



} DAC_TypeDef;



 

typedef struct
{
  volatile uint32_t IDCODE;
  volatile uint32_t CR;	
}DBGMCU_TypeDef;



 

typedef struct
{
  volatile uint32_t CCR;
  volatile uint32_t CNDTR;
  volatile uint32_t CPAR;
  volatile uint32_t CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t IFCR;
} DMA_TypeDef;



 

typedef struct
{
  volatile uint32_t MACCR;
  volatile uint32_t MACFFR;
  volatile uint32_t MACHTHR;
  volatile uint32_t MACHTLR;
  volatile uint32_t MACMIIAR;
  volatile uint32_t MACMIIDR;
  volatile uint32_t MACFCR;
  volatile uint32_t MACVLANTR;              
       uint32_t RESERVED0[2];
  volatile uint32_t MACRWUFFR;              
  volatile uint32_t MACPMTCSR;
       uint32_t RESERVED1[2];
  volatile uint32_t MACSR;                  
  volatile uint32_t MACIMR;
  volatile uint32_t MACA0HR;
  volatile uint32_t MACA0LR;
  volatile uint32_t MACA1HR;
  volatile uint32_t MACA1LR;
  volatile uint32_t MACA2HR;
  volatile uint32_t MACA2LR;
  volatile uint32_t MACA3HR;
  volatile uint32_t MACA3LR;                
       uint32_t RESERVED2[40];
  volatile uint32_t MMCCR;                  
  volatile uint32_t MMCRIR;
  volatile uint32_t MMCTIR;
  volatile uint32_t MMCRIMR;
  volatile uint32_t MMCTIMR;                
       uint32_t RESERVED3[14];
  volatile uint32_t MMCTGFSCCR;             
  volatile uint32_t MMCTGFMSCCR;
       uint32_t RESERVED4[5];
  volatile uint32_t MMCTGFCR;
       uint32_t RESERVED5[10];
  volatile uint32_t MMCRFCECR;
  volatile uint32_t MMCRFAECR;
       uint32_t RESERVED6[10];
  volatile uint32_t MMCRGUFCR;
       uint32_t RESERVED7[334];
  volatile uint32_t PTPTSCR;
  volatile uint32_t PTPSSIR;
  volatile uint32_t PTPTSHR;
  volatile uint32_t PTPTSLR;
  volatile uint32_t PTPTSHUR;
  volatile uint32_t PTPTSLUR;
  volatile uint32_t PTPTSAR;
  volatile uint32_t PTPTTHR;
  volatile uint32_t PTPTTLR;
       uint32_t RESERVED8[567];
  volatile uint32_t DMABMR;
  volatile uint32_t DMATPDR;
  volatile uint32_t DMARPDR;
  volatile uint32_t DMARDLAR;
  volatile uint32_t DMATDLAR;
  volatile uint32_t DMASR;
  volatile uint32_t DMAOMR;
  volatile uint32_t DMAIER;
  volatile uint32_t DMAMFBOCR;
       uint32_t RESERVED9[9];
  volatile uint32_t DMACHTDR;
  volatile uint32_t DMACHRDR;
  volatile uint32_t DMACHTBAR;
  volatile uint32_t DMACHRBAR;
} ETH_TypeDef;



 

typedef struct
{
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
} EXTI_TypeDef;



 

typedef struct
{
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t AR;
  volatile uint32_t RESERVED;
  volatile uint32_t OBR;
  volatile uint32_t WRPR;
#line 920 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"
} FLASH_TypeDef;



 
  
typedef struct
{
  volatile uint16_t RDP;
  volatile uint16_t USER;
  volatile uint16_t Data0;
  volatile uint16_t Data1;
  volatile uint16_t WRP0;
  volatile uint16_t WRP1;
  volatile uint16_t WRP2;
  volatile uint16_t WRP3;
} OB_TypeDef;



 

typedef struct
{
  volatile uint32_t BTCR[8];   
} FSMC_Bank1_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t BWTR[7];
} FSMC_Bank1E_TypeDef;



 
  
typedef struct
{
  volatile uint32_t PCR2;
  volatile uint32_t SR2;
  volatile uint32_t PMEM2;
  volatile uint32_t PATT2;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR2; 
} FSMC_Bank2_TypeDef;  



 
  
typedef struct
{
  volatile uint32_t PCR3;
  volatile uint32_t SR3;
  volatile uint32_t PMEM3;
  volatile uint32_t PATT3;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR3; 
} FSMC_Bank3_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t PCR4;
  volatile uint32_t SR4;
  volatile uint32_t PMEM4;
  volatile uint32_t PATT4;
  volatile uint32_t PIO4; 
} FSMC_Bank4_TypeDef; 



 

typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;



 

typedef struct
{
  volatile uint32_t EVCR;
  volatile uint32_t MAPR;
  volatile uint32_t EXTICR[4];
  uint32_t RESERVED0;
  volatile uint32_t MAPR2;  
} AFIO_TypeDef;


 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t OAR1;
  uint16_t  RESERVED2;
  volatile uint16_t OAR2;
  uint16_t  RESERVED3;
  volatile uint16_t DR;
  uint16_t  RESERVED4;
  volatile uint16_t SR1;
  uint16_t  RESERVED5;
  volatile uint16_t SR2;
  uint16_t  RESERVED6;
  volatile uint16_t CCR;
  uint16_t  RESERVED7;
  volatile uint16_t TRISE;
  uint16_t  RESERVED8;
} I2C_TypeDef;



 

typedef struct
{
  volatile uint32_t KR;
  volatile uint32_t PR;
  volatile uint32_t RLR;
  volatile uint32_t SR;
} IWDG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CSR;
} PWR_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;










} RCC_TypeDef;



 

typedef struct
{
  volatile uint16_t CRH;
  uint16_t  RESERVED0;
  volatile uint16_t CRL;
  uint16_t  RESERVED1;
  volatile uint16_t PRLH;
  uint16_t  RESERVED2;
  volatile uint16_t PRLL;
  uint16_t  RESERVED3;
  volatile uint16_t DIVH;
  uint16_t  RESERVED4;
  volatile uint16_t DIVL;
  uint16_t  RESERVED5;
  volatile uint16_t CNTH;
  uint16_t  RESERVED6;
  volatile uint16_t CNTL;
  uint16_t  RESERVED7;
  volatile uint16_t ALRH;
  uint16_t  RESERVED8;
  volatile uint16_t ALRL;
  uint16_t  RESERVED9;
} RTC_TypeDef;



 

typedef struct
{
  volatile uint32_t POWER;
  volatile uint32_t CLKCR;
  volatile uint32_t ARG;
  volatile uint32_t CMD;
  volatile const uint32_t RESPCMD;
  volatile const uint32_t RESP1;
  volatile const uint32_t RESP2;
  volatile const uint32_t RESP3;
  volatile const uint32_t RESP4;
  volatile uint32_t DTIMER;
  volatile uint32_t DLEN;
  volatile uint32_t DCTRL;
  volatile const uint32_t DCOUNT;
  volatile const uint32_t STA;
  volatile uint32_t ICR;
  volatile uint32_t MASK;
  uint32_t  RESERVED0[2];
  volatile const uint32_t FIFOCNT;
  uint32_t  RESERVED1[13];
  volatile uint32_t FIFO;
} SDIO_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SR;
  uint16_t  RESERVED2;
  volatile uint16_t DR;
  uint16_t  RESERVED3;
  volatile uint16_t CRCPR;
  uint16_t  RESERVED4;
  volatile uint16_t RXCRCR;
  uint16_t  RESERVED5;
  volatile uint16_t TXCRCR;
  uint16_t  RESERVED6;
  volatile uint16_t I2SCFGR;
  uint16_t  RESERVED7;
  volatile uint16_t I2SPR;
  uint16_t  RESERVED8;  
} SPI_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SMCR;
  uint16_t  RESERVED2;
  volatile uint16_t DIER;
  uint16_t  RESERVED3;
  volatile uint16_t SR;
  uint16_t  RESERVED4;
  volatile uint16_t EGR;
  uint16_t  RESERVED5;
  volatile uint16_t CCMR1;
  uint16_t  RESERVED6;
  volatile uint16_t CCMR2;
  uint16_t  RESERVED7;
  volatile uint16_t CCER;
  uint16_t  RESERVED8;
  volatile uint16_t CNT;
  uint16_t  RESERVED9;
  volatile uint16_t PSC;
  uint16_t  RESERVED10;
  volatile uint16_t ARR;
  uint16_t  RESERVED11;
  volatile uint16_t RCR;
  uint16_t  RESERVED12;
  volatile uint16_t CCR1;
  uint16_t  RESERVED13;
  volatile uint16_t CCR2;
  uint16_t  RESERVED14;
  volatile uint16_t CCR3;
  uint16_t  RESERVED15;
  volatile uint16_t CCR4;
  uint16_t  RESERVED16;
  volatile uint16_t BDTR;
  uint16_t  RESERVED17;
  volatile uint16_t DCR;
  uint16_t  RESERVED18;
  volatile uint16_t DMAR;
  uint16_t  RESERVED19;
} TIM_TypeDef;



 
 
typedef struct
{
  volatile uint16_t SR;
  uint16_t  RESERVED0;
  volatile uint16_t DR;
  uint16_t  RESERVED1;
  volatile uint16_t BRR;
  uint16_t  RESERVED2;
  volatile uint16_t CR1;
  uint16_t  RESERVED3;
  volatile uint16_t CR2;
  uint16_t  RESERVED4;
  volatile uint16_t CR3;
  uint16_t  RESERVED5;
  volatile uint16_t GTPR;
  uint16_t  RESERVED6;
} USART_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFR;
  volatile uint32_t SR;
} WWDG_TypeDef;



 
  


 











 




#line 1312 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 1335 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



#line 1354 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"




















 
  


   

#line 1454 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 



 
  
  

 
    
 
 
 

 
 
 
 
 

 



 



 


 
 
 
 
 

 











 
#line 1515 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"




 





 
 
 
 
 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 





 



 






 
 
 
 
 

 
#line 1691 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 1698 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
 








 








 






#line 1734 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 











 











 













 






#line 1850 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"




#line 1870 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 





#line 1883 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 1902 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 1911 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 1919 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



















#line 1944 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"












 













#line 1976 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"





#line 1990 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 1997 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 2007 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"











 


















#line 2043 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2051 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



















#line 2076 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"












 













#line 2108 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"





#line 2122 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 2129 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 2139 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"











 








 








   
#line 2178 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 2273 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 2300 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"
 
 
 
 
 
 

 




































































 




































































 
#line 2462 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2480 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2498 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 2515 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2533 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2552 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 

 






 
#line 2579 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"






 








 









 








 








 









 










 




#line 2654 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 










#line 2685 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 





 
#line 2700 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2709 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

   
#line 2718 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2727 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 





 
#line 2742 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2751 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

   
#line 2760 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2769 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 





 
#line 2784 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2793 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

   
#line 2802 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2811 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 





 
#line 2826 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2835 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

   
#line 2844 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2853 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 2862 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 2871 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 2881 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
 
 
 
 

 





 


 


 




 
 
 
 
 

 
#line 2945 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 2980 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 3015 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 3050 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 3085 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 





 





 





 





 





 





 





 





 






 
#line 3152 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 



 









 
#line 3176 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"




 




 
#line 3192 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 





 
#line 3214 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
 





 
#line 3229 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"
 
#line 3236 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 




 






 


 


 


 
 
 
 
 

 
#line 3285 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 3307 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 3329 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 3351 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 3373 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 3395 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
 
 
 
 

 
#line 3431 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 3461 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 3471 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"















 
#line 3495 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"















 
#line 3519 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"















 
#line 3543 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"















 
#line 3567 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"















 
#line 3591 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"















 
#line 3615 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"















 


 


 


 


 


 


 


 


 


 



 


 


 



 


 


 


 



 


 


 


 


 
 
 
 
 

 






 
#line 3716 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3725 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"















  
 
#line 3748 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"


















 








































 


















































 


 


 


 


 


 


 
#line 3883 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3890 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3897 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3904 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"







 
#line 3918 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3925 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3932 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3939 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3946 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3953 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 3961 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3968 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3975 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3982 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3989 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 3996 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 4004 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 4011 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 4018 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 4025 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"





 


 


 


 


 



 
 
 
 
 

 









































 



 


 


 


 


 


 


 



 



 



 


 


 



 
 
 
 
 
 





 






 


 
#line 4167 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 4177 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 


 


 
 
 
 
 

 
















 









#line 4225 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 

























 
#line 4268 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 4282 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 4292 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 




























 





















 




























 





















 
#line 4411 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
#line 4446 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"





#line 4457 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 4465 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 4472 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 


 
 
 
 
 

 




 
#line 4494 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
 
 
 
 

 


 





 


 



 
 
 
 
 

 
#line 4556 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 
#line 4568 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"







 


 
 
 
 
 

 











#line 4606 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 











#line 4629 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 











#line 4652 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 











#line 4675 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 








































 








































 








































 








































 


































 


































 


































 


































 



























 



























 



























 
#line 5072 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 5081 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 5090 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 5101 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5111 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5121 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5131 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 5142 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5152 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5162 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5172 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 5183 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5193 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5203 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5213 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 5224 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5234 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5244 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5254 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 5265 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5275 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5285 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5295 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 5306 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5316 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5326 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5336 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 5347 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5357 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5367 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

#line 5377 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 


 


 
 
 
 
 

 




 












 


 






#line 5425 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
















 


 
#line 5495 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 5510 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 5536 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 


 


 
 
 
 
 

 
 























 























 























 























 























 























 























 























 
 
#line 5757 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 5769 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 






 
#line 5786 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



     


 
 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


#line 5930 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 5942 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 5954 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 5966 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 5978 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 5990 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6002 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6014 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 

 


#line 6028 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6040 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6052 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6064 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6076 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6088 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6100 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6112 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6124 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6136 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6148 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6160 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6172 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6184 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6196 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 


#line 6208 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 
 
 
 
 

 
 
#line 6228 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6239 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6257 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"











 





 





 
#line 6295 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 












 
#line 6316 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
 






 




 





 





 






 




 





 





 






   




 





 





 





 




 





 





 





 




 





 





 
 


 
#line 6456 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6473 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6490 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6507 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6541 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6575 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6609 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6643 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6677 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6711 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6745 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6779 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6813 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6847 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6881 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6915 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6949 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 6983 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7017 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7051 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7085 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7119 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7153 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7187 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7221 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7255 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7289 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7323 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7357 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7391 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7425 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7459 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
 
 
 
 

 









#line 7486 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7494 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7504 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 


 


 


 


 





















 




 
 
 
 
 

 
#line 7565 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7574 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"







 



#line 7595 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 



 


 
#line 7620 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7630 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 




 


 
 
 
 
 

 
#line 7656 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 


 



 
#line 7680 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7689 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"







 
#line 7709 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
#line 7720 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 
 
 
 
 

 


#line 7749 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 









#line 7783 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 
 
 
 
 

 









 


 


 





 
#line 7823 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"

 


 









 


 

 



 



 



 



 



 



 



 



#line 8287 "E:\\MDK5\\ARM\\PACK\\Keil\\STM32F1xx_DFP\\1.0.5\\Device\\Include\\stm32f10x.h"



 

 

  







 

















 









 

  

 

 
#line 9 "..\\SYSTEM\\System_Init.c"
#line 1 "..\\SYSTEM\\system.h"






 




void System_Initialization(void);



#line 10 "..\\SYSTEM\\System_Init.c"
#line 1 "E:\\MDK5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
 
 
 





 






 







 




  
 








#line 47 "E:\\MDK5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


  



    typedef unsigned int size_t;    









 
 

 



    typedef struct __va_list __va_list;






   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

#line 136 "E:\\MDK5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 166 "E:\\MDK5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 
extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 985 "E:\\MDK5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"



 

#line 11 "..\\SYSTEM\\System_Init.c"






 
static void RCC_Config( void )
{ 
	ErrorStatus HSEStartUpStatus;
	
	    
	 
	RCC_DeInit( );

	 
	RCC_HSEConfig( RCC_HSE_ON );

	 
	HSEStartUpStatus = RCC_WaitForHSEStartUp( );

	if( HSEStartUpStatus == SUCCESS )
	{
		 
    	FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable );

		 
    	FLASH_SetLatency( FLASH_Latency_2 );
 
		 
		RCC_HCLKConfig( RCC_SYSCLK_Div1 ); 
  
		 
		RCC_PCLK2Config( RCC_HCLK_Div1 ); 

		 
		RCC_PCLK1Config( RCC_HCLK_Div2 );

#line 66 "..\\SYSTEM\\System_Init.c"
		 
		RCC_PLLConfig( RCC_PLLSource_HSE_Div1, RCC_PLLMul_9 );


		  
		RCC_PLLCmd( ENABLE );

		 
		while( RCC_GetFlagStatus( RCC_FLAG_PLLRDY ) == RESET )
		{
		}

		 
		RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK );

		 
    	while( RCC_GetSYSCLKSource( ) != 0x08 )
    	{
    	}

		 
		RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE );

		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB  | RCC_APB2Periph_GPIOC |
								RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1 | RCC_APB2Periph_ADC1, ENABLE );

		 
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE );
	}
	else
	{ 
		
     

		 
		while( 1 )
		{
		}
	}
}







 
void NVIC_Configuration(void)
{
  	NVIC_InitTypeDef	NVIC_InitStructure;

  	 
  	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

 	 
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	 






 	 





}


 
void UART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;


	 
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init( ((GPIO_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x0800)), &GPIO_InitStructure );

	 
	 
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init( ((GPIO_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x0800)), &GPIO_InitStructure );

  	











 

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init( ((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800)), &USART_InitStructure );

	USART_ITConfig( ((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800)), USART_IT_RXNE, ENABLE );			 				 

	 
	USART_Cmd( ((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800)), ENABLE ); 
}
 
#line 198 "..\\SYSTEM\\System_Init.c"





 
int fputc( int ch, FILE *f )
{
	 
	 
	USART_SendData( ((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800)), (unsigned char) ch );

	 
	while( USART_GetFlagStatus( ((USART_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x3800)), USART_FLAG_TC ) == RESET )
	{
	}

	return ch;
}

 
void Timer_Configuration(void)
{
	 
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 36000;
	TIM_TimeBaseStructure.TIM_Prescaler = 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0000)), &TIM_TimeBaseStructure);

	 
	TIM_Cmd(((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0000)), ENABLE);

	TIM_ITConfig(((TIM_TypeDef *) (((uint32_t)0x40000000) + 0x0000)), TIM_IT_Update, ENABLE );
}


 
void System_Initialization(void)
{
 	 
  	RCC_Config();
  	 
  	NVIC_Configuration();

	 
	UART_Configuration();

}
