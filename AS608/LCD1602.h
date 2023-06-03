#ifndef _LCD1602_H_
#define _LCD1602_H_

#include <reg52.h>
#define LINE1         0x80                        //1602屏地址定义 第一行地址
#define LINE2         0xc0                        //1602屏地址定义 第二行地址
#define DataPort P0        											  //LCD1602操作位定义

#define uchar unsigned char
#define uint unsigned int

sbit EN = P3^4;     															//读写数据使能   0：停止 1：启动
sbit RS = P3^5;     															//寄存器选择 0:指令寄存器 1:数据寄存器
sbit RW = P3^6;     															//读写控制 0：写  1：读

void LCD1602_Init(void);
void LCD1602_WriteCMD(unsigned char cmd);
void LCD1602_WriteDAT(unsigned char dat);
void LCD1602_CheckBusy(void);
void LCD1602_Display(unsigned char addr,unsigned char* pointer,unsigned char index,unsigned char num);  //入口参数：addr起始地址，pointer指针地址，index下标，num个数

#endif