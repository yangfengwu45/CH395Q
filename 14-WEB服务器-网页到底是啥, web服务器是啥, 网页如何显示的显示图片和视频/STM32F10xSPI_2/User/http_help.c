#define HTTP_HELP_C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CH395INC.H"
#include "http_help.h"


char tempURI[MAX_URI_SIZE]; 	

/*********************************************************************************
* Function Name  : MakeHttpResponse
* Description    : 生成响应报文
* Input          : 缓冲区指针，uri类型
* Output         : None
* Return         : None
*********************************************************************************/
void MakeHttpResponse(unsigned char * buf,char type,long len)
{
  char * head=0;
  char tmp[10];     
  if   (type == PTYPE_HTML)        head = RES_HTMLHEAD_OK;
  else if (type == PTYPE_GIF)      head = RES_GIFHEAD_OK;
  else if (type == PTYPE_TEXT)     head = RES_TEXTHEAD_OK;
  else if (type == PTYPE_JPEG)     head = RES_JPEGHEAD_OK;
  else if (type == PTYPE_FLASH)    head = RES_FLASHHEAD_OK;
  else if (type == PTYPE_MPEG)     head = RES_MPEGHEAD_OK;
  else if (type == PTYPE_PDF)      head = RES_PDFHEAD_OK;
  else if (type == PTYPE_CGI)      head = RETURN_CGI_PAGE;                     
  sprintf(tmp,"%ld", len);  
  strcpy((char*)buf, head);
  strcat((char*)buf, tmp);
  strcat((char*)buf, "\r\n\r\n");
}

 /*********************************************************************************
* Function Name  : ParseUriType
* Description    : 解析URI类型
* Input          : 缓冲区指针，类型返回指针
* Output         : None
* Return         : None
*********************************************************************************/
void ParseUriType(UINT8 * type,char * buf ) 
{
  if    (strstr(buf, ".htm"))                             *type = PTYPE_HTML;
  else if (strstr(buf, ".gif"))                           *type = PTYPE_GIF;
  else if (strstr(buf, ".text") || strstr(buf,".txt"))    *type = PTYPE_TEXT;
  else if (strstr(buf, ".jpeg") || strstr(buf,".jpg"))    *type = PTYPE_JPEG;
  else if (strstr(buf, ".swf"))                           *type = PTYPE_FLASH;
  else if (strstr(buf, ".mpeg") || strstr(buf,".mpg"))    *type = PTYPE_MPEG;
  else if (strstr(buf, ".pdf"))                           *type = PTYPE_PDF;
  else if (strstr(buf, ".cgi") || strstr(buf,".CGI"))     *type = PTYPE_CGI;
  else if (strstr(buf, ".js") || strstr(buf,".JS"))       *type = PTYPE_TEXT;  
  else if (strstr(buf, ".xml") || strstr(buf,".XML"))     *type = PTYPE_HTML;    
  else                                                    *type = PTYPE_ERR;
}

 /*********************************************************************************
* Function Name  : ParseHttpRequest
* Description    : 解析HTTP请求
* Input          : URI请求指针，缓冲区指针
* Output         : None
* Return         : None
*********************************************************************************/
void ParseHttpRequest(st_http_request * request,UINT8 * buf)
{
  char * nexttok;
  nexttok = strtok((char*)buf," ");
  if(!nexttok)
  {
    request->METHOD = METHOD_ERR;
    return;
  }
  if(!strcmp(nexttok, "GET") || !strcmp(nexttok,"get"))
  {
    request->METHOD = METHOD_GET;
    nexttok = strtok(NULL," ");     
  }
  else if(!strcmp(nexttok, "HEAD") || !strcmp(nexttok,"head"))  
  {
    request->METHOD = METHOD_HEAD;
    nexttok = strtok(NULL," ");
    printf("METHOD = HEAD!\n");
  }
  else if (!strcmp(nexttok, "POST") || !strcmp(nexttok,"post"))
  {
    nexttok = strtok(NULL,"\0");
    request->METHOD = METHOD_POST;
    printf("METHOD = POST!\n");    
  }
  else
  {
    request->METHOD = METHOD_ERR;        
	}  
	
  if(!nexttok)
  {
    request->METHOD = METHOD_ERR;      
    return;
  }
	strcpy((char*)request->URI,nexttok);
}

/*********************************************************************************
* Function Name  : DataLocate
* Description    : 寻找指定字符位置
* Input          : 缓冲区指针，寻找字符
* Output         : None
* Return         : None
*********************************************************************************/
char* DataLocate(unsigned char* buf,char * name)
{
   char* p;
   p = strstr((char *)buf,name);
   if (p==NULL) return NULL;
   p += strlen(name); 
   return p;
}

/*********************************************************************************
* Function Name  : GetUriName
* Description    : 获取URI
* Input          : URI
* Output         : None
* Return         : None
*********************************************************************************/
unsigned char* GetUriName(char* uri)
{
  UINT8* uri_name;
  if(!uri) return 0;
  memset (tempURI, 0, MAX_URI_SIZE);  
  strcpy((char*)tempURI,uri);
  uri_name = (UINT8*)strtok(tempURI," ?");
  if(strcmp((char *)uri_name,"/")) uri_name++;
  return uri_name;
}
