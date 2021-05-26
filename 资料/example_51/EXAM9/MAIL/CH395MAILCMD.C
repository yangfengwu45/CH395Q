/********************************** (C) COPYRIGHT *********************************
* File Name          : CH395MAILCMD.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : 编解码
**********************************************************************************/
const 	UINT8 *g_strBoundary ="18ac0781-9ae4-4a2a-b5f7-5479635efb6b";                                   /* 边界，可修改*/
const 	UINT8 *g_strEncode = "base64";                                                                  /* 编码方式*/
const 	UINT8 *g_strUINT8set ="gb2312";                                                                 /* windows格式 (linux格式"utf-8")*/
const   UINT8 *g_xMailer ="X-Mailer: X-WCH-Mail Client Sender\r\n";                                     /* X-Mailer内容*/
const   UINT8 *g_Encoding ="Content-Transfer-Encoding: quoted-printable\r\nReply-To: ";                 /* Encoding 内容*/
const   UINT8 *g_Custom ="X-Program: CSMTPMessageTester";                                               /* X-Program内同，可修改*/
const   UINT8 *g_FormatMail = "This is a multi-part message in MIME format.";                           /* 邮件有多种内容，一般是有附件*/
const   UINT8 *g_AttachHead = "\r\nContent-Transfer-Encoding: quoted-printable\r\n";                    /* 编码方式*/
#ifdef send_mail
const	  UINT8 *base64_map ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
#endif
#ifdef receive_mail
const UINT8 code base64_decode_map[256] = 
{
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 62, 255, 255, 255, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 255, 255,
     255, 0, 255, 255, 255, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
     15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 255, 255, 255, 255, 255, 255, 26, 27, 28,
     29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
     49, 50, 51, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
};
#endif
POP	    m_pop3;
POP	    *p_pop3;
SMTP	m_smtp;
SMTP	*p_smtp;
UINT8 	EncodeName[32];                                                                                /* 保存编码后发件人名字*/
UINT8 	send_buff[512];                                                                                /* 发送数据缓存区*/
UINT8   MailBodyData[128]= "Demonstration test ch395 mail function wch.cn";                            /* 邮件正文内容，用于演示（回复时用于暂存解码的正文内容）*/
UINT8   AttachmentData[attach_max_len]= "0123456789abcdefghijklmnopqrstuvwxyz";                        /* 附件内容，用于演示（回复时用于暂存解码后的附件内容）*/
/****************************************************************************
* Function Name  : Base64Encode
* Description    : base64编码
* Input          : src需要编码的字符串
                   src_len需要编码字符串的长度
                   dst编码后的字符串
* Output         : None
* Return         : None
*****************************************************************************/
#ifdef send_mail
void Base64Encode(UINT8 *src, UINT16 src_len, UINT8 *dst)
{
        UINT16 i = 0;
        UINT16 j = 0;
        
        for (; i < src_len - src_len % 3; i += 3) {
                dst[j++] = base64_map[(src[i] >> 2) & 0x3f];
                dst[j++] = base64_map[((src[i] << 4) | (src[i + 1] >> 4)) & 0x3f];
                dst[j++] = base64_map[((src[i + 1] << 2) | (src[i + 2] >> 6 )) & 0x3f];
                dst[j++] = base64_map[src[i + 2] & 0x3f];
        }
        
        if (src_len % 3 == 1) {
                 dst[j++] = base64_map[(src[i] >> 2) & 0x3f];
                 dst[j++] = base64_map[(src[i] << 4) & 0x3f];
                 dst[j++] = '=';
                 dst[j++] = '=';
        }
        else if (src_len % 3 == 2) {
                dst[j++] = base64_map[(src[i] >> 2) & 0x3f];
                dst[j++] = base64_map[((src[i] << 4) | (src[i + 1] >> 4)) & 0x3f];
                dst[j++] = base64_map[(src[i + 1] << 2) & 0x3f];
                dst[j++] = '=';
        }
        
        dst[j] = '\0';
}
#endif	
/*****************************************************************************
* Function Name  : Base64Decode
* Description    : base64解码
* Input          : src需要解码的字符串
                   src_len需要解码字符串的长度
                   dst解码后的字符串
* Output         : None
* Return         : None
*****************************************************************************/
#ifdef receive_mail
void Base64Decode(UINT8 *src, UINT16 src_len, UINT8 *dst)
{
      int i = 0, j = 0;
        
    for (; i < src_len; i += 4) {
    if(strncmp( &src[i], "\r\n", 2 ) == 0) i += 2;
    	dst[j++] = base64_decode_map[src[i]] << 2 |
              base64_decode_map[src[i + 1]] >> 4;
    	dst[j++] = base64_decode_map[src[i + 1]] << 4 |
              base64_decode_map[src[i + 2]] >> 2;
    	dst[j++] = base64_decode_map[src[i + 2]] << 6 |
              base64_decode_map[src[i + 3]];
        }
  	if(src_len%4 == 3) {
    	dst[strlen(dst)-1] = '\0'; 
    }
  	else if(src_len%4 == 2) {
    	dst[strlen(dst)-1] = '\0'; 
    	dst[strlen(dst)-1] = '\0'; 
    }
  	else dst[j] = '\0';
}
#endif	

