/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395FTPINC.H
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395FTP.c头文件说明
**********************************************************************************/
#ifndef __FTPINC_H__
#define __FTPINC_H__
/**********************************************************************************/
#define DEBUG            1                                                 /* 调试  （晶振22.1184Mhz。波特率115200）*/
#ifndef Access_Authflag
#define Access_Authflag        0                                           /* 设置指定用户名访问（其他用户名无法访问服务器）*/
#endif
/**********************************************************************************/
typedef struct _FTP
{
  UINT8 TimeCount;                                                         /* 定时器计数*/
  UINT8 FileFlag;                                                          /* 判断文件长度大于64字节标志位（本程序支持最大上传文件长度64）*/
  UINT8 BufStatus;                                                         /* 缓冲区标志位（0-3位分别对应四个缓冲区状态，0为空1为被使用）*/
  UINT8 AuthFlag;                                                          /* 用户权限标志位*/
  UINT8 ListFlag;          
  UINT8 CmdDataS;                                                          /* 数据传输状态*/
  UINT8 CmdReceDatS;                                                       /* 接收数据状态*/
  UINT8 DataOver;                                                          /* 数据读取完毕	*/
  UINT8 CmdPortS;
  UINT8 CmdPasvS;
  UINT8 ListState;                                                         /* 0为当前目录 1为下一级目录*/
  UINT8 TcpCtlSta;                                                         /* TCP控制连接状态*/
  UINT8 TcpDatSta;                                                         /* TCP数据连接状态 */
  UINT8 SocketCtl;                                                         /* ftp控制连接*/
  UINT8 SocketDat;                                                         /* ftp数据连接*/
}FTP;
extern   char  UserName[16];                                               /* 用于保存用户名*/
extern   char   SourIP[17];                                                /* 用于保存转换成字符的IP地址*/
#if Access_Authflag
extern   char  *pUserName;                                                 /* 可以访问服务的用户名（其他用户名无法访问服务器）*/
#endif
extern   char  *pPassWord;                                                 /* 有权限的密码（其他密码只支持读）*/
/* TCP连接状态 */
#define FTP_MACH_DISCONT           0x01                                    /* TCP未连接*/
#define FTP_MACH_CONNECT           0x02                                    /* TCP连接上*/
#define FTP_MACH_KEPCONT           0x04                                    /* TCP保持连接*/
/*  数据传输状态 */
#define FTP_MACH_SENDDATA           0x01                                   /* 需要发送数据*/
#define FTP_MACH_RECEDATA           0x02                                   /* 需要接收数据*/
#define FTP_MACH_DATAOVER           0x04                                   /* 数据传输完成*/
#define FTP_MACH_CLOSECTL           0x08                                   /* 发完命令*/
#define FTP_MACH_LIST               0x00                                   /* 获取列表*/
#define FTP_MACH_FILE               0x01                                   /* 操作文件*/
#define FTP_CMD_SUCCESS              0x00                                  /* 获取列表*/
#define FTP_CMD_ERROR               0x01                                   /* 操作文件*/

/**********************************************************************************/
void CH395_FTPSendData( char *PSend, UINT16 Len,UINT8 index  );            /* 发送数据*/
   
void CH395_FTPConnect( void );                                             /* 395初始化*/

void CH395_FTPInitVari( );                             

void CH563NET_FTPGetSockeID( UINT8 socketid );                   

void  mInitFtpList( void );                            

void CH395_FTPListRenew( UINT8 index );                      
                  
void CH395_FTPProcessReceDat( char *recv_buff,UINT8 index );               /* 处理接收到的数据*/

void CH395_FTPCmdRespond( char *recv_buff );                               /* 检测接收到的命令做出相应的回复*/ 

void CH395_FTPDataReady( char *pSendDat );                                 /* 准备要发送的数据*/

void CH395_FTPGetPortNum( char *recv_buff );                               /* 获取进行连接的端口*/

void CH395_FTPGetFileName( char *recv_buff,char *pBuf );      

UINT8 CH395_FTPFileOpen(  char *pName,UINT8 index  );                      /* 打开文件*/

UINT32 CH395_FTPFileSize ( char *pName );                                  /* 获取文件长度*/
          
void CH395_FTPFileRead( char *pName );                                     /* 读文件*/

void CH395_FTPFileWrite( char *recv_buff, UINT16 LEN );                    /* 写文件*/

void CH395_FTPCtlServer( UINT8 socketid );                                 /* 创建FTP控制连接*/

void CH395_FTPDatClient( UINT8 socketid,UINT16 port,UINT8 *pAddr );        /* 创建FTP客户端数据连接*/
                            
void CH395_FTPDatServer( UINT8 socketid,UINT16 *port );                    /* 创建FTP服务器数据连接*/

void CH395_FTPGetSockeID( UINT8 socketid  );                               /* 获取数据连接socket索引*/

void CH395_FTPServerCmd( void );                                           /* 查询状态，执行相应的子程序*/
#endif  
 /**********************************************************************************/
