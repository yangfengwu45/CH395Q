/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395.C
* Author             : tech10
* Version            : V1.0
* Date               : 2014/1/1
* Description        : CH395功能演示
**********************************************************************************/
/**********************************************************************************
CH395 TCP/IP 协议族接口
STM32 演示程序，用于演示Socket0工作在MACRAW模式下。
**********************************************************************************/
/* 头文件包含*/
#include <stm32f10x_lib.h>              /* STM32F10x库定义 */
#include <string.h>
#include "../system/system.h"
#include "string.h"
#include "stdio.h"
#include "../PUB/CH395inc.h"
#include "CH395.H"
/***********************************************************************************/
/*CH395_OP_INTERFACE_MODE可以为1-5
1：硬件总线并口连接方式
2：软件模拟并口连接方式
3: 硬件SPI连接方式
4: 软件模拟SPI方式
5: 硬件异步串口连接方式  */

#define   CH395_OP_INTERFACE_MODE           3                    
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
UINT8  MyBuffer[4096];                                             /* 数据缓冲区 */
struct _SOCK_INF  SockInf;                                         /* 保存Socket信息 */
struct _CH395_SYS  CH395Inf;                                       /* 保存CH395信息 */

/* CH395相关定义 */
const UINT8 CH395MACAddr[6] = {0x02,0x03,0x04,0x05,0x06,0x07};   /* CH395MAC地址 */
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
    printf("Error: %02X\n", (UINT16)iError);                         /* 显示错误 */
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
   UINT8  sock_int_socket;
   UINT16 i;
   UINT16 len;
   UINT16 tmp;
   UINT8  buf[10];

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
       printf("receive len = %d\n",len);
       if(len == 0)return;
       CH395GetRecvData(sockindex,len,MyBuffer);                     /* 读取数据 */
     printf("MacRaw D    : %2x-%2x-%2x-%2x-%2x-%2x\n",(UINT16)MyBuffer[0],(UINT16)MyBuffer[1],(UINT16)MyBuffer[2],(UINT16)MyBuffer[3],(UINT16)MyBuffer[4],(UINT16)MyBuffer[5]);
     printf("MacRaw S    : %2x-%2x-%2x-%2x-%2x-%2x\n",(UINT16)MyBuffer[6],(UINT16)MyBuffer[7],(UINT16)MyBuffer[8],(UINT16)MyBuffer[9],(UINT16)MyBuffer[10],(UINT16)MyBuffer[12]);
     printf("MacRaw Type : %2x %2x\n",(UINT16)MyBuffer[12],(UINT16)MyBuffer[13]);
     printf("MacRaw Data : \n");
     for(i=14;i<len;i++)
     {
    printf("%2x ",(UINT16)MyBuffer[i]);
     }
   }
   if(sock_int_socket & SINT_STAT_CONNECT)                          /* 连接中断，仅在TCP模式下有效*/
   {
       printf("SINT_STAT_CONNECT\n");
       if(SockInf.TcpMode == TCP_SERVER_MODE)                       /* 如果socket 为服务器模式，用户可以获取远端的IP和端口*/
       {
         CH395CMDGetRemoteIPP(sockindex,buf);
         printf("IP address = %d.%d.%d.%d\n",(UINT16)buf[0],(UINT16)buf[1],(UINT16)buf[2],(UINT16)buf[3]);    
         tmp = (UINT16)(buf[5]<<8) + buf[4];
         printf("Port = %d\n",tmp);    
       }
   }
   if(sock_int_socket & SINT_STAT_DISCONNECT)                        /* 断开中断，仅在TCP模式下有效 */
   {
      printf("SINT_STAT_DISCONNECT \n");
   }
   if(sock_int_socket & SINT_STAT_TIM_OUT)                           /* 超时中断，仅在TCP模式下有效 */
   {                                 /*TCP 客户端模式的时候，假如TCP CLIENT无法顺利连接服务器端会进入此中断*/
                                                                     /*此时可以把Socket源端口号进行自加处理，以新的端口去连接服务器*/ 
       printf("SINT_STAT_TIM_OUT\n");
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

        printf("Init status : GINT_STAT_PHY_CHANGE\n");

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
    mDelaymS(10);
    Set_MCU_BaudRate();
    i = xReadCH395Data();                                            /* 如果设置成功，CH395返回CMD_ERR_SUCCESS */
    if(i == CMD_ERR_SUCCESS)printf("Set Success\n");
#endif
#endif
//    CH395CMDSetMACAddr(CH395Inf.MacAddr);                            /* 设置CH395的MAC地址，若手动设置Mac地址，需要在此语句后加200ms延时*/
    i = CH395CMDInitCH395();                                         /* 初始化CH395芯片 */
    return i;
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
    UINT8 i,mac[6]; 
    System_Initialization();
    mDelaymS(200);
    CH395_Port_Init();
    printf("CH395EVT Test Demo\n");
    InitCH395InfParam();                                             /* 初始化CH395相关变量 */
    i = CH395Init();                                                 /* 初始化CH395芯片 */
    mStopIfError(i);
    CH395CMDGetMACAddr(mac);
    printf("Mac : %2x.%2x.%2x.%2x.%2x.%2x\n",(UINT16)mac[0],(UINT16)mac[1],(UINT16)mac[2],(UINT16)mac[3],(UINT16)mac[4],(UINT16)mac[5]);

    while(1)
    {                                                                /* 等待以太网连接成功*/
       if(CH395CMDGetPHYStatus() == PHY_DISCONN)                     /* 查询CH395是否连接 */
       {
           mDelaymS(200);                                            /* 未连接则等待200MS后再次查询 */
       }
       else 
       {
           printf("CH395 Connect Ethernet\n");                       /* CH395芯片连接到以太网，此时会产生中断 */
           break;
       }
    }
    InitSocketParam();                                               /* 初始化socket相关变量 */
    CH395SocketInitOpen();
    while(1)
    {
      if(Query395Interrupt())CH395GlobalInterrupt();
    }
}

/****************************endfile@tech9*************************************/
