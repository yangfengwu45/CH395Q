/********************************** (C) COPYRIGHT *******************************
* File Name          : CH395SPI_HW.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片 硬件SPI串行连接的硬件抽象层 V1.0
*                     
*******************************************************************************/

/* 硬件相关宏定义 */
/* 本例中的硬件连接方式如下(实际应用电路可以参照修改下述定义及子程序) */
/* 单片机的引脚    CH395芯片的引脚
      P1.4                 SCS
      P1.5                 SDI
      P1.6                 SDO
      P1.7                 SCK      */
      
sbit        P14         =          P1^4;
#define CH395_SPI_SCS              P14                               /* CH395的SCS引脚 */

sfr SPDR = 0x86;                                                     /* SPI数据寄存器0x86 */
sfr SPSR = 0xaa;                                                     /* SPI状态寄存器0xaa */
sfr SPCR = 0xd5;                                                     /* SPI控制寄存器0xd5 */

#define SPI_IF_TRANS    0x80                                         /* SPI字节传输完成标志,在SPSR的位7 */

#define CH395_INT_WIRE              INT1                            /* CH395的INT#引脚 */

#define xCH395CmdStart( )         {CH395_SPI_SCS = 0;}               /* 命令开始 */
#define xEndCH395Cmd()            {CH395_SPI_SCS = 1;}               /* 命令结束*/

/*******************************************************************************
* Function Name  : mDelayuS
* Description    : 延时指定微秒时间,根据单片机主频调整,不精确
* Input          : us---延时时间值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelayuS( UINT8 us )
{
    while( us -- );                                                  /* MCS51@24MHz */
}

/*******************************************************************************
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

/******************************************************************************
* Function Name  : CH395_PORT_INIT
* Description    : 硬件初始化部分
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_PORT_INIT(void)
{
    xEndCH395Cmd();
   /* 如果是硬件SPI接口,那么可使用mode3(CPOL=1&CPHA=1)或mode0(CPOL=0&CPHA=0),
    CH395在时钟上升沿采样输入,下降沿输出,数据位是高位在前 */
    SPCR = 0x5C;  
    /* 对于双向I/O引脚模拟SPI接口,那么必须在此设置SPI_SCS,SPI_SCK,SPI_SDI为输出方向,
       SPI_SDO为输入方向 */
    /* 设置SPI模式3, DORD=0(MSB first), CPOL=1, CPHA=1, CH395也支持SPI模式0 */
    SPSR |= 0x08;
        
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
    /* 为了提高速度,可以将该子程序做成宏以减少子程序调用层次 */
    SPDR = d;                                                    /* 先将数据写入SPI数据寄存器,然后查询SPI状态寄存器以等待SPI字节传输完成 */
    while( ( SPSR & SPI_IF_TRANS ) == 0 );                       /* 查询SPI状态寄存器以等待SPI字节传输完成 */
    SPSR &= ~ SPI_IF_TRANS;                                      /* 清除SPI字节传输完成标志,有的单片机会自动清除 */
    return( SPDR );                                              /* 先查询SPI状态寄存器以等待SPI字节传输完成,然后从SPI数据寄存器读出数据 */
}

/******************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : 向CH395写命令
* Input          : cmd 8位的命令码
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd(UINT8 cmd)                                          
{                                                                    
    xEndCH395Cmd();                                                  /* 防止CS原来为低，先将CD置高 */
    xCH395CmdStart( );                                               /* 命令开始，CS拉低 */
    Spi395Exchange(cmd);                                             /* SPI发送命令码 */
    mDelayuS(2);                                                     /* 必要延时,延时1.5uS确保读写周期不小于1.5uS */
}

/******************************************************************************
* Function Name  : xWriteCH395Data
* Description    : 向CH395写数据
* Input          : mdata 8位数据
* Output         : None
* Return         : None
*******************************************************************************/
void  xWriteCH395Data(UINT8 mdata)
{   
    Spi395Exchange(mdata);                                           /* SPI发送数据 */
}

/*******************************************************************************
* Function Name  : xReadCH395Data
* Description    : 从CH395读数据
* Input          : None
* Output         : None
* Return         : 8位数据
*******************************************************************************/
UINT8   xReadCH395Data( void )                                                  
{
    UINT8 i;
    i = Spi395Exchange(0xff);                                        /* SPI读数据 */
    return i;
}

/**************************** endfile *************************************/
 