/********************************** (C) COPYRIGHT *******************************
* File Name          : SPI_HW.C
* Author             : WXF
* Version            : V1.0
* Date               : 2013/12/19
* Description        : CH395芯片 CH395芯片 硬件标准SPI串行连接的硬件抽象层 V1.0
*                      提供I/O接口子程序
*******************************************************************************/
/*
1.?mDelayuS ,mDelaymS????????????
2.CH395_Send_Byte ??????????????

*******************************************************************************/

/*******************************************************************************/
/* 硬件相关宏定义 */
/* 本例中的硬件连接方式如下(实际应用电路可以参照修改下述定义及子程序) */
/* 单片机的引脚               CH395芯片的引脚
    SPI1_NSS-----PB0            	SCS
    SPI1_SCK-----PA5            	SCK      
    SPI1_MISO----PA6            	SDO
    SPI1_MOSI----PA7            	SDI
    INT#---------PA1              INT#
*/
#define CH395SPI_C_
#include "CH395SPI.H"
#include <stm32f10x.h>
#include "CH395INC.H"
#include "delay.h"

/*******************************************************************************
* Function Name  : Delay_uS
* Description    : 微秒级延时函数(基本准确)
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
* Description    : 毫秒级延时函数(基本准确)
* Input          : delay---延时值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelaymS( UINT8 delay )
{
	delay_ms(delay);
}				
				   
/*******************************************************************************
* Function Name  : CH395_Port_Init
* Description    : CH395端口初始化
*                  由于使用SPI读写时序,所以进行初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_PORT_INIT( void )  
{
	SPI_InitTypeDef  SPI_InitStructure;
 	GPIO_InitTypeDef GPIO_InitStructure;

	/* 初始化SPI接口 */   
	/* Enable SPI1 and GPIOA clocks */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE );/* 实际在这之前已经使能过 */
  
	/* Configure SPI1 pins: NSS, SCK, MISO and MOSI */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;	  		 /* 推拉输出备用功能 */
	GPIO_Init( GPIOA, &GPIO_InitStructure );

  	/* Configure PA.4 as Output push-pull, used as Flash Chip select */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  			 /* 推拉输出 */
  	GPIO_Init( GPIOB, &GPIO_InitStructure );

  	/* Deselect the SD: Chip Select high */
  	CH395_SPI_SCS_HIGH( );
 
  	/* SPI1 configuration */ 
  	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; /* SPI配置成两线的单向全双工通信 */
  	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 				   /* SPI主机 */
  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;				   /* SPI8位数据格式传输 */
  	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	  					   /* 时钟低时活动 */  				//	改成高则不行?????????????????
  	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;					   /* 数据在时钟第二个边沿时捕获 */
  	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		 				   /* 内部NSS信号由SSI控制 */
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; /* 波特率预分频数为4 */
  	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;		   		   /* 传输时高位在前 */
  	SPI_InitStructure.SPI_CRCPolynomial = 7;			  			  	    
  	SPI_Init( SPI1, &SPI_InitStructure );
  
  	/* Enable SPI1  */
  	SPI_Cmd( SPI1, ENABLE );   							
	
	/* 初始化中断引脚 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  				 /* 上拉输入 */
    GPIO_Init( GPIOA, &GPIO_InitStructure );				
}

/*******************************************************************************
* Function Name  : Spi395Exchange
* Description    : 硬件SPI输出且输入8个位数据
* Input          : d---将要送入到CH395的数据
* Output         : None
* Return         : None
*******************************************************************************/
UINT8 Spi395Exchange( UINT8 d )  
{  
	/* Loop while DR register in not emplty */
//	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);	
	while( ( SPI1->SR & SPI_I2S_FLAG_TXE ) == RESET );

	/* Send byte through the SPI1 peripheral */
//	SPI_I2S_SendData(SPI1, byte);
	SPI1->DR = d;

	/* Wait to receive a byte */
//	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	while( ( SPI1->SR & SPI_I2S_FLAG_RXNE ) == RESET );

	/* Return the byte read from the SPI bus */
//	return  SPI_I2S_ReceiveData(SPI1);
	return( SPI1->DR );	
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
	CH395_SPI_SCS_HIGH( );  									 /* 防止之前未通过xEndCH395Cmd禁止SPI片选 */
	CH395_SPI_SCS_HIGH( ); 
			
	/* 对于双向I/O引脚模拟SPI接口,那么必须确保已经设置SPI_SCS,SPI_SCK,SPI_SDI为输出方向,SPI_SDO为输入方向 */
	CH395_SPI_SCS_LOW( );  										 /* SPI片选有效 */

	/* 发送命令码 */
	Spi395Exchange( mCmd );  									 /* 发出命令码 */
	mDelayuS( 2 );  											 /* 延时1.5uS确保读写周期大于1.5uS */
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
	Spi395Exchange( mData );  									 /* 发送数据 */
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
	return( Spi395Exchange( 0xFF ) );  	
}

#define	xEndCH395Cmd( )	{ CH395_SPI_SCS_HIGH( ); }  			 /* SPI片选无效,结束CH395命令,仅用于SPI接口方式 */

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


