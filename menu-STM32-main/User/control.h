#ifndef __control_H
#define __control_H
#include "stm32f10x.h"                  // Device header

//全局变量的声明或定义

//uint8_t KeyDeta;


//头文件声明

#include "stm32f10x.h"            
#include "Delay.h"
#include "Timer.h"
#include "Encoder.h"
#include "Key.h"
#include "lian2.h"
#include "OLED.h"
#include "sys.h"
#include "uart.h"

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
void OLED_Menu(void);
void DataScope_Get_data(void);

#endif
