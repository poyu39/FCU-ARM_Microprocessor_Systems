//
// LCD_Bmp_Keypad: use 3x3 keypad to move bitmap on LCD
//
#include <stdio.h>
#include <string.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "Scankey.h"
#include "Draw2D.h"

unsigned char temper[32*4] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x03,0x01,0x01,0x03,0xFE,0x00,0x00,0x00,0x90,0x90,0x90,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0xF0,0xF0,0x00,0xFF,0x00,0x00,0x00,0x24,0x24,0x24,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x60,0x30,0x98,0xCF,0xE0,0xFF,0xFF,0xE0,0xCF,0x98,0x30,0x60,0xC1,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x18,0x30,0x67,0xCF,0x9F,0x9F,0x9F,0x9F,0xCF,0x67,0x30,0x18,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
unsigned char setting[32*4] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x03,0x01,0x01,0x03,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0xF0,0xE0,0x80,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0xF0,0xF0,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x22,0xE3,0xE3,0xE3,0xE3,0xE3,0x22,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x60,0x30,0x98,0xCF,0xE0,0xFF,0xFF,0xE0,0xCF,0x98,0x30,0x60,0xC0,0x00,0x00,0x00,0x03,0x07,0x03,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x18,0x30,0x67,0xCF,0x9F,0x9F,0x9F,0x9F,0xCF,0x67,0x30,0x18,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
unsigned char calendar[32*4] = {
	0x00,0x00,0xE0,0xE0,0xF0,0xF0,0xF0,0x80,0x7C,0x7C,0x7C,0x80,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0x80,0x7C,0x7C,0x7C,0x80,0xF0,0xF0,0xF0,0xF0,0xE0,0x00,0x00,
	0x00,0x00,0xFF,0xFF,0x07,0x07,0x07,0xE7,0xE7,0xE7,0x07,0x07,0xE7,0xE7,0xE7,0x07,0x07,0xE7,0xE7,0xE7,0x07,0x07,0xE7,0xE7,0xE7,0x07,0x07,0x07,0xFF,0xFF,0x00,0x00,
	0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x9C,0x9C,0x9C,0x00,0x00,0x9C,0x9C,0x9C,0x00,0x00,0x9C,0x9C,0x9C,0x00,0x00,0x9C,0x9C,0x9C,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,
	0x00,0x00,0x3F,0x3F,0x70,0x70,0x70,0x73,0x73,0x73,0x70,0x70,0x73,0x73,0x73,0x70,0x70,0x73,0x73,0x73,0x70,0x70,0x73,0x73,0x73,0x70,0x70,0x70,0x3F,0x3F,0x00,0x00
};
unsigned char password[32*4] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xF0,0xF8,0xFC,0x3C,0x1E,0x1E,0x0E,0x1E,0x1E,0x3C,0xFC,0xF8,0xF0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xE0,0xF0,0x38,0x18,0x1F,0x1F,0x1F,0x1C,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1C,0x1F,0x1F,0x1F,0x18,0x38,0xF0,0xE0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0xFC,0xFE,0xFC,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x0F,0x3F,0x38,0x30,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x71,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x30,0x38,0x3F,0x0F,0x00,0x00,0x00,0x00
};
unsigned char temper64[64*8] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xFC,0x3E,0x0E,0x07,0x07,0x07,0x07,0x07,0x0E,0x1E,0xFC,0xF8,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0x07,0x07,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x71,0x71,0x71,0x71,0x71,0x71,0x70,0x70,0x70,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0xFE,0xFE,0xFE,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xF8,0xFC,0x3E,0x0F,0x87,0xE3,0x31,0x18,0x0C,0x04,0x84,0xC7,0xCF,0xFF,0xFE,0xFC,0xFC,0xF8,0xF1,0xE3,0xC7,0x0F,0x1E,0xFC,0xF8,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFB,0x80,0x00,0x3F,0x78,0xF0,0xF0,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x00,0x80,0xF1,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x0F,0x1E,0x1C,0x38,0x79,0x71,0x63,0xE3,0xE7,0xE7,0xE7,0xE7,0xE7,0xE3,0x63,0x71,0x71,0x38,0x1C,0x1E,0x0F,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

unsigned char icon[32*4] = {0};
char text[16];

int main(void)
{
	int8_t keyin=0;
  int8_t c=2;
	
	SYS_Init();
	  
	init_LCD();
	clear_LCD();
	
	OpenKeyPad();	
	draw_Bmp32x32( 0,24,FG_COLOR,BG_COLOR, password);
	draw_Bmp32x32(32,24,FG_COLOR,BG_COLOR, calendar);	
	draw_Bmp32x32(64,24,FG_COLOR,BG_COLOR, temper);
	draw_Bmp32x32(96,24,FG_COLOR,BG_COLOR, setting);
	print_Line(0, "  4 << [5] >> 6");
	
	while(1){
		keyin=ScanKey(); // wait till key is pressed
		sprintf(text,"%d", keyin);
	  print_Line(0, text);		
		if (keyin!=0) {

      switch(keyin){
		    case 4: c=c-1; break;
		    case 6: c=c+1; break;
		    default: break;
	    }
		  if (c<0) c=3;
		  if (c>3) c=0;

		  if (c==0) draw_Rectangle(  0,24, 31, 56,FG_COLOR,BG_COLOR);
		  else      draw_Rectangle(  0,24, 31, 56,BG_COLOR,BG_COLOR);
		  if (c==1) draw_Rectangle( 32,24, 63, 56,FG_COLOR,BG_COLOR);
		  else      draw_Rectangle( 32,24, 63, 56,BG_COLOR,BG_COLOR);							
		  if (c==2) draw_Rectangle( 64,24, 95, 56,FG_COLOR,BG_COLOR);
		  else      draw_Rectangle( 64,24, 95, 56,BG_COLOR,BG_COLOR);
		  if (c==3) draw_Rectangle( 96,24,127, 56,FG_COLOR,BG_COLOR);
		  else      draw_Rectangle( 96,24,127, 56,BG_COLOR,BG_COLOR);		
			
	  }
	}
}
