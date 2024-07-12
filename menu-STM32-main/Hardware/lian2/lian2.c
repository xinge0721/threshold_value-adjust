
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



//回到一级菜单
void list_menu(void)
{
	OLED_Clear();				//OLED清屏，确保OLED中不会显示多于的数据。
	OLED_ShowString_extrude(1,1,"L:Min or Max");//高亮一行字符串
	OLED_ShowString(2,1,"A:Min or Max");
	OLED_ShowString(3,1,"B:Min or Max");
}

//调阈值模式
//void threshold_value(line* line)
//{
//	list_menu();//将OLED中的数据，切换为一级菜单的数据
//	while(1)
//	{
//		if(KeyDeta == 1)
//		{
//			if (pr->next == pt )//如果指针的下一位是哨兵位则进入条件内
//			{
//				if(swap == 0)
//					mood_menu = 1;
//				else if(swap == 1)
//					mood_work = 1;
//				OLED_ShowCharsent(pr->data,1,pr->line,4);//将该行的高亮恢复
//				pr = pr->next ->next;					 //连走两次next，绕过哨兵位
//				OLED_ShowCharsentbright(pr->data,1,pr->line,4);//将第一行高亮
//			}
//			else			//如果指针没有指向哨兵位，则一切正常，正常的到下一位
//			{
//				ps = pr;
//				pr = pr->next;
//				OLED_ShowCharsentbright(pr->data,1,pr->line,4);	//将该行的高亮恢复
//				OLED_ShowCharsent(ps->data,1,ps->line,4);		//下一行高亮
//				if(swap == 0)
//					mood_menu ++;
//				else if(swap == 1)
//					mood_work ++;				}
//			Delay_ms(100);							//暂停一会，以防出错
//			KeyDeta = 0;							//将按键标志位清零防止出现反复执行的情况
//		}
//		else if(KeyDeta == 2)
//		{
//		
//		}
//	}
//}

