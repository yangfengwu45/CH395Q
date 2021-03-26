#ifndef __USART_H
#define __USART_H
#include <stm32f10x.h>
#ifndef USART_C_//如果没有定义
#define USART_Ex_ extern
#else
#define USART_Ex_
#endif

#include "BufferManage.h"
#include "LoopList.h"

/****************************串口1****************************/
/*
串口1接收数据:缓存管理
串口1发送数据:环形队列
*/
USART_Ex_ buff_manage_struct buff_manage_struct_usart1_recv;//串口接收缓存管理
USART_Ex_ rb_t rb_t_usart1_send;//串口1发送缓存环形队列

#define Usart1RecvBuffLen 1024  //串口1接收数据数组大小
#define Usart1RecvBufferMemoryLen 1024 //串口接收缓存区大小
#define Usart1RecvBufferMemoryCopyLen 500 //提取缓存区的数据的数组大小
#define Usart1RecvBufferMemoryManageLen 50 //串口接收缓存区管理
#define Usart1SendBufflen 1024  //串口1发送数据缓存大小

USART_Ex_ unsigned char Usart1RecvBuff[Usart1RecvBuffLen];  //接收数据缓存
USART_Ex_ u32  Usart1RecvCnt;//串口1接收到的数据个数

USART_Ex_ u8   Usart1RecvBufferMemory[Usart1RecvBufferMemoryLen];//接收数据缓存区
USART_Ex_ u8   Usart1RecvBufferMemoryCopy[Usart1RecvBufferMemoryCopyLen];//提取缓存区的数据的数组
USART_Ex_ u32  Usart1RecvBufferMemoryManage[Usart1RecvBufferMemoryManageLen];//管理缓存区

USART_Ex_ unsigned char Usart1SendBuff[Usart1SendBufflen];  //串口1发送数据缓存

/****************************串口2****************************/
/*
串口2接收数据:缓存管理
串口2发送数据:普通中断
*/
USART_Ex_ buff_manage_struct buff_manage_struct_usart2_recv;//串口接收缓存管理

#define Usart2RecvBuffLen 1024 //接收数据缓存
#define Usart2RecvBufferMemoryLen 1024 //接收数据缓存区
#define Usart2RecvBufferMemoryCopyLen 500 //提取缓存区的数据
#define Usart2RecvBufferMemoryManageLen 50 //管理缓存区

USART_Ex_ unsigned char Usart2RecvBuff[Usart2RecvBuffLen];  //接收数据缓存
USART_Ex_ u32  Usart2RecvCnt;//串口接收到的数据个数

USART_Ex_ u8   Usart2RecvBufferMemory[Usart2RecvBufferMemoryLen];//接收数据缓存区
USART_Ex_ u8   Usart2RecvBufferMemoryCopy[Usart2RecvBufferMemoryCopyLen];//提取缓存区的数据
USART_Ex_ u32  Usart2RecvBufferMemoryManage[Usart2RecvBufferMemoryManageLen];//管理缓存区

USART_Ex_ unsigned char *Usart2SendData;//串口中断发送数据的地址
USART_Ex_ u32   Usart2SendDataCnt;//串口中断发送数据的个数

/****************************串口3****************************/
/*
串口3接收数据:缓存管理
串口3发送数据:缓存管理+普通中断
*/
USART_Ex_ buff_manage_struct buff_manage_struct_usart3_recv;//串口接收缓存管理

#define Usart3RecvBuffLen 1024 //接收数据缓存
#define Usart3RecvBufferMemoryLen 1024 //接收数据缓存区
#define Usart3RecvBufferMemoryCopyLen 500 //提取缓存区的数据
#define Usart3RecvBufferMemoryManageLen 50 //管理缓存区

USART_Ex_ unsigned char Usart3RecvBuff[Usart3RecvBuffLen];  //接收数据缓存
USART_Ex_ u32  Usart3RecvCnt;//串口接收到的数据个数

USART_Ex_ u8   Usart3RecvBufferMemory[Usart3RecvBufferMemoryLen];//接收数据缓存区
USART_Ex_ u8   Usart3RecvBufferMemoryCopy[Usart3RecvBufferMemoryCopyLen];//提取缓存区的数据
USART_Ex_ u32  Usart3RecvBufferMemoryManage[Usart3RecvBufferMemoryManageLen];//管理缓存区

USART_Ex_ unsigned char *Usart3SendData;//串口中断发送数据的地址
USART_Ex_ u32   Usart3SendDataCnt;//串口中断发送数据的个数

/*串口3发送数据*/
USART_Ex_ buff_manage_struct buff_manage_struct_usart3_send;//串口发送缓存管理

#define Usart3SendBufferMemoryLen 1024 //数据缓存区
#define Usart3SendBufferMemoryCopyLen 500 //提取缓存区的数据
#define Usart3SendBufferMemoryManageLen 50 //管理缓存区
USART_Ex_ u8   Usart3SendBufferMemory[Usart3SendBufferMemoryLen];//数据缓存区
USART_Ex_ u8   Usart3SendBufferMemoryCopy[Usart3SendBufferMemoryCopyLen];//提取缓存区的数据
USART_Ex_ u32  Usart3SendBufferMemoryManage[Usart3SendBufferMemoryManageLen];//管理缓存区


void UsartOutStrIT(USART_TypeDef* USARTx,unsigned char *c,uint32_t cnt);
void uart_init(u32 bound1,u32 bound2,u32 bound3);//串口初始化
void UsartOutStr(USART_TypeDef* USARTx,unsigned char *c,uint32_t cnt);//串口发送字符串数据
void UsartOutChar(USART_TypeDef* USARTx,unsigned char c);//串口发送一个字节
#endif


