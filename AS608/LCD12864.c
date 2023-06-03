#include <LCD12864.h>

void lcd_wcmd(uchar cmd)
{   
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = cmd;
		Delay_ms(1);
    LCD_EN = 1;
		Delay_ms(1);
    LCD_EN = 0;
}

void lcd_wdat(uchar dat)
{
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    Delay_ms(1);
    LCD_EN = 1;
    Delay_ms(1);
    LCD_EN = 0; 
}

void lcd_init()
{ 
    LCD_PSB = 1;
    lcd_wcmd(0x34);
    Delay_ms(5);
    lcd_wcmd(0x30);
    Delay_ms(5);
    lcd_wcmd(0x0c);
    Delay_ms(5);
    lcd_wcmd(0x01);
    Delay_ms(5);
}

void display(uchar X,uchar Y,uchar *Z)
{
	uchar pos;
	if (X==0){X=0x80;}
	else if (X==1){X=0x90;}
	else if (X==2){X=0x88;}
	else if (X==3){X=0x98;}
	pos = X+Y;  
	lcd_wcmd(pos);
	while(*Z != '\0')
	{
		lcd_wdat(*Z);
		Z++;
	}
}