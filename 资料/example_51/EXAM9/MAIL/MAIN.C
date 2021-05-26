/********************************** (C) COPYRIGHT *********************************
* File Name          : MAIN
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395 mail 功能演示
**********************************************************************************/
#include <reg52.h>
#include <stdio.h>
#include <string.h>
#include "../PUB/CH395INC.H"
#include "../PUB/CH395CMD.H"
#include "ch395.h"
/**************************************************************************************************************************
* 工作类型 (默认为第五种)*
* 1  只发送邮件--发送完成后退出登陆并关闭socket连接；
* 2  只接收邮件--接收完成【获取邮件列表】后退出登陆并关闭socket连接；
* 3  只接收邮件--接收完成【读取邮件后删除】后退出登陆并关闭socket连接；
* 4  发送邮件且接受邮件--发送完成后开始接收邮件，接收完成后退出登陆并关闭socket连接; 
* 5  发送邮件且接受邮件--接收完成后回复邮件，发送完成后发送退出登陆，删除邮件后退出收邮件登陆，并关闭socket连接。  
* 说明：此代码接收与发送用的两个独立的socket连接；
*       如果还需进行其他的操作，eg：发送完接收，接收完继续发送操作只需在ch395mail.c代码中的
        ch395mail_CheckResponse（）子程序中接收完成后，将命令号置为 SMTP_SEND_START；
*************************************************************************************************************************/

#define  mail_work_mode               5           
#define CH395_INT_WIRE              INT1                                                          /* CH395的INT#引脚 */
#include "mailinc.h"
/**********************************************************************************/

/* CH395相关定义 */
const UINT8 CH395IPAddr[4] =   {192,168,1,100};                                                    /* CH395IP地址 */
const UINT8 CH395GWIPAddr[4] = {192,168,1,1};                                                      /* CH395网关 */
const UINT8 CH395IPMask[4] =   {255,255,255,0};                                                     /* CH395子网掩码 */
/* socket0 相关定义,SMTP发送邮件  */                      
const UINT8  Socket0DesIP[4] = {58,213,45,186};                                                     /* Socket 0目的IP地址 */
const UINT16 Socket0DesPort =  SMTP_SERVER_PORT;                                                    /* Socket 0目的端口*/
const UINT16 Socket0SourPort = 6212;                                                                /* Socket 0源端口 */
/*  {123,58,178,201}   "smtp.126.com"    */
/*  {123,58,178,204}  "smtp.163.com"    */
/*  {113,108,16,44}    "smtp.qq.com"    */
/*  {74,125,129,108}  "smtp.gmail.com" */
/* socket1 相关定义, POP收邮件*/                        
const UINT8  Socket1DesIP[4] =  {58,213,45,186};                                                     /* Socket 1目的IP地址*/
const UINT16 Socket1DesPort =  POP3_SERVER_PORT;                                                     /* Socket 1目的端口 */
const UINT16 Socket1SourPort = 8152;                                                                 /* Socket 1源端口   */
/*  {220,181,15,128}  "pop.126.com", */
/*  {220,181,12,101}  "pop.163.com", */
/*  {113,108,16,116}  "pop.qq.com",  */
/*  {74,125,141,108}  "pop.gmail.com"*/
/* smtp发送邮件相关参数 */
const UINT8  *m_Server =   "0000000";                                                                 /* 服务器名称  */
const UINT8  *m_UserName = "000";                                                                     /* 用户名    */
const UINT8  *m_PassWord = "00000000";                                                                /* 密码      */
const UINT8  *m_SendFrom = "000000000";                                                               /* 发件人地址  */
const UINT8  *m_SendName = "one";                                                                     /* 发送人名字  */
const UINT8  *m_SendTo =   "000000";                                                                  /* 收件人地址  */
const UINT8  *m_Subject =  "text";                                                                    /* 主题       */
const UINT8  *m_FileName = "m_file.txt";                                                              /* 附件名字(如果不发送附件,则置为"\0") */
/* pop接收邮件相关 */
const UINT8 *p_Server =   "00000000";                                                                 /* POP服务器       */
const UINT8 *p_UserName = "0000000";                                                                  /* POP登陆用户名    */
const UINT8 *p_PassWord = "0000000";                                                                  /* POP登陆密码    */

/***********************************************************************************/
UINT8   ReceDatFlag = 0;                                                                              /* 收到数据标志位*/
UINT8   SendDatFalg = 0;     
UINT8   CheckType;                                                                                    /* 握手信号核对类型*/ 
UINT8   OrderType;                                                                                    /* 命令类型    */
UINT16   ReceLen;                                                                                     /* 接收缓冲区接收到的数据长度 */
/***********************************************************************************
* Function Name  : main
* Description    : 主函数
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
void main(  )
{
  ch395mail( );
#ifdef send_mail 
  ch395mail_smtpinit( );
  if( send_mail )   CH395SocketInitOpen( SendSocket );
#endif
#ifdef  receive_mail
  ch395mail_pop3init( );
  if( receive_mail )   CH395SocketInitOpen( ReceSocket );
#endif
  while(1){
    if(CH395_INT_WIRE == 0) CH395GlobalInterrupt();
    if(ReceDatFlag){
      ReceDatFlag = 0;
      ch395mail_MailCommand( OrderType );    
#ifdef  POP_RTER 
      if(OrderType == POP_RECEIVE_RTER ) ch395mail_pop3Retr( '1' );                                   /* 处理server邮件的全部文本内容  （输入邮件号）*/
#endif
#ifdef  POP_DELE 
      if(OrderType == POP_RECEIVE_DELE ) ch395mail_pop3Dele( '1' );                                   /* 处理server标记删除，QUIT命令执行时才真正删除（输入邮件号）*/
#endif
#ifdef  POP_RSET 
      if(OrderType == POP_RECEIVE_RSET ) ch395mail_pop3Rset(  );                                      /* 处理撤销所有的DELE命令  */
#endif
#ifdef  POP_TOP 
      if(OrderType == POP_RECEIVE_TOP ) ch395mail_pop3Top( '1','3' );                                 /* 返回n号邮件的前m行内容（输入邮件号，行号（必须为自然数））*/
#endif
#ifdef  POP_UIDL 
      if(OrderType == POP_RECEIVE_UIDL ) ch395mail_pop3Uidl( '1' );                                   /* 处理server返回用于该指定邮件的唯一标识，如果没有指定，返回所有的。（输入邮件号）*/
#endif
    }
  }
}