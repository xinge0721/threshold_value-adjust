#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>
#include "stm32f10x.h"                  // Device header

extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[];

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);
void app_Init(void);
void Serial_SendByte1(uint8_t Byte);
void Serial_SendPacket(void);
uint8_t Serial_GetRxFlag(void);
void sne5_Init(void);
void Serial_SendByte5(uint8_t Byte);
#endif
