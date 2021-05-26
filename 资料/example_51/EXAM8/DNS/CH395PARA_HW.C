
/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395PARA_HW.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395 硬件PARA接口函数
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
* Function Name  : xEndCH395Cmd
* Description    : 结束命令
* Input          : None
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
 	R8_SAFE_ACCESS_SIG = 0x57;		/* unlock step 1 */
	R8_SAFE_ACCESS_SIG = 0xA8;		/* unlock step 2 */
	R8_XBUS_CONFIG = RB_XBUS_ENABLE | RB_XBUS_ADDR_OE;		/* 外部总线使能 */
	R8_XBUS_SETUP_HOLD = 0x04;		/* 1 setup clocks */
  R8_SAFE_ACCESS_SIG = 0x00;		/* lock, to prevent unexpected writing */
}

 /**********************************************************************************
* Function Name  : xWriteCH395Data
* Description    : 写命令
* Input          : 待写的命令
* Output         : None
* Return         : None
*********************************************************************************/
void xWriteCH395Cmd( UINT8 mCmd )  
{
	*( PUINT8V )0x00C00004 = mCmd;									
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
   
	*( PUINT8V )0x00C00000 = mData;
   	Delay_us(1 );  		
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
   UINT8 mData;
   Delay_us(1 );  	
   mData = *( PUINT8V )0x00C00000 ;
	 return (mData);
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
