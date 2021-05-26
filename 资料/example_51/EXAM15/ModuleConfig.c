/********************************** (C) COPYRIGHT *********************************
* File Name          : ModuleConfig.c
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : 模块配置文件
**********************************************************************************/

#include <stdio.h>
#include <string.h>
#include "../PUB/CH395INC.H"
#include "ModuleConfig.h"

#include "CH395.H"
#include "../PUB/ch395cmd.h"

//模块默认配置
UINT8  DefaultSrcIp[4] = {192,168,1,100} ;
UINT8  DefaultMask[4]  = {255,255,255,0} ;
UINT8  DefaultGetway[4]= {192,168,1,1} ;
UINT32 DefaultBaud     = 9600;
UINT16 DefaultSrcPort  = 2000;
UINT8  DefaultDesIp[4] = {192,168,1,10} ;
UINT16 DefaultDesPort  = 1000;
UINT8  MODULE_NAME[21] ="CH395MODULE\0";        

UINT8   BrocatIp[4] = {255,255,255,255};
UINT16  BrocatPort  = 60000;

extern  UINT8 CH395MACAddr[6] ;     
extern  UINT8 Configbuf[60]  ;
/*long 转 char*/
void LongToChar(PUINT8 buf,UINT32 dat)
{
     UINT8 *p ;
  p = buf;

  *p++ = (UINT16)dat & 0xff;
  *p++ = (UINT16)dat>>8 & 0xff;
  *p++ = (UINT16)dat>>16 & 0xff;
  *p   = (UINT16)dat>>24 &  0xff;
  
}
/*配置命令解析*/
UINT8    ParseConfigbuf(PUINT8 buf)
{
   UINT16 i;
   UINT32 len;
   pnet_comm net = (pnet_comm)buf;                     //net通信结构体
   pmodule_cfg mdcfg = (pmodule_cfg)net->dat;
   pmodule_cfg mCurrentCfg = (pmodule_cfg)Configbuf;
 
   i =memcmp(net->flag,NET_MODULE_FLAG,15);
   if(i) return 0;

   switch  (net->cmd)
   {
     case  NET_MODULE_CMD_SEARCH :
           net->cmd    =   NET_MODULE_ACK_SEARCH ;
           memcpy(net->id,CH395MACAddr,6);
           sprintf((char *)net->dat,"%d.%d.%d.%d",(UINT16)mCurrentCfg->src_ip[0],(UINT16)mCurrentCfg->src_ip[1],(UINT16)mCurrentCfg->src_ip[2],(UINT16)mCurrentCfg->src_ip[3]);
           net->len = strlen((char *)net->dat);
           sprintf((char*)&net->dat[net->len + 1],"%s",mCurrentCfg->module_name);
           net->len += strlen((char*)&net->dat[net->len + 1]) + 1;
           len = sizeof(net_comm);
           DelaymS(5);
           CH395UDPSendTo(buf,len,BrocatIp,BrocatPort,0);  
           DelaymS(5);
           printf("CMD_SEARCH********************\n");
           return 0;

     case   NET_MODULE_CMD_SET :
           i =memcmp(net->id,CH395MACAddr,6);
           if(i) return 0;
           i = CH395CloseSocket(0);
           net->cmd  = NET_MODULE_ACK_SET ;
           net->len = 0;   
           memcpy(Configbuf,net->dat,MODULE_CFG_LEN);
           len = sizeof(net_comm);
           DelaymS(5);
           CH395UDPSendTo(buf,len,BrocatIp,BrocatPort,0);  
           DelaymS(5);
           printf("CMD_SET***********************\n");
           return 1;

    case   NET_MODULE_CMD_GET :
           i =memcmp(net->id,CH395MACAddr,6); 
           if(i) return 0;
           net->cmd  = NET_MODULE_ACK_GET ;
           net->len = MODULE_CFG_LEN; 
           memcpy(net->dat,Configbuf,MODULE_CFG_LEN)  ;
           len = sizeof(net_comm);
           DelaymS(5);
           CH395UDPSendTo(buf,len,BrocatIp,BrocatPort,0);  
           DelaymS(5);
           printf("CMD_GET***********************\n");
           return 0;
         
    case   NET_MODULE_CMD_RESET :
           i =memcmp(net->id,CH395MACAddr,6);
           if(i) return 0;
           i = CH395CloseSocket(0);
           memset(mdcfg,0,sizeof(mdcfg));
           strcat((char*)mdcfg->module_name,(char*)MODULE_NAME);        //默认配置
           mdcfg->type = NET_MODULE_TYPE_TCP_C;        
           memcpy(mdcfg->src_ip,DefaultSrcIp,4);
           memcpy(mdcfg->mask,DefaultMask,4);
           memcpy(mdcfg->getway,DefaultGetway,4);
           LongToChar(mdcfg->src_port,DefaultSrcPort);
           memcpy(mdcfg->dest_ip,DefaultDesIp,4);
           LongToChar(mdcfg->dest_port,DefaultDesPort);
           memcpy(Configbuf,net->dat,MODULE_CFG_LEN);       
           net->cmd = NET_MODULE_ACK_RESET ;
           len = sizeof(net_comm);
           DelaymS(5);
           DelaymS(5);
           printf("CMD_RESET*********************\n");
           return 1;
    default :
           return 0 ;
   }

}
