/********************************** (C) COPYRIGHT *******************************
* File Name          : CH395SPI_HW.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片 硬件并口连接的硬件抽象层 V1.0
*                   
*******************************************************************************/

/* 硬件相关宏定义 */
/* 本例中的硬件连接方式如下(实际应用电路可以参照修改下述定义及子程序) */
/*  单片机的引脚       CH395芯片的引脚
        P2.0                 A0
        P2.6                 CS#      
   如果并口上只有CH395,那么CS#可以直接接低电平,强制片选 */
        
UINT8V  xdata     CH395_CMD_PORT   _at_ 0xBDF1;                  /* 假定CH395命令端口的I/O地址 */
UINT8V  xdata     CH395_DAT_PORT   _at_ 0xBCF0;                  /* 假定CH395数据端口的I/O地址 */

#define CH395_INT_WIRE             INT1                          /* 定CH395的INT#引脚 */

/********************************************************************************
* Function Name  : mDelayuS
* Description    : 延时指定微秒时间,根据单片机主频调整,不精确
* Input          : us---延时时间值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelayuS( UINT8 us )
{
    while( us -- );                                              /* MCS51@24MHz */
}

/********************************************************************************
* Function Name  : mDelaymS
* Description    : 延时指定毫秒时间,根据单片机主频调整,不精确
* Input          : ms---延时时间值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelaymS( UINT8 ms )
{
    while( ms -- ) 
    {
        mDelayuS( 250 );
        mDelayuS( 250 );
        mDelayuS( 250 );
        mDelayuS( 250 );
    }
}

/*******************************************************************************
* Function Name  : CH395_PORT_INIT
* Description    : 硬件初始化部分
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_PORT_INIT(void)
{
}

/********************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : 向CH395写命令
* Input          : cmd 8位命令码
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd(UINT8 cmd)                                       /* 向CH395写命令 */
{
    CH395_CMD_PORT = cmd;
    mDelayuS(2);                                                     /* 必要延时,延时1.5uS确保读写周期不小于1.5uS */
}

/********************************************************************************
* Function Name  : xWriteCH395Data
* Description    : 向CH395写8位数据
* Input          : mdata 8位数据
* Output         : None
* Return         : None
*******************************************************************************/
void  xWriteCH395Data(UINT8 mdata)
{
    CH395_DAT_PORT = mdata;                                          /* 向CH395写数据 */
    //mDelayuS(1);                                                   /* 确保读写周期大于0.6uS */
}

/*******************************************************************************
* Function Name  : CH395_PORT_INIT
* Description    : 硬件初始化部分
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
UINT8   xReadCH395Data( void )                                       /* 从CH395读数据 */
{
    UINT8 i;
    i = CH395_DAT_PORT;
    return i;
}
#define xEndCH395Cmd()     {}                                        /* 命令结束，仅在SPI模式下有效 */

/**************************** endfile *************************************/