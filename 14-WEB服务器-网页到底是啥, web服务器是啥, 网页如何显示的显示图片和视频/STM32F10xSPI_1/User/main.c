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


#include "http_help.h"


/*存储网络接收的数据*/
#define recv_buff_len 500
unsigned char recv_buff[recv_buff_len];

char ch395_version=0;//获取版本号

unsigned char buf[20];
int ch395_status=0;//获取中断事件

/* socket 相关定义*/
UINT16 SocketServerPort   = 80;           /*本地监听的 Socket 端口 */
char   SocketServerStatus = 0;//SocketServer状态 0:未启动监听; 1:启动监听

//缓存服务器发送的响应头部的数据
char http_response_data[1024];

//缓存服务器发送的响应的正文
char http_html_data[1024]=
"<html>\r\n \
<head>\r\n \
<title>这是显示网页标题</title>\r\n \
</head> \
<body> \
<h1>这是神么来?</h1> \
</body> \
</html>";


/**
* @brief   初始化socket
* @param   sockindex  Socket索引(0,1,2,3,4,5,6,7)
* @param   None
* @param   None
* @param   surprot 本地端口号
* @retval  0:初始化成功; others:初始化失败
* @warning None
* @example 
**/
char ch395_socket_tcp_server_init(UINT8 sockindex,UINT16 surprot)
{       
    CH395SetSocketProtType(sockindex,PROTO_TYPE_TCP); /* 协议类型 */
    CH395SetSocketSourPort(sockindex,surprot);  			/* 本地端口号 */
		if(CH395OpenSocket(sockindex) !=0)                /* 打开Socket */
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
		
		/*使用串口打印接收的数据*/
		printf("socket%d receive data:\r\n",sockindex);
		PutData(&rb_t_usart1_send,recv_buff,len);
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		
		/*响应头部*/
		len = sprintf((char *)http_response_data,"HTTP/1.1 200 OK\r\n\
Content-Type: text/html\r\n\
Content-Length:%d\r\n\r\n",sizeof(http_html_data)
		);			
		//发送响应头部
		CH395SendData(sockindex,(UINT8*)http_response_data,len);
		delay_ms(10);

		/*发送响应正文*/
		CH395SendData(sockindex,(unsigned char*)http_html_data,sizeof(http_html_data));
	}
	
	/* 连接中断，仅在TCP模式下有效*/
	if(sock_int_socket & SINT_STAT_CONNECT)                          
	{
		printf("socket%d SINT_STAT_CONNECT\r\n",sockindex);
		
		CH395CMDGetRemoteIPP(sockindex,buf);//获取连接的TCP客户端的信息
		printf("IP address = %d.%d.%d.%d\r\n",(UINT16)buf[0],(UINT16)buf[1],(UINT16)buf[2],(UINT16)buf[3]);    
		printf("Port = %d\r\n",((buf[5]<<8) + buf[4]));
	}
	
	/* 断开中断，仅在TCP模式下有效 */
	if(sock_int_socket & SINT_STAT_DISCONNECT)   
	{
		printf("socket%d SINT_STAT_DISCONNECT \r\n",sockindex);
		SocketServerStatus = 0;//服务器状态设置为未启动监听
	}
 
	/* 超时中断，仅在TCP模式下有效 ,TCP CLIENT无法顺利连接服务器端会进入此中断*/
	if(sock_int_socket & SINT_STAT_TIM_OUT)      
	{/*此时可以把Socket源端口号进行自加处理，以新的端口去连接服务器*/ 
		printf("socket%d SINT_STAT_TIM_OUT\r\n",sockindex);
		SocketServerStatus = 0;//服务器状态设置为未启动监听
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
	printf("CH395CMDGetVer =%2x\r\n",ch395_version);
	
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
	
	printf("\r\nstart\r\n");
	while(1)
	{
		IWDG_Feed();//喂狗
		
		
		/*检测到没有启动服务器,则执行启动服务器*/
		if(SocketServerStatus == 0)
		{
			if(ch395_socket_tcp_server_init(0,SocketServerPort) == 0)
			{
				if(CH395TCPListen(0) == 0) //Socke 0 启动TCP监听
				{
					printf("\r\nCH395TCPListen\r\n");
					SocketServerStatus = 1;//服务器状态设置为启动监听
				}
			}
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
					CH395GetIPInf(buf);//获取IP，子网掩码和网关地址
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
				ch395_socket_tcp_client_interrupt(0);
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






