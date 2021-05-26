/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395.c
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395基本函数                      
**********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..\SRC\CH563SFR.H"
#include "..\SRC\SYSFREQ.H"
#include "..\..\PUB\CH395INC.H"
#include "CH395.H"
#include "..\..\PUB\ch395cmd.h"

struct  _SOCK_INF  SockInf;
struct  _CH395_SYS  CH395Inf;  
   
/*******************************************************************************
* Function Name  : InitCH395InfParam
* Description    : 初始化CH395Inf参数
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void InitCH395InfParam(void)
{
    memset(&CH395Inf,0,sizeof(CH395Inf));                            /* 将CH395Inf全部清零*/
    memcpy(CH395Inf.IPAddr,CH395IPAddr,sizeof(CH395IPAddr));         /* 将IP地址写入CH395Inf中 */
    memcpy(CH395Inf.GWIPAddr,CH395GWIPAddr,sizeof(CH395GWIPAddr));   /* 将网关IP地址写入CH395Inf中 */
    memcpy(CH395Inf.MASKAddr,CH395IPMask,sizeof(CH395IPMask));       /* 将子网掩码写入CH395Inf中 */
}

/********************************************************************************
* Function Name  : mStopIfError
* Description    : 调试使用，显示错误代码，并停机
* Input          : iError
* Output         : None
* Return         : None
*******************************************************************************/
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

/*******************************************************************************
* Function Name  : InitSocketParam
* Description    : 初始化socket
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void InitSocketParam(void)
{
    memset(&SockInf,0,sizeof(SockInf));                              /* 将SockInf[0]全部清零*/
    SockInf.SourPort = Socket0SourPort;                              /* 源端口 */
    SockInf.ProtoType = PROTO_TYPE_TCP;                              /* TCP模式 */
    SockInf.TcpMode = TCP_SERVER_MODE;
}

/********************************************************************************
* Function Name  : CH395SocketInitOpen
* Description    : 配置CH395 socket 参数，初始化并打开socket
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SocketInitOpen(void)
{
    UINT8 i;
    /* socket 0为TCP 服务器模式 */
    CH395SetSocketDesIP(0,SockInf.IPAddr);                           /* 设置socket 0目标IP地址 */         
    CH395SetSocketProtType(0,SockInf.ProtoType);                     /* 设置socket 0协议类型 */
    CH395SetSocketDesPort(0,SockInf.DesPort);                        /* 设置socket 0目的端口 */
    CH395SetSocketSourPort(0,SockInf.SourPort);                      /* 设置socket 0源端口 */
    i = CH395OpenSocket(0);                                          /* 打开socket 0 */
    mStopIfError(i);                                                 /* 检查是否成功 */
    i = CH395TCPListen(0);                                           /* TCP连接 */
    mStopIfError(i);                                                 /* 检查是否成功 */
}

/*******************************************************************************
* Function Name  : CH395SocketInterrupt
* Description    : CH395 socket 中断,在全局中断中被调用
* Input          : sockindex
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SocketInterrupt(UINT8 sockindex)
{
   UINT8  sock_int_socket;
   UINT8  buf[10],s;
   memcpy (lastip,CH395IPAddr,4);
   lastport = Socket0SourPort ;
   sock_int_socket = CH395GetSocketInt(sockindex);                   /* 获取socket 的中断状态 */
   if(sock_int_socket & SINT_STAT_SENBUF_FREE)                       /* 发送缓冲区空闲，可以继续写入要发送的数据 */
   {
      printf("SINT_STAT_SENBUF_FREE\n");   
      if(SockInf.SendLen >= SockInf.RemLen)
       {
        SockInf.RemLen = 0;                                          /* 数据已经发送完毕 */
        CH395TCPDisconnect(0);
       }
     else
       {
        SockInf.pSend += SockInf.SendLen;                           /* 对发送指针进行偏移 */
        SockInf.RemLen -= SockInf.SendLen;                          /* 计算剩余长度 */
        if(SockInf.RemLen > 2048)SockInf.SendLen = 2048;            /* 计算本次可以发送的数据长度 */
        else SockInf.SendLen = SockInf.RemLen;    
        CH395SendData(sockindex,SockInf.pSend,SockInf.SendLen);     /* 发送数据 */
       }
   }
   if(sock_int_socket & SINT_STAT_SEND_OK)                           /* 发送完成中断 */
   {
   }
   if(sock_int_socket & SINT_STAT_RECV)                              /* 接收中断 */
   {
       printf("SINT_STAT_RECV\n");
       len = CH395GetRecvLength(sockindex);                          /* 获取当前缓冲区内数据长度 */
       if(len == 0)return;
       CH395GetRecvData(sockindex,len,RecvBuffer);                   /* 读取数据 */
       flag  |= RECVDATA;
   }
   if(sock_int_socket & SINT_STAT_CONNECT)                           /* 连接中断，仅在TCP模式下有效*/
   {
      printf("Tcp Connect\n");
      if(SockInf.TcpMode == TCP_SERVER_MODE)                         /* 如果socket 为服务器模式，用户可以获取远端的IP和端口*/
      {
       CH395CMDGetRemoteIPP(sockindex,buf);
       printf("IP address = %d.%d.%d.%d\n",(UINT16)buf[0],(UINT16)buf[1],(UINT16)buf[2],(UINT16)buf[3]);        
      }
   }
   if(sock_int_socket & SINT_STAT_DISCONNECT)                        /* 断开中断，仅在TCP模式下有效 */
   {
      printf("SINT_STAT_DISCONNECT\n");
      s = CH395OpenSocket(0);                                        /* 打开socket 0 */
      mStopIfError(s);                                               /* 检查是否成功 */
      s = CH395TCPListen(0);                                         /* TCP连接 */
      mStopIfError(s);  

   }
   if(sock_int_socket & SINT_STAT_TIM_OUT)                           /* 超时中断，仅在TCP模式下有效 */
   {
       printf("Tcp Time out\n");
   }
}

/*******************************************************************************
* Function Name  : CH395GlobalInterrupt
* Description    : CH395全局中断函数
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395GlobalInterrupt(void)
{
    UINT16 init_status;
    UINT8  buf[10]; 
    init_status = CH395CMDGetGlobIntStatus_ALL();
    if(init_status & GINT_STAT_UNREACH)                              /* 不可达中断，读取不可达信息 */
    {
        printf("Init status : GINT_STAT_UNREACH\n");                 /* UDP模式下可能会产生不可达中断 */
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

/********************************************************************************
* Function Name  : CH395Init
* Description    : 配置CH395的IP,GWIP,MAC等参数，并初始化
* Input          : None
* Output         : None
* Return         : 函数执行结果
*******************************************************************************/
UINT8  CH395Init(void)
{
    UINT8 i;
    i = CH395CMDCheckExist(0x65); 
    printf("CH395CMDCheckExist = %2x\n",(UINT16)i);                     
    if(i != 0x9a)return CH395_ERR_UNKNOW;                            /* 测试命令，如果无法通过返回0XFA */
    CH395CMDSetIPAddr(CH395Inf.IPAddr);                              /* 设置CH395的IP地址 */
    CH395CMDSetGWIPAddr(CH395Inf.GWIPAddr);                          /* 设置网关地址 */
    CH395CMDSetMASKAddr(CH395Inf.MASKAddr);                          /* 设置子网掩码，默认为255.255.255.0*/   
    i = CH395CMDInitCH395();                                         /* 初始化CH395芯片 */
    printf("CH395CMDInitCH395 = %2x\n",(UINT16)i); 
    return i;
}
