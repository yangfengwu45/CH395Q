/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395FTP.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片FTP服务器应用-FTP命令代码
**********************************************************************************/
#include <reg52.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../PUB/CH395INC.H"
#include "../PUB/CH395CMD.H"
#include "CH395FTPINC.H"
#include "CH395FTPCMD.C"
#include "CH395FTPFILE.C"

/*******************************************************************************
* Function Name  : CH395_FTPSendData
* Description    : 准备好要发送的数据
* Input          : pName - 文件名（如为需要获取列表信息发送为字符0）
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_FTPDataReady( char *pName )
{
     ftp.CmdDataS = FTP_MACH_SENDDATA;
     CH395_FTPFileRead( pName );                                                  /* 将要发送的数据写入发送缓冲区*/
}

/******************************************************************************
* Function Name  : CH395_FTPProcessReceDat
* Description    : 处理接收到的数据
* Input          : recv_buff- 握手信息
                   sockeid  - socket索引
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_FTPProcessReceDat( char *recv_buff,UINT8 sockeid )
{
     if( sockeid == ftp.SocketDat ){
          if(ftp.CmdDataS == FTP_MACH_RECEDATA){                                  /* 接受文件数据*/
               CH395_FTPFileWrite(recv_buff,(UINT16)strlen(recv_buff));
          }
     }
     if( sockeid == ftp.SocketCtl ){                                              /* 接收命令     */          
          CH395_FTPCmdRespond(recv_buff);
     }     
}

/******************************************************************************
* Function Name  : CH395_FTPServerCmd
* Description    : 查询状态，执行相应的命令
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_FTPServerCmd( )
{
     UINT8 i;

     if(ftp.TcpCtlSta == FTP_MACH_CONNECT){                                      /* 建立TCP FTP控制连接*/
          ftp.TcpCtlSta = FTP_MACH_KEPCONT; 
          CH395_FTPSendData( (char *)FTP_SERVICE_CMD[0],strlen(FTP_SERVICE_CMD[0]),ftp.SocketCtl );
     }
     if(ftp.TcpDatSta == FTP_MACH_CONNECT){                                      /* ch395建立数据连接*/
          if( ftp.CmdPortS == 1 ){
               ftp.CmdPortS = 0;
               CH395_FTPSendData( (char *)FTP_SERVICE_CMD[5],strlen(FTP_SERVICE_CMD[5]),ftp.SocketCtl );
          }
          else if( ftp.CmdPasvS == 1 ){
               ftp.CmdPasvS = 0;
          }
     }                                                                                                  
     if(ftp.TcpDatSta == FTP_MACH_DISCONT){                                       /* 接收数据完毕*/
          if(ftp.CmdDataS == FTP_MACH_RECEDATA){
               ftp.CmdDataS = FTP_MACH_DATAOVER;
               CH395_FTPListRenew( ftp.ListFlag );                                /* 更新目录       */
          }
     } 
     if(ftp.CmdDataS == FTP_MACH_DATAOVER){                                       /* 数据传输完成*/
          ftp.CmdDataS = FTP_MACH_CLOSECTL;     
          CH395_FTPSendData( (char *)FTP_SERVICE_CMD[1],strlen(FTP_SERVICE_CMD[1]),ftp.SocketCtl );
     }
     if(ftp.CmdDataS == FTP_MACH_SENDDATA){                                       /* 发送数据     */
          if(ftp.TcpDatSta >= FTP_MACH_CONNECT){ 
               ftp.TcpDatSta = FTP_MACH_KEPCONT;
               CH395_FTPSendData( SendBuf,strlen(SendBuf),ftp.SocketDat );
               if(ftp.DataOver ){                                                  /* 检测到发送完毕*/
                    ftp.CmdDataS = FTP_MACH_DATAOVER;                              /* 置发送完成标志*/
                    i = CH395CloseSocket( ftp.SocketDat );                         /* 关闭数据连接      */
                    mStopIfError(i); 
               }
          }
     }
}
