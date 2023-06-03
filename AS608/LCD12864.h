#ifndef _LCD12864_H_
#define _LCD12864_H_

#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include <delay.h>

#define uchar unsigned char
#define uint unsigned int
#define LCD_data  P0

sbit LCD_RS  =  P3^5; 
sbit LCD_RW  =  P3^6;
sbit LCD_EN  =  P3^4;
sbit LCD_PSB =  P3^7;

void display(uchar X,uchar Y,uchar *Z);
void lcd_init();
void lcd_wdat(uchar dat);
void lcd_wcmd(uchar cmd);

#endif 