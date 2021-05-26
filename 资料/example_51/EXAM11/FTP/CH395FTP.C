/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395FTP.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片FTP客户端应用-FTP接口命令
**********************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../PUB/CH395INC.H"
#include "../PUB/CH395CMD.H"
#include "CH395.H"
#include "CH395FTPINC.H"
#include "CH395FTPCMD.C"
#include "CH395FTPFILE.C"

/******************************************************************************
* Function Name  : CH395_FTPProcessReceDat
* Description    : 处理接收到的数据
* Input          : recv_buff- 握手信息
                   check_type-待核对的命令类型
                   sockeid  - socket索引
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_FTPProcessReceDat( char *recv_buff,UINT8 check_type,UINT8 socketid )
{
    UINT8 S;
    if( socketid == ftp.DatTransfer ){
        if(ftp.CmdDataS == FTP_MACH_RECEDATA){                                        /* 接受文件数据    */
            if( ftp.InterCmdS == FTP_MACH_GETFILE ){ 
                S = CH395_FTPFileWrite(recv_buff,strlen(recv_buff));
            }
            else if(ftp.InterCmdS == FTP_MACH_FINDLIST ){
                S = CH395_FTPFindList( recv_buff );                                    /* 验证传输数据，用于查找指定的目录名*/
                if( S == FTP_CHECK_SUCCESS ) ftp.FindList = 1;                         /* 查到指定的目录名*/
            }
            else if(ftp.InterCmdS == FTP_MACH_FINDFILE ){
                S = CH395_FTPFindFile( recv_buff );                                    /* 查找文件    */
                if( S == FTP_CHECK_SUCCESS ) ftp.FindFile = 1;                         /* 找到文件    */
            }                                                                                    
        }
    }
    else if( socketid == ftp.SocketCtl ){                                              /* 接收为命令应答*/            
        S = CH395_FTPCmdRespond( recv_buff,check_type );

    }
}

/*******************************************************************************
* Function Name  : CH395_FTPSendFile
* Description    : 发送数据
* Input          : NONE
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_FTPSendFile( )
{
    UINT8 S;    

    S = CH395_FTPFileOpen( FileName );
    if(S == FTP_CHECK_SUCCESS)    CH395_FTPFileRead( );
    CH395_SocketSendData( send_buff, strlen(send_buff),ftp.DatTransfer );
    if(ftp.CmdDataS == FTP_MACH_DATAOVER){
        CH395CloseSocket( ftp.DatTransfer );
    }    
}

/*******************************************************************************
* Function Name  : CH395_FTPClientCmd
* Description    : 查询状态，执行相应命令
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_FTPClientCmd( )
{
    if(ftp.CmdDataS == FTP_MACH_SENDDATA){
    if(ftp.TcpStatus == FTP_MACH_CONNECT) CH395_FTPSendFile( );                       /* 向服务器发送数据*/
        return ;     
    }
    if(ftp.FileCmd){
        CH395_FTPInterCmd( );                                                         /* 执行对应的接口命令*/
    }
}

/*******************************************************************************
* Function Name  : CH395_FTPInterCmd
* Description    : 执行对应的命令，可自行调整执行顺序
* Input          : NONE
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_FTPInterCmd( )
{
    switch(ftp.FileCmd){
        case FTP_CMD_LOGIN:                                                            /* 登陆      */
            if( CH395_FTPLogin( ) == FTP_COMMAND_SUCCESS ){                            /* 登陆成功,可进行其他操作*/
                CH395_FTPSearch("USER","FILELIST.TXT" );                               /* 开始查询指定的目录下的文件*/
            }
            break;
        case FTP_CMD_SEARCH:                                                           /* 搜查文件（参数：目录名，文件名）*/
            if( CH395_FTPSearch("USER","FILELIST.TXT" ) == FTP_COMMAND_SUCCESS ){      /* 查询命令执行完毕，可进行其他操作 */        
                if( ftp.FindFile )CH395_FTPGetFile("FILELIST.TXT" );                   /* 搜查到指定的目录下的文件则开始下载文件 */
                else CH395_FTPQuit( );                                                 /* 没搜查到指定的目录下的文件则退出（也可进行其他操作，如上传）*/
            }
            break;
        case FTP_CMD_GETFILE:                                                          /* 下载文件（参数：文件名）*/
            if(CH395_FTPGetFile("FILELIST.TXT" ) == FTP_COMMAND_SUCCESS ){             /* 下载文件成功，可进行其他操作    */
                CH395_FTPPutFile("TEXT","abc.txt");                                    /* 上传文件      */
            }
            break;
        case FTP_CMD_PUTFILE:                                                          /* 上传文件（参数：目录名，文件名）*/
            if( CH395_FTPPutFile("TEXT","abc.txt")== FTP_COMMAND_SUCCESS ){            /* 上传文件成功，可进行其他操作*/
                CH395_FTPQuit( );                                                      /* 退出    */
            }
            break;
        default:
            break;
    }
}
