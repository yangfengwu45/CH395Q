/********************************** (C) COPYRIGHT *********************************
* File Name          : MAIL.H
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : ch395mail.c数据结构定义
**********************************************************************************/
#ifndef __mail_H__
#define __mail_H__

typedef struct
{
  UINT8 g_MIME;                                                                  /* 有无附件标志位*/
  UINT8  m_strFile[48];                                                           /* 附件名字*/
  UINT8  m_strSendFrom[48];                                                       /* 发件人地址*/
  UINT8  m_strSendTo[48];                                                         /* 收件人地址*/
  UINT8  m_strSMTPServer[32];                                                     /* 服务器名称*/
  UINT8  m_strUSERID[32];                                                         /* 用户名*/
  UINT8  m_strPASSWD[32];                                                         /* 密码*/
  UINT8  m_strSubject[32];                                                        /* 主题*/
  UINT8  m_strSenderName[32];                                                     /* 发送人名字*/
}SMTP;
typedef struct
{
  UINT8  analysemailflag;                                                         /* 分析邮件结束标志位*/
  UINT8  identitycheck;                                                           /* 验证附件内容标志位*/
  UINT8  RefreshTime;                                                             /* 没搜查到邮件继续搜索标志位*/
  UINT8  sBufTime[40];                                                            /* 保存接收邮件的时间*/
  UINT8  Ccname[48];                                                              /* 抄送的名字*/
  UINT8  DecodeRName[32];                                                         /* 保存接收到邮件解码后的发件人名字*/
  UINT8 pPop3Server[32];                                                          /* POP服务器*/
  UINT8 pPop3UserName[32];                                                        /* POP登陆用户名*/
  UINT8 pPop3PassWd[32];                                                          /* POP登陆密码*/
}POP;
const  UINT8 code SMTP_CLIENT_CMD[5][11] =                                       /*SMTP CMD Codes*/
{
  "EHLO",                                                                        /* 0 退出*/
  "AUTH LOGIN",                                                                  /* 1 登陆*/
  "MAIL FROM:",                                                                  /* 2 发件人地址*/
  "RCPT TO:",                                                                    /* 3 收件人地址*/
  "DATA",                                                                        /* 4 开始发送数据命令*/
};
const UINT8 code POP3_CLIENT_CMD[12][5] =                                        /*POP3 CMD Codes*/
{
  /* basic POP3 commands*/
  "QUIT",                                                                        /* 0 退出*/
  "USER",                                                                        /* 1 用户名*/
  "PASS",                                                                        /* 2 密码*/
  "STAT",                                                                        /* 3 邮箱统计资料*/
  "LIST",                                                                        /* 4 返回指定邮件的大小*/
  "RETR",                                                                        /* 5 邮件的全部文本*/
  "DELE",                                                                        /* 6 标记删除*/
  "RSET",                                                                        /* 7 撤销所有的DELE命令*/
  "NOOP",                                                                        /* 8 返回一个肯定的响应*/
  /* alternative POP3 commands*/
  "APOP",                                                                        /* 9  认证一种安全传输口令的办法，执行成功导致状态转换*/
  "TOP" ,                                                                        /* 10 处理返回n号邮件的前m行内容，m必须是自然数*/
  "UIDL"                                                                         /* 11 返回用于该指定邮件的唯一标识*/
};
/* smtp发送邮件相关参数 */
extern const UINT8 *m_Server;                                                    /* 服务器名称*/
extern const UINT8  *m_UserName;                                                 /* 用户名*/
extern const UINT8  *m_PassWord;                                                 /* 密码*/
extern const UINT8  *m_SendFrom;                                                 /* 发件人地址*/
extern const UINT8  *m_SendName;                                                 /* 发送人名字*/
extern const UINT8  *m_SendTo;                                                   /* 收件人地址*/
extern const UINT8  *m_Subject;                                                  /* 主题*/
extern const UINT8  *m_FileName;                                                 /* 附件名字(如果不发送附件,则置为"\0")*/
/* pop接收邮件相关 */
extern const UINT8  *p_Server;                                                   /* POP服务器*/
extern const UINT8  *p_UserName;                                                 /* POP登陆用户名*/
extern const UINT8  *p_PassWord;                                                 /* POP登陆密码*/
#endif
