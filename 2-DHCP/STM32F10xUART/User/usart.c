/**
  ******************************************************************************
  * @file    usart.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   串口配置函数
  ******************************************************************************
  ******************************************************************************
  */
#define USART_C_
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>

#include "BufferManage.h"

/****************************串口1****************************/
unsigned char Usart1RecvBuff[Usart1RecvBuffLen]={0};  //接收数据缓存
u32  Usart1RecvCnt = 0;//串口接收到的数据个数

u8   Usart1RecvBufferMemory[Usart1RecvBufferMemoryLen];//接收数据缓存区
u8   Usart1RecvBufferMemoryCopy[Usart1RecvBufferMemoryCopyLen];//提取缓存区的数据
u32  Usart1RecvBufferMemoryManage[Usart1RecvBufferMemoryManageLen];//管理缓存区

unsigned char Usart1SendBuff[Usart1SendBufflen];  //串口发送数据缓存
u8 Usart1SendBits=0;//串口提取环形队列1个字节

unsigned char *Usart1SendData;//串口中断发送数据的地址
u32   Usart1SendDataCnt=0;//串口中断发送数据的个数


/****************************串口2****************************/
unsigned char Usart2RecvBuff[Usart2RecvBuffLen]={0};  //接收数据缓存
u32  Usart2RecvCnt = 0;//串口接收到的数据个数

u8   Usart2RecvBufferMemory[Usart2RecvBufferMemoryLen];//接收数据缓存区
u8   Usart2RecvBufferMemoryCopy[Usart2RecvBufferMemoryCopyLen];//提取缓存区的数据
u32  Usart2RecvBufferMemoryManage[Usart2RecvBufferMemoryManageLen];//管理缓存区

unsigned char *Usart2SendData;//串口中断发送数据的地址
u32   Usart2SendDataCnt=0;//串口中断发送数据的个数



/****************************串口3****************************/
unsigned char Usart3RecvBuff[Usart3RecvBuffLen]={0};  //接收数据缓存
u32  Usart3RecvCnt = 0;//串口接收到的数据个数

u8   Usart3RecvBufferMemory[Usart3RecvBufferMemoryLen];//接收数据缓存区
u8   Usart3RecvBufferMemoryCopy[Usart3RecvBufferMemoryCopyLen];//提取缓存区的数据
u32  Usart3RecvBufferMemoryManage[Usart3RecvBufferMemoryManageLen];//管理缓存区

unsigned char *Usart3SendData;//串口中断发送数据的地址
u32   Usart3SendDataCnt=0;//串口中断发送数据的个数

u8   Usart3SendBufferMemory[Usart3SendBufferMemoryLen];//接收数据缓存区
u8   Usart3SendBufferMemoryCopy[Usart3SendBufferMemoryCopyLen];//提取缓存区的数据
u32  Usart3SendBufferMemoryManage[Usart3SendBufferMemoryManageLen];//管理缓存区

/**
* @brief   串口初始化
* @param   bound  波特率
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void uart_init(u32 bound1,u32 bound2,u32 bound3){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	rbCreate(&rb_t_usart1_send,Usart1SendBuff,Usart1SendBufflen);//创建环形队列(用于发送数据)
	BufferManageCreate(&buff_manage_struct_usart1_recv,Usart1RecvBufferMemory,Usart1RecvBufferMemoryLen,Usart1RecvBufferMemoryManage,Usart1RecvBufferMemoryManageLen*4);/*串口接收缓存*/
	
	BufferManageCreate(&buff_manage_struct_usart2_recv,Usart2RecvBufferMemory,Usart2RecvBufferMemoryLen,Usart2RecvBufferMemoryManage,Usart2RecvBufferMemoryManageLen*4);/*串口接收缓存*/
	
	BufferManageCreate(&buff_manage_struct_usart3_recv,Usart3RecvBufferMemory,Usart3RecvBufferMemoryLen,Usart3RecvBufferMemoryManage,Usart3RecvBufferMemoryManageLen*4);/*串口接收缓存*/
	BufferManageCreate(&buff_manage_struct_usart3_send,Usart3SendBufferMemory,Usart3SendBufferMemoryLen,Usart3SendBufferMemoryManage,Usart3SendBufferMemoryManageLen*4);/*串口发送缓存*/
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO , ENABLE);	//??USART1,GPIOA??
	
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
  
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10 
	
	
	
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //USART2_RX	  GPIOA.3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	 //USART3_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  //USART3_RX	  GPIOB.11
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
  
	
  //USART 初始化设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	
	
	USART_InitStructure.USART_BaudRate = bound1;//串口波特率
  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
	USART_InitStructure.USART_BaudRate = bound2;//串口波特率
	USART_Init(USART2, &USART_InitStructure); //初始化串口2
	
	USART_InitStructure.USART_BaudRate = bound3;//串口波特率
	USART_Init(USART3, &USART_InitStructure); //初始化串口3
	
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
	
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//空闲中断
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//空闲中断
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//空闲中断
  USART_Cmd(USART1, ENABLE);                    //使能串口
	USART_Cmd(USART2, ENABLE);                    //使能串口
	USART_Cmd(USART3, ENABLE);                    //使能串口
}