/*****************************************************************************
* Function Name  : QuotedPrintableEncode
* Description    : quotedprintable编码
* Input          : pSrc需要编码的字符串
                   pDst编码后的字符串
                   nSrcLen需要编码字符串的长度
                   nMaxLineLen最大行数
* Output         : None
* Return         : None
*****************************************************************************/
#ifdef send_mail
void QuotedPrintableEncode( UINT8 *pSrc, UINT8 *pDst, UINT16 nSrcLen, UINT16 nMaxLineLen )
{
	UINT16 nDstLen  = 0;
	UINT16 nLineLen = 0;
	UINT16 i = 0;

	for(i = 0; i < nSrcLen; i++, pSrc++ ){            
  	if( (*pSrc >= '!') && (*pSrc <= '~') && (*pSrc != '=') ){
      *pDst++ = (char)*pSrc;
    	nDstLen++;
    	nLineLen++;
    }
  	else{
    	sprintf(pDst, "=%02x", *pSrc);
    	pDst += 3; 
    	nDstLen += 3;
    	nLineLen += 3;
    }
  	if( nLineLen >= nMaxLineLen - 3 ){    
     	sprintf(pDst, "=\r\n");
    	pDst += 3;
    	nDstLen += 3;
    	nLineLen = 0;
    }
  }
  *pDst = '\0';
}
#endif	

/*****************************************************************************
* Function Name  : QuotedPrintableEncode
* Description    : quotedprintable解码
* Input          : pSrc需要解码的字符串
                   nSrcLen需要编码字符串的长度
                   pDst解码后的字符串
* Output         : None
* Return         : None
*****************************************************************************/
#ifdef receive_mail
void QuotedPrintableDecode( UINT8 *pSrc, UINT8 *pDst, UINT16 nSrcLen )
{
	UINT16 i = 0;
	UINT16 nDstLen = 0;

	while( i < nSrcLen ){
  	if( strncmp( pSrc, "=\r\n", 3 ) == 0 ){
    	pSrc += 3;
    	i += 3;
    }
  	else{
    	if( *pSrc == '=' ){
      	sscanf( pSrc, "=%02x",*pDst);
      	pDst++;
      	pSrc += 3;
      	i += 3;
      }
    	else{
        *pDst++ = *pSrc++;
      	i++;
      }
    	nDstLen++;
    }
  }
  *pDst = '\0';
}
#endif	

