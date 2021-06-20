/********************************** (C) COPYRIGHT *******************************
* File Name          : SPI_HW.C
* Author             : WXF
* Version            : V1.0
* Date               : 2013/12/19
* Description        : CH395芯片 CH395芯片 软件模拟SPI串行连接的硬件抽象层 V1.0
*                      提供I/O接口子程序
*******************************************************************************/

#include "CH395INC.H"

/*******************************************************************************/
/* 硬件相关宏定义 */
/* 本例中的硬件连接方式如下(实际应用电路可以参照修改下述定义及子程序) */
/* 单片机的引脚               CH395芯片的引脚
    SPI1_NSS-----PB0            	SCS
    SPI1_SCK-----PA5            	SCK      
    SPI1_MISO----PA6            	SDO
    SPI1_MOSI----PA7            	SDI
    INT#---------PA1                INT#
*/
#define CH395_SPI_SCS_LOW( )       ( GPIOB->BRR  = GPIO_Pin_0 )  /* SPI片选引脚输出低电平 */
#define CH395_SPI_SCS_HIGH( )      ( GPIOB->BSRR = GPIO_Pin_0 )  /* SPI片选引脚输出高电平 */
#define CH395_SPI_SCK_LOW( )       ( GPIOA->BRR  = GPIO_Pin_5 )  /* SPI时钟引脚输出低电平 */
#define CH395_SPI_SCK_HIGH( )      ( GPIOA->BSRR = GPIO_Pin_5 )  /* SPI时钟引脚输出高电平 */
#define CH395_SPI_SDI_LOW( )       ( GPIOA->BRR  = GPIO_Pin_7 )  /* SPI数据引脚输出低电平 */
#define CH395_SPI_SDI_HIGH( )      ( GPIOA->BSRR = GPIO_Pin_7 )  /* SPI数据引脚输出高电平 */
#define	CH395_SPI_SDO_PIN( )	   GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_6 ) /* 获取CH395的SPI数据输出引脚电平 */											 											   

#define	CH395_INT_PIN_WIRE( )	   GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_1 ) /* 假定CH395的INT#引脚,如果未连接那么也可以通过查询兼做中断输出的SDO引脚状态实现 */

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
	UINT8  i;
	UINT16 j;

	for( i = delay; i != 0; i -- ) 
	{
		for( j = 200; j != 0; j -- )
		{
			mDelayuS( 5 );
		}		
	}
}			
/*******************************************************************************
* Function Name  : CH395_PORT_INIT
* Description    : CH395端口初始化
*                  由于使用软件模拟SPI读写时序,所以进行初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_PORT_INIT( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 配置SPI接口对应的引脚SCS(PB0)、SCK(PA5)、MOSI(PA7)方向均为输出 */		
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;			                	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 /* 推挽式输出 */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                               	
	GPIO_Init( GPIOA, &GPIO_InitStructure );

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			                	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 /* 推挽式输出 */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                               	
	GPIO_Init( GPIOB, &GPIO_InitStructure );
	
	/* 配置MISO(PA6)、INT#(PA1)方向均为输入 */		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  				 /* 上拉输入 */
    GPIO_Init( GPIOA, &GPIO_InitStructure );	
        
	/* 设置引脚SCS(PB0)、SCK(PA5)、MOSI(PA7)默认输出电平 */
	CH395_SPI_SCS_HIGH( );
	CH395_SPI_SCK_HIGH( );
	CH395_SPI_SDI_HIGH( );
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
	UINT8  i;

	CH395_SPI_SCS_HIGH( );  									 /* 防止之前未通过xEndCH395Cmd禁止SPI片选 */

	/* 对于双向I/O引脚模拟SPI接口,那么必须确保已经设置SPI_SCS,SPI_SCK,SPI_SDI为输出方向,SPI_SDO为输入方向 */
	i = 8;
	CH395_SPI_SCS_LOW( ); 										 /* SPI片选有效 */
	while( i-- )
   	{
		CH395_SPI_SCK_LOW( );
		if( mCmd & 0x80 ) 
		{
			CH395_SPI_SDI_HIGH( );
		}
		else 
		{
			CH395_SPI_SDI_LOW( );
		}
		mCmd <<= 1;  											 /* 数据位是高位在前 */
		CH395_SPI_SCK_HIGH( );  								 /* CH395在时钟上升沿采样输入 */
	}
	mDelayuS( 1 );  											 /* 延时2uS确保读写周期大于2uS,或者用上面一行的状态查询代替 */
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
	UINT8  i;

	i = 8;
	while( i-- )
   	{
		CH395_SPI_SCK_LOW( );
		if( mData & 0x80 ) 
		{
			CH395_SPI_SDI_HIGH( );
		}
		else 
		{
			CH395_SPI_SDI_LOW( );
		}
		mData <<= 1;  											 /* 数据位是高位在前 */
		CH395_SPI_SCK_HIGH( );  								 /* CH395在时钟上升沿采样输入 */
	}
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
	/* 如果是硬件SPI接口,应该是先查询SPI状态寄存器以等待SPI字节传输完成,然后从SPI数据寄存器读出数据 */
	UINT8  i, d;
	
	d = 0;
	i = 8;
	while( i-- )
   	{
		CH395_SPI_SCK_LOW( );							 		 /* CH395在时钟下降沿输出 */
		CH395_SPI_SCK_LOW( );
		d <<= 1;  												 /* 数据位是高位在前 */
		if( ( GPIOA->IDR & GPIO_Pin_6 ) != 0x00 ) 
		{
			d++;
		}
		CH395_SPI_SCK_HIGH( );
	}
	return( d );
}

#define	xEndCH395Cmd( )			   { CH395_SPI_SCS_HIGH( ); }  	 /* SPI片选无效,结束CH395命令,仅用于SPI接口方式 */

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


