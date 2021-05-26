/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395基本函数
**********************************************************************************/
/* 头文件包含*/
#include <reg52.h>
#include <stdio.h>
#include <string.h>
#include "../PUB/CH395INC.H"
#include "CH395.H"
#include "CH395FTPINC.H"
extern FTP ftp;			
/********************************************************************************/
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
#endif
/********************************************************************************/
/* 包含命令文件 */
#include "../PUB/CH395CMD.C"
/*******************************************************************************/

/* 常用变量定义 */
#define MybufLen  536                                               /* 定义ch395接收数据的缓冲区最大长度 */
#define CH395_DEBG					1
UINT8  MyBuffer[2][MybufLen];                                       /* 数据缓冲区 */
struct _SCOK_INF  ScokInf[2];                                       /* 保存Socket信息 */
struct _CH395_SYS CH395Inf;                                         /* 保存CH395信息 */
UINT8  PortTmp;                                                     /* 用于改变端口值 */

/*******************************************************************************
* Function Name  : mStopIfError
* Description    : 调试使用，显示错误代码，并停机
* Input          : iError
* Output         : None
* Return         : None
*******************************************************************************/
void mStopIfError(UINT8 iError)
{
    if (iError == CMD_ERR_SUCCESS) return;                         /* 操作成功 */
    printf("Error: %02X\n", (UINT16)iError);                       /* 显示错误 */
    while ( 1 ) 
    {
        mDelaymS(200);
        mDelaymS(200);
    }
}

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

/*******************************************************************************
* Function Name  : CH395ClientSocketInitOpen
* Description    : 配置CH395 socket 参数，初始化并打开socket
* Input          : index
* Output         : None
* Return         : None
*******************************************************************************/
void CH395ClientSocketInitOpen(UINT8 index)
{
    UINT8 i;

    CH395SetSocketDesIP(index,ScokInf[index].IPAddr);                  /* 设置socket 目标IP地址 */         
    CH395SetSocketProtType(index,ScokInf[index].ProtoType);            /* 设置socket 协议类型 */
    CH395SetSocketDesPort(index,ScokInf[index].DesPort);               /* 设置socket 目的端口 */
    CH395SetSocketSourPort(index,ScokInf[index].SourPort);             /* 设置socket 源端口 */
    i = CH395OpenSocket(index);                                        /* 打开socket  */
    mStopIfError(i);                                                   /* 检查是否成功 */
    i = CH395TCPConnect(index);                                        /* TCP连接 */
    mStopIfError(i);                                                   /* 检查是否成功 */
}

/********************************************************************************
* Function Name  : CH395ServerSocketInitOpen
* Description    : 配置CH395 socket 参数，初始化并打开socket
* Input          : index
* Output         : None
* Return         : None
*******************************************************************************/
void CH395ServerSocketInitOpen(UINT8 index)
{
    UINT8 i;

    CH395SetSocketProtType(index,ScokInf[index].ProtoType);          /* 设置socket 协议类型 */
    CH395SetSocketSourPort(index,ScokInf[index].SourPort);           /* 设置socket 源端口 */
    i = CH395OpenSocket(index);                                      /* 打开socket  */
    mStopIfError(i);                                                 /* 检查是否成功 */
    i = CH395TCPListen(index);                                       /* TCP连接 */
    mStopIfError(i);                                                 /* 检查是否成功 */
}

/*******************************************************************************
* Function Name  : CH395_FTPCtlClient
* Description    : 建立TCP控制连接
* Input          : socketid
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_FTPCtlClient( UINT8 socketid )
{
  memset(&ScokInf[socketid],0,sizeof(ScokInf[socketid]));           /* 将对应ScokInf全部清零*/
  memcpy(ScokInf[socketid].IPAddr,DestIPAddr,4);                    /* 将目的IP地址写入 */
  ScokInf[socketid].DesPort  = 21;                                  /* 目的端口 */
  ScokInf[socketid].SourPort = 4000;                                /* 源端口 */
  ScokInf[socketid].ProtoType= PROTO_TYPE_TCP;                      /* TCP模式 */
  ScokInf[socketid].TcpMode  = TCP_CLIENT_MODE;                     /* TCP客户端模式 */
  ftp.SocketCtl = socketid; 
  CH395ClientSocketInitOpen( socketid );
  memset((void *)MyBuffer[socketid],'\0',sizeof(MyBuffer[socketid]));			  
}

/******************************************************************************
* Function Name  : CH395_FTPDatClient
* Description    : 建立TCP数据连接
* Input          : socketid,port
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_FTPDatClient( UINT8 socketid,UINT16 *port )
{
  if( PortTmp<100 || PortTmp>200 ) PortTmp=100;
	PortTmp++;
    memset(&ScokInf[socketid],0,sizeof(ScokInf[socketid]));           /* 将对应ScokInf全部清零*/
    memcpy(ScokInf[socketid].IPAddr,DestIPAddr,4);                    /* 将目的IP地址写入 */
    ScokInf[socketid].DesPort = 20;                                   /* 目的端口 */
    ScokInf[socketid].SourPort = 5000+PortTmp;                        /* 源端口 */
	*port = ScokInf[socketid].SourPort;
    ScokInf[socketid].ProtoType= PROTO_TYPE_TCP;                      /* TCP模式 */
    ScokInf[socketid].TcpMode  = TCP_CLIENT_MODE;                     /* TCP客户端模式 */
	ftp.DatTransfer = socketid; 
	CH395ClientSocketInitOpen( socketid );
	memset((void *)MyBuffer[socketid],'\0',sizeof(MyBuffer[socketid]));			  
}

