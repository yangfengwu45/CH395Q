/********************************** (C) COPYRIGHT *******************************
* File Name          : CH395SPI_SW.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片 模拟SPI串行连接的硬件抽象层 V1.0
*                      
*******************************************************************************/

/* 硬件相关宏定义 */
/* 本例中的硬件连接方式如下(实际应用电路可以参照修改下述定义及子程序) */
/* 单片机的引脚               CH395芯片的引脚
        P1.4                       SCS
        P1.5                       SDI
        P1.6                       SDO
        P1.7                       SCK                                */
sbit    P14          =             P1^4;
sbit    P15          =             P1^5;
sbit    P16          =             P1^6;
sbit    P17          =             P1^7;
#define CH395_SPI_SCS              P14                               /* CH395的SCS引脚 */
#define CH395_SPI_SDI              P15                               /* CH395的SDI引脚 */
#define CH395_SPI_SDO              P16                               /* CH395的SDO引脚 */
#define CH395_SPI_SCK              P17                               /* CH395的SCK引脚 */

#define CH395_INT_WIRE             INT1                              /* CH395的INT#引脚 */

#define xCH395CmdStart( )         {CH395_SPI_SCS = 0;}
#define xEndCH395Cmd()            {CH395_SPI_SCS = 1;}


/********************************************************************************
* Function Name  : mDelayuS
* Description    : 延时指定微秒时间,根据单片机主频调整,不精确
* Input          : us---延时时间值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelayuS(UINT8 us)
{
    while(us --);                                                    /* MCS51@24MHz */
}

/*******************************************************************************
* Function Name  : mDelaymS
* Description    : 延时指定毫秒时间,根据单片机主频调整,不精确
* Input          : ms---延时时间值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelaymS(UINT8 ms)
{
    while(ms --) 
    {
        mDelayuS(250);
        mDelayuS(250);
        mDelayuS(250);
        mDelayuS(250);
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
    CH395_SPI_SCS = 1;
    CH395_SPI_SCK = 1;                                               /*  SIP_CLK为高电平，本程序使用SPI模式3，也可以使用模式0*/
}

/*******************************************************************************
* Function Name  : Spi395OutByte
* Description    : 向CH395发送8位数据
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Spi395OutByte(UINT8 mdata)                                      /* SPI输出8位数据 */
{                                                                    /* 如果是硬件SPI，在只需要将数据写入SPI的数据寄存器中 */
    UINT8   i;                                                       /* 然后等待发送完成即可 */

    for ( i = 0; i < 8; i ++ ) 
    {
        CH395_SPI_SCK = 0;                                           /* CLK拉低 */
        if( mdata & 0x80 )CH395_SPI_SDI = 1; 
        else CH395_SPI_SDI = 0;
        mdata <<= 1;                                                 /* 数据位是高位在前 */
        CH395_SPI_SCK = 1;                                           /* CH395在时钟上升沿采样输入 */
    }
}

/*******************************************************************************
* Function Name  : Spi395InByte
* Description    : 从CH395读8位数据
* Input          : None
* Output         : None
* Return         : 8位数据
*******************************************************************************/
UINT8 Spi395InByte(void)                                             /* SPI输入8位数据 */
{                                                                    /* 如果是硬件SPI接口,应该是先查询SPI状态寄存器以等待SPI字节*/
    UINT8   i, d;                                                    /* 传输完成,然后从SPI数据寄存器读出数据 */
    d = 0;

    for ( i = 0; i < 8; i ++ )  
    {
        CH395_SPI_SCK = 0;                                           /* CH395在时钟下降沿输出 */
        d <<= 1;  /* 数据位是高位在前 */
        if ( CH395_SPI_SDO) d ++;
        CH395_SPI_SCK = 1;
    }
    return( d );
}

/*******************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : 向CH395发送8位命令码
* Input          : 8位命令码
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd(UINT8 cmd)                                       /* 向CH395写命令 */
{
    xEndCH395Cmd();                                                  /* 防止CS原来为低，先将CD置高 */
    xCH395CmdStart( );                                               /* 命令开始，必须CS拉低 */
    Spi395OutByte(cmd);                                              /* 硬件SPI发送8位命令码 */
    mDelayuS(2);                                                     /* 必要延时,延时1.5uS确保读写周期不小于1.5uS */
}

/********************************************************************************
* Function Name  : xWriteCH395Data
* Description    : 向CH395发送8位数据
* Input          : 8位数据
* Output         : None
* Return         : None
*******************************************************************************/
void  xWriteCH395Data(UINT8 mdata)                                  /* 向CH395写数据 */
{   
    Spi395OutByte(mdata);                                                      
}

/********************************************************************************
* Function Name  : xReadCH395Data
* Description    : 从CH395读读数据
* Input          : None 
* Output         : None
* Return         : 8位数据
*******************************************************************************/
UINT8   xReadCH395Data( void )                                       /* 从CH395读数据 */
{
    UINT8 i;
    i = Spi395InByte( );
    return i;
}

/**************************** endfile *************************************/
