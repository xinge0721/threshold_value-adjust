#ifndef __control_H
#define __control_H
#include "stm32f10x.h"                  // Device header

//全局变量的声明或定义

extern int16_t Encoder_Count;					//全局变量，用于计数旋转编码器的增量值

typedef enum
{									//各个字符对应的行号
	L_Min = 0,				 	//亮灯灭灯
	L_Max = 100,			//电机控制
	menu_temperature = 9,			//温度控制
	menu_light_green = 13,			//绿灯：
	menu_light_red   = 17,			//红灯：
	menu_electrical_switch = 21,	//开机：
	menu_electrical_speed  = 25,	//转速：
}word;

typedef enum 
{
	first_line    = 1,  //第一行
	second_line   = 2,	//第二行
	thirdly_line  = 3,  //第三行
	fourthly_line = 4,  //第四行

}line_number;

//头文件声明

#include "stm32f10x.h"            
#include "Delay.h"
#include "Timer.h"
#include "Encoder.h"
#include "Key.h"
#include "lian2.h"
#include "OLED.h"
#include "sys.h"
#include "Serial.h"
//标准库头文件声明

#include <math.h>
#include <stdio.h>
#include <string.h> 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

//函数声明
void main_Init(void);
void OLED_menu(void);

#endif
