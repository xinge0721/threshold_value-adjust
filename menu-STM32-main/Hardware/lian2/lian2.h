#ifndef __lian2_H
#define __lian2_H
#include <stdio.h>
#include <stdlib.h>

typedef struct line {
    struct line* prior;//ָ��ֱ��ǰ��
    int line;
    int data;
    struct line* up;
    struct line* next;//ָ��ֱ�Ӻ��
}line;

line* line_Init(void);
line* menu_Init(void);
void line_tail(line* li, int x, int y);
void menu_tail(line* pr, line* li, int x, int y);
void menu_tail_t(line* pr, line* li, int x, int y);

#endif
