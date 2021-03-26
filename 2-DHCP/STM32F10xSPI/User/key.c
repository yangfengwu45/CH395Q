/**
  ******************************************************************************
  * @file    key.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   按键检测模板
  ******************************************************************************
  一,使用说明:检测引脚(PB5)
		1,把以下程序放在1ms定时器中断中
			if(Key1Value[1])
				Key1Value[5]++;
			else
				Key1Value[5]=0;

			if(Key1Value[2])
				Key1Value[6]++;
			else
				Key1Value[6]=0;
		
		2,主循环调用使用
			while(1)
			{
				Key1Function();
				
				//例1:检测到按键按下执行某段代码
				if(Key1Value[3] == 1)
				{
					Key1Value[3] = 0;//清零以后,只有按键松开再按下的时候才会进入
					//执行的代码
				}

				//例2:检测到按键按下,然后根据按下时间执行某段代码
				if(Key1Value[3] == 1)
				{
					if(Key1Value[5]>=3000)//按下时间大于3S
					{
						Key1Value[3] = 0;//清零以后,只有按键松开再按下的时候才会进入
						//执行的代码
					}
				}
				
				//例3:检测到按键松开执行某段代码
				if(Key1Value[4] == 1)
				{
					Key1Value[4] = 0;//清零以后,只有按键按下然后松开的时候才会进入
					//执行的代码
				}
				
				//例4:检测到按键松开,然后根据松开时间执行某段代码
				if(Key1Value[4] == 1)
				{
					if(Key1Value[6]>=3000)//松开时间大于3S
					{
						Key1Value[4] = 0;//清零以后,只有按键按下再松开的时候才会进入
						//执行的代码
					}
				}
			}
  ******************************************************************************
  */

#define __KEY_C_
#include "key.h"

int Key1Value[7]={0};//消抖变量 按下标记 松开标记 按下标记拷贝  松开标记拷贝 按下时间(Ms) 松开时间(Ms)
	
/**
* @brief  按键处理
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
void Key1Function(void)
{
  if(Key1PinIn == Key1Down)
	{
		if(Key1Value[1] == 0)
		{
			Key1Value[0]++;
			if(Key1Value[0]>=500)//按下以后进入
			{
				Key1Value[0] = 0;//Cnt
				Key1Value[2] = 0;//UP
				Key1Value[1] = 1;//Down
				Key1Value[3] = 1;//DownCopy
				Key1Value[4] = 0;//UpCopy
			}
		}
	}
	else
	{
		Key1Value[0]++;
		if(Key1Value[0]>2000)
		{
			Key1Value[0]=0;
			if(Key1Value[1]==1)//按下后松开后进入
			{
				Key1Value[2] = 1;//UP
				Key1Value[1] = 0;//Down
				Key1Value[3] = 0;//DownCopy
				Key1Value[4] = 1;//UpCopy
			}
		}
	}
}
