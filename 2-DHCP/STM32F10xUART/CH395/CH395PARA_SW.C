/********************************** (C) COPYRIGHT *******************************
* File Name          : PARA_SW.C
* Author             : MJX
* Version            : V1.0
* Date               : 2012/11/30
* Description        : CH395芯片 软件模拟8位并口连接的硬件抽象层 V1.0
*                      提供I/O接口子程序
*******************************************************************************/



/*******************************************************************************/
/*******************************************************************************/
/* 硬件相关宏定义 */
/* 本例中的硬件连接方式如下(实际应用电路可以参照修改下述定义及子程序) */
/*   单片机的引脚                  CH395芯片的引脚
	 D0---D7(PB8---PB15) 	          D0---D7
		PB7								PCS#
		PB6								A0				 	
		PB5								WR#
		PB4								RD#
		PA1							  INT#	
*/

#define PIN_CH395_PCS_LOW( )       ( GPIOB->BRR  = GPIO_Pin_7 )  /* 模拟并口片选引脚输出低电平 */
#define PIN_CH395_PCS_HIGH( )      ( GPIOB->BSRR = GPIO_Pin_7 )  /* 模拟并口片选引脚输出高电平 */
#define PIN_CH395_A0_LOW( )        ( GPIOB->BRR  = GPIO_Pin_6 )  /* 模拟并口A0引脚输出低电平 */
#define PIN_CH395_A0_HIGH( )       ( GPIOB->BSRR = GPIO_Pin_6 )  /* 模拟并口A0引脚输出高电平 */
#define PIN_CH395_WR_LOW( )        ( GPIOB->BRR  = GPIO_Pin_5 )  /* 模拟并口WR引脚输出低电平 */
#define PIN_CH395_WR_HIGH( )       ( GPIOB->BSRR = GPIO_Pin_5 )  /* 模拟并口WR引脚输出高电平 */
#define PIN_CH395_RD_LOW( )        ( GPIOB->BRR  = GPIO_Pin_4 )  /* 模拟并口RD引脚输出低电平 */
#define PIN_CH395_RD_HIGH( )       ( GPIOB->BSRR = GPIO_Pin_4 )  /* 模拟并口RD引脚输出高电平 */

#define CH395_DATA_SET_IN( )	   { GPIOB->CRH = 0x44444444; }  /* 设置CH395数据引脚为输入模式 */    
#define CH395_DATA_SET_OUT( )	   { GPIOB->CRH = 0x33333333; }  /* 设置CH395数据引脚为输出模式 */

#define	CH395_INT_PIN_WIRE( )	   GPIOA->IDR & GPIO_Pin_1 		  /* 假定CH395的INT#引脚,如果未连接那么也可以通过查询兼做中断输出的SDO引脚状态实现                                                                                                                                                                                                                                */


#define  CH395_WR_DATA(d)		  GPIOA->ODR = d
#define  CH395_RD_DATA()		  GPIOA->IDR

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
		    __nop();   __nop();
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
			
/*******************************************************************************
* Function Name  : CH395_Port_Init
* Description    : CH395端口初开始化
*                  由于使用通用I/O模拟并口读写时序,所以进行初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_PORT_INIT( void ) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 由于其中的PB3、PB4对应与单片机的JTAG功能,所以必须先禁用JTAG功能 */
	GPIO_PinRemapConfig( GPIO_Remap_SWJ_Disable, ENABLE ); 
	
	/* 配置CH395对应的引脚PCS#(PB7)、A0(PB6)、WD#(PB5)、RD#(PB4)方向均为输出 */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4;			
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 /* 推挽式输出 */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;            /* 速度50MHZ */
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	/* CH395对应的引脚PCS#(PB7)、A0(PB6)、WD#(PB5)、RD#(PB4)默认输出高电平 */
    PIN_CH395_WR_HIGH();		     										 /* WR默认为高 */
    PIN_CH395_RD_HIGH();		    										 /* RD默认为高 */
    PIN_CH395_A0_LOW();		 										 /* A0默认为低 */
    PIN_CH395_PCS_HIGH();		     										 /* CS默认为高 */
    CH395_DATA_SET_IN();      										 /* 端口设置为输入 */
	
	/* 配置CH395对应的数据引脚PB8---PB15方向均为输出 */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11
  	                            | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;			
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 /* 推挽式输出 */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;            /* 速度50MHZ */
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	/* 配置CH395对应的INT#(PA1)方向均为输入 */		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  				 /* 上拉输入 */
    GPIO_Init( GPIOA, &GPIO_InitStructure );					   
}

