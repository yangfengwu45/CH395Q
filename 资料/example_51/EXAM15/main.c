/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : 本例程用于演示上位机软件通过UDP广播的方式配置CH395功能,CH395创建了一个
                       UDP Socket 用于收发广播信息。
             
**********************************************************************************/
#include <reg52.h>
#include "stdio.h"
#include "string.h"
#include "../PUB/CH395INC.H"
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

#include "CH395.H"
#include "../PUB/CH395CMD.C"
#include "ModuleConfig.h"


UINT8 RecvFlag = 0;
UINT8 Recvbuf[300] ;  
UINT8 Configbuf[60]= { 
   'C','H','3','9','5','M','O','D','U','L','E',0,0,0,0,0,0,0,0,0,0,/*模块本身的IP地址*/    
  1,                                                               /*标识模块处于那模式(TCP client)*/
  192,168,1,10,                                                    /*模块本身的IP地址  */
  255,255,255,0,                                                   /*模块本身的子网掩码 */
  192,168,1,1,                                                     /*模块对应的网关地址 */
  2000%256,2000/256,                                               /*模块源端口 */
  192,168,1,100,                                                   /*目的IP地址 */
    1000%256,1000/256 ,                                            /*目的端口  */
}; 
 pmodule_cfg CFG = (pmodule_cfg)Configbuf;

/**********************************************************************************/
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

/**********************************************************************************
* Function Name  : main                                                                            
* Description    : main主函数
* Input          : None                                                  
* Output         : None
* Return         : None
**********************************************************************************/
int main(void)
{
  UINT8 i,*p;
 
  mDelaymS(100);
  mInitSTDIO();                                                   /* 延时100毫秒 */
  printf("CH395EVT Test Demo\n");

  CH395_PORT_INIT();
CH395INIT:  
  memcpy(CH395IPAddr,CFG->src_ip,sizeof(CFG->src_ip));         
  memcpy(CH395GWIPAddr,CFG->getway,sizeof(CFG->getway));   
  memcpy(CH395IPMask,CFG->getway,sizeof(CFG->getway));       

  InitCH395InfParam();                                              /* 初始化CH395相关变量 */
  i = CH395Init();                                                  /* 初始化CH395芯片 */
  mStopIfError(i);
  while(1)
  {                                                                 /* 等待以太网连接成功*/
  if(CH395CMDGetPHYStatus() == PHY_DISCONN)                         /* 查询CH395是否连接 */
  {
     mDelaymS(200);                                                 /* 未连接则等待200MS后再次查询 */
  }
  else 
  {
     printf("CH395 Connect Ethernet\n");                            /* CH395芯片连接到以太网，此时会产生中断 */
     break;
  }
  }
  InitSocketParam();                                                /* 初始化socket相关变量 */
  CH395SocketInitOpen();
  while(1)
  {
   if(CH395_INT_WIRE == 0)CH395GlobalInterrupt();
   if(RecvFlag){
   RecvFlag = 0;
   p = &Recvbuf[8] ;
   i = ParseConfigbuf(p) ;                                          /*解析数据*/
   if(i){
        printf("RESET CH395\n");
        CH395CMDReset();
        mDelaymS(200);
        goto CH395INIT;
        }
  }
  }

}