/*****************************************************************************
* Function Name  : ch395mail_xtochar
* Description    : 16进制转字符串
* Input          : dat-要转换的十六进制数据
                   p-转换后对应的字符串
                   len-要转换的长度
* Output         : None
* Return         : None
*****************************************************************************/
#ifdef receive_over_reply
void ch395mail_xtochar( UINT8 data *dat,UINT8 data *p,UINT8 len)
{
	UINT8 k;
	for(k=0;k<len;k++){
    *p = (((dat[k]&0xf0)>>4)/10)?(((dat[k]&0xf0)>>4)+'A'-10):(((dat[k]&0xf0)>>4)+'0');
  	p++;
    *p = ((dat[k]&0x0f)/10)?((dat[k]&0x0f)+'A'-10):((dat[k]&0x0f)+'0');
  	p++;
  	if(k<len-1){
      *p = '.';
    	p++;    
    }
  }
}
#endif 
/******************************************************************************/
#ifdef send_mail
/*****************************************************************************
* Function Name  : ch395mail_IsMIME
* Description    : 判断有无附件
* Input          : None
* Output         : None
* Return         : 0-无附件
                   1-有附件
*****************************************************************************/
void ch395mail_IsMIME( )
{
	if( strlen(p_smtp->m_strFile) <= 0 ) p_smtp->g_MIME = 0;
	else p_smtp->g_MIME = 1;
}

/*****************************************************************************
* Function Name  : ch395mail_GetAttachHeader
* Description    : 用于组建附件信封 
* Input          : pFileName-附件名字
                   pAttachHeader-组建好的信封内容
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_GetAttachHeader(  UINT8 *pFileName, UINT8 *pAttachHeader )
{
	const UINT8 *strContentType = "application/octet-stream";
	sprintf(pAttachHeader, "\r\n\r\n--%s\r\nContent-Type: %s;\r\n name=\"%s\"%sContent-Disposition: \
	attachment;\r\n filename=\"%s\"\r\n\r\n", g_strBoundary, strContentType, pFileName,g_AttachHead, pFileName ); 
}  

/*****************************************************************************
* Function Name  : ch395mail_GetAttachEnd
* Description    : 组建附件结束内容 
* Input          : EndSize,pAttachEnd
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_GetAttachEnd( UINT16 *EndSize, UINT8 *pAttachEnd )
{
	strcat( pAttachEnd, "\r\n--" );
	strcat( pAttachEnd, g_strBoundary );
	strcat( pAttachEnd, "--" );
  *EndSize = strlen(pAttachEnd);
}

/*****************************************************************************
* Function Name  : ch395mail_SendHeader
* Description    : 邮件信封  
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_SendHeader(  )
{
	UINT8   s;
	const 	UINT8 *strContentType = "multipart/mixed";
  /* "FROM: "*/
	memset( send_buff, '\0', sizeof(send_buff) );
	strcat( send_buff, "From: \"" );
	strcat( send_buff, p_smtp->m_strSenderName );
	strcat( send_buff, "\" <" );
	strcat( send_buff, p_smtp->m_strSendFrom );
	strcat( send_buff, ">\r\n" );
  /* "TO: " */
	strcat( send_buff, "To: <" );
	strcat( send_buff, p_smtp->m_strSendTo );
	strcat( send_buff, ">\r\n" );
  /* "Subject: " */
	strcat( send_buff, "Subject: ");
#ifdef receive_over_reply
	strcat( send_buff, "Re: ");
#endif
	strcat( send_buff, p_smtp->m_strSubject );
	strcat( send_buff, "\r\n" );
  /*"Date: "*/ 
	strcat( send_buff, "Date: ");
	strcat( send_buff, '\0' );                                                                          /* 时间*/
 	strcat( send_buff, "\r\n" );
  /* "X-Mailer: " */
	strcat( send_buff, g_xMailer );
                                                                                                      
	if( p_smtp->g_MIME == 1 ){																			                                    /* 有附件*/
  	strcat( send_buff, "MIME-Version: 1.0\r\nContent-Type: " );
  	strcat( send_buff, strContentType );
  	strcat( send_buff, ";\r\n\tboundary=\"" );
  	strcat( send_buff, g_strBoundary );
  	strcat( send_buff, "\"\r\n" );
  }
  /* Encoding information*/
	strcat( send_buff, g_Encoding );
	strcat( send_buff, p_smtp->m_strSenderName );
	strcat( send_buff, " <" );
	strcat( send_buff, p_smtp->m_strSendFrom );
	strcat( send_buff, ">\r\n" );
  /*add custom-tailor*/
	strcat( send_buff, g_Custom );
  /*end of mail header*/
	strcat( send_buff, "\r\n\r\n" );
