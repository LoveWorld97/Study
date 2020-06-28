#include "display.h"
#include "rtc.h"

char display_array[256] = {0};
void display_time(void)
{
    /*显示日期*/
    display_array[0] = 2 + 0x30;
    display_array[1] = 0 + 0x30;
    display_array[2] = getdate.Year / 10 % 100 + 0x30;
    display_array[3] = getdate.Year % 10 + 0x30;
    show_string_atype(0, 0, display_array, 4);
    show_string_atype(0, 4, ".", 1);
    display_array[0] = getdate.Month / 10 + 0x30;
    display_array[1] = getdate.Month % 10 + 0x30;
    show_string_atype(0, 5, display_array, 2);
    show_string_atype(0, 7, ".", 1);
    display_array[0] = getdate.Date / 10 + 0x30;
    display_array[1] = getdate.Date % 10 + 0x30;
    show_string_atype(0, 8, display_array, 2);
    /*显示时间*/
    display_array[0] = gettime.Hours / 10 + 0x30;
    display_array[1] = gettime.Hours % 10 + 0x30;
    show_string_atype(2, 0, display_array, 2);
    show_string_atype(2, 2, ":", 1);
    display_array[0] = gettime.Minutes / 10 + 0x30;
    display_array[1] = gettime.Minutes % 10 + 0x30;
    show_string_atype(2, 3, display_array, 2);
    show_string_atype(2, 5, ":", 1);
    display_array[0] = gettime.Seconds / 10 + 0x30;
    display_array[1] = gettime.Seconds % 10 + 0x30;
    show_string_atype(2, 6, display_array, 2);
}