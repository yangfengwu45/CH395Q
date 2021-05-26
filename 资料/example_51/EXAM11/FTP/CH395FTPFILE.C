/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395FTPFILE.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片FTP客户端应用-文件读写代码
*                     
**********************************************************************************/
const  UINT8 *pTest = "abcdefghijklmnopqrstuvwxyz0123456789";     /* 上传文档的内容 */
/**********************************************************************************
* Function Name  : CH395_FTPFileOpen
* Description    : 打开文件   
* Input          : pFileName-文件名
* Output         : None                  
* Return         : None
*********************************************************************************/
UINT8 CH395_FTPFileOpen ( char *pFileName)
{
     return FTP_CHECK_SUCCESS;
}

/*********************************************************************************
* Function Name  : CH395_FTPFileWrite
* Description    : 读取下载数据   
* Input          : recv_buff-数据
                   len -     长度
* Output         : None                  
* Return         : None
*********************************************************************************/
UINT8 CH395_FTPFileWrite ( char *recv_buff ,UINT16 len)
{
     memcpy(send_buff,recv_buff,len);          
     return (FTP_CHECK_SUCCESS);
}

/*********************************************************************************
* Function Name  : CH395_FTPFileRead
* Description    : 传送数据   
* Input          : None
* Output         : None                  
* Return         : None
*********************************************************************************/
void CH395_FTPFileRead( )
{
     memset( send_buff, '\0', sizeof(send_buff));
     if(strlen(pTest)<536) {
          sprintf( send_buff, "%s\r\n",pTest);                  /*将数据写入发送缓冲区，如数据较大，分多次写入 */
          ftp.CmdDataS = FTP_MACH_DATAOVER;                     /*如果数据读完则置为数据读完标志位 */
     }
}