#if DEBUG
	printf("Mail Header:%s\n", send_buff);
#endif
	s = ch395mail_SendData( send_buff, strlen(send_buff),uncheck ,SendSocket);  
#if DEBUG
	if( s != send_data_success ) printf("ERROR: %02x\n",(UINT16)s);
#endif
}
/*****************************************************************************
* Function Name  : ch395mail_SendAttach
* Description    : 发送附件  
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_SendAttach(  )
{
	UINT16  EndSize;
	UINT8	s;

	memset( send_buff, '\0', sizeof(send_buff) );
	ch395mail_GetAttachHeader( p_smtp->m_strFile, send_buff);
#if DEBUG
	printf("Attach Header:%s\n", send_buff);
#endif
	s = ch395mail_SendData( send_buff, strlen(send_buff),uncheck ,SendSocket);   
#if DEBUG
	if( s != send_data_success ) printf("ERROR: %02x\n",(UINT16)s);
#endif


/*发送附件内容 */
/*	GetAttachedFileBody( &FileSize, m_smtp->m_strFile, pAttachedFileBody );*/
	memset( send_buff, '\0', sizeof(send_buff) );
	QuotedPrintableEncode( AttachmentData, send_buff, strlen(AttachmentData),200 );
#if DEBUG
	printf("Attach Data send_buff:\n%s\n", send_buff);
#endif
	s = ch395mail_SendData( send_buff, strlen(send_buff),uncheck ,SendSocket);
#if DEBUG
	if( s != send_data_success ) printf("ERROR: %02x\n",(UINT16)s);
#endif
	memset( send_buff, '\0', sizeof(send_buff) );
	ch395mail_GetAttachEnd( &EndSize, send_buff );
#if DEBUG
	printf("Attach End :%s\n", send_buff);
#endif
	s = ch395mail_SendData( send_buff, strlen(send_buff),uncheck ,SendSocket);                          /*Send attached file end*/
#if DEBUG
	if( s != send_data_success ) printf("ERROR: %02x\n",(UINT16)s);
#endif
} 

/*****************************************************************************
* Function Name  : ch395mail_SendAttachHeader
* Description    : 发送附件信封  
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_SendAttachHeader( )
{
	UINT8 s;
	const UINT8 *strContentType = "text/plain";

	s = ch395mail_SendData( g_FormatMail, strlen(g_FormatMail),uncheck,SendSocket );
#if DEBUG
	if( s != send_data_success ) printf("ERROR: %02x\n",(UINT16)s);
#endif
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "\r\n--%s\r\nContent-Type: %s;\r\n\tcharset=\"%s\"%s\r\n", g_strBoundary, strContentType, g_strUINT8set,g_AttachHead );
#if DEBUG
	printf("MIME Header:\n%s\n", send_buff);
#endif
	s = ch395mail_SendData( send_buff, strlen(send_buff),uncheck,SendSocket);
#if DEBUG
	if( s != send_data_success ) printf("ERROR: %02x\n",(UINT16)s);
#endif
}

/*****************************************************************************
* Function Name  : ch395mail_smtpEhlo
* Description    : 进入发送邮件状态  
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_smtpEhlo(  )
{
	memset( EncodeName, '\0', sizeof(EncodeName) );
	QuotedPrintableEncode( (UINT8 *)p_smtp->m_strSenderName, EncodeName, strlen(p_smtp->m_strSenderName),76 );
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s %s\r\n", SMTP_CLIENT_CMD[0],EncodeName );
#if DEBUG
	printf("EHLO :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff),SMTP_CHECK_HELO ,SendSocket);
}

/*****************************************************************************
* Function Name  : ch395mail_smtpLoginAuth
* Description    : 进入发送邮件状态  
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_smtpLoginAuth(  )
{
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s\r\n",SMTP_CLIENT_CMD[1]);
#if DEBUG
	printf("AUTH :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff),SMTP_CHECK_AUTH ,SendSocket);                      /*send "AUTH LOGIN" command*/
}

