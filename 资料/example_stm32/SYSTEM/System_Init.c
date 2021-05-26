/********************************** (C) COPYRIGHT *********************************
* File Name          : System_Init.C
* Author             : tech10
* Version            : V1.0
* Date               : 2014/1/1
* Description        : STM32 系统初始化
**********************************************************************************/
#include <stm32f10x.h>              /* STM32F10x库 */
#include "system.h"
#include "stdio.h"
/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void RCC_Config( void )
{ 
	ErrorStatus HSEStartUpStatus;
	
	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
	/* RCC system reset(for debug purpose) */
	RCC_DeInit( );

	/* Enable HSE */
	RCC_HSEConfig( RCC_HSE_ON );

	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp( );

	if( HSEStartUpStatus == SUCCESS )
	{
		/* Enable Prefetch Buffer */
    	FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable );

		/* Flash 2 wait state */
    	FLASH_SetLatency( FLASH_Latency_2 );
 
		/* HCLK = SYSCLK */
		RCC_HCLKConfig( RCC_SYSCLK_Div1 ); 
  
		/* PCLK2 = HCLK */
		RCC_PCLK2Config( RCC_HCLK_Div1 ); 

		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config( RCC_HCLK_Div2 );

#ifdef STM32F10X_CL
		/* Configure PLLs *********************************************************/
    	/* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
    	RCC_PREDIV2Config( RCC_PREDIV2_Div5 );
    	RCC_PLL2Config( RCC_PLL2Mul_8 );

		/* Enable PLL2 */
		RCC_PLL2Cmd( ENABLE );

		/* Wait till PLL2 is ready */
		while( RCC_GetFlagStatus( RCC_FLAG_PLL2RDY ) == RESET )
		{}

		/* PLL configuration: PLLCLK = (PLL2 / 5) * 9 = 72 MHz */ 
		RCC_PREDIV1Config( RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5 );
		RCC_PLLConfig( RCC_PLLSource_PREDIV1, RCC_PLLMul_9 );
#else
		/* PLLCLK = 8MHz * 9 = 72 MHz */
		RCC_PLLConfig( RCC_PLLSource_HSE_Div1, RCC_PLLMul_9 );
#endif

		/* Enable PLL */ 
		RCC_PLLCmd( ENABLE );

		/* Wait till PLL is ready */
		while( RCC_GetFlagStatus( RCC_FLAG_PLLRDY ) == RESET )
		{
		}

		/* Select PLL as system clock source */
		RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK );

		/* Wait till PLL is used as system clock source */
    	while( RCC_GetSYSCLKSource( ) != 0x08 )
    	{
    	}

		/* Enable DMA1 clock */
		RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE );

		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB  | RCC_APB2Periph_GPIOC |
								RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1 | RCC_APB2Periph_ADC1, ENABLE );

		/* AFIO clock enable */
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE );
	}
	else
	{ 
		/* If HSE fails to start-up, the application will have wrong clock configuration.
           User can add here some code to deal with this error */    

		/* Go to infinite loop */
		while( 1 )
		{
		}
	}
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  	NVIC_InitTypeDef	NVIC_InitStructure;

  	/* Set the Vector Table base location at 0x08000000 */
  	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

 	/* Enable the TIM2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the EXTI1 Interrupt */
//		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQChannel;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);

 	/* Enable the USART1 Interrupt */
//  	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  	NVIC_Init(&NVIC_InitStructure);
}


/*    USART Initialization    */
void UART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;


	/* Configure USART1 Tx (PA9) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

	/* USART1 Hard configured: */
	/* Configure USART1 Rx (PA10) as input floating */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

  	/* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
        - USART Clock disabled
        - USART CPOL: Clock is active low
        - USART CPHA: Data is captured on the middle 
        - USART LastBit: The clock pulse of the last data bit is not output to 
                         the SCLK pin
  	*/

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init( USART1, &USART_InitStructure );

	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );			 				/* 使能USART1接收中断 */

	/* Enable USART1 */
	USART_Cmd( USART1, ENABLE ); 
}
/* 串口打印输出相关部分 */
#ifdef __GNUC__
	/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
       set to 'Yes') calls __io_putchar() */
	#define PUTCHAR_PROTOTYPE int __io_putchar( int ch )
#else
	#define PUTCHAR_PROTOTYPE int fputc( int ch, FILE *f )
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData( USART1, (unsigned char) ch );

	/* Loop until the end of transmission */
	while( USART_GetFlagStatus( USART1, USART_FLAG_TC ) == RESET )
	{
	}

	return ch;
}

/* Timer2 interrupt every 1ms */
void Timer_Configuration(void)
{
	/* Time base configuration */
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 36000;
	TIM_TimeBaseStructure.TIM_Prescaler = 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* TIM enable counter */
	TIM_Cmd(TIM2, ENABLE);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );
}


/* STM32F10x Configuration */
void System_Initialization(void)
{
 	/* System Clocks Configuration */
  	RCC_Config();
  	/* NVIC configuration */
  	NVIC_Configuration();

	/* UART Configuration */
	UART_Configuration();

}
