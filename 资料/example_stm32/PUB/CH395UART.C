/********************************** (C) COPYRIGHT *******************************
* File Name          : UART.C
* Author             : MJX
* Version            : V1.0
* Date               : 2012/11/30
* Description        : CH395芯片 硬件标准异步串口连接的硬件抽象层 V1.0
*                      提供I/O接口子程序
*******************************************************************************/



/*******************************************************************************/
/* 头文件包含 */
#include "stm32f10x_usart.h"

/*******************************************************************************/
/* 硬件相关宏定义 */
/* 本例中的硬件连接方式如下(实际应用电路可以参照修改下述定义及子程序) */
/* 单片机的引脚               CH395芯片的引脚
    UART2_TXD----PA2                RXD
    UART2_RXD----PA3         	    TXD       
    INT#---------PA1                INT#
*/
      

#define	CH395_INT_PIN_WIRE( )	   GPIOA->IDR & GPIO_Pin_1 		

/*******************************************************************************
* Function Name  : Delay_uS
* Description    : 微秒级延时函数(基本准确)
* Input          : delay---延时值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelayuS( UINT8 delay )
{
	UINT8 i, j;

	for( i = delay; i != 0; i -- ) 
	{
		for( j = 5; j != 0; j -- )
		{
		}		
	}
}

/*******************************************************************************
* Function Name  : Delay_mS
* Description    : 毫秒级延时函数(基本准确)
* Input          : delay---延时值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelaymS( UINT8 delay )
{
	UINT8 i;
  UINT16 j;
	for( i = delay; i != 0; i -- ) 
	{
		for( j = 200; j != 0; j -- )
		{
			mDelayuS( 5 );
		}		
	}
}
#define	UART_INIT_BAUDRATE		   9600							 /* 默认通讯波特率9600bps,建议通过硬件引脚设定直接选择更高的CH395的默认通讯波特率 */
//#define	UART_WORK_BAUDRATE		   57600					 /* 正式通讯波特率57600bps */
#define	UART_WORK_BAUDRATE		   115200					 /* 正式通讯波特率115200bps */
//#define	UART_WORK_BAUDRATE		   230400					 /* 正式通讯波特率230400bps */
//#define	UART_WORK_BAUDRATE		   460800					 /* 正式通讯波特率460800bps */
//#define	UART_WORK_BAUDRATE		   921600					 /* 正式通讯波特率921600bps */
         
/*******************************************************************************
* Function Name  : USART2_Configuration
* Description    : 串口2初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_Configuration( UINT32 baudrate )
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* UART2 clock enable */
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE );	 /* 使能UART2 */

	/* USART2 Hard configured: */
	/* Configure USART2 Rx (PA3) as input floating */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

	/* Configure USART2 Tx (PA2) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init( GPIOA, &GPIO_InitStructure );


	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init( USART2, &USART_InitStructure );

	/* Enable USART2 */
	USART_Cmd( USART2, ENABLE ); 
}

/*******************************************************************************
* Function Name  : USART2_Send_Byte
* Description    : 串口2发送一个字节数据
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_Send_Byte( UINT8 dat )
{
	USART2->DR = ( dat & (UINT16)0x01FF );								
	while( !( USART2->SR & USART_FLAG_TXE ) ); 		
}

/*******************************************************************************
* Function Name  : CH395_Port_Init
* Description    : CH395端口初始化
*                  由于使用异步串口读写时序,所以进行初始化  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_PORT_INIT( void ) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	USART2_Configuration( UART_INIT_BAUDRATE );
	
	/* 配置INT#(PA1)方向均为输入 */		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  				 /* 上拉输入 */
    GPIO_Init( GPIOA, &GPIO_InitStructure );		
}

#ifdef UART_WORK_BAUDRATE
/*******************************************************************************
* Function Name  : Set_MCU_BaudRate
* Description    : 设置单片机波特率
*                  将单片机切换到正式通讯波特率 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Set_MCU_BaudRate( void )  								 
{
	USART2_Configuration( UART_WORK_BAUDRATE );
}
#endif

/*******************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : 向CH395写命令
* Input          : mCmd---将要写入CH395的命令码
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd( UINT8 mCmd ) 
{
	USART2_Send_Byte( SER_SYNC_CODE1 );							 /* 启动操作的第1个串口同步码 */
	USART2_Send_Byte( SER_SYNC_CODE2 );							 /* 启动操作的第2个串口同步码 */
	USART2_Send_Byte( mCmd );							 		 /* 输出命令码 */
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
	USART2_Send_Byte( mData );  								 /* 串口输出 */
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

#define	xEndCH395Cmd( )  										 /* 结束CH395命令,仅用于SPI接口方式 */



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

