#include "stm32f10x.h"                  // Device header
#include "lian2.H"

/**
  * ��    �����˵��ĳ�ʼ��
	* ��		������
  * �� �� ֵ���ṹ�������ַ
*/
line* line_Init(void)
{
	line* li = (line*)malloc(sizeof(line));//���?���������������???
	li->prior = li;
	li->next  = li;
	li->up = NULL;
	return li;
}
line* menu_Init(void)
{
	line* li = (line*)malloc(sizeof(line));//���?���������������???
	li->data = li->line = 0;
	li->next = li->up = li->prior = li;
	return li;
}


/**
  * ��    ����һ���˵���Ҳ����ѡ��Ľ����ʼ��
  * ��    ����line* li��ָ��Ҫ���������Ľṹ��ĵ�ַ
							int x :�����Ÿýṹ����OLED����ʵ������
  * �� �� ֵ����
*/
void line_tail(line* li, int x)
{
	line* ps = (line*)malloc(sizeof(line));
	ps->line = x;
	ps->up = NULL;
	ps->prior = li->prior;
	ps->next = (li->prior)->next;
	(li->prior)->next = ps;
	li->prior = (li->prior)->next;
}


/**
  * ��    ���������˵���Ҳ���ǵ��εĽ����ʼ�������������ʱһ���˵��Ͷ����˵������Ӵ�
  * ��    ����line* pr��ָ��Ҫ���������Ľṹ��ĵ�ַ
							line* li��ָ��һ���˵��ĵ�ַ
							int x :�����Ÿýṹ����OLED����ʵ������
							int y :�����Ÿýṹ����OLED����ʾ������
							int z :�����ŵ���ֵʱ���򴮿ڷ��͵����ݡ�
  * �� �� ֵ����
*/
void menu_tail(line* pr,line* li, int x, int y,int z)
{
	line* ps   = (line*)malloc(sizeof(line));
	ps->line   = x;
	ps->data   = y;
	ps->Serial = z;
	ps->up = li;
 	li->up = ps;

	ps->prior = pr->prior;
	ps->next = (pr->prior)->next;
	(pr->prior)->next = ps;
	pr->prior = (pr->prior)->next;
}
/**
  * ��    ���������˵���Ҳ���ǵ��εĽ����ʼ��
  * ��    ����line* pr��ָ��Ҫ���������Ľṹ��ĵ�ַ
							line* li��ָ��һ���˵��ĵ�ַ
							int x :�����Ÿýṹ����OLED����ʵ������
							int y :�����Ÿýṹ����OLED����ʾ������
							int z :�����ŵ���ֵʱ���򴮿ڷ��͵����ݡ�
  * �� �� ֵ����
*/
void menu_tail_t(line* pr, line* li, int x, int y,int z)
{
	line* ps = (line*)malloc(sizeof(line));
	ps->line  = x;
	ps->data  = y;
	ps->Serial = z;
	ps->up = li;
	ps->prior = pr->prior;
	ps->next = (pr->prior)->next;
	(pr->prior)->next = ps;
	pr->prior = (pr->prior)->next;
}


/**
  * ��    ����˫������ĳ�ʼ����Ҳ���ǲ˵��ĳ�ʼ��
  * ��    ������
  * �� �� ֵ��ָ��������ָ��
*/
line* list_Init(void)
{
	line* l1 = line_Init();		//��ʼ���˵�����	
	line_tail(l1,first_line);			//��һ��first_line
	line_tail(l1,second_line);		//�ڶ���second_line   
	line_tail(l1,thirdly_line);		//������thirdly_line  
	
	line* pz = l1->next;					//���˵��Ŀ��ص�λ����pr

	line* l2 = line_Init();			//��ʼ��Lֵ�ķ�Χ

	menu_tail(l2, pz, first_line, 0,97);	//���ӹ�����˵����ڱ�λ
	menu_tail_t(l2, pz, second_line, 100,99); //��������Ĺ���λ���Ҷ�Ӧ�Ĳ˵�λ�������Ĳ�����ϵ

	pz = pz->next;

	l2 = line_Init();						//��ʼ��Aֵ�ķ�Χ

	menu_tail(l2, pz, first_line, -127,101);
	menu_tail_t(l2, pz, second_line, 127,103); 

	pz = pz->next;

	l2 = line_Init();						//��ʼ��Bֵ�ķ�Χ
	menu_tail(l2, pz, first_line, -127,105);
	menu_tail_t(l2, pz, second_line, 127,107);
	return l1;						
}



