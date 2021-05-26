/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395功能演示
**********************************************************************************/

/**********************************************************************************
CH395 TCP/IP 协议族接口
MSC51 演示程序，用于演示CH395的低能耗模式，GPIO操作，及EEPROM操作。MCS51@24MHZ,KEIL 3.51
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
UINT8 xdata MyBuffer[512];                                           /* 数据缓冲区 */
struct _SOCK_INF xdata SockInf;                                      /* 保存Socket信息 */
struct _CH395_SYS xdata CH395Inf;                                    /* 保存CH395信息 */

/* CH395相关定义 */
const UINT8 CH395IPAddr[4] = {192,168,1,10};                         /* CH395IP地址 */
const UINT8 CH395GWIPAddr[4] = {192,168,1,1};                        /* CH395网关 */
const UINT8 CH395IPMask[4] = {255,255,255,0};                        /* CH395子网掩码 */

/* socket 相关定义*/
const UINT8  Socket0DesIP[4] = {192,168,1,100};                      /* Socket 0目的IP地址 */
const UINT16 Socket0DesPort = 1000;                                  /* Socket 0目的端口 */
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
    memcpy(SockInf.IPAddr,Socket0DesIP,sizeof(Socket0DesIP));        /* 将目的IP地址写入 */
    SockInf.DesPort = Socket0DesPort;                                /* 目的端口 */
    SockInf.SourPort = Socket0SourPort;                              /* 源端口 */
    SockInf.ProtoType = PROTO_TYPE_TCP;                              /* TCP模式 */
    SockInf.TcpMode = TCP_CLIENT_MODE;
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

    /* socket 0为TCP 客户端模式 */
    CH395SetSocketDesIP(0,SockInf.IPAddr);                           /* 设置socket 0目标IP地址 */         
    CH395SetSocketProtType(0,SockInf.ProtoType);                     /* 设置socket 0协议类型 */
    CH395SetSocketDesPort(0,SockInf.DesPort);                        /* 设置socket 0目的端口 */
    CH395SetSocketSourPort(0,SockInf.SourPort);                      /* 设置socket 0源端口 */
    i = CH395OpenSocket(0);                                          /* 打开socket 0 */
    mStopIfError(i);                                                 /* 检查是否成功 */
    i = CH395TCPConnect(0);                                          /* TCP连接 */
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
   UINT8  i;
   UINT16 len;
   UINT16 tmp;

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
       if(len > 512)len = 512;                                       /* MyBuffer缓冲区长度为512 */
       CH395GetRecvData(sockindex,len,MyBuffer);                     /* 读取数据 */
       for(tmp =0; tmp < len; tmp++)                                 /* 将所有数据按位取反 */
       {
          MyBuffer[tmp] = ~MyBuffer[tmp];
       }
       CH395SendData(sockindex,MyBuffer,len);

   }
   if(sock_int_socket & SINT_STAT_CONNECT)                          /* 连接中断，仅在TCP模式下有效*/
   {
    }
   if(sock_int_socket & SINT_STAT_DISCONNECT)                        /* 断开中断，仅在TCP模式下有效 */
   {
   }
   if(sock_int_socket & SINT_STAT_TIM_OUT)                           /* 超时中断，仅在TCP模式下有效 */
   {
       /* 产生超时中断表示连接/发送/接收数据超时或者失败，产生超时时CH395芯片内部将会将此    */
       /* socket关闭，在某些情况下CH395并不会重试连接，例如远端端口未打开，如果CH395连接，则 */
       /* 远端设备可能会发出RST强制将此连接复位，此时CH395仍然会产生超时中断。本程序仅作演示 */
       /* 实际应用中不推荐产生产生超时中断后立即连接，可以间隔一定时间内重新打开socket进行连 */
       /* 即可。*/         
       if(SockInf.TcpMode == TCP_CLIENT_MODE)                        /* 本程序实际只用了一个socket */
       {
           mDelaymS(200);                                            /* 延时200MS后再次重试，没有必要过于频繁连接 */
           i = CH395OpenSocket(sockindex);
           mStopIfError(i);
           CH395TCPConnect(sockindex);                               /* 开始连接 */
           mStopIfError(i);
      }
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
   UINT8   buf[10]; 
 
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
    CH395CMDSetIPAddr(CH395Inf.IPAddr);                              /* 设置CH395的IP地址 */
    CH395CMDSetGWIPAddr(CH395Inf.GWIPAddr);                          /* 设置网关地址 */
    CH395CMDSetMASKAddr(CH395Inf.MASKAddr);                          /* 设置子网掩码，默认为255.255.255.0*/   
 
    CH395SetStartPara(FUN_PARA_FLAG_LOW_PWR);                         /* CH395进入低能耗模式*/
    mDelaymS(100);

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
* Function Name  : CH395EEPROMTEST
* Description    : EEPROM操作演示
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void CH395EEPROMTEST(void)
{
   UINT8 i,s,Buf[64],BufT[64],n = 0;
   UINT16 add = 0;
   UINT16 mdata = 0;
   UINT8 k;
   printf("Test EEPROM\n");
   i = CH395EEPROMErase();                                           /*擦除EEPROM数据*/
   printf("EEPROM Erase = %02x\n",(UINT16)i);

   while(1)
   {
     for(i = 0; i < 64;i++)
     {
      Buf[i] = mdata++;
      BufT[i] = Buf[i];
     }
     if((n==0 || n==31 || n== 63))
     {
      printf("|-----EepromNum: %d ---------|\n",(UINT16)n);
      printf("Write EEProm:.......  ");
     }
     k = CH395EEPROMWrite(add,Buf,64);                 
     if((n==0 || n==31 || n== 63))                                   /*写EEPROM数据*/
     {       
      printf("WS = %02x      ",(UINT16)k);        
      printf("Read EEProm:.......\n");                   
      for(i = 0; i < 64;i++)Buf[i] = 0;
     }

     CH395EEPROMRead(add,Buf,64);
     if((n==0 || n==31 || n== 63))                                   /*读EEPROM数据*/
     {            
      for(i = 0; i < 32;i++)printf("%02x ",(UINT16)Buf[i]);
      printf("\n");
      for(i = 0; i < 32;i++)printf("%02x ",(UINT16)BufT[i]);
      printf("\n");
     }          
     s = memcmp(Buf,BufT,64);  
     if(s) printf("********************EEPROM ERROR*****************\n");        
     add += 64;
     n++;
     if(mdata >255) mdata = 0;
     if(add >= 4096)break;
    }
}

/**********************************************************************************
* Function Name  : CH395GpioTest
* Description    : GPIO操作演示
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void CH395GpioTest(void)
{
   UINT8 i,j;
   printf("|*******************GPIO TesT*******************************|\r\n");

   printf("|************GPIO OutPutTest ***********************|\r\n");
   CH395WriteGPIOAddr(GPIO_DIR_REG,0xff);                            /*设输入上拉*/
   CH395WriteGPIOAddr(GPIO_PU_REG, 0xff);       
   CH395WriteGPIOAddr(GPIO_OUT_REG,0x00);                            /*输出低电平*/
   
   printf("|*************Twinkle 5 times*************************|\r\n");
   for(i=0;i<5;i++)
   {                                                                 /*演示GPIO的输出功能，控制LED等闪烁5次*/
     CH395WriteGPIOAddr(GPIO_OUT_REG,0x00);
     mDelaymS(200);
     CH395WriteGPIOAddr(GPIO_OUT_REG,0x55);
     mDelaymS(200);
     CH395WriteGPIOAddr(GPIO_OUT_REG,0xaa);
     mDelaymS(200);
     CH395WriteGPIOAddr(GPIO_OUT_REG,0xff);
     mDelaymS(200);
   }
   printf("|************GPIO InPutTest ***********************|\r\n");  
   CH395WriteGPIOAddr(GPIO_DIR_REG,0x00);     
   CH395WriteGPIOAddr(GPIO_PU_REG, 0xff);       
   mDelaymS(500);
   for( j=0;j<50;j++)
   {
     i = CH395ReadGPIOAddr(GPIO_IN_REG);                             /*获取当前GPIO状态*/
     printf("CurrentStatus : %2x \r\n",(UINT16)i);
     mDelaymS(1000);
   }
    
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
    printf("CH395EVT Test Demo\n");
    CH395_PORT_INIT();
    InitCH395InfParam();                                             /* 初始化CH395相关变量 */
    i = CH395Init();                                                 /* 初始化CH395芯片 ，此函数中演示进入低能耗模式*/
    mStopIfError(i);
    
    CH395EEPROMTEST();                                               /*EEPROM功能演示*/
    CH395GpioTest();                                                 /*GPIO功能演示*/                  
 
    while(1)
    {                                                                 /* 等待以太网连接成功*/
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
    while(1)
    {
       if(CH395_INT_WIRE == 0)CH395GlobalInterrupt();
    }
}

