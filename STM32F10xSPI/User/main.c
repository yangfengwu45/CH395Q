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
#include "CH395INC.H"
#include "CH395CMD.H"
/*提示:(只是提示!这节使用的Socket0通信,并没有人为分配缓存区)
芯片共有48块缓存区,每个缓存区512字节
芯片共有8个Socket,默认把48块缓存区分给了Socket0,Socket1,Socket2,Socket3
这四个Socket,每个 Socket 使用8块缓存区作为接收,4块缓存区作为发送,
即Socket0,Socket1,Socket2,Socket3的接收区各为512*8 = 4KB
即Socket0,Socket1,Socket2,Socket3的发送区各为512*4 = 2KB
如果要使用Socket4,Socket5,Socket6,Socket7需要重新分配缓存区
*/


/*存储网络接收的数据*/
#define recv_buff_len 1500
unsigned char recv_buff[recv_buff_len];

char ch395_version=0;//获取版本号

unsigned char buf[20];
int ch395_status=0;//获取中断事件

/* socket 相关定义*/
UINT8  SocketIndex = 0; /* Socket 索引0,1,2,3,4,5,6,7*/
UINT8  SocketDesIP[4] = {192,168,0,103}; /* Socket 目的IP地址 */
const UINT8  IPRawProto = 0x06;          /* IP包协议类型 */

/**
* @brief   初始化socket
* @param   sockindex  Socket索引(0,1,2,3,4,5,6,7)
* @param   ipaddr  目的地址
* @param   desprot 目的端口号
* @param   surprot 本地端口号
* @retval  0:初始化成功; others:初始化失败
* @warning None
* @example 
**/
char ch395_socket_tcp_client_init(UINT8 sockindex,UINT8 *ipaddr)
{
    CH395SetSocketDesIP(sockindex,ipaddr);         		   /* 目的地址 */         
    CH395SetSocketProtType(sockindex,PROTO_TYPE_IP_RAW); /* 协议类型 */
		CH395SetSocketIPRAWProto(sockindex,IPRawProto);      /* 设置协议字段 */
		if(CH395OpenSocket(sockindex) !=0)                   /* 打开Socket */
		{
			return 1;
		}
		return 0;
}


/**
* @brief   socket处理函数(把此函数放到全局socket中断里面)
* @param   sockindex  Socket索引(0,1,2,3,4,5,6,7)
* @param   None
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void ch395_socket_tcp_client_interrupt(UINT8 sockindex)
{
	UINT8  sock_int_socket;
	UINT16 len;
	
	/* 获取socket 的中断状态 */
	sock_int_socket = CH395GetSocketInt(sockindex);
	
	/* 发送缓冲区空闲，可以继续写入要发送的数据 */
	if(sock_int_socket & SINT_STAT_SENBUF_FREE)
	{
	}
	
	/* 发送完成中断 */
	if(sock_int_socket & SINT_STAT_SEND_OK)                           
	{
	}
	
	/* 接收数据中断 */
	if(sock_int_socket & SINT_STAT_RECV)                              
	{
		len = CH395GetRecvLength(sockindex);/* 获取当前缓冲区内数据长度 */
		if(len == 0)return;
		if(len > recv_buff_len)len = recv_buff_len;
		CH395GetRecvData(sockindex,len,recv_buff);/* 读取数据 */
		
		/*把接收的数据发送给服务器*/
		CH395SendData(sockindex,recv_buff,len);
		
		/*使用串口打印接收的数据*/
		PutData(&rb_t_usart1_send,recv_buff,len);
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	}
	
	/* 连接中断，仅在TCP模式下有效*/
	if(sock_int_socket & SINT_STAT_CONNECT)                          
	{
		printf("SINT_STAT_CONNECT\n");
	}
	
	/* 断开中断，仅在TCP模式下有效 */
	if(sock_int_socket & SINT_STAT_DISCONNECT)   
	{
		printf("SINT_STAT_DISCONNECT \n");
	}
 
	/* 超时中断，仅在TCP模式下有效 ,TCP CLIENT无法顺利连接服务器端会进入此中断*/
	if(sock_int_socket & SINT_STAT_TIM_OUT)      
	{/*此时可以把Socket源端口号进行自加处理，以新的端口去连接服务器*/ 
		printf("SINT_STAT_TIM_OUT\n");
	}
}

int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	delay_init();
	timer2_config();
	
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
	
	/*测试命令，按位取反返回说明测试通过*/
	while(CH395CMDCheckExist(0x55) != 0xaa)
	{
		printf("\r\nCH395CMDCheck ERR\r\n");
		delay_ms(100);
	}
	
	/*初始化模块:成功返回 0 */
	while(CH395CMDInitCH395() != 0)
	{
		printf("\r\nCH395CMDInitCH395 ERR\r\n");
		delay_ms(100);
	}
	
	CH395CMDGetMACAddr(buf);
	printf("\r\nCH395MAC %02x:%02x:%02x:%02x:%02x:%02x\r\n",buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);
	
	/*初始化IP RAW*/
	ch395_socket_tcp_client_init(SocketIndex,SocketDesIP);
	
	printf("\r\nstart\r\n");
	while(1)
	{
		IWDG_Feed();//喂狗
		
		/*每隔一段时间发送个数据*/
		//填写的数据为IPRAW数据,应该根据协议包含端口号等等,但是我只是随意写了111111
		if(Timer2Cnt>8000)
		{
			Timer2Cnt = 0;
			CH395SendData(SocketIndex,"111111",6);
		}
		
		
		//INT引脚产生低电平中断以后进去判断
		if(Query395Interrupt())
		{
			/*获取中断事件*/
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
				if(CH395GetDHCPStatus() == 0)//DHCP OK
				{
					CH395GetIPInf(buf);//获取IP地址,网关和子网掩码
					printf("IP:%d.%d.%d.%d\r\n",buf[0],buf[1],buf[2],buf[3]);
					printf("GWIP:%d.%d.%d.%d\r\n",buf[4],buf[5],buf[6],buf[7]);
					printf("Mask:%d.%d.%d.%d\r\n",buf[8],buf[9],buf[10],buf[11]);
					printf("DNS1:%d.%d.%d.%d\r\n",buf[12],buf[13],buf[14],buf[15]);
					printf("DNS2:%d.%d.%d.%d\r\n",buf[16],buf[17],buf[18],buf[19]);
				}
			}

			/* 处理不可达中断，读取不可达信息 */
			if(ch395_status & GINT_STAT_UNREACH){
				CH395CMDGetUnreachIPPT(buf);
			}
			
			/* 处理IP冲突中断，建议重新修改CH395的 IP，并初始化CH395*/
			if(ch395_status & GINT_STAT_IP_CONFLI){

			}
			/* 处理 SOCK0 中断 */
			if(ch395_status & GINT_STAT_SOCK0){
				ch395_socket_tcp_client_interrupt(SocketIndex);
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






