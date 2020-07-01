#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "oled.h"

extern void display_time(uint8_t line, uint8_t column);
extern void display_date(uint8_t line, uint8_t column);
#endif /*__DISPLAY_H*/