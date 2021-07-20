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
#include "CH395CMD.H"

char ch395_version=0;//获取版本号
int ch395_status=0;//获取中断事件
UINT8  buf[20];//缓存DHCP数据
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
	
	/*获取芯片版本*/
	while((ch395_version = CH395CMDGetVer()) < 0x40)
	{
		printf("CH395CMDGetVer ERR\r\n");
		delay_ms(100);
	}
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

		//INT引脚产生低电平中断以后进去判断
		if(Query395Interrupt())
		{
			/*获取中断事件(不同版本获取的函数不一样)*/
			if(ch395_version>=0x44)
			{
				ch395_status = CH395CMDGetGlobIntStatus_ALL();
			}				
			else
			{
				ch395_status = CH395CMDGetGlobIntStatus();
			}

			/* 处理PHY改变中断*/
			if(ch395_status & GINT_STAT_PHY_CHANGE)                           
			{
				if(CH395CMDGetPHYStatus() == PHY_DISCONN)//网线断开
				{
					printf("\r\nPHY_DISCONN\r\n");
				}
				else//网线连接
				{
					printf("\r\nPHY_CONNECTED\r\n");
					CH395DHCPEnable(1);//启动DHCP
				}
			}
			
			
			/* 处理DHCP/PPPOE中断 */
			if(ch395_status & GINT_STAT_DHCP)
			{
				if(CH395GetDHCPStatus() == 0)//DHCP是OK的
				{
					CH395GetIPInf(buf);//获取IP，子网掩码和网关地址

					printf("IP:%d.%d.%d.%d\r\n",buf[0],buf[1],buf[2],buf[3]);
					printf("GWIP:%d.%d.%d.%d\r\n",buf[4],buf[5],buf[6],buf[7]);
					printf("Mask:%d.%d.%d.%d\r\n",buf[8],buf[9],buf[10],buf[11]);
					printf("DNS1:%d.%d.%d.%d\r\n",buf[12],buf[13],buf[14],buf[15]);
					printf("DNS2:%d.%d.%d.%d\r\n",buf[16],buf[17],buf[18],buf[19]);
				}
			}
			
			/* 处理不可达中断，读取不可达信息 */
			if(ch395_status & GINT_STAT_UNREACH)                              
			{
				CH395CMDGetUnreachIPPT(buf);                                
			}
			
			/* 处理IP冲突中断，建议重新修改CH395的 IP，并初始化CH395*/
			if(ch395_status & GINT_STAT_IP_CONFLI){
				
			}
			/* 处理 SOCK0 中断 */
			if(ch395_status & GINT_STAT_SOCK0){
				
			}
			/* 处理 SOCK1 中断 */
			if(ch395_status & GINT_STAT_SOCK1){
				
			}
			/* 处理 SOCK2 中断 */
			if(ch395_status & GINT_STAT_SOCK2){
				
			}
			/* 处理 SOCK3 中断 */
			if(ch395_status & GINT_STAT_SOCK3){
				
			}
			
			if(ch395_version>=0x44)
			{
				/* 处理 SOCK4 中断 */
				if(ch395_status & GINT_STAT_SOCK4){

				}
				/* 处理 SOCK5 中断 */
				if(ch395_status & GINT_STAT_SOCK5){

				}
				/* 处理 SOCK6 中断 */
				if(ch395_status & GINT_STAT_SOCK6){

				}
				/* 处理 SOCK7 中断 */
				if(ch395_status & GINT_STAT_SOCK7){

				}
			}
		}
	}
}