/*******************************************************************************
* Function Name  : CH395_FTPDatServer
* Description    : 初始化socket
* Input          : socketid,port
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_FTPDatServer( UINT8 socketid,UINT16 *port )
{
	if(PortTmp < 100||PortTmp > 200) PortTmp = 100;
    PortTmp++;
    memset(&ScokInf[socketid],0,sizeof(ScokInf[socketid]));           /* 将对应ScokInf全部清零*/
    ScokInf[socketid].SourPort = 5000+ PortTmp;                       /* 源端口 */
	*port = ScokInf[socketid].SourPort;
    ScokInf[socketid].ProtoType = PROTO_TYPE_TCP;                     /* TCP模式 */
    ScokInf[socketid].TcpMode = TCP_SERVER_MODE;                      /* TCP服务器模式 */
	ftp.DatMonitor = socketid; 
	CH395ServerSocketInitOpen( socketid );
	memset((void *)MyBuffer[socketid],'\0',sizeof(MyBuffer[socketid]));			  
}

/******************************************************************************
* Function Name  : CH395SocketInterrupt
* Description    : CH395 socket 中断,在全局中断中被调用
* Input          : sockindex
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SocketInterrupt(UINT8 sockindex)
{
   UINT8  sock_int_socket;
   UINT16 len;

#if CH395_DEBG
	printf("sockindex =%d\n",(UINT16)sockindex);
#endif	
  sock_int_socket = CH395GetSocketInt(sockindex);                        /* 获取socket 的中断状态 */
  if(sock_int_socket & SINT_STAT_SENBUF_FREE)                            /* 发送缓冲区空闲，可以继续写入要发送的数据 */
   {
   }
   if(sock_int_socket & SINT_STAT_SEND_OK)                               /* 发送完成中断 */
   {
#if CH395_DEBG
	printf("send data success\n");
#endif
   }
   if(sock_int_socket & SINT_STAT_CONNECT)                               /* 连接中断，仅在TCP模式下有效*/
   {
#if CH395_DEBG
	printf("TCP Connect\n");
#endif	
		if(sockindex == ftp.DatMonitor){
			ftp.TcpStatus = FTP_MACH_CONNECT;
			ftp.DatTransfer = sockindex;
		}
   }
   if(sock_int_socket & SINT_STAT_RECV)                                  /* 接收中断 */
   {
 
	   len = CH395GetRecvLength(sockindex);                              /* 获取当前缓冲区内数据长度 */
	   if(len){
	 	   if(len>MybufLen) len = MybufLen;
	       CH395GetRecvData(sockindex,len,MyBuffer[sockindex]);          /* 读取数据 */
	       ScokInf[sockindex].RemLen = len;                              /* 保存长度 */
		   ftp.RecDatLen = len; 
#if CH395_DEBG
	printf("len:%d\n",len);
	printf("MyBuffer:\n%s\n",MyBuffer[sockindex]);
#endif	
		  CH395_FTPProcessReceDat((char *)MyBuffer[sockindex],ftp.FileCmd,sockindex);
    	  memset((void *)MyBuffer[sockindex],'\0',sizeof(MyBuffer[sockindex]));
       }
   }
   if(sock_int_socket & SINT_STAT_DISCONNECT)                           /* 断开中断，仅在TCP模式下有效 */
   {
#if CH395_DEBG                                                          /* 产生此中断，CH563NET_库内部会将此socket清除，置为关闭*/
    printf("TCP Disconnect\n");                                         /* 应用曾需可以重新创建连接 */
#endif
		if(sockindex == ftp.DatTransfer){
			ftp.TcpStatus = 0;
			ftp.CmdDataS = FTP_MACH_DATAOVER;
		}
		CH395CloseSocket(sockindex);
   }
   if(sock_int_socket & SINT_STAT_TIM_OUT)                              /* 超时中断，仅在TCP模式下有效 */
   {
#if CH395_DEBG                                                          /* 产生此中断，CH563NET_库内部会将此socket清除，置为关闭*/
    printf("TCP Timout\n");                                             /* 应用曾需可以重新创建连接 */
#endif
       /* 产生超时中断表示连接/发送/接收数据超时或者失败，产生超时时CH395芯片内部将会将此    */
       /* socket关闭，在某些情况下CH395并不会重试连接，例如远端端口未打开，如果CH395连接，则 */
       /* 远端设备可能会发出RST强制将此连接复位，此时CH395仍然会产生超时中断。本程序仅作演示 */
       /* 实际应用中不推荐产生产生超时中断后立即连接，可以间隔一定时间内重新打开socket进行连 */
       /* 即可。*/         
		if(sockindex == ftp.DatTransfer){
			ftp.TcpStatus = 0;
			ftp.CmdDataS = FTP_MACH_DATAOVER;
		}
	    CH395CloseSocket(sockindex);
   }
}

