#ifndef __U8G2_TEST_H
#define __U8G2_TEST_H

#include "main.h"
#include "u8g2.h"
#include "stdio.h"

void delay_us(uint32_t time);
uint8_t STM32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

void Draw_Line_Test(u8g2_t *u8g2);
void process_Test(u8g2_t *u8g2);
void font_Test(u8g2_t *u8g2);
void u8g2_DrawBox_Test(u8g2_t *u8g2);
void DrawBox_Test(u8g2_t *u8g2);
void u8g2_DrawCircle_Test(u8g2_t *u8g2);
void u8g2_DrawEllipse_Test(u8g2_t *u8g2);
#endif // __U8G2_TEST_H