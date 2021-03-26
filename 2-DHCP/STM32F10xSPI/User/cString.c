/**
  ******************************************************************************
  * @file    key.c
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/10/13
  * @brief   字符串处理函数
  ******************************************************************************

  ******************************************************************************
  */
#define CSTRING_C_
#include "cString.h"
#include <string.h>
#include <stdlib.h>

char *StringStr = NULL;
void cStringFree(void){
	free(StringStr);
}

/**
* @brief  获取两个字符串之间的字符串
* @param  Str  源字符串
* @param  StrBegin  开始的字符串
* @param  StrEnd    结束的字符串
* @retval 字符串首地址
* @example  printf("%s",StrBetwString("wqe5w4ew46e5w","5w","6e"));cStringFree(Str);  输出:4ew4   
**/
char *StrBetwStringMalloc(char *Str,char *StrBegin,char *StrEnd)
{
	char *StrStart=0,*StrStop=0,len=0;
	len = strlen(StrBegin);//字符串长度
	
  StrStart=strstr(Str, StrBegin);//第一个字符串开始的地址
	if(StrStart)
	{
	  StrStop = strstr(StrStart+len+1, StrEnd);//第二个字符串开始的地址
		if(StrStop)
		{
			StringStr = (char *)malloc(((StrStop - (StrStart+len))+1) *sizeof(char));//多分配一个空间,防止其它数据干扰
			memset(StringStr,NULL,(StrStop - (StrStart+len))+1);
			memcpy(StringStr, StrStart+len, (StrStop - (StrStart+len)));
			return StringStr;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
	  return NULL;
	}
}

char *StrStop = NULL;
char StringValue;
void cStringRestore(void){
	if(StrStop!=NULL){
		*StrStop = StringValue;//补上当时截断的字符串
	}
}
/**
* @brief  获取两个字符串之间的字符串
* @param  Str  源字符串
* @param  StrBegin  开始的字符串
* @param  StrEnd    结束的字符串
* @retval 字符串首地址
* @example  printf("%s",StrBetwString("wqe5w4ew46e5w","5w","6e"));cStringRestore();  输出:4ew4   
**/
char *StrBetwString(char *Str,char *StrBegin,char *StrEnd)
{
	char *StrStart=0,len=0;
	len = strlen(StrBegin);//字符串长度
  StrStart=strstr(Str, StrBegin);//第一个字符串开始的地址
	if(StrStart)
	{
	  StrStop = strstr(StrStart+len+1, StrEnd);//第二个字符串开始的地址
		if(StrStop)
		{
      StringValue = *StrStop;
			*StrStop = 0;//截断
			return StrStart+len;
		}
		else return NULL;
	}
	else return NULL;
}


/**
* @brief  分割字符串
* @param  src        源字符串
* @param  separator  分割
* @param  dest       接收子串的数组
* @param  num        子字符串的个数
* @retval None
* @example split("42,uioj,dk4,56",",",temp,&cnt);  temp[0]=42,...temp[3]=56  cnt=4
**/
int split(char *src,const char *separator,char **dest,int DestLen)
{
	char *pNext;
	int count = 0;
	if (src == NULL || strlen(src) == 0)
		return 0;
	if (separator == NULL || strlen(separator) == 0)
		return 0;
	pNext = (char *)strtok(src,separator);
	while(pNext != NULL)
	{
		if(dest != NULL)
		*dest++ = pNext;
		++count;
		pNext = (char *)strtok(NULL,separator);
		if(count>=DestLen){
		  break;
		}
	}
	return count;
}



/**
* @brief  16进制转字符串显示
* @param  pHex       源16进制
* @param  pAscii     转化后的
* @param  nLen       长度
* @param  None       
* @retval None
* @example 
**/
void HexToAscii(unsigned char *pHex, unsigned char *pAscii, int nLen)
{
	unsigned char Nibble[2];
	unsigned int i,j;
	for (i = 0; i < nLen; i++)
	{
		Nibble[0] = (pHex[i] & 0xF0) >> 4;
		Nibble[1] = pHex[i] & 0x0F;
		for (j = 0; j < 2; j++)
		{
			if (Nibble[j] < 10)
			{            
				Nibble[j] += 0x30;
			}
			else
			{
				if (Nibble[j] < 16)
					Nibble[j] = Nibble[j] - 10 + 'a';
			}
			*pAscii++ = Nibble[j];
		}              
	}          
}

/**
* @brief  数组插入数据
* @param  temp   源数组
* @param  len    当前数组中数据的长度    
* @param  k      要插入的位置
* @param  data   插入的数据     
* @retval None
* @example 
**/
void insert(char *temp, int len,int k, char data)
{
	int i;
	for(i=len-1; i>=k; i--){
		temp[i+1] = temp[i];
	}
	temp[k] = data;
	len++;
}