/********************************************************************************
* Function Name  : CH395GlobalInterrupt
* Description    : CH395全局中断函数
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395GlobalInterrupt(void) 
{
    UINT16  init_status;
    UINT16 i;
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
#if  CH395_DEBG
        printf("Init status : GINT_STAT_PHY_CHANGE\n");
#endif
        i = CH395CMDGetPHYStatus();                                  /* 获取PHY状态 */
        if(i == PHY_DISCONN){
#if  CH395_DEBG
     printf("Ethernet Disconnect\n");                                /* 如果是PHY_DISCONN，CH395内部会自动关闭所有的socket*/
#endif
		}
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
     CH395SocketInterrupt(2);                                        /* 处理socket 2中断*/
    }
    if(init_status & GINT_STAT_SOCK3)                                
    {
        CH395SocketInterrupt(3);                                     /* 处理socket 3中断*/
    }    
	if(init_status & GINT_STAT_SOCK4)
    {
     CH395SocketInterrupt(4);                                        /* 处理socket 4中断*/
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
    if(i != 0x9a)return CH395_ERR_UNKNOW;                            /* 测试命令，如果无法通过返回0XFA */
                                                                     /* 返回0XFA一般为硬件错误或者读写时序不对 */
#if (CH395_OP_INTERFACE_MODE == 5)                                   
#ifdef UART_WORK_BAUDRATE
    CH395CMDSetUartBaudRate(UART_WORK_BAUDRATE);                     /* 设置波特率 */   
    mDelaymS(1);
    SetMCUBaudRate();
    i = xReadCH395Data();                                            /* 如果设置成功，CH395返回CMD_ERR_SUCCESS */
    if(i == CMD_ERR_SUCCESS)printf("Set Success\n");
#endif
#endif
    CH395CMDSetIPAddr(CH395Inf.IPAddr);                              /* 设置CH395的IP地址 */
    CH395CMDSetGWIPAddr(CH395Inf.GWIPAddr);                          /* 设置网关地址 */
    CH395CMDSetMASKAddr(CH395Inf.MASKAddr);                          /* 设置子网掩码，默认为255.255.255.0*/   
    i = CH395CMDInitCH395();                                         /* 初始化CH395芯片 */
    return i;
}

/********************************************************************************
* Function Name  : mInitSTDIO
* Description    : 串口初始化,仅调试使用
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void mInitSTDIO( void )
{
    SCON = 0x50;
    PCON = 0x80;
    TMOD = 0x21;
    TH1 = 0xf3;                                                      /* 24MHz晶振, 9600bps */
    TR1 = 1;
    TI = 1;
}

/********************************************************************************
* Function Name  : CH395_SocketSendData
* Description    : 发送数据
* Input          : PSend-发送的数据内容
				           Len-  长度
				           index-socket索引
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_SocketSendData( char *PSend, UINT32 Len,UINT8 index  )
{
   CH395SendData(index,PSend,Len);
   printf("Send:%s",PSend);
}

/********************************************************************************
* Function Name  : CH395_FTPInitVari
* Description    : 变量初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_FTPInitVari( )
{
	FTP *pFTP;
	UINT8 i,j;

	pFTP = &ftp;
	memset((void *)pFTP,'\0',sizeof(ftp));
	ftp.SocketCtl = 255; 
	ftp.DatMonitor = 255;
	ftp.DatTransfer = 255;
  ftp.FileCmd = FTP_CMD_LOGIN;                                       /* 执行登陆命令		*/
	memset((void *)SourIP,'\0',sizeof(SourIP));		   		
	j = 0;
  for(i=0;i<4;i++){                                                  /* 将十进制的IP地址转换所需要的字符格式	*/
		if( CH395IPAddr[i]/100 ){
			SourIP[j++] = CH395IPAddr[i]/100 + '0';
			SourIP[j++] = (CH395IPAddr[i]%100)/10 + '0' ;
			SourIP[j++] = CH395IPAddr[i]%10 + '0';
		} 
		else if( CH395IPAddr[i]/10 ){
			SourIP[j++] = CH395IPAddr[i]/10 + '0';
			SourIP[j++] = CH395IPAddr[i]%10 + '0';
		} 
		else SourIP[j++] = CH395IPAddr[i]%10 + '0';
 		SourIP[j++] = ',';
	}
#if  CH395_DEBG
	printf("SourIP: %s\n",SourIP);
#endif	
}

/******************************************************************************
* Function Name  : CH395_FTPConnect
* Description    : ch395初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_FTPConnect( )
{
    UINT8 i;
 
    mDelaymS(100);                                                    /* 延时100毫秒 */
    mInitSTDIO();  
    CH395_FTPInitVari( );                                                  
#if  CH395_DEBG
    printf("CH395FTP Demo\n");
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
#if  CH395_DEBG
           printf("CH395 Connect Ethernet\n");                       /* CH395芯片连接到以太网，此时会产生中断 */
#endif	
          break;
       }
   }
}
