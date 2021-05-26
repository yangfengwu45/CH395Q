/********************************** (C) COPYRIGHT *********************************
* File Name          : MAIN.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395WEB功能演示
**********************************************************************************/

/*********************************************************************************
CH395 TCP/IP 协议族接口
CH563 演示程序，用于演示CH395WEB服务器功能
1、通过WEBSEVER控制页面可方便的进行LED控制，并及时显示LED状态。
2、可通过默认IP：192.168.111.64（默认端口80）访问WebServer，并可在控制页面进行IP，Port设置，点击change按钮后，
   可在浏览求输入新的IP和端口，通过新的IP和Port访问WebServer。
3、在监测窗口，可通过点击watch按钮实时查看监测信息。
**********************************************************************************/

/* 头文件包含*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..\SRC\CH563SFR.H"
#include "..\SRC\SYSFREQ.H"
#include "..\..\PUB\CH395INC.H"
#include "CH395.H"
#include "HTTPS.H"

/**********************************************************************************/
/*
CH395_OP_INTERFACE_MODE可以为1-5
1：硬件总线并口连接方式
2：软件模拟并口连接方式
3: 硬件SPI连接方式
4: 软件模拟SPI方式
5: 硬件异步串口连接方式
*/
#define   CH395_OP_INTERFACE_MODE             3                    
#if   (CH395_OP_INTERFACE_MODE == 1)                                                  /* SEL = 0, TX = 1*/
#include "CH395PARA_HW.C"                                           
#elif (CH395_OP_INTERFACE_MODE == 2)                                                  /* SEL = 0, TX = 1*/
#include "CH395PARA_SW.C"                                                             /*模拟并口，暂无接口程序*/
#elif (CH395_OP_INTERFACE_MODE == 3)                                                  /* SEL = 1, TX = 0*/
#include "CH395SPI_HW.C"
#elif (CH395_OP_INTERFACE_MODE == 4)                                                  /* SEL = 1, TX = 0*/
#include "CH395SPI_SW.C"                                                              /*模拟spi暂无接口程序*/
#elif (CH395_OP_INTERFACE_MODE == 5)                                                  /* SEL = 1, TX = 1*/
#include "CH395UART.C"
#else
#error "Please Select Correct Communication Interface "
#endif

/***********************************************************************************/
/* 包含命令文件 */
#include "..\..\PUB\CH395CMD.C"

/* 常用变量定义 */
 st_http_request *http_request;  
 UINT8  flag;		   		  									                                              /*CH395重新初始化标志*/
 UINT8  RecvBuffer[4096];               

/* CH395相关定义 */
 UINT8 CH395MACAddr[6] = {0x02,0x03,0x04,0x05,0x06,0x07};                                /* CH395MAC地址 */
 UINT8 CH395IPAddr[4] = {192,168,1,10};                                                /* CH395IP地址 */
 UINT8 CH395GWIPAddr[4] = {192,168,10,1};                                               /* CH395网关 */
 UINT8 CH395IPMask[4] = {255,255,255,0};                                                 /* CH395子网掩码 */

/* socket 相关定义*/
/* socket 相关定义*/
 UINT16 Socket0SourPort = 80;                                                            /* Socket 0源端口 */

__irq void FIQ_Handler( void )
{
    while(1);
}
__irq void IRQ_Handler( void )
{
    while(1);
}

