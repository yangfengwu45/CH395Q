/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   
  ******************************************************************************
	
  ******************************************************************************
  */
/* 单片机的引脚               CH395芯片的引脚
UART2_TXD----PA2                RXD
UART2_RXD----PA3         	      TXD 
             PB2                RST
						 PB5                SEL
INT#---------PA1                INT#
*/
	
#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "System.h"
#include "usart.h"
#include "gpio.h"
#include "delay.h"
#include "timer.h"
#include "iwdg.h"
#include "cString.h"
#include "key.h"


#include "CH395inc.h"
#include "CH395SPI.h"
#include "CH395CMD.C"

//缓存数据使用
unsigned char MainBuffer[MainBufferLen];//缓存数据,全局通用
u32  MainLen=0;      //全局通用变量
unsigned char *MainString;    //全局通用变量


int main(void)
{
  NVIC_Configuration();
	uart_init(115200,9600,9600);	 //串口初始化为115200
	GpioInit();
	CH395_PORT_INIT();
	DelayInit();
	Timer2_Config();
	IWDG_Init(IWDG_Prescaler_256,156*10);
	PBout(2)=0;
	delay_ms(1000);
	PBout(2)=1;
	
	printf("\r\nstart\r\n");
	while(1)
	{
		IWDG_Feed();//喂狗
		
		if(Timer2Cnt>1000){
			Timer2Cnt=0;
			
			printf("CH395VER : %2x\n",CH395CMDGetVer());
		}
		
		
		
		//读取串口1接收的数据
		BufferManageRead(&buff_manage_struct_usart1_recv,Usart1RecvBufferMemoryCopy,&buff_manage_struct_usart1_recv.ReadLen);
		if(buff_manage_struct_usart1_recv.ReadLen>0){//有数据
			
		}
		//读取串口2接收的数据
		BufferManageRead(&buff_manage_struct_usart2_recv,Usart2RecvBufferMemoryCopy,&buff_manage_struct_usart2_recv.ReadLen);
		if(buff_manage_struct_usart2_recv.ReadLen>0){//有数据
			
			printf("%x\r\n",Usart2RecvBufferMemoryCopy[0]);
			
		}
		
		//读取串口3接收的数据
		BufferManageRead(&buff_manage_struct_usart3_recv,Usart3RecvBufferMemoryCopy,&buff_manage_struct_usart3_recv.ReadLen);
		if(buff_manage_struct_usart3_recv.ReadLen>0){//有数据
			
		}

		if(Usart3SendDataCnt<=0)
		{
			BufferManageRead(&buff_manage_struct_usart3_send,Usart3SendBufferMemoryCopy,&buff_manage_struct_usart3_send.ReadLen);
			if(buff_manage_struct_usart3_send.ReadLen>0)
			{
				UsartOutStrIT(USART3,Usart3SendBufferMemoryCopy,buff_manage_struct_usart3_send.ReadLen);
			}
		}
	}
}
