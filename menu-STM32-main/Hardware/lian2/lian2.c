
#include "stm32f10x.h"                  // Device header
#include "lian2.H"

line* line_Init(void)
{
	line* li = (line*)malloc(sizeof(line));//′′?¨á′±íéú±???
	li->prior = li;
	li->next  = li;
	li->up = NULL;
	return li;
}
line* menu_Init(void)
{
	line* li = (line*)malloc(sizeof(line));//′′?¨á′±íéú±???
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
	line* l1 = line_Init();		//初始化菜单链表	
	line_tail(l1,first_line);			//第一行first_line
	line_tail(l1,second_line);		//第二行second_line   
	line_tail(l1,thirdly_line);		//第三行thirdly_line  
	
	line* pz = l1->next;					//将菜单的开关灯位付给pr

	line* l2 = line_Init();			//初始化L值的范围

	menu_tail(l2, pz, first_line, 0);	//连接功能与菜单的哨兵位
	menu_tail_t(l2, pz, second_line, 100); //创建正真的功能位，且对应的菜单位不与他的产生联系

	pz = pz->next;

	l2 = line_Init();						//初始化A值的范围

	menu_tail(l2, pz, first_line, -127);
	menu_tail_t(l2, pz, second_line, 127);

	pz = pz->next;

	l2 = line_Init();						//初始化B值的范围
	menu_tail(l2, pz, first_line, -127);
	menu_tail_t(l2, pz, second_line, 127);
	return l1;						
}
