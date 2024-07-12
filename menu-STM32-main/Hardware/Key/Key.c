#include "key.h"


/**
  * 函    数：按键初始化
  * 参    数：无
  * 返 回 值：无
  */
void Key_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
	GPIO_InitTypeDef GPIO_Key_InitStructure;
	GPIO_Key_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Key_InitStructure.GPIO_Pin=GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Key_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_Key_InitStructure);
}

/**
  * 函    数：按键消抖-长按、单点
  * 参    数：无
  * 返 回 值：无
*/
Keys key[4]={0};//初始化

void Key_Scan(uint8_t i)
{
	int data = i + 3;
	key[i].Key_sta = PFin(data);
	
	switch(key[i].judge_sta)
	{
		case 0:
		{
				if(key[i].Key_sta == 0)
				{
					key[i].judge_sta  = 1;
					key[i].ky_time  = 0;
				}
				break;
		}
		case  1:
		{
			if(key[i].Key_sta  == 0)
			{
				key[i].judge_sta = 2;
				
			}
			else
			{
				key[i].judge_sta = 0;
			}
			break;
		}
		case 2:
		{
				if(key[i].Key_sta == 1)
				{
						key[i].judge_sta = 0;
					if(key[i].ky_time <= 70)
					{
						key[i].single_flag = 1;
					}
				}
				else
				{
					key[i].ky_time++;
					if(key[i].ky_time >= 70)
					{
						key[i].key_longflag = 1;
					}
				}
			break;
		}
		
	}
}

