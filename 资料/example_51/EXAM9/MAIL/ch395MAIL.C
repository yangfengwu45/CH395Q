/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395MAIL.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片用于收发邮件
**********************************************************************************/
#include <reg52.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../PUB/CH395INC.H"
#include "../PUB/CH395CMD.H"
#include "mailinc.h"
#include "ch395.h"
#include "mail.h"
#include "ch395mailcmd.c"

#ifdef  receive_over_reply
const  UINT8 *g_mailbody =   "welcome.";                                                       /* 回复邮件正文内容，可修改*/
const  UINT8 *g_autograph1 = "\r\n\r\nBest Regards!\r\n----- Original Message ----\r\n";       /* 回复邮件签名栏部分内容*/
const  UINT8 *g_autograph2 = "\r\nweb:http://www.wch.cn\r\n";                                  /* 回复邮件签名栏部分内容*/
UINT8 data  macaddr[6];                                                                        /* 保存mac地址（16进制数据）*/
UINT8 data  macaddrchar[18];                                                                   /* 用于保存转换后的mac地址字符*/
UINT8   R_argv[3][32];                                                                         /* 用于保存解析的邮件的信息*/
#endif  
/**********************************************************************************
* Function Name  : ch395mail_pop3init
* Description    : 接收邮件初始化
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
#ifdef receive_mail
void ch395mail_pop3init( )
{
  p_pop3 = &m_pop3;
  memset( p_pop3, '\0', sizeof(POP) );
  strcpy( p_pop3->pPop3Server,   p_Server );                                                   /* 服务器名称*/
  strcpy( p_pop3->pPop3UserName, p_UserName );                                                 /* 用户名*/
  strcpy( p_pop3->pPop3PassWd,   p_PassWord );                                                 /* 密码 */ 
}
#endif   
/******************************************************************************/
#ifdef send_mail
/**********************************************************************************
* Function Name  : ch395mail_smtpinit
* Description    : 发送邮件初始化
* Input          : type 用于判断是手动设置发送，还是回复邮件发送
* Output         : None
* Return         : None
**********************************************************************************/
void ch395mail_smtpinit(  )
{
  p_smtp = &m_smtp;
  p_smtp->g_MIME = 0;
  memset( p_smtp, '\0', sizeof(SMTP) );
  strcpy( p_smtp->m_strSMTPServer, m_Server );                                                  /* 服务器名称*/
  strcpy( p_smtp->m_strUSERID,m_UserName );                                                     /* 用户名*/
  strcpy( p_smtp->m_strPASSWD,m_PassWord );                                                     /* 密码 */   
  strcpy( p_smtp->m_strSendFrom,m_SendFrom );                                                   /* 发件人地址*/
  strcpy( p_smtp->m_strSenderName, m_SendName );                                                /* 发送人名字*/
#ifdef receive_over_reply
  strcpy( p_smtp->m_strSendTo,R_argv[0] );                                                      /* 收件人地址*/
  strcpy( p_smtp->m_strSubject,R_argv[1] );                                                     /* 主题*/
  strcpy(  p_smtp->m_strFile,R_argv[2] );                                                       /* 附件名字(如果不发送附件，此处不需初始化)*/
#else 
  strcpy( p_smtp->m_strSendTo,m_SendTo );                                                       /* 收件人地址*/
  strcpy( p_smtp->m_strSubject,m_Subject );                                                     /* 主题*/
  strcpy( p_smtp->m_strFile,m_FileName );                                                       /* 附件名字(如果不发送附件，此处不需初始化)*/
#endif 
}

