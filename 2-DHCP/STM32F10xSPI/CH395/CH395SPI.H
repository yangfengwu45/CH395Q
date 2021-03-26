#ifndef CH395SPI_H_
#define CH395SPI_H_
#include <stm32f10x.h>

#ifndef CH395SPI_C_
#define CH395SPI_Cx_ extern
#else
#define CH395SPI_Cx_
#endif

#include "CH395INC.H"


#define CH395_SPI_SCS_LOW( )       ( GPIOB->BRR  = GPIO_Pin_0 )   /* SPI片选引脚输出低电平 */
#define CH395_SPI_SCS_HIGH( )      ( GPIOB->BSRR = GPIO_Pin_0 )   /* SPI片选引脚输出高电平 */
#define	CH395_SPI_SDO_PIN( )	   GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_6 ) /* 获取CH395的SPI数据输出引脚电平 */

#define	CH395_INT_PIN_WIRE( )	   GPIOA->IDR & GPIO_Pin_1 		  /* 假定CH395的INT#引脚,如果未连接那么也可以通过查询兼做中断输出的SDO引脚状态实现                                                                                                                                                                                                                                */


void CH395_PORT_INIT( void ) ;
void mDelayuS( UINT8 delay );
void mDelaymS( UINT8 delay );
void xWriteCH395Cmd( UINT8 mCmd );
void xWriteCH395Data( UINT8 mData );
UINT8 xReadCH395Data( void );
UINT8 Query395Interrupt( void );


#endif
