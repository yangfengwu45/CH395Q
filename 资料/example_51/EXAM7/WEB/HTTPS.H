/********************************** (C) COPYRIGHT *********************************
* File Name          : https.h
* Author             : WCH
* Version            : V1.8
* Date               : 2014/8/1
* Description        : web接口函数
*             
**********************************************************************************/
#ifndef	__HTTPS_H__
#define	__HTTPS_H__


#define HTTP_SERVER_PORT		80	

/* HTTP Method */
#define		METHOD_ERR		0		/**< Error Method. */
#define		METHOD_GET		1		/**< GET Method.   */
#define		METHOD_HEAD		2		/**< HEAD Method.  */
#define		METHOD_POST		3		/**< POST Method.  */

/* HTTP GET Method */
#define		PTYPE_ERR		0		/**< Error file. */
#define		PTYPE_HTML		1		/**< HTML file.  */
#define		PTYPE_GIF		2		/**< GIF file.   */
#define		PTYPE_TEXT		3		/**< TEXT file.  */
#define		PTYPE_JPEG		4		/**< JPEG file.  */
#define		PTYPE_FLASH	    5	    /**< FLASH file. */
#define		PTYPE_MPEG		6		/**< MPEG file.  */
#define		PTYPE_PDF		7		/**< PDF file.   */
#define 	PTYPE_CGI		8		/**< CGI         */



/* HTML Doc. for ERROR */
#define ERROR_HTML_PAGE "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 78\r\n\r\n<HTML>\r\n<BODY>\r\nSorry, the page you requested was not found.\r\n</BODY>\r\n</HTML>\r\n\0"
//static char  ERROR_HTML_PAGE[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 78\r\n\r\n<HTML>\r\n<BODY>\r\nSorry, the page you requested was not found.\r\n</BODY>\r\n</HTML>\r\n\0";

#define ERROR_REQUEST_PAGE "HTTP/1.1 400 OK\r\nContent-Type: text/html\r\nContent-Length: 50\r\n\r\n<HTML>\r\n<BODY>\r\nInvalid request.\r\n</BODY>\r\n</HTML>\r\n\0"
//static char ERROR_REQUEST_PAGE[] = "HTTP/1.1 400 OK\r\nContent-Type: text/html\r\nContent-Length: 50\r\n\r\n<HTML>\r\n<BODY>\r\nInvalid request.\r\n</BODY>\r\n</HTML>\r\n\0";

#define RETURN_CGI_PAGE "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: "

/* Response header for HTML*/
#define RES_HTMLHEAD_OK	"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: "
//static PROGMEM char RES_HTMLHEAD_OK[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: ";
/* Response head for TEXT */
#define RES_TEXTHEAD_OK	"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: "

/* Response head for GIF */
#define RES_GIFHEAD_OK	"HTTP/1.1 200 OK\r\nContent-Type: image/gif\r\nContent-Length: "

/* Response head for JPEG */
#define RES_JPEGHEAD_OK	"HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: "		

/* Response head for FLASH */
#define RES_FLASHHEAD_OK "HTTP/1.1 200 OK\r\nContent-Type: application/x-shockwave-flash\r\nContent-Length: "

/* Response head for MPEG */
#define RES_MPEGHEAD_OK "HTTP/1.1 200 OK\r\nContent-Type: video/mpeg\r\nContent-Length: "	

/* Response head for PDF */
#define RES_PDFHEAD_OK "HTTP/1.1 200 OK\r\nContent-Type: application/pdf\r\nContent-Length: "

 /*-----------------*/

#define TX_RX_MAX_BUF_SIZE	2048
#define MAX_URI_SIZE	128	

#define TX_BUF	tx_buf
#define RX_BUF	rx_buf


typedef struct _st_http_request
{
	UINT8	METHOD;					
	UINT8	TYPE;					
	UINT8	URI[MAX_URI_SIZE];			
}st_http_request;


extern void ParseHttpRequest(st_http_request *, UINT8 *);		

extern void ParseUriType(UINT8 *, char *);				

extern void MakeHttpResponse(unsigned char *, char);				

extern unsigned char* GetUriName(char* uri);

extern void GetAddr(unsigned char* addr,unsigned char *ip);

extern PINT8 DataLocate(PINT8 buf,PINT8 name);

extern void LedControl(UINT8 *buf);

extern void IpSeting(UINT8 *buf1,UINT8 *buf2);

extern void IpRefrsh(UINT8 *buf,UINT8 *buf2);

extern UINT16  PortSeting (UINT8 *buf);

extern void PortRefresh (UINT8 *buf,UINT16 port);

extern void TempratureRefresh (UINT8 *buf,UINT8 temp);

extern void CurrentRefresh (UINT8 *buf,UINT8 curr);

extern void VoltageRefresh (UINT8 *buf,UINT8 volt);

extern void ADCData(UINT8 *buf);				  /*随机数生成，模拟ADC结果*/

extern void WebServer(void);

#endif	
