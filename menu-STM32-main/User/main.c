#include "control.h"

int num;
int main()
{
	main_Init();
	while(1)
	{
		if(PFin(2) || PFin(3))
			num++;
		OLED_ShowNum(1,1,num,1);

	}
}

//void TIM4_IRQHandler(void)//10ms
//{
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)//1ms
//	{
//		for(int i = 0 ;i < 4 ; i++)
//		{
//				Key_Scan(i);
//				if(key[i].single_flag == 1 || key[i].key_longflag == 1)
//				KeyDeta = i + 1;
//		}
//	}
//	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//}



//uint8_t Key_list,KeyDeta,swap,speed;		//������־λ
//uint8_t mood_work = 1,mood_menu = 1;  		//ģʽ��־λ
//uint8_t noot;
//int electrical_speed;

//typedef enum
//{									//�����ַ���Ӧ���к�
//	menu_light = 1,				 	//�������
//	menu_electrical = 5,			//�������
//	menu_temperature = 9,			//�¶ȿ���
//	menu_light_green = 13,			//�̵ƣ�
//	menu_light_red   = 17,			//��ƣ�
//	menu_electrical_switch = 21,	//������
//	menu_electrical_speed  = 25,	//ת�٣�
//}word;

//typedef enum 
//{
//	first_line    = 1,  //��һ��
//	second_line   = 2,	//�ڶ���
//	thirdly_line  = 3,  //������
//	fourthly_line = 4,  //������

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
//	line* l1 = line_Init();		//��ʼ���˵�����	
//	line_tail(l1,first_line,menu_light);
//	line_tail(l1,second_line,menu_electrical);
//	line_tail(l1,thirdly_line,menu_temperature);
//	
//	menu(l1);					//���˵���ӡ����Ļ��
//	
//	line* pz = l1->next;		//���˵��Ŀ��ص�λ����pr

//	line* l2 = line_Init();		//��ʼ�����ƵĹ�������

//	menu_tail(l2, pz, first_line, menu_light_green);	//���ӹ�����˵����ڱ�λ
//	menu_tail_t(l2, pz, second_line, menu_light_red); //��������Ĺ���λ���Ҷ�Ӧ�Ĳ˵�λ�������Ĳ�����ϵ

//	pz = pz->next;

//	line* l3 = line_Init();		//��ʼ������Ĺ�������

//	menu_tail(l3, pz, first_line, menu_electrical_switch);
//	menu_tail_t(l3, pz, second_line, menu_electrical_speed);

//	pz = pz->next;

//	line* l4 = line_Init();		//��ʼ���¶ȵĹ�������
//	menu_tail(l4, pz, first_line, 29);


//	
//	line* pr = l1->next;		//����һ��ָ��ָ��˵��ڱ�λ����һλ
//	
//	OLED_ShowCharsentbright(pr->data,1,pr->line,4);		//��ǰ���˵���һ�и���
//	line* pt = l1;
//	line* ps = pr;									

//	while (1)
//	{
//		switch (KeyDeta)		//��ⰴ���Ƿ񱻰���
//		{
//			case 1:				//����ǰ���һ�������¹���
//				if (pr->next == pt )//���ָ�����һλ���ڱ�λ�����������
//					{
//						if(swap == 0)
//							mood_menu = 1;
//						else if(swap == 1)
//							mood_work = 1;
//						OLED_ShowCharsent(pr->data,1,pr->line,4);//�����еĸ����ָ�
//						pr = pr->next ->next;					 //��������next���ƹ��ڱ�λ
//						OLED_ShowCharsentbright(pr->data,1,pr->line,4);//����һ�и���
//					}
//				else			//���ָ��û��ָ���ڱ�λ����һ�������������ĵ���һλ
//				{
//					ps = pr;
//					pr = pr->next;
//					OLED_ShowCharsentbright(pr->data,1,pr->line,4);	//�����еĸ����ָ�
//					OLED_ShowCharsent(ps->data,1,ps->line,4);		//��һ�и���
//					if(swap == 0)
//						mood_menu ++;
//					else if(swap == 1)
//						mood_work ++;				}
//				Delay_ms(100);							//��ͣһ�ᣬ�Է�����
//				KeyDeta = 0;							//��������־λ�����ֹ���ַ���ִ�е����
//				break;
//			case 2:										//��case 1��ͬ���������ϵ�
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
//			case 3:					//�����л�
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
//				speed = 0;			//��speed���㣬��ֹ�Ӷ�	
//				pr = pr->up;		//��ת��ָ�븶��pr�����ʱpr��ָ���ܲ˵�����֮��Ȼ
//				OLED_Clear();		//�����Ļ��ֹ�˵�������߹��ܽ��滥�����
//				menu(pt);			//���´�ӡ�½���
//				OLED_ShowCharsentbright(pr->data,1,pr->line,4);		//��ǰ���˵���һ�и���
//				KeyDeta = 0;		//��������־λ�����ֹ���ַ���ִ�е����
//				break;
//			case 4:
//				if(swap)
//				{
//					if(speed == 4)
//						speed = 0;
//					speed ++;
//				}
//				Delay_ms(100);							//��ͣһ�ᣬ�Է�����
//				KeyDeta = 0;		//��������־λ�����ֹ���ַ���ִ�е����
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


