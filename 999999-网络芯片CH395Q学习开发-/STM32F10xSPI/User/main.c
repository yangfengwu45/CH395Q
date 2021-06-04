/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   
  ******************************************************************************
	
  ******************************************************************************/
	
#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcu_api.h"
#include "usart.h"
#include "delay.h"
#include "timer.h"
#include "iwdg.h"


#include "CH395SPI.H"
#include "CH395CMD.C"


int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	delay_init();
	//初始化CH395使用的GPIO
	CH395_PORT_INIT();
	//复位 CH395
	CH395_RST();
	
	IWDG_Init(IWDG_Prescaler_256,156*10);
	printf("\r\nstart\r\n");
	
	//打印芯片版本
	printf("CH395VER : %2x\n",CH395CMDGetVer());
	//测试命令，按位取反返回说明测试通过
	while(CH395CMDCheckExist(0x55) == 0xaa)
	{
		printf("\r\nCH395CMDCheck OK\r\n");
		break;
	}
	//初始化模块:成功返回 0 
	while(!CH395CMDInitCH395())
	{
		printf("\r\nCH395CMDInitCH395 OK\r\n");
		break;
	}
	
	printf("\r\nstart\r\n");
	while(1)
	{
		IWDG_Feed();//喂狗

		/* 查询CH395是否连接 */
		if(CH395CMDGetPHYStatus() == PHY_DISCONN)
		{
			
			printf("CH395 DisConnect Ethernet\n");
		}
		else /* CH395芯片连接到以太网，此时会产生中断 */
		{   
			printf("CH395 Connect Ethernet\n");
		}
		
		delay_ms(300);
	}
}









