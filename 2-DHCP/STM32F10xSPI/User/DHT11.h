#ifndef __DHT11_H_
#define __DHT11_H_

#ifndef _DHT11_C_
#define _DHT11_C_ extern
#else
#define _DHT11_C_
#endif
#include <stm32f10x.h>
  
										   
#define	DHT11_DQ_OUT PBout(9) 
#define	DHT11_DQ_IN  PBin(9)


_DHT11_C_ u8 DHT11Data[4];//温湿度数据(温度高位,温度低位,湿度高位,湿度低位)

void DHT11_start(void);
void DHT11_Receive(void);     //接收40位的数据


u8 DHT11_Init(void);//???DHT11
void DHT11_Read_Data(void); 
u8 DHT11_Read_Byte(void);//??????
u8 DHT11_Read_Bit(void);//?????
u8 DHT11_Check(void);//??????DHT11
void DHT11_Rst(void);//??DHT11  



#endif

