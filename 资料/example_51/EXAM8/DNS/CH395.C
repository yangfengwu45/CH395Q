/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395.C
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
#include "dns.h"

/*相关变量初始化*/
 struct  _SOCK_INF   SockInf[2];
 struct  _CH395_SYS  CH395Inf;     
 UINT8  MyBuffer[2][4096];  

/* CH395相关定义 */
 UINT8 CH395IPAddr[4] = {192,168,1,10};                            /* CH395IP地址 */
 UINT8 CH395GWIPAddr[4] = {192,168,1,1};                           /* CH395网关 */
 UINT8 CH395IPMask[4] = {255,255,255,0};                           /* CH395子网掩码 */
 
 UINT16 Socket0SourPort = 2000;                                    /* Socket 0源端口 */
 UINT16 Socket1SourPort = 4000;                                    /* Socket 1源端口 */

/*********************************************************************************
* Function Name  : InitCH395InfParam
* Description    : 初始化CH395Inf参数
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void InitCH395InfParam(void)
{
    memset(&CH395Inf,0,sizeof(CH395Inf));                           /* 将CH395Inf全部清零*/
    memcpy(CH395Inf.IPAddr,CH395IPAddr,sizeof(CH395IPAddr));        /* 将IP地址写入CH395Inf中 */
    memcpy(CH395Inf.GWIPAddr,CH395GWIPAddr,sizeof(CH395GWIPAddr));  /* 将网关IP地址写入CH395Inf中 */
    memcpy(CH395Inf.MASKAddr,CH395IPMask,sizeof(CH395IPMask));      /* 将子网掩码写入CH395Inf中 */
}

/*********************************************************************************
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
        Delay_ms(200);
        Delay_ms(200);
    }
}

/*********************************************************************************
* Function Name  : UDPSocketParamInit
* Description    : 初始化socket
* Input          : sockindex，addr，SourPort，DesPort
* Output         : None
* Return         : None
**********************************************************************************/
void UDPSocketParamInit(UINT8 sockindex,UINT8 *addr,UINT16 SourPort,UINT16 DesPort)
{
    UINT8 i;
    memset(&SockInf[sockindex],0,sizeof(SockInf[sockindex]));        /* 将SockInf[0]全部清零*/
    memcpy(SockInf[sockindex].IPAddr,addr,sizeof(addr));             /* 将目的IP地址写入 */
    SockInf[sockindex].DesPort = DesPort;                            /* 目的端口 */
    SockInf[sockindex].SourPort = SourPort;                          /* 源端口 */
    SockInf[sockindex].ProtoType = PROTO_TYPE_UDP; 

    CH395SetSocketDesIP(sockindex,SockInf[sockindex].IPAddr);        /* 设置socket 0目标IP地址 */         
    CH395SetSocketProtType(sockindex,PROTO_TYPE_UDP);                /* 设置socket 0协议类型 */
    CH395SetSocketDesPort(sockindex,SockInf[sockindex].DesPort);     /* 设置socket 0目的端口 */
    CH395SetSocketSourPort(sockindex,SockInf[sockindex].SourPort);   /* 设置socket 0源端口 */
    i = CH395OpenSocket(sockindex);                                  /* 打开socket 0 */
    mStopIfError(i);  
}

/*********************************************************************************
* Function Name  : UDPSendData
* Description    : UDP方式发送数据
* Input          : sockindex，databuf，len
* Output         : None
* Return         : None
**********************************************************************************/
UINT16 UDPSendData(UINT8 sockindex,UINT8 *databuf,UINT16 len)
{
  UINT16 ret;
  if(len>512){
  ret = 512;
  }
  else ret =len;
  CH395SendData(sockindex,databuf,len); 
  return ret;
}

