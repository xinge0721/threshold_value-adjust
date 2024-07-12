#include "control.h"

unsigned char Send_Count; //串口需要发送的数据个数

void main_Init(void)
{
	OLED_Init();
	Key_Init();
	Encoder_Init();
}


void OLED_menu(line* l1)
{
	line* ps  = l1->next;
	while(ps != l1)
	{
		OLED_ShowNum(ps->data,1,ps->line,4);
		ps = ps->next;
	}
}


unsigned char Send_Count; //串口需要发送的数据个数

