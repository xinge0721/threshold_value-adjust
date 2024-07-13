#include "control.h"

unsigned char Send_Count; //������Ҫ���͵����ݸ���

void main_Init(void)
{
	Stm32_Clock_Init(9);            //ϵͳʱ������
	delay_init(72);    							//��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();										//OLED��ʼ��
	Key_Init();											//������ʼ��
	Timer_Init();										//��ʱ����ʼ��
	Encoder_Init();									//��ת��������ʼ��
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


unsigned char Send_Count; //������Ҫ���͵����ݸ���

