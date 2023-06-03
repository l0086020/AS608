#ifndef _LCD1602_H_
#define _LCD1602_H_

#include <reg52.h>
#define LINE1         0x80                        //1602����ַ���� ��һ�е�ַ
#define LINE2         0xc0                        //1602����ַ���� �ڶ��е�ַ
#define DataPort P0        											  //LCD1602����λ����

#define uchar unsigned char
#define uint unsigned int

sbit EN = P3^4;     															//��д����ʹ��   0��ֹͣ 1������
sbit RS = P3^5;     															//�Ĵ���ѡ�� 0:ָ��Ĵ��� 1:���ݼĴ���
sbit RW = P3^6;     															//��д���� 0��д  1����

void LCD1602_Init(void);
void LCD1602_WriteCMD(unsigned char cmd);
void LCD1602_WriteDAT(unsigned char dat);
void LCD1602_CheckBusy(void);
void LCD1602_Display(unsigned char addr,unsigned char* pointer,unsigned char index,unsigned char num);  //��ڲ�����addr��ʼ��ַ��pointerָ���ַ��index�±꣬num����

#endif