/*********************************************************************************
* Function Name  : CH395SocketInterrupt
* Description    : CH395 socket 中断,在全局中断中被调用
* Input          : sockindex  Socket索引
* Output         : None
* Return         : None
**********************************************************************************/
void CH395SocketInterrupt(UINT8 sockindex)
{
    UINT8  sock_int_socket;
    UINT8  i;
    UINT16 len;
    UINT16 tmp;
    UINT8  buf[10];

    sock_int_socket = CH395GetSocketInt(sockindex);                  /* 获取socket 的中断状态 */
    if(sock_int_socket & SINT_STAT_SENBUF_FREE)                      /* 发送缓冲区空闲，可以继续写入要发送的数据 */
    {
        if(SockInf[sockindex].SendLen >= SockInf[sockindex].RemLen)
        SockInf[sockindex].RemLen = 0;                               /* 数据已经发送完毕 */
        else
        {
            SockInf[sockindex].pSend += SockInf[sockindex].SendLen;  /* 对发送指针进行偏移 */
            SockInf[sockindex].RemLen -= SockInf[sockindex].SendLen; /* 计算剩余长度 */
            if(SockInf[sockindex].RemLen > 2048)
            SockInf[sockindex].SendLen = 2048;                       /* 计算本次可以发送的数据长度 */
            else SockInf[sockindex].SendLen = 
            SockInf[sockindex].RemLen;     
            CH395SendData(sockindex,SockInf[sockindex].pSend,
            SockInf[sockindex].SendLen);                             /* 发送数据 */
        }
    }
    if(sock_int_socket & SINT_STAT_SEND_OK)                          /* 发送完成中断 */
    {
    }
    if(sock_int_socket & SINT_STAT_RECV)                             /* 接收中断 */
    {
        len = CH395GetRecvLength(sockindex);                         /* 获取当前缓冲区内数据长度 */
        if(len == 0)return;
    if (len > 0)
    {  
      if(SockInf[sockindex].RemLen != 0)return;                       /* 如果数据未发送完毕，则不再接收 */
      if(sockindex==0)
      {
         CH395GetRecvData(sockindex,len,dns_buf);
         status = 4;
         i = CH395CloseSocket(sockindex);
         mStopIfError(i);
      }
      else
      {
          if(SockInf[sockindex].RemLen != 0)return;                    /* 如果数据未发送完毕，则不再接收 */
          CH395GetRecvData(sockindex,len,MyBuffer[sockindex]);         /* 读取数据 */
          SockInf[sockindex].RemLen = len;                             /* 保存长度 */
          for(tmp =0; tmp < len; tmp++)                                /* 将所有数据按位取反 */
          {
              MyBuffer[sockindex][tmp] = ~MyBuffer[sockindex][tmp];
          }
          if(len > 2048)len = 2048;                                     /* 发送缓冲区最大为2048 */
          CH395SendData(sockindex,MyBuffer[sockindex],len);
          SockInf[sockindex].SendLen = len;                             /* 保存发送的长度 */
          SockInf[sockindex].pSend = MyBuffer[sockindex];               /* 发送换取区指针 */
      }
    }
   }
   if(sock_int_socket & SINT_STAT_CONNECT)                              /* 连接中断，仅在TCP模式下有效*/
   {
       printf("Tcp Connect\n");
       if(SockInf[sockindex].TcpMode == TCP_SERVER_MODE)                /* 如果socket 为服务器模式，用户可以获取远端的IP和端口*/
       {
         CH395CMDGetRemoteIPP(sockindex,buf);
         printf("IP address = %d.%d.%d.%d\n",(UINT16)buf[0],\
         (UINT16)buf[1],(UINT16)buf[2],(UINT16)buf[3]);    
         tmp = (UINT16)(buf[5]<<8) + buf[4];
         printf("Port = %d\n",tmp);    
       }
   }
   if(sock_int_socket & SINT_STAT_DISCONNECT)                          /* 断开中断，仅在TCP模式下有效 */
   {
   }
   if(sock_int_socket & SINT_STAT_TIM_OUT)                             /* 超时中断，仅在TCP模式下有效 */
   {
       printf("Tcp Time out\n");
       status = 2;
    }
}

/*********************************************************************************
* Function Name  : CH395GlobalInterrupt
* Description    : CH395全局中断函数
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void CH395GlobalInterrupt(void)
{
   UINT16  init_status;
   UINT16 i;
   UINT8  buf[10]; 
 
    init_status = CH395CMDGetGlobIntStatus_ALL();
    if(init_status & GINT_STAT_UNREACH)                               /* 不可达中断，读取不可达信息 */
    {
        printf("Init status : GINT_STAT_UNREACH\n");                  /* UDP模式下可能会产生不可达中断 */
        CH395CMDGetUnreachIPPT(buf);                                
    }
    if(init_status & GINT_STAT_IP_CONFLI)                             /* 产生IP冲突中断，建议重新修改CH395的 IP，并初始化CH395*/
    {
    }
    if(init_status & GINT_STAT_PHY_CHANGE)                            /* 产生PHY改变中断*/
    {
        printf("Init status : GINT_STAT_PHY_CHANGE\n");
        i = CH395CMDGetPHYStatus();       /* 获取PHY状态 */
        if(i==0x08) status = 1;    
        printf("status = 1\n");                           
        if(i == PHY_DISCONN)printf("Ethernet Disconnect\n");          /* 如果是PHY_DISCONN，CH395内部会自动关闭所有的socket*/
    }
    if(init_status & GINT_STAT_SOCK0)
    {
        CH395SocketInterrupt(0);                                      /* 处理socket 0中断*/
    }
    if(init_status & GINT_STAT_SOCK1)                                 
    {
        CH395SocketInterrupt(1);                                      /* 处理socket 1中断*/
    }
    if(init_status & GINT_STAT_SOCK2)                                 
    {
        CH395SocketInterrupt(2);                                      /* 处理socket 2中断*/
    }
    if(init_status & GINT_STAT_SOCK3)                                 
    {
        CH395SocketInterrupt(3);                                      /* 处理socket 3中断*/
    }
    if(init_status & GINT_STAT_SOCK4)
    {
        CH395SocketInterrupt(4);                                      /* 处理socket 4中断*/
    }
    if(init_status & GINT_STAT_SOCK5)                                 
    {
        CH395SocketInterrupt(5);                                      /* 处理socket 5中断*/
    }
    if(init_status & GINT_STAT_SOCK6)                                 
    {
        CH395SocketInterrupt(6);                                      /* 处理socket 6中断*/
    }
    if(init_status & GINT_STAT_SOCK7)                                 
    {
        CH395SocketInterrupt(7);                                      /* 处理socket 7中断*/
    }
}

/*********************************************************************************
* Function Name  : CH395Init
* Description    : 配置CH395的IP,GWIP,MAC等参数，并初始化
* Input          : None
* Output         : None
* Return         : 函数执行结果
**********************************************************************************/
UINT8  CH395Init(void)
{
    UINT8 i;    
    i = CH395CMDCheckExist(0x55); 
    printf("CH395CMDCheckExist = %2x\n",(UINT16)i);
    if(i != 0xaa)return CH395_ERR_UNKNOW;                            /* 测试命令，如果无法通过返回0XFA */
    CH395CMDSetIPAddr(CH395Inf.IPAddr);                              /* 设置CH395的IP地址 */
    CH395CMDSetGWIPAddr(CH395Inf.GWIPAddr);                          /* 设置网关地址 */
    CH395CMDSetMASKAddr(CH395Inf.MASKAddr);                          /* 设置子网掩码，默认为255.255.255.0*/  
    i = CH395CMDInitCH395();                                         /* 初始化CH395芯片 */
    return i;
}
