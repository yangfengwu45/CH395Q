/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395UART.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395 uart接口函数
*             
**********************************************************************************/

/*串口波特率默认为9600*/
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
		for( i = 0; i != 20; i++ );
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
		for( i = FREQ_SYS / 5000; i != 0; -- i );

	}
}

/**********************************************************************************
* Function Name  : UART1_SendByte
* Description    : 串口1按字节发送数据
* Input          : dat
* Output         : None
* Return         : None
*********************************************************************************/
void UART1_SendByte( UINT8 dat )   
{		
		R8_UART1_THR  = dat;
    while( ( R8_UART1_LSR & RB_LSR_TX_ALL_EMP ) == 0 );                                 /* 等待数据发送*/	   
}

/**********************************************************************************
* Function Name  : UART1_RcvByte
* Description    : 串口1按字节接收数据
* Input          : None
* Output         : None
* Return         : 接收到的数据
*********************************************************************************/
UINT8 UART1_RcvByte(void)    
{
     UINT8 Rcvdat; 
     while( ( R8_UART1_LSR & RB_LSR_DATA_RDY  ) == 0 );                                /* 等待数据准备好 */
     Rcvdat = R8_UART1_RBR;                                                            /* 从接收缓冲寄存器读出数据 */
	   return( Rcvdat );
}
 /**********************************************************************************
* Function Name  : xEndCH395Cmd
* Description    : 结束片选，为空兼容程序
* Input          : none
* Output         : None
* Return         : None
*********************************************************************************/
void xEndCH395Cmd( void )
{ 

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
    UART1_SendByte(0x57);
	  UART1_SendByte(0xAB);
    UART1_SendByte(mCmd);
	  Delay_us(2);											
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
 	UART1_SendByte(mData); 			
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
  UINT8 Rcv;
  Rcv = UART1_RcvByte(); 
  return (Rcv);
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
