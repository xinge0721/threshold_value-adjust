#ifndef __control_H
#define __control_H
#include "stm32f10x.h"                  // Device header

//ȫ�ֱ�������������

//uint8_t KeyDeta;


//ͷ�ļ�����

#include "stm32f10x.h"            
#include "Delay.h"
#include "Timer.h"
#include "Encoder.h"
#include "Key.h"
#include "lian2.h"
#include "OLED.h"
#include "sys.h"
#include "uart.h"

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
void OLED_Menu(void);
void DataScope_Get_data(void);

#endif
