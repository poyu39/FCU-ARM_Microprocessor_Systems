#include <stdio.h>
#include <math.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "Scankey.h"
#include "Seven_Segment.h"

#define BUZZER_UPDATE_TICK 1
#define SEVEN_SEG_UPDATE_TICK 1
#define TICK_PER_MS 5000

#define LCD_SPACE "                "
#define NID "D1009212"
#define MATH_SYMBOLS "+-*/%^^"

void show_seven_seg(int PC_values[], uint8_t index_seven_seg, int limit_buzzer) {
	if (index_seven_seg == 4) index_seven_seg = 0;
	while (PC_values[index_seven_seg] == 16) {
		index_seven_seg++;
		if (index_seven_seg == 4) index_seven_seg = 0;
	}
	if (PC_values[index_seven_seg] != 0) {
		CloseSevenSegment();
		ShowSevenSegment(index_seven_seg, PC_values[index_seven_seg]);
	}
}

void update_seven_seg(int PC_values[], int x, int y) {
	PC_values[3] = x / 10;
	PC_values[2] = x % 10;
	PC_values[1] = y / 10;
	PC_values[0] = y % 10;
}

int math(int x, int y, int i) {
	switch (i) {
	case 0:
		return x + y;
	case 1:
		return x - y;
	case 2:
		return x * y;
	case 3:
		return x / y;
	case 4:
		return x % y;
	case 5:
		return pow(x, 2);
	case 6:
		return pow(y, 2);
	default:
		return 0;
	}
}

void update_result(int result[], int x, int y) {
	int i;
	for (i = 0; i < 7; i++) {
		result[i] = math(x, y, i);
	}
}

void update_lcd_buffer(int x, int y, int math_op_index, int result[], char lcd_buffer[3][17]) {
	int i;
	for (i = 0; i < 3; i++) {
		int index = math_op_index + i;
		if (index < 5) {
			sprintf(lcd_buffer[i], "%2d %c %2d = %4d  ", x, MATH_SYMBOLS[index], y, result[index]);
		} else if (index == 5) {
			sprintf(lcd_buffer[i], "%2d %c %2d = %4d  ", x, MATH_SYMBOLS[index], 2, result[index]);
		} else if (index == 6) {
			sprintf(lcd_buffer[i], "%2d %c %2d = %4d  ", y, MATH_SYMBOLS[index], 2, result[index]);
		} else if (index == 7) {
			sprintf(lcd_buffer[i], "END             ");
		}
	}
}

void show_lcd(int lcd_x, int lcd_y, char lcd_buffer[3][17], char lcd_now[3][17]) {
	if (lcd_buffer[lcd_y][lcd_x] != lcd_now[lcd_y][lcd_x]) {
		lcd_now[lcd_y][lcd_x] = lcd_buffer[lcd_y][lcd_x];
		printC(lcd_x * 8, (lcd_y + 1) * 16, lcd_now[lcd_y][lcd_x]);
	}
}

int main(void) {
	uint8_t keyin = 0, isPressed = 1, index_seven_seg = 0, lcd_x = 0, lcd_y = 0, update_lcd = 0;
	int x = 0, y = 0, temp_x, math_op_index = 0, limit_buzzer = 0;
	int PC_values[4] = {16, 16, 16, 16};
	int result[7];
	char lcd_buffer[3][17] = {LCD_SPACE, LCD_SPACE, LCD_SPACE};
	char lcd_now[3][17] = {LCD_SPACE, LCD_SPACE, LCD_SPACE};
	int loop_count = 0;

	SYS_Init();
	init_LCD();
	clear_LCD();
	OpenKeyPad();
	print_Line(0, NID);

	while (TRUE) {
		keyin = ScanKey();
		// 用 goto 節省每次迴圈執行
		if (keyin != 0) {
			if (isPressed == 1) goto display;
			isPressed = 1;
		}
		switch (keyin) {
		case 0:
			isPressed = 0;
			break;
		case 2:
			// 運算式向上滾動
			if (x == 0 && y == 0) break;
			math_op_index--;
			if (math_op_index < 0) {
				math_op_index = 0;
				limit_buzzer = 10;
			}
			break;
		case 4:
			// 向左偏移, ex: 1234 -> 2341
			if (x == 0 && y == 0) break;
			temp_x = x;
			x = (x % 10 * 10) + y / 10;
			y = (y % 10 * 10) + temp_x / 10;
			update_result(result, x, y);
			break;
		case 5:
			// 亂數
			srand(loop_count);
			x = (rand() % 9 + 1) * 10 + rand() % 9 + 1;
			y = (rand() % 9 + 1) * 10 + rand() % 9 + 1;
			update_result(result, x, y);
			break;
		case 6:
			// 向右偏移, ex: 1234 -> 4123
			if (x == 0 && y == 0) break;
			temp_x = x;
			x = (x / 10) + (y % 10 * 10);
			y = (y / 10) + (temp_x % 10 * 10);
			update_result(result, x, y);
			break;
		case 8:
			// 運算式向下滾動
			if (x == 0 && y == 0) break;
			math_op_index++;
			if (math_op_index > 5) {
				math_op_index = 5;
				limit_buzzer = 10;
			}
			break;
		default:
			break;
		}
		if (isPressed == 1) {
			update_seven_seg(PC_values, x, y);
			update_lcd_buffer(x, y, math_op_index, result, lcd_buffer);
			update_lcd = 1;
		}
		display:
		if (update_lcd == 1 && x != 0 && y != 0) {
			show_lcd(lcd_x, lcd_y, lcd_buffer, lcd_now);
			if (lcd_y < 3) {
				if (lcd_x < 16) {
					lcd_x++;
				} else {
					lcd_x = 0;
					lcd_y++;
				}
			}
			if (lcd_y == 3) {
				lcd_x = 0;
				lcd_y = 0;
				update_lcd = 0;
			}
		}
		if (limit_buzzer > 0 && loop_count % 1 == 0) PB11 = 0;
		if (x != 0 && y != 0 && loop_count % SEVEN_SEG_UPDATE_TICK == 0) {
			show_seven_seg(PC_values, index_seven_seg, limit_buzzer);
			index_seven_seg++;
			if (index_seven_seg == 4) index_seven_seg = 0;
		}
		if (limit_buzzer > 0 && loop_count % 3 == 0) {
			PB11 = 1;
			limit_buzzer--;
		}
		if ((loop_count + 1)> INT32_MAX) loop_count = 0;
		loop_count++;
		CLK_SysTickDelay(TICK_PER_MS);
	}
}

