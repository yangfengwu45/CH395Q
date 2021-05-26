/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395.H
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395.C数据结构定义                      
**********************************************************************************/

#ifndef __CH395_H__
#define __CH395_H__

/* TCP模式，0为客户端，1为服务器 */
#define TCP_CLIENT_MODE                                      0
#define TCP_SERVER_MODE                                      1

struct _CH395_SYS
{
    UINT8   IPAddr[4];                                           /* CH395IP地址 32bit*/
    UINT8   GWIPAddr[4];                                         /* CH395网关地址 32bit*/
    UINT8   MASKAddr[4];                                         /* CH395子网掩码 32bit*/
    UINT8   MacAddr[6];                                          /* CH395MAC地址 48bit*/
    UINT8   PHYStat;                                             /* CH395 PHY状态码 8bit*/
    UINT8   MackFilt;                                            /* CH395 MAC过滤，默认为接收广播，接收本机MAC 8bit*/
    UINT32  RetranCount;                                         /* 重试次数 默认为10次*/
    UINT32  RetranPeriod;                                        /* 重试周期,单位MS,默认200MS */
    UINT8   IntfMode;                                            /* 接口模式 */
    UINT8   UnreachIPAddr[4];                                    /* 不可到达IP */
    UINT16  UnreachPort;                                         /* 不可到达端口 */
};

struct _SCOK_INF
{
    UINT8  IPAddr[4];                                           /* socket目标IP地址 32bit*/
    UINT8  MacAddr[6];                                          /* socket目标地址 48bit*/
    UINT8  ProtoType;                                           /* 协议类型 */
    UINT8  ScokStatus;                                          /* socket状态，参考scoket状态定义 */
    UINT8  TcpMode;                                             /* TCP模式 */
    UINT32 IPRAWProtoType;                                      /* IPRAW 协议类型 */
    UINT16 DesPort;                                             /* 目的端口 */
    UINT16 SourPort;                                            /* 目的端口 */
    UINT16 SendLen;                                             /* 发送数据长度 */
    UINT16 RemLen;                                              /* 剩余长度 */
    UINT8  *pSend;                                              /* 发送指针 */                                               
};                                                           

/* CH395相关定义 */
extern const UINT8 CH395MACAddr[6];
extern const UINT8 CH395IPAddr[4];                              /* CH395IP地址 */
extern const UINT8 CH395GWIPAddr[4];                            /* CH395网关 */
extern const UINT8 CH395IPMask[4];                              /* CH395子网掩码 */
extern const UINT8 DestIPAddr[4];                               /* 目的IP */


void CH395GlobalInterrupt(void); 									

void CH395SocketInitOpen( );									

void mDelaymS(UINT8 ms);

#endif
/************************** endfile **************************************/
