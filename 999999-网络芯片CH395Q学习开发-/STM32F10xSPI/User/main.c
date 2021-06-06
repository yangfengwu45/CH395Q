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

int ch395_status=0;//获取中断事件
UINT8  buf[20];//缓存DHCP数据
UINT8 dhcp_enable_flage = 1; //1:没有使能DHCP, 0:使能DHCP
UINT8 dhcp_success_flage = 0;//0:未获取到DHCP分配的地址信息,  1:获取地址成功
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
		/* 查询CH395是否连接上路由器 */
		if(CH395CMDGetPHYStatus() == PHY_DISCONN)
		{
			printf("CH395 DisConnect Ethernet\r\n");//模块没有连接上路由器
			delay_ms(1000);
			//重置变量
			dhcp_enable_flage = 1;
			dhcp_success_flage = 0;
		}
		else /*网线连接上以后再去启动DHCP*/
		{
			if(dhcp_enable_flage !=0)//没有启动DHCP
			{
				dhcp_enable_flage =CH395DHCPEnable(1);//启动DHCP,成功返回0
				if(dhcp_enable_flage !=0){
					printf("CH395DHCPEnable ERR\r\n");
					delay_ms(100);
				}
			}
			else //已经启用DHCP,轮训事件
			{
				//INT引脚产生低电平中断以后进去判断
				if(Query395Interrupt()) //也可以屏蔽掉这句,让下面的程序一直轮训模组
				{
					/*获取中断事件*/
					ch395_status = CH395CMDGetGlobIntStatus_ALL();

					/* 处理不可达中断，读取不可达信息 */
					if(ch395_status & GINT_STAT_UNREACH)                              
					{
						CH395CMDGetUnreachIPPT(buf);                                
					}
					
					/* 处理PHY改变中断*/
					if(ch395_status & GINT_STAT_PHY_CHANGE)                           
					{
						printf("Init status : GINT_STAT_PHY_CHANGE\r\n");
						//重置变量
						dhcp_enable_flage = 1;//重新DHCP
						dhcp_success_flage = 0;
					}
					
					/* 处理DHCP/PPPOE中断 */
					if(ch395_status & GINT_STAT_DHCP)
					{
						if(!dhcp_success_flage)//还没有获取到DHCP分配的地址信息
						{
							if(CH395GetDHCPStatus() == 0)//DHCP是OK的
							{
								
								CH395GetIPInf(buf);//获取IP，子网掩码和网关地址
								
								//确定获取到了
								if(buf[0]!=0 || buf[1]!=0 || buf[2]!=0 || buf[3]!=0)
								{
									dhcp_success_flage = 1;
									
									printf("IP:%d.%d.%d.%d\r\n",buf[0],buf[1],buf[2],buf[3]);
									printf("GWIP:%d.%d.%d.%d\r\n",buf[4],buf[5],buf[6],buf[7]);
									printf("Mask:%d.%d.%d.%d\r\n",buf[8],buf[9],buf[10],buf[11]);
									printf("DNS1:%d.%d.%d.%d\r\n",buf[12],buf[13],buf[14],buf[15]);
									printf("DNS2:%d.%d.%d.%d\r\n",buf[16],buf[17],buf[18],buf[19]);
								}
							}
						}
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
}









