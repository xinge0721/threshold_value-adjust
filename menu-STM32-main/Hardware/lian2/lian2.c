
#include "stm32f10x.h"                  // Device header
#include "lian2.H"

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


void menu_tail(line* pr,line* li, int x, int y)
{
	line* ps = (line*)malloc(sizeof(line));
	ps->line = x;
	ps->data = y;

	ps->up = li;
 	li->up = ps;

	ps->prior = pr->prior;
	ps->next = (pr->prior)->next;
	(pr->prior)->next = ps;
	pr->prior = (pr->prior)->next;
}

void menu_tail_t(line* pr, line* li, int x, int y)
{
	line* ps = (line*)malloc(sizeof(line));
	ps->line = x;
	ps->data = y;

	ps->up = li;
	ps->prior = pr->prior;
	ps->next = (pr->prior)->next;
	(pr->prior)->next = ps;
	pr->prior = (pr->prior)->next;
}



line* list_Init(void)
{
	line* l1 = line_Init();		//��ʼ���˵�����	
	line_tail(l1,first_line);			//��һ��first_line
	line_tail(l1,second_line);		//�ڶ���second_line   
	line_tail(l1,thirdly_line);		//������thirdly_line  
	
	line* pz = l1->next;					//���˵��Ŀ��ص�λ����pr

	line* l2 = line_Init();			//��ʼ��Lֵ�ķ�Χ

	menu_tail(l2, pz, first_line, 0);	//���ӹ�����˵����ڱ�λ
	menu_tail_t(l2, pz, second_line, 100); //��������Ĺ���λ���Ҷ�Ӧ�Ĳ˵�λ�������Ĳ�����ϵ

	pz = pz->next;

	l2 = line_Init();						//��ʼ��Aֵ�ķ�Χ

	menu_tail(l2, pz, first_line, -127);
	menu_tail_t(l2, pz, second_line, 127);

	pz = pz->next;

	l2 = line_Init();						//��ʼ��Bֵ�ķ�Χ
	menu_tail(l2, pz, first_line, -127);
	menu_tail_t(l2, pz, second_line, 127);
	return l1;						
}
