/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395功能演示
**********************************************************************************/

/**********************************************************************************
CH395 TCP/IP 协议族接口
MSC51 演示程序，用于演示Socket0工作在MAC RAW模式下，单片机收到数据后，直接
上传。MCS51@24MHZ,KEIL 4
**********************************************************************************/
/* 头文件包含*/
#include <reg52.h>
#include "stdio.h"
#include "string.h"
#include "../PUB/CH395INC.H"
#include "CH395.H"

/**********************************************************************************
/*
CH395_OP_INTERFACE_MODE可以为1-5
1：硬件总线并口连接方式
2：软件模拟并口连接方式
3: 硬件SPI连接方式
4: 软件模拟SPI方式
5: 硬件异步串口连接方式
*/
#define   CH395_OP_INTERFACE_MODE             3                      
#if   (CH395_OP_INTERFACE_MODE == 1)                                 /* SEL = 0, TX = 1*/
#include "../PUB/CH395PARA_HW.C"                                           
#elif (CH395_OP_INTERFACE_MODE == 2)                                 /* SEL = 0, TX = 1*/
#include "../PUB/CH395PARA_SW.C"                                            
#elif (CH395_OP_INTERFACE_MODE == 3)                                 /* SEL = 1, TX = 0*/
#include "../PUB/CH395SPI_HW.C"
#elif (CH395_OP_INTERFACE_MODE == 4)                                 /* SEL = 1, TX = 0*/
#include "../PUB/CH395SPI_SW.C"
#elif (CH395_OP_INTERFACE_MODE == 5)                                 /* SEL = 1, TX = 1*/
#include "../PUB/CH395UART.C"
#else
#error "Please Select Correct Communication Interface "
#endif

/**********************************************************************************/
/* 包含命令文件 */
#include "../PUB/CH395CMD.C"
/* 常用变量定义 */
UINT8 xdata MyBuffer[512];
struct _SOCK_INF  xdata  SockInf;
struct _CH395_SYS xdata  CH395Inf;
/* CH395相关定义 */
const UINT8 CH395MACAddr[6] = {0x02,0x03,0x04,0x05,0x06,0x07};       /* CH395MAC地址 */
/*注：CH395出厂时已烧录MAC地址，此处设置MAC地址主要为演示操作，建议正常使用时候，直接调用获取MAC地址命令，无需重新设置MAC地址*/

#define  CH395_DEBUG                     0
/**********************************************************************************
* Function Name  : mStopIfError
* Description    : 调试使用，显示错误代码，并停机
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void mStopIfError(UINT8 iError)
{
    if (iError == CMD_ERR_SUCCESS) return;                           /* 操作成功 */
#if  CH395_DEBUG
    printf("Error: %02X\n", (UINT16)iError);                         /* 显示错误 */
#endif
    while ( 1 ) 
    {
        mDelaymS(200);
        mDelaymS(200);
    }
}

/*********************************************************************************
* Function Name  : InitCH395InfParam
* Description    : 初始化CH395Inf参数
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void InitCH395InfParam(void)
{
    memset(&CH395Inf,0,sizeof(CH395Inf));                            /* 将CH395Inf全部清零*/
    memcpy(CH395Inf.MacAddr,CH395MACAddr,sizeof(CH395MACAddr));      /* MAC地址 */
}

/**********************************************************************************
* Function Name  : InitSocketParam
* Description    : 初始化socket
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void InitSocketParam(void)
{
    memset(&SockInf,0,sizeof(SockInf));                              /* 将SockInf[0]全部清零*/
    SockInf.ProtoType = PROTO_TYPE_MAC_RAW;                          /* MAC RAW模式 */
}