/**
* @brief  串口中断发送数据
* @param  c:数据的首地址  cnt:发送的数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStrIT(USART_TypeDef* USARTx,unsigned char *c,uint32_t cnt)
{
	if(USARTx == USART1){
		PutData(&rb_t_usart1_send,c,cnt);
		USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
	}
	else if(USARTx == USART2){
		Usart2SendData=c;
		Usart2SendDataCnt=cnt;
		USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
	}
	else if(USARTx == USART3){
		Usart3SendData=c;
		Usart3SendDataCnt=cnt;
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
void UsartOutStr(USART_TypeDef* USARTx,unsigned char *c,uint32_t cnt)
{
	while(cnt--)
	{
		USART_SendData(USARTx, *c++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
	}
}


/**
* @brief  串口发送一个字节
* @param  *c:发送的数据指针
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutChar(USART_TypeDef* USARTx,unsigned char c)
{
	USART_SendData(USARTx,c);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
}



void USART1_IRQHandler(void)//串口1中断服务程序
{
	u8 Res;
	int value;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		
		Usart1RecvBuff[Usart1RecvCnt] = Res;	//接收的数据存入数组
		Usart1RecvCnt++;
		if(Usart1RecvCnt > Usart1RecvBuffLen -10)//防止数组溢出
		{
			Usart1RecvCnt = 0;
		}
	} 
	else if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET)//空闲中断
	{
		USART1->DR; //清除USART_IT_IDLE标志
		//把数据存入缓存
	  BufferManageWrite(&buff_manage_struct_usart1_recv,Usart1RecvBuff,Usart1RecvCnt,&value);
		Usart1RecvCnt=0;
  }  
	
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {
    if(rbCanRead(&rb_t_usart1_send)>0)//如果里面的数据个数大于0
    {
			rbRead(&rb_t_usart1_send,&Usart1SendBits,1);
			USART_SendData(USART1, Usart1SendBits);
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


void USART2_IRQHandler(void)//串口2中断服务程序
{
	u8 Res;
	int value;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		
		Usart2RecvBuff[Usart2RecvCnt] = Res;	//接收的数据存入数组
		Usart2RecvCnt++;
		if(Usart2RecvCnt > Usart2RecvBuffLen -10)//防止数组溢出
		{
			Usart2RecvCnt = 0;
		}
	} 
	else if(USART_GetITStatus(USART2,USART_IT_IDLE) == SET)//空闲中断
	{
		USART2->DR; //清除USART_IT_IDLE标志
		//把数据存入缓存
		/*不超过提取数据数组大小,预防数组溢出*/
		if(Usart2RecvCnt<= Usart2RecvBufferMemoryCopyLen)
		{
			BufferManageWrite(&buff_manage_struct_usart2_recv,Usart2RecvBuff,Usart2RecvCnt,&value);
		}
		
	  
		Usart2RecvCnt=0;
  }  
	
	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {
    if(Usart2SendDataCnt>0)//如果里面的数据个数大于0
    {
			USART_SendData(USART2, *Usart2SendData);
			Usart2SendData++;
		  Usart2SendDataCnt--;
    }
    else
    {
      //发送字节结束			
      USART_ClearITPendingBit(USART2,USART_IT_TXE);
      USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART2, USART_IT_TC, ENABLE);
    }
  }
	//发送完成
  if (USART_GetITStatus(USART2, USART_IT_TC) != RESET)
  {
    USART_ClearITPendingBit(USART2,USART_IT_TC);
    USART_ITConfig(USART2, USART_IT_TC, DISABLE);
  }
} 

void USART3_IRQHandler(void)//串口3中断服务程序
{
	u8 Res;
	int value;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART3);	//读取接收到的数据
		
		Usart3RecvBuff[Usart3RecvCnt] = Res;	//接收的数据存入数组
		Usart3RecvCnt++;
		if(Usart3RecvCnt > Usart3RecvBuffLen -10)//防止数组溢出
		{
			Usart3RecvCnt = 0;
		}
	} 
	else if(USART_GetITStatus(USART3,USART_IT_IDLE) == SET)//空闲中断
	{
		USART3->DR; //清除USART_IT_IDLE标志
		//把数据存入缓存
		/*不超过提取数据数组大小,预防数组溢出*/
		if(Usart3RecvCnt<= Usart3RecvBufferMemoryCopyLen)
		{	
			BufferManageWrite(&buff_manage_struct_usart3_recv,Usart3RecvBuff,Usart3RecvCnt,&value);
		}
		Usart3RecvCnt=0;
  }  
	
	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  {
    if(Usart3SendDataCnt>0)//如果里面的数据个数大于0
    {
			USART_SendData(USART3, *Usart3SendData);
			Usart3SendData++;
		  Usart3SendDataCnt--;
    }
    else
    {
      //发送字节结束			
      USART_ClearITPendingBit(USART3,USART_IT_TXE);
      USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART3, USART_IT_TC, ENABLE);
    }
  }
	//发送完成
  if (USART_GetITStatus(USART3, USART_IT_TC) != RESET)
  {
    USART_ClearITPendingBit(USART3,USART_IT_TC);
    USART_ITConfig(USART3, USART_IT_TC, DISABLE);
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

