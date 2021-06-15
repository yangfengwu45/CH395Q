#ifndef CH395UART_H_
#define CH395UART_H_
#include <stm32f10x.h>

#ifndef CH395UART_C_
#define CH395UART_Cx_ extern
#else
#define CH395UART_Cx_
#endif

#include "CH395INC.H"


#define	CH395_INT_PIN_WIRE( )	   GPIOA->IDR & GPIO_Pin_1 	


void mDelayuS( UINT8 delay );
void mDelaymS( UINT8 delay );
void CH395_Send_Byte( UINT8 dat );
void xWriteCH395Cmd( UINT8 mCmd );
void xWriteCH395Data( UINT8 mData );
UINT8 xReadCH395Data( void );
UINT8 Query395Interrupt( void );


#endif