/*******************************************************************************
* Function Name  : xReadCH395Status
* Description    : 从CH395读状态,仅用于并口方式
* Input          : None
* Output         : None
* Return         : 返回读取的状态数据
*******************************************************************************/

/*==============================================================================
* Function Name  : xWriteCH395Cmd
* Description    : 向CH395写命令
* Input          : cmd 8位命令码
* Output         : None
* Return         : None
==============================================================================*/
void xWriteCH395Cmd(UINT8 cmd)									     /* 向CH395写命令 */
{
	GPIOB->ODR = ( GPIOB->ODR & 0x00FF ) | ( cmd << 8 );		 /* 向CH395的并口输出数据 */												 /* 设置输出 */
 	CH395_DATA_SET_OUT();											 /* 设置输出 */
    PIN_CH395_A0_HIGH();		 											 /* 将A0置为高 */
    PIN_CH395_WR_LOW();		     									 /* 将WR拉低 */
    PIN_CH395_PCS_LOW();		     									 /* 将CS拉低 */
    PIN_CH395_PCS_LOW();		     									 /* 无效操作仅作延时使用 */
    PIN_CH395_PCS_LOW();		     									 /* 无效操作仅作延时使用 */
    PIN_CH395_WR_HIGH();		     										 /* 将WR置为高 */
    PIN_CH395_PCS_HIGH();		     										 /* 将CS置为高 */
    PIN_CH395_PCS_HIGH();		     										 /* 将CS置为高 */
    PIN_CH395_A0_LOW();		 										 /* 将A0拉低 */
    PIN_CH395_A0_LOW();		 										 /* 将A0拉低 */
    CH395_DATA_SET_IN(); 											 /* 数据端口设置为输入 */
    mDelayuS(5);      												 /* 必要延时 */
}

/*==============================================================================
* Function Name  : xWriteCH395Data
* Description    : 向CH395写8位数据
* Input          : mdata 8位数据
* Output         : None
* Return         : None
==============================================================================*/
void  xWriteCH395Data(UINT8 mdata)
{																	 /* 向CH395写数据 */
	GPIOB->ODR = ( GPIOB->ODR & 0x00FF ) | ( mdata << 8 );		 /* 向CH395的并口输出数据 */	
	CH395_DATA_SET_OUT();											 /* 设置输出 */
    PIN_CH395_WR_LOW();		     									 /* 将WR拉低 */
    PIN_CH395_PCS_LOW();		     									 /* 将CS拉低 */
    PIN_CH395_PCS_LOW();		     									 /* 无效操作仅作延时使用 */
    PIN_CH395_PCS_LOW();		     									 /* 无效操作仅作延时使用 */
    PIN_CH395_PCS_LOW();		     									 /* 将CS拉低 */
    PIN_CH395_WR_HIGH();		     										 /* 将WR置为高 */
    PIN_CH395_PCS_HIGH();		     										 /* 将CS置为高 */
    PIN_CH395_PCS_HIGH();		     										 /* 将CS置为高 */
    CH395_DATA_SET_IN();											 /* 数据端口设置为输入 */
}

/*==============================================================================
* Function Name  : CH395_PORT_INIT
* Description    : 硬件初始化部分
* Input          : None
* Output         : None
* Return         : None
==============================================================================*/
UINT8	xReadCH395Data( void )                                       /* 从CH395读数据 */
{
    UINT8 i;
    CH395_DATA_SET_IN();											 /* 数据端口设置为输入 */
    PIN_CH395_PCS_LOW();		     									 /* 将CS拉低 */
	PIN_CH395_RD_LOW();		     								     /* 将RD拉低 */
    PIN_CH395_PCS_LOW();		     									 /* 无效操作仅作延时使用 */
    PIN_CH395_PCS_LOW();		     									 /* 无效操作仅作延时使用 */
	i = (UINT8)( ( GPIOB->IDR ) >> 8 );											 /* 从端口读数据 */
    PIN_CH395_RD_HIGH();		     										 /* 将RD置为高 */
    PIN_CH395_PCS_HIGH();		     										 /* 将CS置为高 */
    PIN_CH395_PCS_HIGH();		     										 /* 将CS置为高 */
    CH395_DATA_SET_IN();											 /* 数据端口设置为输入 */
	return i;
}
#define xEndCH395Cmd() 	   {  PIN_CH395_PCS_HIGH();}  									     /* 命令结束，仅在SPI模式下有效 */



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

