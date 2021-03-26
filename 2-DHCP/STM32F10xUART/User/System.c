#include "System.h"
#include <stdlib.h>
#include <stdio.h>

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	
	/*串口--1*/
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
		/*串口--2*/
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
		/*串口--3*/
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
		//定时器2
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
}
/*复位芯片*/
void Reset_MCU(void)
{
  __disable_fault_irq();   
	NVIC_SystemReset();
}


uint32_t idAddr[]={
	0x1FFFF7AC,/*STM32F0唯一ID起始地址*/
	0x1FFFF7E8,/*STM32F1唯一ID起始地址*/
	0x1FFF7A10,/*STM32F2唯一ID起始地址*/
	0x1FFFF7AC,/*STM32F3唯一ID起始地址*/
	0x1FFF7A10,/*STM32F4唯一ID起始地址*/
	0x1FF0F420,/*STM32F7唯一ID起始地址*/
	0x1FF80050,/*STM32L0唯一ID起始地址*/
	0x1FF80050,/*STM32L1唯一ID起始地址*/
	0x1FFF7590,/*STM32L4唯一ID起始地址*/
	0x1FF0F420 /*STM32H7唯一ID起始地址*/
}; 
 
/*获取MCU唯一ID*/
void GetSTM32MCUID(uint32_t *MCUID,char AddrID)
{
	if(MCUID!=NULL)
	{
		MCUID[0]=*(uint32_t*)(idAddr[AddrID]);
		MCUID[1]=*(uint32_t*)(idAddr[AddrID]+4);
		MCUID[2]=*(uint32_t*)(idAddr[AddrID]+8);
		
		printf("\r\n 芯片唯一ID: %X-%X-%X\r\n",MCUID[0],MCUID[1],MCUID[2]);   
	}
}

