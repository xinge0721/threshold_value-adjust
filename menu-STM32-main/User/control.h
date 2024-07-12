#ifndef __control_H
#define __control_H
#include "stm32f10x.h"                  // Device header

//ȫ�ֱ�������������

extern int16_t Encoder_Count;					//ȫ�ֱ��������ڼ�����ת������������ֵ

typedef enum
{									//�����ַ���Ӧ���к�
	L_Min = 0,				 	//�������
	L_Max = 100,			//�������
	menu_temperature = 9,			//�¶ȿ���
	menu_light_green = 13,			//�̵ƣ�
	menu_light_red   = 17,			//��ƣ�
	menu_electrical_switch = 21,	//������
	menu_electrical_speed  = 25,	//ת�٣�
}word;

typedef enum 
{
	first_line    = 1,  //��һ��
	second_line   = 2,	//�ڶ���
	thirdly_line  = 3,  //������
	fourthly_line = 4,  //������

}line_number;

//ͷ�ļ�����

#include "stm32f10x.h"            
#include "Delay.h"
#include "Timer.h"
#include "Encoder.h"
#include "Key.h"
#include "lian2.h"
#include "OLED.h"
#include "sys.h"
#include "Serial.h"
//��׼��ͷ�ļ�����

#include <math.h>
#include <stdio.h>
#include <string.h> 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

//��������
void main_Init(void);
void OLED_menu(void);

#endif