/**********************************************************************************
* Function Name  : ch395mail_replybody
* Description    : 分析回复邮件正文内容,内容可修改
* Input          : None
* Output         : None
* Return         : None
**********************************************************************************/
#ifdef receive_over_reply
void ch395mail_replybody( ) 
{
  memset( MailBodyData,'\0',sizeof(MailBodyData));
  QuotedPrintableEncode( (UINT8 *)"Hello" ,MailBodyData, strlen("Hello"),76 );
  strcat( send_buff, MailBodyData );
  strcat( send_buff, "\r\n    " );
  strcat( send_buff, p_pop3->DecodeRName );
  strcat( send_buff, "!" );
  memset( MailBodyData,'\0',sizeof(MailBodyData));
  QuotedPrintableEncode( (UINT8 *)g_mailbody ,MailBodyData, strlen(g_mailbody),76 );
  strcat( send_buff, MailBodyData );
  if(p_pop3->identitycheck == 1){
    memset( macaddr, '\0', sizeof(macaddr) );
    memset( macaddrchar, '\0', sizeof(macaddrchar) );
    CH395CMDGetMACAddr(macaddr);
    ch395mail_xtochar(macaddr,&macaddrchar[0],strlen(macaddr));
#if DEBUG  
  printf("B len= %02X\n",(UINT16)strlen(macaddrchar));
#endif
    if(strlen(macaddrchar)>17) macaddrchar[17] = '\0';
    strcat( send_buff, "\r\n" );
    memset( MailBodyData,'\0',sizeof(MailBodyData));
     QuotedPrintableEncode( (UINT8 *)"I am ", MailBodyData, strlen("I am "),76 );
    strcat( send_buff, MailBodyData );
    memset( MailBodyData,'\0',sizeof(MailBodyData));
     QuotedPrintableEncode( (UINT8 *)macaddrchar, MailBodyData, strlen(macaddrchar),76 );
    strcat( send_buff, MailBodyData );
    strcat( send_buff, "。\r\n" );
  }
  strcat( send_buff, g_autograph1 );
  strcat( send_buff, "From: \"" );
  strcat( send_buff, p_pop3->DecodeRName );
  strcat( send_buff, "\" <" );
  strcat( send_buff, R_argv[0] );
  strcat( send_buff, ">\r\n" );
  strcat( send_buff, "To: ");
  strcat( send_buff, p_smtp->m_strSendFrom );
   strcat( send_buff, "\r\n" );
  if(strlen(p_pop3->Ccname)){
    strcat( send_buff, "Cc: ");
    strcat( send_buff, p_pop3->Ccname);
     strcat( send_buff, "\r\n" );
  }
  strcat( send_buff, "Sent: ");
  strcat( send_buff, p_pop3->sBufTime );
  strcat( send_buff, "\r\nSubject: ");
  strcat( send_buff, p_smtp->m_strSubject );
  strcat( send_buff, g_autograph2 );
}
#endif  
/******************************************************************************/
#endif  
/*********************************************************************************
* Function Name  : ch395mail_analysemaildata
* Description    : 分析接收到的邮件
* Input          : recv_buff-邮件内容
* Output         : None
* Return         : None
**********************************************************************************/
#ifdef receive_over_reply
void ch395mail_analysemaildata( char *recv_buff ) 
{
   UINT16  i,j;
  char AttachEncodetype;
  char conreceiveattach;  

  if(conreceiveattach){
    i = 0;
    if(AttachEncodetype==2) goto type2;                                                        /*  跳转到附件接收 编码方式--quoted-printable*/
    if(AttachEncodetype==1) goto type1;                                                        /*  跳转到附件接收 编码方式--base64*/
    if(AttachEncodetype==0) goto type0;                                                        /*  跳转到附件接收 编码方式--others*/
  }
  for(i=0;i<ReceLen;i++){
/* 发件人名字/地址 */        
    if( strncmp("\nFrom: ", &recv_buff[i], 7) == 0 ){
      i += 7;
#if DEBUG
  printf("1#From \n");
#endif
      if(recv_buff[i] == '"') i++;  
      if(recv_buff[i] == '='){                                                                  /* 名字经过编码*/
        while(strncmp("?B?", &recv_buff[i], 3)&&(i < ReceLen)) i++;
        i += 3;
        j = 0;
        memset( send_buff, '\0', sizeof(send_buff) );
        while((recv_buff[i] != '=')&&(recv_buff[i] != '?')&&(i < ReceLen)){
          send_buff[j] = recv_buff[i];
          j++;
          i++;      
        }
        memset( p_pop3->DecodeRName, '\0', sizeof(p_pop3->DecodeRName) );
        Base64Decode(send_buff,  strlen(send_buff),p_pop3->DecodeRName);
#if DEBUG
  printf("DecName:%s\n", p_pop3->DecodeRName);
#endif
      }
      else{  /* 名字未编码*/
        j = 0;
        while((recv_buff[i] != '"')&&(i < ReceLen)){
          p_pop3->DecodeRName[j] = recv_buff[i];
          j++;
          i++;      
        }
      }             
      while((recv_buff[i] != '<')&&(i < ReceLen)) i++;
      i++;
      j = 0;
      while((recv_buff[i] != '>')&&(i < ReceLen)){
        R_argv[0][j] = recv_buff[i];
        j++;
        i++; 
      }
    }
// 抄送
    if( strncmp("\nCc: ", &recv_buff[i], 5) == 0 ){
      i += 5;
#if DEBUG
  printf("2#Cc \n");
#endif    
      while(recv_buff[i] != '<')  i++;
      i++;
      j = 0;
      while(recv_buff[i] != '>'&&(i < ReceLen)){                                               /* 抄送人的地址*/
        p_pop3->Ccname[j] = recv_buff[i];
        j++;
        i++;      
      }
    }
// 日期
    if( strncmp("\nDate: ", &recv_buff[i], 7) == 0 ){
      i += 7;
#if DEBUG
  printf("3#date \n");
#endif
      j = 0;
      while((recv_buff[i] != '\r')&&(i < ReceLen)){                                            /* 发送邮件日期*/
        p_pop3->sBufTime[j] = recv_buff[i];
        j++;
        i++;      
      }
    }
// 主题
    if( strncmp("\nSubject: ", &recv_buff[i], 10) == 0 ){
      i += 10;
#if DEBUG
  printf("4#Subject \n");
#endif
      if(recv_buff[i] == '[') {
        while(recv_buff[i] == ']'&&(i < ReceLen)) i++;
        i += 2;
      }
      if(recv_buff[i] == '='){
        while(strncmp("?B?", &recv_buff[i], 3)&&(i < ReceLen)) i++;                            /* 主题经过编码*/
        i += 3;
        j = 0;
        memset( send_buff, '\0', sizeof(send_buff) );
        while((recv_buff[i] != '=')&&(recv_buff[i] != '?')&&(i < ReceLen)){                    /* 邮件的主题*/
          send_buff[j] = recv_buff[i];
          j++;
          i++;    
        }
        Base64Decode(send_buff,strlen(send_buff),R_argv[1]);
#if DEBUG
  printf("Decodesubject:%s\n", R_argv[1]);
#endif
      }
      else{                                                                                    /* 未编码*/
        j = 0;
        while(recv_buff[i] != '\r'&&(i < ReceLen)){                                            /* 邮件的主题*/
          R_argv[1][j] = recv_buff[i];
          j++;
          i++;    
        }
      }
    }
/* 附件的编码方式、名字、内容*/
    if( strncmp("name=", &recv_buff[i], 5) == 0 ){
#if DEBUG
  printf("5#\n");
#endif
      i += 5;
      while(strncmp("Content-Transfer-Encoding: ", &recv_buff[i], 27)&&strncmp("filename=", &recv_buff[i], 9)&&(i < ReceLen)) i++;
      if(strncmp("Content-Transfer-Encoding: ", &recv_buff[i], 27) == 0){
/* 编码方式*/
        i += 27;
        if(strncmp("base64", &recv_buff[i], 6) == 0 ){
#if DEBUG
  printf("5#base64 \n");
#endif
          i += 6;
          AttachEncodetype = 1;
        }
        else if(strncmp("quoted-printable", &recv_buff[i], 16) == 0 ) {
#if DEBUG
  printf("5#quoted-printable \n");
#endif
          i += 16;
          AttachEncodetype = 2;
        }
        else AttachEncodetype = 0;  
/* 附件名字*/
        while(strncmp("filename=", &recv_buff[i], 9)) i++;
        i += 9;
        while(recv_buff[i] != '"'&&i<ReceLen) i++;
        i++;
#if DEBUG
  printf("6#filename \n");
#endif
        if(recv_buff[i] == '='){
          while(strncmp("?B?", &recv_buff[i], 3)&&(i < ReceLen)) i++;
          i += 3;
          j = 0;
          memset(send_buff,'\0', sizeof(send_buff) );
          while((recv_buff[i] != '=')&&(recv_buff[i] != '?')&&(i < ReceLen)){
            send_buff[j] = recv_buff[i];
            j++;
            i++;    
          }
          Base64Decode(send_buff,  strlen(send_buff),R_argv[2]);
        }
        else{
          j = 0;
          while(recv_buff[i] != '"'&&(i < ReceLen)){
            R_argv[2][j] = recv_buff[i];
            j++;
            i++;      
          }
        }
      }
/* 附件名字*/
      else if( strncmp("filename=", &recv_buff[i], 9) == 0 ){
#if DEBUG
  printf("6#filename \n");
#endif
        i += 9;
        while(recv_buff[i] != '"'&&i<ReceLen) i++;
        i++;
        if(recv_buff[i] == '='){
          while(strncmp("?B?", &recv_buff[i], 3)&&(i < ReceLen)) i++;
          i += 3;
          j = 0;
          memset(send_buff,'\0', sizeof(send_buff) );
          while((recv_buff[i] != '=')&&(recv_buff[i] != '?')&&(i < ReceLen)){
            send_buff[j] = recv_buff[i];
            j++;
            i++;    
          }
          Base64Decode(send_buff,  strlen(send_buff),R_argv[2]);
        }
        else{
          j = 0;
          while(recv_buff[i] != '"'&&(i < ReceLen)){
            R_argv[2][j] = recv_buff[i];
            j++;
            i++;      
          }
        }
/* 附件编码方式*/
        while(strncmp("Content-Transfer-Encoding: ", &recv_buff[i], 27)) i++;
        i += 27;
        if(strncmp("base64", &recv_buff[i], 6) == 0 ){
#if DEBUG
  printf("5#base64 \n");
#endif
          i += 6;
          AttachEncodetype = 1;
        }
        else if(strncmp("quoted-printable", &recv_buff[i], 16) == 0 ) {
#if DEBUG
  printf("5#quoted-printable \n");
#endif
          i += 16;
          AttachEncodetype = 2;
        }
        else AttachEncodetype = 0;  
      }
/* 附件内容*/
      while( strncmp("\n\r\n", &recv_buff[i], 3) != 0 &&(i < ReceLen)) i++;
      i += 3;
      if(AttachEncodetype==1){  
        j = 0;
        memset(send_buff,'\0', sizeof(send_buff) );
type1:      while((recv_buff[i] != '=')&&strncmp("\r\n--", &recv_buff[i], 4)&&strncmp("\r\n\r\n", &recv_buff[i], 4)&&(i < ReceLen)&&(j<attach_max_len)){
          send_buff[j] = recv_buff[i];
          j++;
          i++;      
        }
        if(i>=ReceLen-1) conreceiveattach = 1;
        else {
          conreceiveattach = 0;
          Base64Decode(send_buff,  strlen(send_buff),AttachmentData);
        }
      }
      else if(AttachEncodetype==2){   
        j = 0;
        memset(send_buff,'\0', sizeof(send_buff));
type2:      while(strncmp("\r\n.\r\n", &recv_buff[i], 5)&&strncmp("\r\n--", &recv_buff[i], 4)&&(i < ReceLen)&&(j<attach_max_len)){
          send_buff[j] = recv_buff[i];
          j++;
          i++;      
        }
        if(i>=ReceLen-1) conreceiveattach = 1;
        else {
          conreceiveattach = 0;
          QuotedPrintableDecode(send_buff,(char *)AttachmentData, strlen(send_buff));
        }
      }
      else{  
#if DEBUG
  printf("7# \n");
#endif
        j = 0;
type0:      while(recv_buff[i] != '\r'&&(i < ReceLen)&&(j<attach_max_len)){
          AttachmentData[j] = recv_buff[i];
          j++;
          i++;      
        }
        if(i>=ReceLen-1) conreceiveattach = 1;
        else conreceiveattach = 1; 
      }
    }
  }
#if DEBUG
  printf("addr:\n %s\n",R_argv[0]);                                                            /* 发送人的地址*/
  printf("send name:\n %s\n",p_pop3->DecodeRName);                                             /* 发送人名字*/
  printf("subject:\n %s\n",R_argv[1]);                                                         /* 邮件主题*/
  printf("attach name:\n%s\n",R_argv[2]);                                                      /* 附件名字*/
  printf("send time:\n %s\n",p_pop3->sBufTime);                                                /* 发送时间*/
  printf("attach text:\n%s\n",AttachmentData);                                                 /* 附件内容*/
#endif
  if(p_pop3->analysemailflag){
    if(strncmp("wch", AttachmentData, 3) == 0) p_pop3->identitycheck = 1;
    else p_pop3->identitycheck = 0;
#if DEBUG
  printf("11# \n");
#endif
    ch395mail_smtpinit(  );
  }
}
#endif  
/**********************************************************************************
* Function Name  : ch395mail_CheckResponse
* Description    : 验证握手信号
* Input          : recv_buff-握手信息
                   check_type-检测的类型
* Output         : None
* Return         : None
**********************************************************************************/
UINT8 ch395mail_CheckResponse( UINT8 *recv_buff,UINT8 check_type )
{
  switch(check_type){
#ifdef send_mail
    case SMTP_CHECK_CNNT:   
      if( strncmp("220", recv_buff, 3) == 0 ){
        OrderType = SMTP_SEND_HELO;
        return (CHECK_SUCCESS);
      }
      return SMTP_ERR_CNNT;
    case SMTP_CHECK_HELO:   
      if( strncmp("250", recv_buff, 3) == 0 ){
        OrderType = SMTP_SEND_AUTH;
        return (CHECK_SUCCESS);
      }
      return SMTP_ERR_HELO;
    case SMTP_CHECK_AUTH:                                                                      /* 登陆命令*/
      if(strncmp("250", recv_buff, 3) == 0){
        OrderType = COMMAND_UNUSEFULL;
        return (CHECK_SUCCESS);
      }
      if(strncmp("334", recv_buff, 3) == 0){
        OrderType = SMTP_SEND_USER;
        return (CHECK_SUCCESS);
      }
      return SMTP_ERR_AUTH;
    case SMTP_CHECK_USER:                                                                      /* 用户名*/
      if(strncmp("334", recv_buff, 3) == 0){
        OrderType = SMTP_SEND_PASS;
        return (CHECK_SUCCESS);
      }
      return SMTP_ERR_USER;
    case SMTP_CHECK_PASS:                                                                      /* 密码*/
      if(strncmp("235", recv_buff, 3) == 0){
        OrderType = SMTP_SEND_MAIL;
        return (CHECK_SUCCESS);
      }
      return SMTP_ERR_PASS;
    case SMTP_CHECK_MAIL:                                                                      /* 发送者*/
      if(strncmp("250", recv_buff, 3) == 0){
        OrderType = SMTP_SEND_RCPT;
        return (CHECK_SUCCESS);  
      } 
      return SMTP_ERR_MAIL;
    case SMTP_CHECK_RCPT:                                                                      /* 接收*/
      if(strncmp("250", recv_buff, 3) == 0){
        OrderType = SMTP_SEND_DATA;
        return (CHECK_SUCCESS);      
      }
      return SMTP_ERR_RCPT;
    case SMTP_CHECK_DATA:                                                                      /* data 命令*/
      if(strncmp("354", recv_buff, 3) == 0){
        OrderType = SMTP_DATA_OVER;
        return (CHECK_SUCCESS);
      } 
      return SMTP_ERR_DATA;
    case SMTP_CHECK_DATA_END:                                                                  /* 数据发送完成*/
      if(strncmp("250", recv_buff, 3) == 0){
#ifdef  send_over_receive
        OrderType = POP_RECEIVE_START;
#endif
#ifdef  send_over_quit
        OrderType = SMTP_SEND_QUIT;
#endif
        return (CHECK_SUCCESS);
      }
      return SMTP_ERR_DATA_END;
    case SMTP_CHECK_QUIT:                                                                      /* 退出登陆*/
      if(strncmp("220", recv_buff, 3) == 0||strncmp("221", recv_buff, 3) == 0){
        OrderType = SMTP_CLOSE_SOCKET;
        return (CHECK_SUCCESS);
      }
      return SMTP_ERR_QUIT;
#endif 
#ifdef receive_mail
    case POP_CHECK_CNNT:                                                                       /* 用户名*/
      if(strncmp("+OK", recv_buff, 3) == 0){
        OrderType = POP_RECEIVE_USER;
        return (CHECK_SUCCESS);
      }
      return POP_ERR_CNNT;
    case POP_CHECK_USER:                                                                       /* 用户名*/
      if(strncmp("+OK", recv_buff, 3) == 0){
        OrderType = POP_RECEIVE_PASS;
        return (CHECK_SUCCESS);
      }
      return POP_ERR_USER;
    case POP_CHECK_PASS:                                                                       /* 密码*/
      if(strncmp("+OK", recv_buff, 3) == 0){
        OrderType = POP_RECEIVE_STAT;
        return (CHECK_SUCCESS);
      }
      return POP_ERR_PASS;
    case POP_CHECK_STAT:                                                                       /* 总邮件信息*/
      if(strncmp("+OK", recv_buff, 3) == 0){
        OrderType = POP_RECEIVE_LIST;
        return (CHECK_SUCCESS);  
      } 
      return POP_ERR_STAT;
    case POP_CHECK_LIST:                                                                       /* 邮件列表*/
      if((strncmp("+OK", recv_buff, 3) == 0)){
        OrderType = COMMAND_UNUSEFULL;
        return (CHECK_SUCCESS);
      }
      if((strncmp(".", recv_buff, 1) == 0)){
        p_pop3->RefreshTime = 1;
        OrderType = POP_RECEIVE_QUIT;
        return (CHECK_SUCCESS);
      }
      if((strncmp("1", recv_buff, 1) == 0)){
        p_pop3->RefreshTime = 0;
#ifdef  receive_over_reply
        OrderType = POP_RECEIVE_RTER;
#endif
#ifdef  receive_over_quit  
        OrderType = POP_RECEIVE_QUIT;
#endif
#ifdef  receive_dele_quit
        OrderType = POP_RECEIVE_RTER;
#endif
        return (CHECK_SUCCESS);
      }
      return POP_ERR_LIST;
    case POP_CHECK_QUIT:                                                                       /* 退出登陆*/
      if(strncmp("+OK", recv_buff, 3) == 0){
#ifdef  POP_REFRESH
        if(p_pop3->RefreshTime){
          mDelaymS(200);
          mDelaymS(200);
          OrderType = POP_RECEIVE_START;
        } 
        else OrderType = POP_CLOSE_SOCKET; 
#else
        OrderType = POP_CLOSE_SOCKET;
#endif   
        return (CHECK_SUCCESS);
      }
      return POP_ERR_QUIT;
    case POP_CHECK_RETR:                                                                       /* 读取邮件内容*/ 
      if(strncmp("+OK", recv_buff, 3) == 0){
        OrderType = COMMAND_UNUSEFULL;  
#ifdef  receive_over_reply
        memset(AttachmentData,'\0',sizeof(AttachmentData));
        memset(R_argv,'\0',sizeof(R_argv));
        memset( p_pop3, '\0', sizeof(POP) );
#endif
        return (CHECK_SUCCESS);
      } 
      else if(strncmp("-ERROR", recv_buff, 6) != 0){
        if( strncmp("\r\n.\r\n", &recv_buff[ReceLen-5], 5) == 0 ){
#ifdef  receive_dele_quit
        OrderType = POP_RECEIVE_DELE;
#endif  
#ifdef  receive_over_quit  
        OrderType = POP_RECEIVE_QUIT;  
#endif

#ifdef  receive_over_reply
          p_pop3->analysemailflag = 1;                                                         /* 接收邮件完成标志*/
          ch395mail_analysemaildata( recv_buff );                                              /* 分析邮件内容*/
          OrderType = SMTP_SEND_START;
        }
        else{
          p_pop3->analysemailflag = 0;
          ch395mail_analysemaildata( recv_buff );
#endif   
        }
        return (CHECK_SUCCESS);
      } 
      return POP_ERR_RETR;
    case POP_CHECK_DELE:                                                                       /* 删除*/
      if(strncmp("+OK", recv_buff, 3) == 0){
        OrderType = POP_RECEIVE_QUIT;                                                          /* 执行完后不执行其他命令，如需可自行选择下一条命令*/
        return (CHECK_SUCCESS);
      }
      return POP_ERR_DELE;
    case POP_CHECK_RSET:                                                                       /* 撤销删除*/ 
      if(strncmp("+OK", recv_buff, 3) == 0){
        OrderType = POP_RECEIVE_QUIT;                                                          /* 执行完后不执行其他命令，如需可自行选择下一条命令*/
        return (CHECK_SUCCESS);
      }
      return POP_ERR_RSET;
    case POP_CHECK_TOP:                                                                        /* 获取邮件前n行*/ 
      if(strncmp("+OK", recv_buff, 3) == 0){
        OrderType = POP_RECEIVE_QUIT;                                                          /* 执行完后不执行其他命令，如需可自行选择下一条命令*/
        return (CHECK_SUCCESS);
      }
      if(strncmp("Return", recv_buff, 6) == 0){
        OrderType = POP_RECEIVE_QUIT;                                                          /* 执行完后不执行其他命令，如需可自行选择下一条命令*/
        return (CHECK_SUCCESS);
      } 
      return POP_ERR_TOP;
    case POP_CHECK_UIDL:                                                                       /* 获取邮件唯一标识符*/
      if(strncmp("+OK", recv_buff, 3) == 0){
        OrderType = POP_RECEIVE_QUIT;                                                          /* 执行完后不执行其他命令，如需可自行选择下一条命令*/
        return (CHECK_SUCCESS);
      }
      return POP_ERR_UIDL;
#endif  
    default:
      return SMTP_ERR_UNKNOW;
  }
}