/**
  * ��    �����л�Ϊһ���˵�
  * ��    ������
  * �� �� ֵ����
*/
void list_menu(void)
{
	OLED_Clear();				//OLED������ȷ��OLED�в�����ʾ���ڵ����ݡ�
	OLED_ShowChar(1,1,'*');
	OLED_ShowString(1,2,"L:Min or Max");//����һ���ַ���
	OLED_ShowString(2,2,"A:Min or Max");
	OLED_ShowString(3,2,"B:Min or Max");
}
/**
  * ��    �����л�Ϊ�����˵�
  * ��    ����һ���˵���ָ���λ��
  * �� �� ֵ����
*/void list_data(line* pr)
{
	OLED_Clear();				//OLED������ȷ��OLED�в�����ʾ���ڵ����ݡ�
	OLED_ShowChar(1,1,'*');
	OLED_ShowString(1,2,"Min:");
	OLED_ShowString(2,2,"Max:");
	OLED_ShowSignedNum(1,6,pr->data,3);
	OLED_ShowSignedNum(2,6,pr->next->data,3);
}




/**
  * ��    ��������ֵģʽ
  * ��    ����������ʼ�� line* �Ľṹ��
  * �� �� ֵ����
*/

void threshold_value(line* line_sign)
{
	char swap = 0;
	char metering;
	list_menu();//��OLED�е����ݣ��л�Ϊһ���˵�������
	line* line_up = line_sign;
	line* line    = line_sign ->next;
	Key_eliminate(&KeyDeta);
	while(1)
	{
		//���Ƕ̰��°���1,�����¹���
		if(KeyDeta == 1 && key[KeyDeta].single_flag == 1)
		{
			if (line->next == line_sign )//���ָ�����һλ���ڱ�λ�����������
			{
				if(!swap)
				{
					list_menu();
				}
				else 
				{
					list_data(line);
				}
				line = line->next->next;
			}
			else			//���ָ��û��ָ���ڱ�λ����һ�������������ĵ���һλ
			{
					OLED_ShowChar(line->line,1,' ');
					line = line ->next;
				if(line->line == 0)
					OLED_ShowChar(1,1,'*');
				else
					OLED_ShowChar(line->line,1,'*');

			}
			Key_eliminate(&KeyDeta); //���������־λ
		}
		else if( KeyDeta == 2  && key[KeyDeta].single_flag == 1)
		{
			if (line->prior == line_sign )//���ָ�����һλ���ڱ�λ�����������
			{
				if(!swap)
				{
					OLED_ShowChar(line->line,1,' ');
					line = line->prior->prior;
					OLED_ShowChar(line->line,1,'*');
				}
				else 
				{
					OLED_ShowChar(line->line,1,' ');
					line = line->prior->prior;
					OLED_ShowChar(line->line,1,'*');
				}
			}
			else			//���ָ��û��ָ���ڱ�λ����һ�������������ĵ���һλ
			{
					OLED_ShowChar(line->line,1,' ');
					line = line ->prior;
				if(line->line == 0)
					OLED_ShowChar(1,1,'*');
				else
					OLED_ShowChar(line->line,1,'*');
			}
			Key_eliminate(&KeyDeta); //���������־λ
		}
		else if (key[KeyDeta ].key_longflag == 1 && key[KeyDeta].Key_sta == 1 )
		{
			
			if(KeyDeta == 0x01)//Ҫ�ǳ�������һ�����һ�һ�����˵�
			{
				if(!swap)//�л�Ϊ�����˵�
				{
					swap = !swap;
					line_sign = line;
					line = line->up;
					list_data(line);
				}
				else
				{
					swap = !swap;
					line = line_up->next;
					line_sign = line_up;
					list_menu();
				}
				Key_eliminate(&KeyDeta);

			}
			else if(KeyDeta == 0x02) //Ҫ�ǳ��������������˳�����ֵģʽ
			{
				Serial_SendByte(123);
				Key_eliminate(&KeyDeta);
				break;
			}
		}

		
		
		if(swap == 1) //�����Ѿ���������˵�����������ת�������ĵ���ֵģʽ
		{
			int number= Encoder_Get();				//��ȡ���ϴ˵��ô˺�������ת������������ֵ����������ֵ�ӵ�Num��
			line->data += number ;
			OLED_ShowSignedNum(line->line,6,line->data,3);
			metering += number  > 0 ? number  : - number ;
			for(int i = 0 ; i < metering ;i++)
			{
				if(number >= 0 )
					Serial_SendByte(line->Serial);
				else 
					Serial_SendByte((line->Serial)+1);
			}
			metering = 0;
		}
	}
}