/*****************************************************************************
* Function Name  : ch395mail_smtpLoginUser
* Description    : 认证用户名   
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_smtpLoginUser()
{
	memset( send_buff, '\0', sizeof(send_buff) );
	Base64Encode( (UINT8 *)p_smtp->m_strUSERID, strlen(p_smtp->m_strUSERID), send_buff );
	sprintf( send_buff, "%s\r\n", send_buff);
#if DEBUG
	printf("USER :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff),SMTP_CHECK_USER,SendSocket );
}

/*****************************************************************************
* Function Name  : ch395mail_smtpLoginPass
* Description    : 登陆密码    
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_smtpLoginPass( )
{
	memset( send_buff, '\0', sizeof(send_buff) );
	Base64Encode( (UINT8 *)p_smtp->m_strPASSWD, strlen(p_smtp->m_strPASSWD), send_buff);
	sprintf( send_buff, "%s\r\n", send_buff);
#if DEBUG
	printf("PASS :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff),SMTP_CHECK_PASS,SendSocket );
}

/*****************************************************************************
* Function Name  : ch395mail_smtpCommandMail
* Description    : 发送发件人名字  
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_smtpCommandMail( )
{
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s <%s>\r\n", SMTP_CLIENT_CMD[2],p_smtp->m_strSendFrom );
#if DEBUG
	printf("MAIL :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff),SMTP_CHECK_MAIL,SendSocket );
}

/*****************************************************************************
* Function Name  : ch395mail_smtpCommandRcpt
* Description    : 收件人地址 
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_smtpCommandRcpt( )
{
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s <%s>\r\n", SMTP_CLIENT_CMD[3],p_smtp->m_strSendTo );  
#if DEBUG
	printf("RCPT :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff),SMTP_CHECK_RCPT,SendSocket );
}

/*****************************************************************************
* Function Name  : ch395mail_smtpCommandData
* Description    : 发送data命令 
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_smtpCommandData(  )
{
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s\r\n",SMTP_CLIENT_CMD[4] );
#if DEBUG
	printf("DATA :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff),SMTP_CHECK_DATA,SendSocket );
}

/*****************************************************************************
* Function Name  : ch395mail_smtpSendData
* Description    : 发送邮件内容  
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_smtpSendData( )
{
	UINT8	s;

	ch395mail_IsMIME( );                                                                                /* 判断有无附件*/
	ch395mail_SendHeader(  );                                                                           /* 发送邮件信封*/
	if( p_smtp->g_MIME ==  1 ){
    ch395mail_SendAttachHeader(  );                                                                     /* 发送附件信封*/
  }
	else {
  	ch395mail_SendData("\r\n", strlen("\r\n"),uncheck,SendSocket);
#if DEBUG
  	if( s != send_data_success ) printf("ERROR: %02x\n",(UINT16)s);
#endif
  }
	memset( send_buff, '\0', sizeof(send_buff) );
#ifdef	receive_over_reply
	ch395mail_replybody( );
#else   /* receive_over_reply */
 	QuotedPrintableEncode( (UINT8 *)MailBodyData, send_buff, strlen(MailBodyData),76 );
#endif	/* receive_over_reply */
#if DEBUG
	printf("text data %s\n",send_buff);
#endif
	s = ch395mail_SendData( send_buff, strlen(send_buff),uncheck ,SendSocket);
#if DEBUG
	if( s != send_data_success ) printf("ERROR: %02x\n",(UINT16)s);
#endif
	if( 1 == p_smtp->g_MIME ) ch395mail_SendAttach( );                                                   /*Send Attached file*/
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "\r\n.\r\n" );
#if DEBUG
	printf("OVER :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff),SMTP_CHECK_DATA_END ,SendSocket);                   /*Send end flag of Mail*/

}

