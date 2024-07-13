#include "control.h"

int num,num1;
char KeyDeta;
int add1;
int add2;
int add3;
int add4;


int main()
{
	main_Init();			//硬件初始化
	OLED_menu();			//OLED界面初始化
	
	line* lien = list_Init(); //旋转编码器调阈值的初始化
														//接受这个结构体
														//然后传到下面的函数，即可开启调阈值模式
	threshold_value(lien);
	while(1)
	{
		
//		Key_eliminate(KeyDeta);
	}
}

void TIM4_IRQHandler(void)//10ms
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)//1ms
	{
		for(int i = 1 ;i < 3 ; i++)
		{
				Key_Scan(i);
			if(key[i].single_flag == 1 || key[i].key_longflag == 1)
			{
					KeyDeta = i;
			}	
		}
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}


/**
  * 函    数：EXTI1外部中断函数
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
  *           函数名为预留的指定名称，可以从启动文件复制
  *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
  */
void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET)		//判断是否是外部中断1号线触发的中断
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)		//PB1的下降沿触发中断，此时检测另一相PB0的电平，目的是判断旋转方向
			{
				Encoder_Count ++;					//此方向定义为正转，计数变量自增
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line1);			//清除外部中断1号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}





//uint8_t Key_list,KeyDeta,swap,speed;		//按键标志位
//uint8_t mood_work = 1,mood_menu = 1;  		//模式标志位
//uint8_t noot;
//int electrical_speed;

//typedef enum
//{									//各个字符对应的行号
//	menu_light = 1,				 	//亮灯灭灯
//	menu_electrical = 5,			//电机控制
//	menu_temperature = 9,			//温度控制
//	menu_light_green = 13,			//绿灯：
//	menu_light_red   = 17,			//红灯：
//	menu_electrical_switch = 21,	//开机：
//	menu_electrical_speed  = 25,	//转速：
//}word;

//typedef enum 
//{
//	first_line    = 1,  //第一行
//	second_line   = 2,	//第二行
//	thirdly_line  = 3,  //第三行
//	fourthly_line = 4,  //第四行

//}line_number;

//void menu(line* l1)
//{
//	line* ps  = l1->next;
//	while(ps != l1)
//	{
//		OLED_ShowNum(ps->data,1,ps->line,4);
//		ps = ps->next;
//	}
//}


//int main(void)
//{
//	
//	
//	line* l1 = line_Init();		//初始化菜单链表	
//	line_tail(l1,first_line,menu_light);
//	line_tail(l1,second_line,menu_electrical);
//	line_tail(l1,thirdly_line,menu_temperature);
//	
//	menu(l1);					//将菜单打印在屏幕上
//	
//	line* pz = l1->next;		//将菜单的开关灯位付给pr

//	line* l2 = line_Init();		//初始化开灯的功能链表

//	menu_tail(l2, pz, first_line, menu_light_green);	//连接功能与菜单的哨兵位
//	menu_tail_t(l2, pz, second_line, menu_light_red); //创建正真的功能位，且对应的菜单位不与他的产生联系

//	pz = pz->next;

//	line* l3 = line_Init();		//初始化电机的功能链表

//	menu_tail(l3, pz, first_line, menu_electrical_switch);
//	menu_tail_t(l3, pz, second_line, menu_electrical_speed);

//	pz = pz->next;

//	line* l4 = line_Init();		//初始化温度的功能链表
//	menu_tail(l4, pz, first_line, 29);


//	
//	line* pr = l1->next;		//创造一个指针指向菜单哨兵位的下一位
//	
//	OLED_ShowCharsentbright(pr->data,1,pr->line,4);		//提前将菜单第一列高亮
//	line* pt = l1;
//	line* ps = pr;									

