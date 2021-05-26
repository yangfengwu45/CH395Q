
/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395SPI_HW
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395 硬件spi接口函数
*             
**********************************************************************************/

/*********************************************************************************
* Function Name  : mDelayuS
* Description    : 延时指定微秒时间,根据单片机主频调整,不精确
* Input          : us---延时时间值
* Output         : None
* Return         : None
*********************************************************************************/
void mDelayuS( UINT8 us )
{
	int i;	
	while( us -- ) 
	{
		for( i =20; i != 0; -- i );
	}
}

/**********************************************************************************
* Function Name  : mDelaymS
* Description    : 延时指定毫秒时间,根据单片机主频调整,不精确
* Input          : ms---延时时间值
* Output         : None
* Return         : None
*********************************************************************************/
void mDelaymS( UINT8 ms )
{
	int i;
	
	while( ms -- ) 
	{
		for( i = 0; i != 20000; i++ );
	}
}

 /**********************************************************************************
* Function Name  : xEndCH395Cmd
* Description    : 取消片选
* Input          : none
* Output         : None
* Return         : None
*********************************************************************************/
void xEndCH395Cmd( void )
{ 
 R32_PB_OUT |= CAT0 ;
}

 /**********************************************************************************
* Function Name  : xCH395CmdStart
* Description    : 片选
* Input          : none
* Output         : None
* Return         : None
*********************************************************************************/
void xCH395CmdStart(void )
{
	R32_PB_CLR |= CAT0 ;
}

 /**********************************************************************************
* Function Name  : CH395_PROT_INIT
* Description    : 接口初始化
* Input          : none
* Output         : None
* Return         : None
*********************************************************************************/
void CH395_PROT_INIT ( )
{
  R8_SPI0_CTRL_MOD = RB_SPI_MOSI_OE|RB_SPI_SCK_OE;
  R8_SPI0_CLOCK_DIV = 0x0a;         	                                  /* 10分频。100/10=10M */
  R32_PB_DIR |= (MOSI | SCK0 | SCS |CAT0  );                            /* MISO(PB15)为输入，MOSI(PB14)，SCS(PB13)为输出： */
  R32_PB_PU  |=  CAT0  ; 
  R8_SPI0_CTRL_DMA = 0;				  	                                      /* 不启动DMA方式 */
}

 /**********************************************************************************
* Function Name  : SPI0_MASTER_Trans
* Description    : spi发送数据
* Input          : data：待发送数据
* Output         : None
* Return         : None
*********************************************************************************/
void SPI0_MASTER_Trans( UINT8 data )
{
	R32_SPI0_FIFO = data;
	R16_SPI0_TOTAL_CNT = 0x01;
	while( R8_SPI0_FIFO_COUNT != 0 );	                             	/*等待数据发送完成*/
}

 /**********************************************************************************
* Function Name  : SPI0_MASTER_Recv
* Description    : spi接收数据
* Input          : NOne
* Output         : 接收到的数据
* Return         : None
*********************************************************************************/
UINT8 SPI0_MASTER_Recv( void )
{

	R32_SPI0_FIFO = 0xff;
	R16_SPI0_TOTAL_CNT = 0x01;
	while( R8_SPI0_FIFO_COUNT != 0 );		                              /*等待数据回来*/
  return 	R8_SPI0_BUFFER;
}
 /**********************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : 写命令
* Input          : 待写的命令
* Output         : None
* Return         : None
*********************************************************************************/
void xWriteCH395Cmd( UINT8 mCmd )  
{
  R32_PB_OUT |= CAT0 ;				 
  R32_PB_CLR |= CAT0 ;								
	SPI0_MASTER_Trans( mCmd );  									
	mDelayuS(1 );  										
}

 /**********************************************************************************
* Function Name  : xWriteCH395Data
* Description    : 写数据
* Input          : 待写的数据
* Output         : None
* Return         : None
*********************************************************************************/
void xWriteCH395Data( UINT8 mData ) 
{
	SPI0_MASTER_Trans( mData );
}

/**********************************************************************************
* Function Name  : xReadCH395Data
* Description    : 读数据
* Input          : None
* Output         : 读到的数据
* Return         : None
*********************************************************************************/
UINT8 xReadCH395Data( void ) 
{
	return( SPI0_MASTER_Recv( ) );

}

 /**********************************************************************************
* Function Name  : Query395Interrupt
* Description    : 查询中断
* Input          : None
* Output         : None
* Return         : 中断状态
*********************************************************************************/
UINT8 Query395Interrupt( void )
{
	return( (R32_PB_PIN & PWM0) ? FALSE : TRUE );  
}
