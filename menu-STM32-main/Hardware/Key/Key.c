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
	GPIO_Key_InitStructure.GPIO_Pin=GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Key_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_Key_InitStructure);
}

/**
  * 函    数：按键消抖-长按、单点
  * 参    数：无
  * 返 回 值：无
*/
Keys key[3]={0};//初始化

void Key_Scan(uint8_t i)
{
	int data = i + 2;
	key[i].Key_sta = PFin(data);
	
	switch(key[i].judge_sta)
			{
				case 0:
				{
					if(key[i].Key_sta ==0) 
					{
						key[i].judge_sta =1;
						key[i].ky_time = 0;//按键按下时间清0
					}
				}
				break;
				case 1:
				{
					if(key[i].Key_sta ==0)
					{
						key[i].judge_sta =2;
					}
					else
					{
						key[i].judge_sta =0;
					}
				}
				break;
				case 2:
				{
					if(key[i].Key_sta ==1)//松开
					{
						key[i].judge_sta = 0;
						if(key[i].ky_time<70)//小于700ms
						{
							key[i].ky_time = 0;
							key[i].single_flag  = 1;//小于700ms松开手在确认
							key[i].key_longflag = 0;
						}
					}
					else									//按下
					{
						key[i].ky_time++;
						if(key[i].ky_time>70)//大于700ms，到了700ms就执行长按功能
						{
							key[i].key_longflag = 1;
						}
					}
				}
				break;
		}
}

/**
  * 函    数：消除按键标志位
  * 参    数：无
  * 返 回 值：无
*/
void Key_eliminate(char* KeyDeta)
{
	if(key[*KeyDeta ].Key_sta == 1)
	{
			key[*KeyDeta ].judge_sta = 0;
			key[*KeyDeta ].single_flag = 0;
			key[*KeyDeta ].key_longflag = 0;
			key[*KeyDeta ].ky_time = 0;
			*KeyDeta	 = 0;
	}
}




