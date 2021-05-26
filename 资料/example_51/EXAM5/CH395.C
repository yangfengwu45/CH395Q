/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395功能演示
**********************************************************************************/

/**********************************************************************************
CH395 TCP/IP 协议族接口
MSC51 演示程序，用于演示Socket0工作在TCP Server模式下，单片机收到数据后，按位取反后
上传。此功能仅0x44版本以上支持，如有疑问请联系技术支持邮箱：tech@wch.cn。
MCS51@24MHZ,KEIL 3.51
**********************************************************************************/
/* 头文件包含*/
#include <reg52.h>
#include "stdio.h"
#include "string.h"
#include "../PUB/CH395INC.H"
#include "CH395.H"

/***********************************************************************************
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

#define  CH395_DEBUG                1

#define  SocketNum                  8                                /*TCP SERVER 支持的Socket个数：(SocketNum -1)*/
#define  TcpMss                     536                              /*定义TCPMSS*/
/* 常用变量定义 */
UINT8 xdata MyBuffer[SocketNum-1][TcpMss*2];                         /* 数据缓冲区 */
struct _SOCK_INF xdata SockInf;                                      /* 保存Socket信息 */
struct _CH395_SYS xdata CH395Inf;                                    /* 保存CH395信息 */

/* CH395相关定义 */
const UINT8 CH395IPAddr[4] = {192,168,1,10};                         /* CH395IP地址 */
const UINT8 CH395GWIPAddr[4] = {192,168,1,1};                        /* CH395网关 */
const UINT8 CH395IPMask[4] = {255,255,255,0};                        /* CH395子网掩码 */

/* socket 相关定义*/
const UINT16 Socket0SourPort = 5000;                                 /* Socket 0源端口 */

/**********************************************************************************
* Function Name  : mStopIfError
* Description    : 调试使用，显示错误代码，并停机
* Input          : iError
* Output         : None
* Return         : None
**********************************************************************************/
void mStopIfError(UINT8 iError)
{
    if (iError == CMD_ERR_SUCCESS) return;                           /* 操作成功 */
#if CH395_DEBUG
    printf("Error: %02X\n", (UINT16)iError);                         /* 显示错误 */
#endif
    while ( 1 ) 
    {
        mDelaymS(200);
        mDelaymS(200);
    }
}

/**********************************************************************************
* Function Name  : InitCH395InfParam
* Description    : 初始化CH395Inf参数
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void InitCH395InfParam(void)
{
    memset(&CH395Inf,0,sizeof(CH395Inf));                            /* 将CH395Inf全部清零*/
    memcpy(CH395Inf.IPAddr,CH395IPAddr,sizeof(CH395IPAddr));         /* 将IP地址写入CH395Inf中 */
    memcpy(CH395Inf.GWIPAddr,CH395GWIPAddr,sizeof(CH395GWIPAddr));   /* 将网关IP地址写入CH395Inf中 */
    memcpy(CH395Inf.MASKAddr,CH395IPMask,sizeof(CH395IPMask));       /* 将子网掩码写入CH395Inf中 */
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
    SockInf.SourPort = Socket0SourPort;                              /* 源端口 */
    SockInf.ProtoType = PROTO_TYPE_TCP;                              /* TCP模式 */
    SockInf.TcpMode = TCP_SERVER_MODE;
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
    /* socket 0为TCP 服务器模式 */
    CH395SetSocketProtType(0,SockInf.ProtoType);                       /* 设置socket 0协议类型 */
    CH395SetSocketSourPort(0,SockInf.SourPort);                        /* 设置socket 0源端口 */
    i = CH395OpenSocket(0);                                            /* 打开socket 0 */
    mStopIfError(i);                                                   /* 检查是否成功 */
    i = CH395TCPListen(0);                                             /* TCP侦听 */
    mStopIfError(i); 
  
  for(i=1;i<SocketNum;i++)
  {
      CH395SetSocketProtType(i,SockInf.ProtoType);                     /* 设置socket 0协议类型 */
      CH395SetSocketSourPort(i,SockInf.SourPort);                      /* 设置socket 0源端口 */
  }                                                
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
   UINT8  sock_int_socket;
   UINT16 len;
   UINT16 tmp;
   UINT8 idata buf[10];

   sock_int_socket = CH395GetSocketInt(sockindex);                   /* 获取socket 的中断状态 */
   if(sock_int_socket & SINT_STAT_SENBUF_FREE)                       /* 发送缓冲区空闲，可以继续写入要发送的数据 */
   {
   }
   if(sock_int_socket & SINT_STAT_SEND_OK)                           /* 发送完成中断 */
   {
   }
   if(sock_int_socket & SINT_STAT_RECV)                              /* 接收中断 */
   {
       len = CH395GetRecvLength(sockindex);                          /* 获取当前缓冲区内数据长度 */
#if CH395_DEBUG
       printf("receive len = %d\n",len);
#endif
       if(len == 0)return;
       if(len > 100)len = 100;                                       /* MyBuffer缓冲区长度为512*/
       CH395GetRecvData(sockindex,len,MyBuffer[sockindex]);          /* 读取数据 */
       CH395SendData(sockindex,MyBuffer[sockindex],len);
   }
   if(sock_int_socket & SINT_STAT_CONNECT)                           /* 连接中断，仅在TCP模式下有效*/
   {
#if CH395_DEBUG
       printf("Tcp Connect\n");
#endif
       if(SockInf.TcpMode == TCP_SERVER_MODE)                       /* 如果socket 为服务器模式，用户可以获取远端的IP和端口*/
       {
           CH395CMDGetRemoteIPP(sockindex,buf);
           tmp = (UINT16)(buf[5]<<8) + buf[4];
#if CH395_DEBUG
           printf("IP address = %d.%d.%d.%d\n",(UINT16)buf[0],(UINT16)buf[1],(UINT16)buf[2],(UINT16)buf[3]);    
           printf("Port = %d\n",tmp);    
#endif
       }
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
   UINT8  buf[10]; 
 
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
#if (CH395_OP_INTERFACE_MODE == 5)                                   
#ifdef UART_WORK_BAUDRATE
    CH395CMDSetUartBaudRate(UART_WORK_BAUDRATE);                     /* 设置波特率 */   
    mDelaymS(1);
    SetMCUBaudRate();
#endif
#endif
    CH395CMDSetIPAddr(CH395Inf.IPAddr);                              /* 设置CH395的IP地址 */
    CH395CMDSetGWIPAddr(CH395Inf.GWIPAddr);                          /* 设置网关地址 */
    CH395CMDSetMASKAddr(CH395Inf.MASKAddr);                          /* 设置子网掩码，默认为255.255.255.0*/   
    CH395SetStartPara(FUN_PARA_FLAG_TCP_SERVER);                     /*TCP SERVER支持多连接时，需初始化此启动参数*/
    mDelaymS(100);
    i = CH395CMDInitCH395();                                         /* 初始化CH395芯片 */
    return i;
}