/******************************************************************************/
#endif	
/******************************************************************************/
#ifdef receive_mail
/*****************************************************************************
* Function Name  : ch395mail_pop3LoginUser
* Description    : 认证用户名  
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_pop3LoginUser(  )              
{
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf(send_buff, "%s %s\r\n",POP3_CLIENT_CMD[1], p_pop3->pPop3UserName);
#if DEBUG
	printf("USER :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff), POP_CHECK_USER ,ReceSocket); 
}

/*****************************************************************************
* Function Name  : ch395mail_pop3LoginPass
* Description    : 密码  
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_pop3LoginPass(  )              
{
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s %s\r\n", POP3_CLIENT_CMD[2], p_pop3->pPop3PassWd );
#if DEBUG
	printf("PASS :%s\n", send_buff);
#endif
	ch395mail_SendData(  send_buff, strlen(send_buff), POP_CHECK_PASS,ReceSocket );  
}

/*****************************************************************************
* Function Name  : ch395mail_pop3Stat
* Description    : 回送邮箱统计资料  
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_pop3Stat( )
{
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff,"%s\r\n", POP3_CLIENT_CMD[3] );
#if DEBUG
	printf("STAT :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff), POP_CHECK_STAT,ReceSocket );
}

/*****************************************************************************
* Function Name  : ch395mail_pop3List
* Description    : 处理server返回指定邮件的大小 
* Input          : None
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_pop3List( )
{
#if	0	    /* 如果需指定某封邮件则置1；*/
	UINT8 num;
	num = '1';  /* 根据需要修改邮件号；*/
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s %c\r\n", POP3_CLIENT_CMD[4],num );
#else
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s\r\n", POP3_CLIENT_CMD[4] );
#endif	
#if DEBUG
	printf("LIST :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff), POP_CHECK_LIST,ReceSocket);  
}

