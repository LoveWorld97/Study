#ifndef __OLED_H
#define __OLED_H

#include "i2c.h"
#include "stdint.h"
#define u8 uint8_t
#define u32 uint32_t
//    一些使用例�?
//		OLED_ShowStr(0, 0, "hello world", 2);//显示字符�?
//	  OLED_ShowStr(0, 2, "hello world", 1);//显示字符�?
//	  OLED_ShowCN_STR(0, 4 , 0 , 8);
//		sprintf(num_temp_buffer,"show num:%0.2f",num);
//		OLED_ShowStr(0, 6, num_temp_buffer, 2);//显示字符�?
//		OLED_CLS();
//		OLED_DrawBMP(0,0,128,7,BMP2);

#define OLED0561_ADD 0x78 // OLED的I2C地址（禁止修改）
#define OLED_CMD 0x00          // OLED 指令（禁止修改）
#define OLED_DAT 0x40          // OLED 数据（禁止修改）

#define GB_16_num sizeof(GB_16) / sizeof(GB_16[0])
#define ASC_16_num sizeof(ASC_16) / sizeof(ASC_16[0])

typedef struct 
{
    char Index[4];
    unsigned char Msk[32];
}typFNT_GB16;
typedef struct 
{
    char Index[1];
    unsigned char Msk[16];
}typFNT_ASC16;

extern void OLED_I2C_Write_Byte(unsigned char OLED_TYPE, unsigned char I2C_Command);
extern void OLED_Init(void);                     //初始�?
extern void OLED_SetPos(unsigned char x, unsigned char y);
extern void OLED_Fill(unsigned char fill_Data); //全屏填充
extern void OLED_CLS(void);
extern void OLED_ON(void);
extern void OLED_OFF(void);

extern void show_drawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]); //显示图片（取模：阴，列行，逆，输出索引，精简�?
extern void show_char_a1type(uint8_t line, uint8_t column, char character);/*显示一个字�?*/
extern void show_string_atype(uint8_t line, uint8_t column, char *data, uint8_t len);/*显示字符�?*/
extern void show_hanzi(uint8_t line, uint8_t column, char *data);/*显示一个汉�?*/
extern void show_chs_string(uint8_t line, uint8_t column, char *data);/*显示一个中文字符串*/
extern u32 oled_pow(u8 m, u8 n);

#endif