/*********************************************************************************
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

/*********************************************************************************
* Function Name  : Socket_R_S_Buf_Modify
* Description    : Socket收发缓冲区定义
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void Socket_R_S_Buf_Modify(void )
{

   CH395SetSocketRecvBuf(0,0,4);                                     /* Socket 0 ，接收缓冲区4*512 = 2K，发送缓冲区2*512 = 1K*/
   CH395SetSocketSendBuf(0,4,2);  
  
   CH395SetSocketRecvBuf(1,6,4);                                     /* Socket 1 */
   CH395SetSocketSendBuf(1,10,2);  
  
   CH395SetSocketRecvBuf(2,12,4);                                    /* Socket 2 */
   CH395SetSocketSendBuf(2,16,2);  
  
   CH395SetSocketRecvBuf(3,18,4);                                    /* Socket 3 */
   CH395SetSocketSendBuf(3,22,2);  
  
   CH395SetSocketRecvBuf(4,24,4);                                    /* Socket 4 */
   CH395SetSocketSendBuf(4,28,2);  
  
   CH395SetSocketRecvBuf(5,30,4);                                    /* Socket 5 */
   CH395SetSocketSendBuf(5,34,2);
  
   CH395SetSocketRecvBuf(6,36,4);                                    /* Socket 6 */
   CH395SetSocketSendBuf(6,40,2);  
  
   CH395SetSocketRecvBuf(7,42,4);                                    /* Socket 7 */
   CH395SetSocketSendBuf(7,46,2);  

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
 
    mDelaymS(100);
    mInitSTDIO();                                                    /* 延时100毫秒 */
#if CH395_DEBUG
    printf("CH395EVT Test Demo\n");
#endif
    CH395_PORT_INIT();
 
    i =   CH395CMDGetVer();
    if(i < 0x44)                                                     /* TCP SERVER多连接模式仅0X44及以上版本支持，0x44以下版本TCP SERVER只支持一个连接 */
    {
#if CH395_DEBUG
     printf("Error: Not Support!\n");                                /* 显示错误 */
#endif
     while ( 1 ) 
     {
        mDelaymS(200);
        mDelaymS(200);
     }   
    }
    InitCH395InfParam();                                             /* 初始化CH395相关变量 */
    i = CH395Init();                                                 /* 初始化CH395芯片 */
    mStopIfError(i);
 
    Socket_R_S_Buf_Modify();                                         /* 定义Socket发送和接收缓冲区*/
    CH395SetTCPMss(TcpMss);                                          /* 定义TCPMSS*/
                                                                    
    while(1)
    {                                                                /* 等待以太网连接成功*/
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
       if(CH395_INT_WIRE == 0)CH395GlobalInterrupt();
    }
}

