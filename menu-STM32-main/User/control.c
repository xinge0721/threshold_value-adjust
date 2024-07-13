#include "control.h"

unsigned char Send_Count; //串口需要发送的数据个数

void main_Init(void)
{
	Stm32_Clock_Init(9);            //系统时钟设置
	delay_init(72);    							//延时初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();										//OLED初始化
	Key_Init();											//按键初始化
	Timer_Init();										//定时器初始化
	Encoder_Init();									//旋转编码器初始化
	Serial_Init();
}

void OLED_menu(void)
{
		OLED_ShowString(1,1,"L:Min or Max");
		OLED_ShowString(2,1,"A:Min or Max");
		OLED_ShowString(3,1,"B:Min or Max");
}


void OLED_data(line* l1)
{
	line* ps  = l1->next;
	while(ps != l1)
	{
		OLED_ShowNum(ps->data,1,ps->line,4);
		ps = ps->next;
	}
}


unsigned char Send_Count; //串口需要发送的数据个数