/**********************************************************************************
* Function Name  : CH395SocketInitOpen
* Description    : 配置CH395 socket 参数，初始化并打开socket
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void CH395SocketInitOpen(void)
{
    UINT8 i;
     /* socket 0为MAC RAW模式 */
    CH395SetSocketProtType(0,SockInf.ProtoType);                     /* 设置socket 0协议类型 */
    i = CH395OpenSocket(0);                                          /* 打开socket 0 */
    mStopIfError(i);                                                 /* 检查是否成功 */
}

/**********************************************************************************
* Function Name  : CH395SocketInterrupt
* Description    : CH395 socket 中断,在全局中断中被调用
* Input          : sockindex
* Output         : None
* Return         : None
**********************************************************************************/
void CH395SocketInterrupt(UINT8 sockindex)
{
   UINT8  sock_int_socket,tmp1[6],tmp2[6],i;
   UINT16 len;

   sock_int_socket = CH395GetSocketInt(sockindex);                   /* 获取socket 的中断状态 */
   if(sock_int_socket & SINT_STAT_SENBUF_FREE)                       /* 发送缓冲区空闲，可以继续写入要发送的数据 */
   {
   }
   if(sock_int_socket & SINT_STAT_SEND_OK)                           /* 发送完成中断 */
   {
   }
   if(sock_int_socket & SINT_STAT_RECV)                              /* 接收中断 */
   {
    len = CH395GetRecvLength(sockindex);                             /* 获取当前缓冲区内数据长度 */
#if CH395_DEBUG
    printf("receive len = %d\n",len);
#endif
    if(len == 0)return;
    if(len > 512) len = 512;                                         /*MyBuffer缓冲区长度为512，*/
    CH395GetRecvData(sockindex,len,MyBuffer);                        /* 读取数据 */
    for(i=0;i<6;i++)                                                 /*接收到的前12字节数据位目的Mac地址和源Mac地址，交换位置进行转发*/
    {
      tmp1[i] =  MyBuffer[i];
    }
    for(i=0;i<6;i++)
    {
      tmp2[i] =  MyBuffer[i+6];
    }
    for(i=0;i<6;i++)
    {
      MyBuffer[i] =  tmp2[i];
    }
    for(i=0;i<6;i++)
    {
      MyBuffer[i+6] =  tmp1[i];
    }

    CH395SendData(sockindex,MyBuffer,len);
   }
   if(sock_int_socket & SINT_STAT_CONNECT)                           /* 连接中断，仅在TCP模式下有效*/
   {
       
   }
   if(sock_int_socket & SINT_STAT_DISCONNECT)                        /* 断开中断，仅在TCP模式下有效 */
   {
   }
   if(sock_int_socket & SINT_STAT_TIM_OUT)                           /* 超时中断，仅在TCP模式下有效 */
   {
   }
}

/**********************************************************************************
* Function Name  : CH395GlobalInterrupt
* Description    : CH395全局中断函数
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void CH395GlobalInterrupt(void)
{
   UINT16  init_status;
   UINT8 xdata buf[64]; 
 
    init_status = CH395CMDGetGlobIntStatus_ALL();
    if(init_status & GINT_STAT_UNREACH)                              /* 不可达中断，读取不可达信息 */
    {
        CH395CMDGetUnreachIPPT(buf);                                
    }
    if(init_status & GINT_STAT_IP_CONFLI)                            /* 产生IP冲突中断，建议重新修改CH395的 IP，并初始化CH395*/
    {
    }
    if(init_status & GINT_STAT_PHY_CHANGE)                           /* 产生PHY改变中断*/
    {
#if CH395_DEBUG
        printf("Init status : GINT_STAT_PHY_CHANGE\n");
#endif
    }
    if(init_status & GINT_STAT_SOCK0)
    {
        CH395SocketInterrupt(0);                                     /* 处理socket 0中断*/
    }
    if(init_status & GINT_STAT_SOCK1)
    {
        CH395SocketInterrupt(1);                                     /* 处理socket 1中断*/
    }
    if(init_status & GINT_STAT_SOCK2)
    {
        CH395SocketInterrupt(2);                                     /* 处理socket 2中断*/
    }
    if(init_status & GINT_STAT_SOCK3)
    {
        CH395SocketInterrupt(3);                                     /* 处理socket 3中断*/       
    }
    if(init_status & GINT_STAT_SOCK4)
    {
        CH395SocketInterrupt(4);                                     /* 处理socket 4中断*/
    }
    if(init_status & GINT_STAT_SOCK5)                                
    {
        CH395SocketInterrupt(5);                                     /* 处理socket 5中断*/
    }
    if(init_status & GINT_STAT_SOCK6)                                
    {
        CH395SocketInterrupt(6);                                     /* 处理socket 6中断*/
    }
    if(init_status & GINT_STAT_SOCK7)                                
    {
        CH395SocketInterrupt(7);                                     /* 处理socket 7中断*/
    }
}

