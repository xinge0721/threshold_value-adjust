#include "stm32f10x.h"                  // Device header
#include "lian2.H"

/**
  * 函    数：菜单的初始化
	* 参		数：无
  * 返 回 值：结构体的起点地址
*/
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


/**
  * 函    数：一级菜单，也就是选择的界面初始化
  * 参    数：line* li：指向要和他相连的结构体的地址
							int x :代表着该结构体在OLED中现实的行数
  * 返 回 值：无
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
  * 函    数：二级菜单，也就是调参的界面初始化，但这个函数时一级菜单和二级菜单的连接处
  * 参    数：line* pr：指向要和他相连的结构体的地址
							line* li：指向一级菜单的地址
							int x :代表着该结构体在OLED中现实的行数
							int y :代表着该结构体在OLED中显示的数据
							int z :代表着调阈值时，向串口发送的数据。
  * 返 回 值：无
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
  * 函    数：二级菜单，也就是调参的界面初始化
  * 参    数：line* pr：指向要和他相连的结构体的地址
							line* li：指向一级菜单的地址
							int x :代表着该结构体在OLED中现实的行数
							int y :代表着该结构体在OLED中显示的数据
							int z :代表着调阈值时，向串口发送的数据。
  * 返 回 值：无
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
  * 函    数：双向链表的初始化，也就是菜单的初始化
  * 参    数：无
  * 返 回 值：指向该链表的指针
*/
line* list_Init(void)
{
	line* l1 = line_Init();		//初始化菜单链表	
	line_tail(l1,first_line);			//第一行first_line
	line_tail(l1,second_line);		//第二行second_line   
	line_tail(l1,thirdly_line);		//第三行thirdly_line  
	
	line* pz = l1->next;					//将菜单的开关灯位付给pr

	line* l2 = line_Init();			//初始化L值的范围

	menu_tail(l2, pz, first_line, 0,97);	//连接功能与菜单的哨兵位
	menu_tail_t(l2, pz, second_line, 100,99); //创建正真的功能位，且对应的菜单位不与他的产生联系

	pz = pz->next;

	l2 = line_Init();						//初始化A值的范围

	menu_tail(l2, pz, first_line, -127,101);
	menu_tail_t(l2, pz, second_line, 127,103); 

	pz = pz->next;

	l2 = line_Init();						//初始化B值的范围
	menu_tail(l2, pz, first_line, -127,105);
	menu_tail_t(l2, pz, second_line, 127,107);
	return l1;						
}



/**
  * 函    数：切换为一级菜单
  * 参    数：无
  * 返 回 值：无
*/
void list_menu(void)
{
	OLED_Clear();				//OLED清屏，确保OLED中不会显示多于的数据。
	OLED_ShowChar(1,1,'*');
	OLED_ShowString(1,2,"L:Min or Max");//高亮一行字符串
	OLED_ShowString(2,2,"A:Min or Max");
	OLED_ShowString(3,2,"B:Min or Max");
}
/**
  * 函    数：切换为二级菜单
  * 参    数：一级菜单所指向的位置
  * 返 回 值：无
*/void list_data(line* pr)
{
	OLED_Clear();				//OLED清屏，确保OLED中不会显示多于的数据。
	OLED_ShowChar(1,1,'*');
	OLED_ShowString(1,2,"Min:");
	OLED_ShowString(2,2,"Max:");
	OLED_ShowSignedNum(1,6,pr->data,3);
	OLED_ShowSignedNum(2,6,pr->next->data,3);
}




/**
  * 函    数：调阈值模式
  * 参    数：进过初始化 line* 的结构体
  * 返 回 值：无
*/

void threshold_value(line* line_sign)
{
	char swap = 0;
	char metering;
	list_menu();//将OLED中的数据，切换为一级菜单的数据
	line* line_up = line_sign;
	line* line    = line_sign ->next;
	Key_eliminate(&KeyDeta);
	while(1)
	{
		//若是短按下按键1,则向下滚动
		if(KeyDeta == 1 && key[KeyDeta].single_flag == 1)
		{
			if (line->next == line_sign )//如果指针的下一位是哨兵位则进入条件内
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
			else			//如果指针没有指向哨兵位，则一切正常，正常的到下一位
			{
					OLED_ShowChar(line->line,1,' ');
					line = line ->next;
				if(line->line == 0)
					OLED_ShowChar(1,1,'*');
				else
					OLED_ShowChar(line->line,1,'*');

			}
			Key_eliminate(&KeyDeta); //清除按键标志位
		}
		else if( KeyDeta == 2  && key[KeyDeta].single_flag == 1)
		{
			if (line->prior == line_sign )//如果指针的下一位是哨兵位则进入条件内
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
			else			//如果指针没有指向哨兵位，则一切正常，正常的到下一位
			{
					OLED_ShowChar(line->line,1,' ');
					line = line ->prior;
				if(line->line == 0)
					OLED_ShowChar(1,1,'*');
				else
					OLED_ShowChar(line->line,1,'*');
			}
			Key_eliminate(&KeyDeta); //清除按键标志位
		}
		else if (key[KeyDeta ].key_longflag == 1 && key[KeyDeta].Key_sta == 1 )
		{
			
			if(KeyDeta == 0x01)//要是长按按键一，则且换一二级菜单
			{
				if(!swap)//切换为二级菜单
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
			else if(KeyDeta == 0x02) //要是长按按键二，则退出调阈值模式
			{
				Serial_SendByte(123);
				Key_eliminate(&KeyDeta);
				break;
			}
		}

		
		
		if(swap == 1) //若是已经进入二级菜单，则启动旋转编码器的调阈值模式
		{
			int number= Encoder_Get();				//获取自上此调用此函数后，旋转编码器的增量值，并将增量值加到Num上
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

