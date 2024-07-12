#ifndef __lian2_H
#define __lian2_H

#include "control.h"


typedef struct line {
    struct line* prior;//???¨°?¡À?¨®?¡ã?¡Â
    int line;
    int data;
    struct line* up;
    struct line* next;//???¨°?¡À?¨®o¨®?¨¬
}line;

line* list_Init(void);
line* menu_Init(void);
void line_tail(line* li, int x);
void menu_tail(line* pr, line* li, int x, int y);
void menu_tail_t(line* pr, line* li, int x, int y);
void list_menu(void);


#endif
