/********************************** (C) COPYRIGHT *********************************
* File Name          : MAIN.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片FTP客户端应用-主程序
**********************************************************************************/
#include <reg52.h>
#include <stdio.h>
#include <string.h>
#include "../PUB/CH395INC.H"
#include "../PUB/CH395CMD.H"
#include "CH395FTPINC.H"
#include "ch395.h"
extern FTP ftp;			
/**********************************************************************************/
#define CH395_INT_WIRE       INT1                                   /* CH395的INT#引脚  */
/* CH395相关定义 */
const  UINT8 CH395MACAddr[6]  = {0x02,0x03,0x04,0x05,0x06,0x07};    /* CH395MAC地址 */
const  UINT8 CH395IPAddr[4]   = {192,168,1,10};                   /* CH395IP地址 */
const  UINT8 CH395GWIPAddr[4] = {192,168,1,1};                  /* CH395网关 */
const  UINT8 CH395IPMask[4]   = {255,255,255,0};                    /* CH395子网掩码 */
const  UINT8 DestIPAddr[4]    = {192,168,1,100};                   /* 目的IP */
/* FTP相关定义 */
const  UINT8 *pUserName = "anonymous";                              /* 匿名登陆 */
const  UINT8 *pPassword = "123@";									
char   ListName[24];                                                /* 用于保存目录名 */
char   ListMdk[24];                                                 /*用于保存新创建的目录名 */
char   FileName[24];                                                /*用于保存搜查文件的文件名	*/
char   SourIP[17];                                                  /*用于保存转换成字符的IP地址 */

/***********************************************************************************
* Function Name  : main
* Description    : 主函数
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void main( void )
{
  CH395_FTPConnect( );                                              /*进行TCP FTP控制连接*/
	while(1)
	{
		if(CH395_INT_WIRE == 0) CH395GlobalInterrupt();
    CH395_FTPClientCmd( );                                          /*查询状态执行相应命令*/
	}
}
