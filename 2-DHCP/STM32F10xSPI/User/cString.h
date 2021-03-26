#ifndef CSTRING_H_
#define CSTRING_H_
#include <stm32f10x.h>
#ifndef CSTRING_C_//如果没有定义
#define CSTRING_Ex_ extern
#else
#define CSTRING_Ex_
#endif

void cStringFree(void);
void cStringRestore(void);
char *StrBetwString(char *Str,char *StrBegin,char *StrEnd);
int split(char *src,const char *separator,char **dest,int DestLen);


/**
* @brief  16进制转字符串显示
* @param  pHex       源16进制
* @param  pAscii     转化后的
* @param  nLen       长度
* @param  None       
* @retval None
* @example 
**/
void HexToAscii(unsigned char *pHex, unsigned char *pAscii, int nLen);
/**
* @brief  数组插入数据
* @param  temp   源数组
* @param  len    当前数组中数据的长度    
* @param  k      要插入的位置
* @param  data   插入的数据     
* @retval None
* @example 
**/
void insert(char *temp, int len,int k, char data);


#endif

