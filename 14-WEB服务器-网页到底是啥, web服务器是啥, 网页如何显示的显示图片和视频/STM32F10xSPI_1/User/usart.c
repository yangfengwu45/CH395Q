/**
  ******************************************************************************
  * @file    usart.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   串口配置函数
				
  ******************************************************************************
  */
#define USART_C_
#include <stdio.h>
#include "usart.h"

/****************************串口1****************************/
//接收环形队列
rb_t rb_t_usart1_read;
//环形队列缓存数组
unsigned char rb_t_usart1_read_buff[rb_t_usart1_read_buff_len];
//从缓存拷贝数据使用
unsigned char usart1_read_buff_copy[rb_t_usart1_read_buff_len];
//接收计数
int usart1_read_count=0;


//发送环形队列
rb_t rb_t_usart1_send;
//环形队列缓存数组
unsigned char rb_t_usart1_send_buff[rb_t_usart1_send_buff_len];
//串口提取环形队列1个字节
unsigned char rb_t_usart1_send_byte;
//空闲中断标志
unsigned char usart1_idle_flag=0;


/**
* @brief   串口初始化
* @param   bound  波特率
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void uart_init(u32 bound1){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//创建环形队列(用于串口1接收数据)
	rbCreate(&rb_t_usart1_read,rb_t_usart1_read_buff,rb_t_usart1_read_buff_len);
	//创建环形队列(用于串口1发送数据)
	rbCreate(&rb_t_usart1_send,rb_t_usart1_send_buff,rb_t_usart1_send_buff_len);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO , ENABLE);
	
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  
  //USART 初始化设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	
	USART_InitStructure.USART_BaudRate = bound1;//串口波特率
  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
	
	/*串口--1*/
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//空闲中断
  USART_Cmd(USART1, ENABLE);                    //使能串口
}


/**
* @brief  串口中断发送数据
* @param  c:数据的首地址  cnt:发送的数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStrIT(USART_TypeDef* USARTx, unsigned char *c, uint32_t cnt)
{
	if(USARTx == USART1){
		PutData(&rb_t_usart1_send,c,cnt);
		USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
	}
}


/**
* @brief  串口发送字符串数据
* @param  *c:发送的数据指针  cnt:数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStr(USART_TypeDef* USARTx, unsigned char *c,uint32_t cnt)
{
	while(cnt--)
	{
		USART_SendData(USARTx, *c++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
	}
}


/**
* @brief  串口发送一个字节
* @param  *c:发送的数据指针  cnt:数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutChar(USART_TypeDef* USARTx, unsigned char c)
{
	USART_SendData(USARTx,c);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
}


//串口中断服务程序
void USART1_IRQHandler(void)
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		
		PutData(&rb_t_usart1_read,&Res,1);
		usart1_read_count++;
	}
	else if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET)//空闲中断
	{
		USART1->DR; //清除USART_IT_IDLE标志
		usart1_idle_flag = 1;
  }
	
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {
    if(rbCanRead(&rb_t_usart1_send)>0)//如果里面的数据个数大于0
    {
			rbRead(&rb_t_usart1_send,&rb_t_usart1_send_byte,1);
			USART_SendData(USART1, rb_t_usart1_send_byte);
    }
    else
    {
      //发送字节结束			
      USART_ClearITPendingBit(USART1,USART_IT_TXE);
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    }
  }
	//发送完成
  if (USART_GetITStatus(USART1, USART_IT_TC) != RESET)
  {
    USART_ClearITPendingBit(USART1,USART_IT_TC);
    USART_ITConfig(USART1, USART_IT_TC, DISABLE);
  }
} 



/**
* @brief  使用microLib的方法,使用printf
* @warningg 勾选 microLib
* @param  None
* @param  None
* @param  None
* @retval None
* @example 
**/

int fputc(int ch, FILE *f)
{
	static char flage=0;
	uint8_t data = ch;
	if(!flage)
	{
	  flage=1;
		USART_ClearITPendingBit(USART1,USART_IT_TC);//解决printf丢失第一个字节的问题
	}
	PutData(&rb_t_usart1_send,&data,1);
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  return ch;
}

