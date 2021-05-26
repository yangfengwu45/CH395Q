/********************************** (C) COPYRIGHT *******************************
* File Name          : CH395UART.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片 UART串行连接的硬件抽象层 V1.0
*                      
*******************************************************************************/

/* 硬件相关宏定义 */
/* 本例中的硬件连接方式如下(实际应用电路可以参照修改下述定义及子程序) */
/* 单片机的引脚    CH395芯片的引脚
      TXD                  RXD
      RXD                  TXD       */
#define CH395_INT_WIRE             INT1                          /* 假定CH395的INT#引脚,如果未连接那么也可以通过查询串口中断状态码实现 */

#define UART_INIT_BAUDRATE         9600                          /* 默认通讯波特率9600bps,建议通过硬件引脚设定直接选择更高的CH395的默认通讯波特率 */
#define UART_WORK_BAUDRATE         57600                         /* 正式通讯波特率57600bps */


/*******************************************************************************
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
    /* 如果单片机只有一个串口,那么必须禁止通过串口输出监控信息 */
    SCON = 0x50;
    PCON = 0x80;
//  TL2 = RCAP2L = 0 - 18432000/32/UART_INIT_BAUDRATE;               /* 18.432MHz晶振 */
    TL2 = RCAP2L = 0 - 24000000/32/UART_INIT_BAUDRATE;               /* 24MHz晶振 */

    /* 建议通过硬件引脚设定直接选择更高的CH395的默认通讯波特率 */
    TH2 = RCAP2H = 0xFF;
    T2CON = 0x34;                                                    /* 定时器2用于串口的波特率发生器 */
    RI = 0;
    
}

/*******************************************************************************
* Function Name  : Set_MCU_BaudRate
* Description    : 设置单片机波特率
*                  将单片机切换到正式通讯波特率 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SetMCUBaudRate(void)                                
{
//  TL2 = RCAP2L = 0 - 18432000/32/UART_WORK_BAUDRATE;               /* 18.432MHz晶振 */
    TL2 = RCAP2L = 0 - 24000000/32/UART_WORK_BAUDRATE;               /* 24MHz晶振 */
    RI = 0;
}


/********************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : 向CH395写命令
* Input          : cmd 8位的命令码
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd(UINT8 cmd)                                      
{
    TI = 0;
    SBUF = SER_SYNC_CODE1;                                           /* 启动操作的第1个串口同步码 */
    while(TI == 0);
    TI = 0;
    SBUF = SER_SYNC_CODE2;                                           /* 启动操作的第2个串口同步码 */
    while(TI == 0);
    TI = 0;
    SBUF = cmd;                                                      /* 串口输出 */
    while(TI == 0);
    RI = 0;                                                                 
}

/********************************************************************************
* Function Name  : xWriteCH395Data
* Description    : 向CH395写数据
* Input          : mdata 8位数据
* Output         : None
* Return         : None
*******************************************************************************/
void  xWriteCH395Data(UINT8 mdata)
{                                                                    /* 向CH395写数据 */
    TI = 0;
    SBUF = mdata;                                                    /* 串口输出 */
    while(TI == 0);
}

/********************************************************************************
* Function Name  : xReadCH395Data
* Description    : 从CH395读数据
* Input          : None
* Output         : None
* Return         : 8位数据
*******************************************************************************/
UINT8  xReadCH395Data(void)                                          /* 从CH395读数据 */
{
    UINT32 i;
    
    for(i = 0; i < 500000; i ++) 
    {  
        /* 计数防止超时 */
        if(RI) 
        {  
            /* 串口接收到 */
            RI = 0;
            return(SBUF);                                            /* 串口输入 */
        }
    }
    return(0);                                                       /* 不应该发生的情况 */
}

#define xEndCH395Cmd()     {}                                        /* 命令结束，仅在SPI模式下有效 */

/**************************** endfile *************************************/
