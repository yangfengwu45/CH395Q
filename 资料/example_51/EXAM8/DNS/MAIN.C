/********************************** (C) COPYRIGHT *********************************
* File Name          : MAIN.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395 DNS功能演示
**********************************************************************************

 CH395 DNS域名解析应用，根据域名可查询该域名所对应实际IP。 
 1、本例程包含一份CH395DNS功能例程，通过调用DnsQuery()函数，可实现域名到IP的转换。
 2、DNS.c文件中DNS_SERVER_IP需要根据实际情况进行修改。
**********************************************************************************/
/* 头文件包含*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..\SRC\CH563SFR.H"
#include "..\SRC\SYSFREQ.H"
#include "..\..\PUB\CH395INC.H"
#include "CH395.H"
#include "dns.h"
/**********************************************************************************
CH395_OP_INTERFACE_MODE可以为1-5
1：硬件总线并口连接方式
2：软件模拟并口连接方式
3: 硬件SPI连接方式
4: 软件模拟SPI方式
5: 硬件异步串口连接方式
**********************************************************************************/
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

#define MAX_URL_SIZE                            128

UINT8  url_dn1[MAX_URL_SIZE] = "www.baidu.com";    
UINT8  url_dn2[MAX_URL_SIZE] = "www.google.com";    
UINT8  url_dn3[MAX_URL_SIZE] = "www.wch.cn";    

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
/* 为printf和getkey输入输出初始化串口 */
void  mInitSTDIO( )
{
  UINT32  x, x2;
  x = 10 * FREQ_SYS * 2 / 16 /115200;                                                    /* 串口波特率为115200bps*/
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

  x = 10 * FREQ_SYS * 2 / 16 /9600;                                                       /* 115200bps */
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
   
    UINT8 i,ip[4];
    Delay_ms(100);                                                                      /* 延时100毫秒 */ 
    mInitSTDIO(); 

    R32_PA_DIR = 0xffffffff;                                                            /*设置PA输出上拉*/
    R32_PA_PU  = 0xffffffff;
                                                                 
    printf("CH395EVT  DNS TEST \n");
    CH395_PROT_INIT();
    InitCH395InfParam();                                                                /* 初始化CH395相关变量 */
    i = CH395Init();                                                                    /* 初始化CH395芯片 */
    mStopIfError(i);
 
    while(1)
    {                                                                                    /* 等待以太网连接成功*/
       if(CH395CMDGetPHYStatus() == PHY_DISCONN)                                         /* 查询CH395是否连接 */
       {                                          
           Delay_ms(10);                                                                 /* 未连接则等待200MS后再次查询 */
       }
       else 
       {
           break;
       }
    }
    Delay_ms(10);

    while(1)
    {
     if(Query395Interrupt())CH395GlobalInterrupt();                                      /*查询总中断*/
     i = DnsQuery(0,url_dn3,ip);                                                         /*查询"www.baidu.com"*/
     if(i)
     { 
      printf("Domain name: %s \n",url_dn3);
      printf(" HTTPs_IP= %d.%d.%d.%d\n\n",ip[0],ip[1],ip[2],ip[3]);
      status = 1;
      break;
     }   
    }
    while(1);  
}


