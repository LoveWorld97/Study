#include "u8g2_test.h"

void delay_us(uint32_t time)
{
    uint32_t i = 8*time;
    while (i--);
}
uint8_t STM32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch (msg)
    {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8
        __NOP();
        break;			                // can be used to setup pins
    case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
        __NOP();
        break;
    case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
        __NOP();
        break;
    case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
        for (uint16_t n = 0; n < 320; n++)
        {
            __NOP();
        }
        break;
    case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
        delay_us(1);
        break;
    case U8X8_MSG_DELAY_I2C:				// arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
        delay_us(5);
        break;							// arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
    case U8X8_MSG_GPIO_D0:				// D0 or SPI clock pin: Output level in arg_int
    //case U8X8_MSG_GPIO_SPI_CLOCK:
        break;
    case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
    //case U8X8_MSG_GPIO_SPI_DATA:
        break;
    case U8X8_MSG_GPIO_D2:				// D2 pin: Output level in arg_int
        break;
    case U8X8_MSG_GPIO_D3:				// D3 pin: Output level in arg_int
        break;
    case U8X8_MSG_GPIO_D4:				// D4 pin: Output level in arg_int
        break;
    case U8X8_MSG_GPIO_D5:				// D5 pin: Output level in arg_int
        break;
    case U8X8_MSG_GPIO_D6:				// D6 pin: Output level in arg_int
        break;
    case U8X8_MSG_GPIO_D7:				// D7 pin: Output level in arg_int
        break;
    case U8X8_MSG_GPIO_E:				// E/WR pin: Output level in arg_int
        break;
    case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
        break;
    case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
        break;
    case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
        break;
    case U8X8_MSG_GPIO_CS1:				// CS1 (chip select) pin: Output level in arg_int
        break;
    case U8X8_MSG_GPIO_CS2:				// CS2 (chip select) pin: Output level in arg_int
        break;
    case U8X8_MSG_GPIO_I2C_CLOCK:		// arg_int=0: Output low at I2C clock pin
        if (arg_int == 1)
        {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
        }
        else if (arg_int == 0)
        {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
        }
        break;							// arg_int=1: Input dir with pullup high for I2C clock pin
    case U8X8_MSG_GPIO_I2C_DATA:			// arg_int=0: Output low at I2C data pin
        if (arg_int == 1)
        {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
        }
        else if (arg_int == 0)
        {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
        }
        break;							// arg_int=1: Input dir with pullup high for I2C data pin
    case U8X8_MSG_GPIO_MENU_SELECT:
        u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
        break;
    case U8X8_MSG_GPIO_MENU_NEXT:
        u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
        break;
    case U8X8_MSG_GPIO_MENU_PREV:
        u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
        break;
    case U8X8_MSG_GPIO_MENU_HOME:
        u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
        break;
    default:
        u8x8_SetGPIOResult(u8x8, 1);			// default return value
        break;
    }
    return 1;
}

void Draw_Line_Test(u8g2_t *u8g2)
{
    u8g2_ClearBuffer(u8g2);
    for (int i=0;i<20;i++)
    {
        u8g2_DrawLine(u8g2, 0, 0, i*10, 63);
        u8g2_SendBuffer(u8g2);
    }
    for (int i=0;i<20;i++)
    {
        u8g2_DrawLine(u8g2, 128, 0, 128-i * 10, 63);
        u8g2_SendBuffer(u8g2);
    }
}

void process_Test(u8g2_t *u8g2)
{
	for(int i=10;i<=80;i=i+2)
	{
	u8g2_ClearBuffer(u8g2); 
		
	    char buff[20];
		sprintf(buff,"%d%%",(int)(i/80.0*100));
		
		u8g2_SetFont(u8g2,u8g2_font_ncenB18_tf);
		u8g2_DrawStr(u8g2,32,32,"u8g2");//字符显示
		
		u8g2_SetFont(u8g2,u8g2_font_ncenB08_tf);
		u8g2_DrawStr(u8g2,100,49,buff);//当前进度显示
		
		u8g2_DrawRBox(u8g2,16,40,i,10,4);//圆角填充框矩形框
		u8g2_DrawRFrame(u8g2,16,40,80,10,4);//圆角矩形
	
	u8g2_SendBuffer(u8g2);
	}
}