/**********************************************************************************
* Function Name  : CH395Init
* Description    : 配置CH395的IP,GWIP,MAC等参数，并初始化
* Input          : None
* Output         : None
* Return         : 函数执行结果
**********************************************************************************/
UINT8  CH395Init(void)
{
    UINT8 i;
    
    i = CH395CMDCheckExist(0x65);                      
    if(i != 0x9a)return CH395_ERR_UNKNOW;                            /* 测试命令，如果无法通过返回0XFA */
                                                                     /* 返回0XFA一般为硬件错误或者读写时序不对 */
#if (CH395_OP_INTERFACE_MODE == 5)                                   
#ifdef UART_WORK_BAUDRATE
    CH395CMDSetUartBaudRate(UART_WORK_BAUDRATE);                     /* 设置波特率 */   
    mDelaymS(1);
    SetMCUBaudRate();
#endif
#endif

    CH395CMDSetMACAddr(CH395Inf.MacAddr);                            /* 设置CH395的MAC地址，MAC RAW仅需要设置MAC地址 */
    mDelaymS(200);                                                   /*必要的延时函数*/
    mDelaymS(200);    
    mDelaymS(200);    
    mDelaymS(200);    
    mDelaymS(200);    
    mDelaymS(200);    
    mDelaymS(200);    
    mDelaymS(200);    
    mDelaymS(200);    
    i = CH395CMDInitCH395();                                         /* 初始化CH395芯片 */
    return i;
}

/**********************************************************************************
* Function Name  : mInitSTDIO
* Description    : 串口初始化,仅调试使用
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void mInitSTDIO( void )
{
    SCON = 0x50;
    PCON = 0x80;
    TMOD = 0x21;
    TH1 = 0xf3;                                                      /* 24MHz晶振, 9600bps */
    TR1 = 1;
    TI = 1;
}

/**********************************************************************************
* Function Name  : main
* Description    : main主函数
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
int main(void)
{
    UINT8 i;
 
    mDelaymS(100);                                                   /* 延时100毫秒 */
    mInitSTDIO();
#if CH395_DEBUG
    printf("CH395EVT Test Demo\n");
#endif
    CH395_PORT_INIT();
    InitCH395InfParam();                                             /* 初始化CH395相关变量 */
    i = CH395Init();                                                 /* 初始化CH395芯片 */
    mStopIfError(i);
                                                                     
   while(1)
   {                                                                 /* 等待以太网连接成功*/
       if(CH395CMDGetPHYStatus() == PHY_DISCONN)                     /* 查询CH395是否连接 */
       {
           mDelaymS(200);                                            /* 未连接则等待200MS后再次查询 */
       }
       else 
       {
#if CH395_DEBUG
           printf("CH395 Connect Ethernet\n");                       /* CH395芯片连接到以太网，此时会产生中断 */
#endif
           break;
       }
   }
   InitSocketParam();                                                /* 初始化socket相关变量 */
   CH395SocketInitOpen();
   while(1)
   {
       if(CH395_INT_WIRE == 0)CH395GlobalInterrupt();                /* 中断处理函数 */
   }
}