/**********************************************************************************
* Function Name  : mInitSTDIO
* Description    : 串口初始化,仅调试使用
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void  mInitSTDIO(void)
{
  UINT32  x, x2;

  /*串口0初始化，由于打印调试信息*/
  x = 10 * FREQ_SYS * 2 / 16 /115200;                                                   /* 串口波特率为115200bps*/
  x2 = x % 10;
  x /= 10;
  if ( x2 >= 5 ) x ++;                                                                   /* 四舍五入 */
  R8_UART0_LCR = 0x80;                                                                   /* DLAB位置1   */
  R8_UART0_DIV = 1;                                                                      /* 预分频   */
  R8_UART0_DLM = x>>8;
  R8_UART0_DLL = x&0xff;
  R8_UART0_LCR = RB_LCR_WORD_SZ ;                                                         /*设置字节长度为8 */
  R8_UART0_FCR = RB_FCR_FIFO_TRIG|RB_FCR_TX_FIFO_CLR|RB_FCR_RX_FIFO_CLR |  RB_FCR_FIFO_EN ;/*设置FIFO长度为28，清发送和接收FIFO，FIFO使能  */
  R8_UART0_IER = RB_IER_TXD_EN | RB_IER_LINE_STAT |RB_IER_THR_EMPTY | RB_IER_RECV_RDY  ;  /* TXD enable */
  R8_UART0_MCR = RB_MCR_OUT2;                                                             /*串口中断输出使能 */
  R8_INT_EN_IRQ_0 |= RB_IE_IRQ_UART0;  
  R32_PB_SMT |= RXD0|TXD0;                                                                /* RXD0 schmitt input, TXD1 slow rate     */
  R32_PB_PD &= ~ RXD0;                                                                    /* disable pulldown for RXD1, keep pullup */
  R32_PB_DIR |= TXD0;                                                                     /* TXD1 output enable */

  /*串口1初始化，由于CH395通信*/
  x = 10 * FREQ_SYS * 2 / 16 /9600;                                                       /* 9600bps */
  x2 = x % 10;
  x /= 10;
  if ( x2 >= 5 ) x ++; 
  R8_UART1_LCR = 0x80;  
  R8_UART1_DIV = 1;  
  R8_UART1_DLM = x>>8;
  R8_UART1_DLL = x&0xff;
  R8_UART1_LCR = RB_LCR_WORD_SZ ;
  R8_UART1_FCR = RB_FCR_FIFO_TRIG|RB_FCR_TX_FIFO_CLR|RB_FCR_RX_FIFO_CLR |  RB_FCR_FIFO_EN ;
  R8_UART1_IER = RB_IER_TXD_EN | RB_IER_LINE_STAT |RB_IER_THR_EMPTY | RB_IER_RECV_RDY  ;  
  R8_UART1_MCR = RB_MCR_OUT2; 
  R8_INT_EN_IRQ_0 |= RB_IE_IRQ_UART1;  
  R32_PB_SMT |= RXD1|TXD1;  
  R32_PB_PD &= ~ RXD1; 
  R32_PB_DIR |= TXD1;  
}

int  fputc( int c, FILE *f )
{
  R8_UART0_THR = c;                          
  while( ( R8_UART0_LSR & RB_LSR_TX_FIFO_EMP ) == 0 );      
  return( c );
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
   UINT16 i;
   R32_PA_DIR = 0xffffffff;                                                            /*设置PA输出上拉*/
   R32_PA_PU  = 0xffffffff;
   R32_PA_DIR |= (TACK|TDI);                                                           /*GPIO初始化，用于LED灯控制*/
   R32_PA_PU  |= (TACK|TDI);
   R32_PA_OUT |= (TACK|TDI);
   mDelaymS(100);
   mInitSTDIO();
   http_request = (st_http_request*)RecvBuffer;
   printf("CH395EVT Test Demo\n");
   CH395_PROT_INIT();
 restart:                                                                               /* 延时100毫秒 */ 
   InitCH395InfParam();                                                                /* 初始化CH395相关变量 */
   i = CH395Init();                                                                    /* 初始化CH395芯片 */
   mStopIfError(i);
   while(1)
   {                                                                                   /* 等待以太网连接成功*/
       if(CH395CMDGetPHYStatus() == PHY_DISCONN)                                       /* 查询CH395是否连接 */
       {
           mDelaymS(200);                                                              /* 未连接则等待200MS后再次查询 */
       }
       else 
       {
           printf("CH395 Connect Ethernet\n");                                         /* CH395芯片连接到以太网，此时会产生中断 */
           break;
       }
   }
   InitSocketParam();                                                                  /* 初始化socket相关变量 */
   CH395SocketInitOpen();
   while(1)
   {
     if(Query395Interrupt())CH395GlobalInterrupt();                                    /*查询总中断*/
     WebServer();
     if((flag & IPCHANGE )|( flag & PORTCHANGE) )                                      /*IP或者Port改变则复位CH395并重新初始化*/
     {
       flag  &=~(IPCHANGE|PORTCHANGE) ;
       printf("reset all!\n");
       CH395CMDReset();
       for(i=0;i<15;i++) { mDelaymS(200);}                                             /*大约延时3S*/
       printf("restart\n");
       goto restart;
     }
   }
}

