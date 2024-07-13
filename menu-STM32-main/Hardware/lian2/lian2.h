#ifndef __lian2_H
#define __lian2_H

#include "control.h"


typedef struct line {
    struct line* prior;//???и░?б└?ио?бу?б┬
    int line;
    int data;
    struct line* up;
    struct line* next;//???и░?б└?иоoио?им
}line;

line* list_Init(void);
line* menu_Init(void);
void line_tail(line* li, int x);
void menu_tail(line* pr, line* li, int x, int y);
void menu_tail_t(line* pr, line* li, int x, int y);
void list_menu(void);
void threshold_value(line* line_sign);


#endif