/*****************************************************************************
* Function Name  : ch395mail_pop3Retr
* Description    : 处理server邮件的全部文本 
* Input          : num-邮件号
* Output         : None
* Return         : None
*****************************************************************************/
#ifdef	POP_RTER 
void ch395mail_pop3Retr( UINT8 num )
{
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s %c\r\n", POP3_CLIENT_CMD[5], num );
#if DEBUG
	printf("RTER :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff), POP_CHECK_RETR,ReceSocket );
}
#endif	
 
/*****************************************************************************
* Function Name  : ch395mail_pop3Dele
* Description    : 处理server标记删除 
* Input          : num-邮件号
* Output         : None
* Return         : None
*****************************************************************************/
#ifdef	POP_DELE
void ch395mail_pop3Dele( UINT8 num )
{
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s %c\r\n", POP3_CLIENT_CMD[6], num );
#if DEBUG
	printf("DELE :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff), POP_CHECK_DELE,ReceSocket );
}
#endif	
 
/*****************************************************************************
* Function Name  : ch395mail_pop3Dele
* Description    : 处理server撤销删除
* Input          : num-邮件号
* Output         : None
* Return         : None
*****************************************************************************/
#ifdef	POP_RSET
void ch395mail_pop3Rset( )
{
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s \r\n", POP3_CLIENT_CMD[7]);
#if DEBUG
	printf("RSET :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff), POP_CHECK_RSET,ReceSocket );
}
#endif	
 
/*****************************************************************************
* Function Name  : ch395mail_pop3Top
* Description    : 返回n号邮件的前m行内容
* Input          : num-邮件号
                   m-行数
* Output         : None
* Return         : None
*****************************************************************************/
#ifdef	POP_TOP
void ch395mail_pop3Top( UINT8 num ,UINT8 m  )
{
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s %c %c\r\n", POP3_CLIENT_CMD[10],num,m);
#if DEBUG
	printf("TOP :%s\n", send_buff);
#endif
	ch395mail_SendData( send_buff, strlen(send_buff), POP_CHECK_TOP,ReceSocket );
}
#endif	

/*****************************************************************************
* Function Name  : ch395mail_pop3Top
* Description    : 处理server返回用于该指定邮件的唯一标识
* Input          : num-邮件号
* Output         : None
* Return         : None
*****************************************************************************/
#ifdef	POP_UIDL
void ch395mail_pop3Uidl( UINT8 num )
{
     memset( send_buff, '\0', sizeof(send_buff) );
     sprintf( send_buff, "%s %c\r\n", POP3_CLIENT_CMD[11], num);
#if DEBUG
     printf("UIDL :%s\n", send_buff);
#endif
     ch395mail_SendData( send_buff, sizeof(send_buff), POP_CHECK_UIDL,ReceSocket );
}
#endif	

/******************************************************************************/
#endif	

/*****************************************************************************
* Function Name  : Quit
* Description    : 退出登陆
* Input          : index
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_Quit(UINT8 index )
{
	memset( send_buff, '\0', sizeof(send_buff) );
	sprintf( send_buff, "%s\r\n", POP3_CLIENT_CMD[0]);
	if(index==SendSocket){
#if  DEBUG
	printf("smtp QUIT\n");
#endif
  	ch395mail_SendData( send_buff, strlen(send_buff),SMTP_CHECK_QUIT,index );
  }
	if(index==ReceSocket){
#if  DEBUG
	printf("pop3 QUIT\n");
#endif
  	ch395mail_SendData( send_buff, strlen(send_buff),POP_CHECK_QUIT,index );
  }

}

/*****************************************************************************
* Function Name  : ch395mail_MailCommand
* Description    : 判断命令进入对应子程序
* Input          : choiceorder-命令类型
* Output         : None
* Return         : None
*****************************************************************************/
void ch395mail_MailCommand( UINT8 choiceorder )
{
	UINT8 i;
  
	switch( choiceorder ){
#ifdef send_mail
  	case SMTP_SEND_HELO: 
    	ch395mail_smtpEhlo( );
    	break;
  	case SMTP_SEND_AUTH: 
    	ch395mail_smtpLoginAuth( );
    	break;
  	case SMTP_SEND_USER: 
    	ch395mail_smtpLoginUser( );
    	break;
  	case SMTP_SEND_PASS: 
    	ch395mail_smtpLoginPass( );
    	break;
  	case SMTP_SEND_MAIL: 
    	ch395mail_smtpCommandMail( );
    	break;
  	case SMTP_SEND_RCPT: 
    	ch395mail_smtpCommandRcpt( );
    	break;
  	case SMTP_SEND_DATA: 
    	ch395mail_smtpCommandData( );
    	break;
  	case SMTP_DATA_OVER:
    	ch395mail_smtpSendData( );
    	break;
  	case SMTP_ERR_CHECK:
    	ch395mail_Quit( SendSocket );
    	i = CH395CloseSocketp( SendSocket );
    	break;
  	case SMTP_SEND_QUIT:
    	ch395mail_Quit( SendSocket );
    	break;
  	case SMTP_CLOSE_SOCKET:
    	CheckType = uncheck;
#if DEBUG
    	printf("clost smtp socket\n");
#endif
    	i = CH395CloseSocketp( SendSocket );
#ifdef	receive_over_reply
    	OrderType = POP_RECEIVE_DELE;
#endif
    	break;
  	case SMTP_SEND_START:
    	CH395SocketInitOpen( SendSocket );
    	break;
#endif	
#ifdef receive_mail
  	case POP_RECEIVE_USER: 
    	ch395mail_pop3LoginUser(  );
    	break;
  	case POP_RECEIVE_PASS: 
    	ch395mail_pop3LoginPass(  );
    	break;
  	case POP_RECEIVE_STAT: 
    	ch395mail_pop3Stat(  );
    	break;
  	case POP_RECEIVE_LIST: 
    	ch395mail_pop3List(  );
    	break;
  	case POP_ERR_CHECK:
    	ch395mail_Quit( ReceSocket );
    	i = CH395CloseSocketp( ReceSocket );
    	break;
  	case POP_RECEIVE_QUIT:
    	ch395mail_Quit( ReceSocket );
    	break;
  	case POP_CLOSE_SOCKET:
    	CheckType = uncheck;
#if DEBUG
    	printf("close pop3 socket\n");
#endif
    	i = CH395CloseSocketp( ReceSocket );
#ifdef	send_over_receive
    	OrderType = SMTP_SEND_QUIT;
#endif
    	break;
  	case POP_RECEIVE_START:
    	CH395SocketInitOpen( ReceSocket );
    	break;
#endif	
  	default: 
#if DEBUG
    	printf("COMMAND UNUSEFULL\n");
#endif
    	break;
  }
}
