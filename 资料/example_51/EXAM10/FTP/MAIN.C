/********************************** (C) COPYRIGHT *********************************
* File Name          : MAIN.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片FTP服务器应用
**********************************************************************************/
#define Access_Authflag          0                                    /* 设置指定用户名访问（其他用户名无法访问服务器）*/
                                                                      /* 置1开启此功能，默认为0任何用户都可登录     */
#include <reg52.h>
#include <stdio.h>
#include <string.h>
#include "../PUB/CH395INC.H"
#include "../PUB/CH395CMD.H"
#include "CH395FTPINC.H"
#include "CH395.h"

/**********************************************************************************/
/* CH395相关定义 ,根据使用情况进行相应的修改*/
const UINT8 CH395MACAddr[6]  = {0x02,0x03,0x04,0x05,0x06,0x07};       /* CH395MAC地址 */
const UINT8 CH395IPAddr[4]   = {192,168,1,100};                      /* CH395IP地址 */
const UINT8 CH395GWIPAddr[4] = {192,168,1,1};                     /* CH395网关 */
const UINT8 CH395IPMask[4]   = {255,255,255,0};                       /* CH395子网掩码 */

#define CH395_INT_WIRE       INT1                                     /*  CH395的INT#引脚  */
extern FTP ftp;      
char   UserName[16];                                                  /* 用于保存用户名 */
char   SourIP[17];                                                    /* 用于保存转换成字符的IP地址 */
#if Access_Authflag
char  *pUserName = "anonymous";                                       /* 可以访问服务的用户名（其他用户名无法访问服务器）*/
#endif
char  *pPassWord = "IEUser@";                                         /* 有权限的密码（其他密码只支持读操作）*/

/*********************************************************************************
* Function Name  : main
* Description    : 主函数
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void main( void )
{
  CH395_FTPConnect( );                                                /* 进行TCP FTP控制连接及初始化*/
  while(1)
  {
    if(CH395_INT_WIRE == 0) CH395GlobalInterrupt();                   /* 查询中断状态      */
    CH395_FTPServerCmd( );                                            /* 查询状态执行相应命令  */
  }
}