//字体测试 数字英文可选用 u8g2_font_ncenB..(粗) 系列字体
//u8g2_font_unifont_t_symbols/u8g2_font_unifont_h_symbols(细 圆润)
void font_Test(u8g2_t *u8g2)
{
	u8g2_ClearBuffer(u8g2); 
		u8g2_SetFont(u8g2,u8g2_font_u8glib_4_tf);
		u8g2_DrawStr(u8g2,0,5,"hello world 1");
	u8g2_SendBuffer(u8g2); 
    HAL_Delay(100);
	u8g2_ClearBuffer(u8g2); 
		u8g2_SetFont(u8g2,u8g2_font_u8glib_4_tf);
		u8g2_DrawStr(u8g2,0,5,"hello world 12");
	
	    u8g2_SetFont(u8g2,u8g2_font_ncenB08_tf);
		u8g2_DrawStr(u8g2,0,20,"hello world 12");
	u8g2_SendBuffer(u8g2); 
	HAL_Delay(100);
	u8g2_ClearBuffer(u8g2); 
		u8g2_SetFont(u8g2,u8g2_font_u8glib_4_tf);
		u8g2_DrawStr(u8g2,0,5,"hello world 123");
	
		u8g2_SetFont(u8g2,u8g2_font_ncenB10_tr);
		u8g2_DrawStr(u8g2,0,40,"hello world 123");
		
		u8g2_SetFont(u8g2,u8g2_font_ncenB08_tf);
		u8g2_DrawStr(u8g2,0,20,"hello world 123");
	u8g2_SendBuffer(u8g2); 
	HAL_Delay(100);
	u8g2_ClearBuffer(u8g2); 
		u8g2_SetFont(u8g2,u8g2_font_u8glib_4_tf);
		u8g2_DrawStr(u8g2,0,5,"hello world 1234");
	
		u8g2_SetFont(u8g2,u8g2_font_ncenB10_tr);
		u8g2_DrawStr(u8g2,0,40,"hello world 1234");
		
		u8g2_SetFont(u8g2,u8g2_font_ncenB08_tf);
		u8g2_DrawStr(u8g2,0,20,"hello world 1234");
		
		u8g2_SetFont(u8g2,u8g2_font_ncenB12_tf);
		u8g2_DrawStr(u8g2,0,60,"hello world 1234");
	u8g2_SendBuffer(u8g2);
	HAL_Delay(1000);
}

//矩形测试
void u8g2_DrawBox_Test(u8g2_t *u8g2)
{
	for(int i=0;i<32;i=i+2)
	{
	u8g2_ClearBuffer(u8g2); 
		
		u8g2_DrawBox(u8g2,0,0,i*2,i);//矩形填充框
	    u8g2_DrawFrame(u8g2,64,0,i*2,i);//矩形框
		
	    u8g2_DrawRBox(u8g2,0,32,i*2,i,i/3);//圆角矩形填充框
	    u8g2_DrawRFrame(u8g2,64,32,i*2,i,i/3);//圆角矩形框
		
	u8g2_SendBuffer(u8g2);
	}
}

void DrawBox_Test(u8g2_t *u8g2)
{
	u8g2_ClearBuffer(u8g2);
	for(int i=0;i<31;i+=2)
	{
		u8g2_DrawFrame(u8g2,i*2,i,128-i*4,64-2*i);
	u8g2_SendBuffer(u8g2);
	}
	
	u8g2_ClearBuffer(u8g2);
	for(int i=0;i<31;i+=2)
	{
		 u8g2_DrawRFrame(u8g2,i*2,i,128-i*4,64-2*i,10-i/3);
	u8g2_SendBuffer(u8g2);
	}
	
}

//圆形测试
void u8g2_DrawCircle_Test(u8g2_t *u8g2)
{
	for(int i=0;i<32;i=i+2)
	{
	u8g2_ClearBuffer(u8g2); 
		
		u8g2_DrawCircle(u8g2,64,32,i,U8G2_DRAW_ALL);//画圆
	   	u8g2_DrawCircle(u8g2,32,32,i,U8G2_DRAW_ALL);
		u8g2_DrawCircle(u8g2,96,32,i,U8G2_DRAW_ALL);
		
	u8g2_SendBuffer(u8g2);
	}
}

//椭圆形测试
void u8g2_DrawEllipse_Test(u8g2_t *u8g2)
{
	for(int i=0;i<32;i=i+2)
	{
	u8g2_ClearBuffer(u8g2); 
		
		u8g2_DrawEllipse(u8g2,32,32,15+i,10,U8G2_DRAW_ALL);//画椭圆
		u8g2_DrawEllipse(u8g2,64,32,15+i,10,U8G2_DRAW_ALL);//
		u8g2_DrawEllipse(u8g2,96,32,15+i,10,U8G2_DRAW_ALL);//
		
		u8g2_DrawEllipse(u8g2,64,16,10,15+i,U8G2_DRAW_ALL);//画椭圆
		u8g2_DrawEllipse(u8g2,64,32,10,15+i,U8G2_DRAW_ALL);//
		u8g2_DrawEllipse(u8g2,64,48,10,15+i,U8G2_DRAW_ALL);//
		
		u8g2_DrawFilledEllipse(u8g2,64,32,15,10,U8G2_DRAW_ALL);//画填充椭圆
		
	u8g2_SendBuffer(u8g2);
	}
}