//	while (1)
//	{
//		switch (KeyDeta)		//检测按键是否被按下
//		{
//			case 1:				//如果是按键一，就向下滚动
//				if (pr->next == pt )//如果指针的下一位是哨兵位则进入条件内
//					{
//						if(swap == 0)
//							mood_menu = 1;
//						else if(swap == 1)
//							mood_work = 1;
//						OLED_ShowCharsent(pr->data,1,pr->line,4);//将该行的高亮恢复
//						pr = pr->next ->next;					 //连走两次next，绕过哨兵位
//						OLED_ShowCharsentbright(pr->data,1,pr->line,4);//将第一行高亮
//					}
//				else			//如果指针没有指向哨兵位，则一切正常，正常的到下一位
//				{
//					ps = pr;
//					pr = pr->next;
//					OLED_ShowCharsentbright(pr->data,1,pr->line,4);	//将该行的高亮恢复
//					OLED_ShowCharsent(ps->data,1,ps->line,4);		//下一行高亮
//					if(swap == 0)
//						mood_menu ++;
//					else if(swap == 1)
//						mood_work ++;				}
//				Delay_ms(100);							//暂停一会，以防出错
//				KeyDeta = 0;							//将按键标志位清零防止出现反复执行的情况
//				break;
//			case 2:										//和case 1相同但这是向上的
//				if (pr->prior == pt )
//					{	
//						if(swap == 0)
//							mood_menu = 3;
//						else if(swap == 1)
//							mood_work = 2;
//						OLED_ShowCharsent(pr->data,1,pr->line,4);
//						pr = pr->prior ->prior;
//						OLED_ShowCharsentbright(pr->data,1,pr->line,4);
//						Delay_ms(100);
//					}
//				else
//				{
//					mood_menu--;
//					ps = pr;
//					pr = pr->prior;
//					OLED_ShowCharsentbright(pr->data,1,pr->line,4);
//					OLED_ShowCharsent(ps->data,1,ps->line,4);
//					Delay_ms(100);
//					if(swap == 0)
//						mood_menu --;
//					else if(swap == 1)
//						mood_work --;	
//				}
//				KeyDeta = 0;
//				break;
//			case 3:					//界面切换
//				if(!swap)		
//				{
//					pt = (pr->up) -> prior;
//					swap = 1;
//				}
//				else
//				{
//					pt = l1;
//					swap = 0;
//				}
//				speed = 0;			//将speed清零，防止加多	
//				pr = pr->up;		//将转换指针付给pr，则此时pr将指向功能菜单，反之亦然
//				OLED_Clear();		//清空屏幕防止菜单界面或者功能界面互相干扰
//				menu(pt);			//重新打印新界面
//				OLED_ShowCharsentbright(pr->data,1,pr->line,4);		//提前将菜单第一列高亮
//				KeyDeta = 0;		//将按键标志位清零防止出现反复执行的情况
//				break;
//			case 4:
//				if(swap)
//				{
//					if(speed == 4)
//						speed = 0;
//					speed ++;
//				}
//				Delay_ms(100);							//暂停一会，以防出错
//				KeyDeta = 0;		//将按键标志位清零防止出现反复执行的情况
//			break;
//		}
//			if(swap == 1)
//			{
//				if(mood_menu == 1 &&  speed != 0)
//				{
//					if(mood_work == 1)
//					{
//						LED1_Turn();
//						
//						Delay_ms(100);
//					}
//					else if(mood_work == 2)
//					{
//						LED2_Turn();
//					}
//					speed = 0;
//				}
//				else if (mood_menu == 2 &&  speed != 0)
//				{
//					if(mood_work == 1)
//					{
//						noot = ~noot;
//						Delay_ms(100);
//					}
//					if(mood_work == 2 && noot != 0)
//					{
//						electrical_speed = electrical_speed + (speed*25);
//						if(electrical_speed > 100)
//							electrical_speed = -200;
//						Motor_SetSpeed(electrical_speed);
//					}					
//					speed = 0;

//				}
//			}
//	}
//}

//void TIM4_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)//1ms
//	{
//		Key_list++;
//		if(Key_list == 10)
//		{
//			KeyDeta  = Key_Scan();
//			Key_list = 0;
//		}
//		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//	}
//}


