#include "stm32f10x.h"                  // Device header
#include "lian2.H"

line* line_Init(void)
{
	line* li = (line*)malloc(sizeof(line));//创建链表哨兵位
	li->prior = li;
	li->next  = li;
	li->up = NULL;
	return li;
}
line* menu_Init(void)
{
	line* li = (line*)malloc(sizeof(line));//创建链表哨兵位
	li->data = li->line = 0;
	li->next = li->up = li->prior = li;
	return li;
}

void line_tail(line* li, int x, int y)
{
	line* ps = (line*)malloc(sizeof(line));
	ps->line = y;
	ps->data = x;
	ps->up = NULL;
	ps->prior = li->prior;
	ps->next = (li->prior)->next;
	(li->prior)->next = ps;
	li->prior = (li->prior)->next;
}

void menu_tail(line* pr,line* li, int x, int y)
{
	line* ps = (line*)malloc(sizeof(line));
	ps->line = y;
	ps->data = x;

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
	ps->line = y;
	ps->data = x;

	ps->up = li;
	ps->prior = pr->prior;
	ps->next = (pr->prior)->next;
	(pr->prior)->next = ps;
	pr->prior = (pr->prior)->next;
}




