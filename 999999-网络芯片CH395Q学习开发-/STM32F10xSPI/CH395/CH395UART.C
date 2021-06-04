/********************************** (C) COPYRIGHT *******************************
* File Name          : UART.C
* Author             : MJX
* Version            : V1.0
* Date               : 2012/11/30
* Description        : CH395芯片 硬件标准异步串口连接的硬件抽象层 V1.0
*                      提供I/O接口子程序
*******************************************************************************/
/*
1.在mDelayuS ,mDelaymS函数中实现自己的延时程序
2.CH395_Send_Byte 函数中实现自己的串口发送函数

*******************************************************************************/

#define CH395UART_C_

/* 头文件包含 */
#include "CH395UART.H"
#include "CH395INC.H"
#include "delay.h"

/*******************************************************************************
* Function Name  : Delay_uS
* Description    : 微秒级延时函数
* Input          : delay---延时值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelayuS( UINT8 delay )
{
	delay_us(delay);
}

/*******************************************************************************
* Function Name  : Delay_mS
* Description    : 毫秒级延时函数
* Input          : delay---延时值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelaymS( UINT8 delay )
{
	delay_ms(delay);
}


/*******************************************************************************
* Function Name  : CH395_Send_Byte
* Description    : 向CH395写入一字节数据
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_Send_Byte( UINT8 dat )
{
	USART2->DR = ( dat & (UINT16)0x01FF );								
	while( !( USART2->SR & USART_FLAG_TXE ) ); 
}


/*******************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : 向CH395写命令
* Input          : mCmd---将要写入CH395的命令码
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd( UINT8 mCmd ) 
{
	CH395_Send_Byte( SER_SYNC_CODE1 );							 /* 启动操作的第1个串口同步码 */
	CH395_Send_Byte( SER_SYNC_CODE2 );							 /* 启动操作的第2个串口同步码 */
	CH395_Send_Byte( mCmd );							 		 /* 输出命令码 */
  mDelayuS( 2 );  											 /* 延时2uS确保读写周期大于2uS */
}

/*******************************************************************************
* Function Name  : xWriteCH395Data
* Description    : 向CH395写数据
* Input          : mData---将要写入CH395的数据
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Data( UINT8 mData ) 
{
	CH395_Send_Byte( mData );  								 /* 串口输出 */
}

/*******************************************************************************
* Function Name  : xReadCH395Data
* Description    : 从CH395读数据
* Input          : None
* Output         : None
* Return         : 返回读取的数据
*******************************************************************************/
UINT8 xReadCH395Data( void )  
{
	UINT32 i;
	
	for( i = 0; i < 0xFFFFF0; i ++ ) 
	{  
		/* 计数防止超时 */		
		if( USART2->SR & USART_FLAG_RXNE ) 
		{  
			/* 串口接收到 */
			return( ( UINT8 )( USART2->DR & (UINT16)0x01FF ) );/* 串口输入 */
		}
	}
	return( 0 );  												 /* 不应该发生的情况 */
}



/*******************************************************************************
* Function Name  : Query395Interrupt
* Description    : 查询CH395中断(INT#低电平)
* Input          : None
* Output         : None
* Return         : 返回中断状态
*******************************************************************************/
UINT8 Query395Interrupt( void )
{
	return( CH395_INT_PIN_WIRE( ) ? FALSE : TRUE );  
}

