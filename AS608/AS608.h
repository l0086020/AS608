#ifndef _AS608_H_
#define _AS608_H_
#include <Uart.h>
#include <Beep.h>
#include <delay.h>
#include <LCD12864.h>
#include <Key.h>
#include <stdio.h>

#define uchar unsigned char
#define uint unsigned int
	
extern uchar flag;
extern char local_date;
extern unsigned int finger_id;
extern uchar Buffer [];

void AS608_Cmd_Send_Pack_Head(void);
void AS608_Cmd_Check(void);
void AS608_Receive_Data(unsigned char ucLength);
void AS608_Cmd_Get_Img(void);
void FINGERPRINT_Cmd_Img_To_Buffer1(void);
void FINGERPRINT_Cmd_Img_To_Buffer2(void);
void AS608_Cmd_Search_Finger(void);
void AS608_Cmd_Reg_Model(void);
void FINGERPRINT_Cmd_Delete_All_Model(void);
void AS608_Cmd_Save_Finger( unsigned int storeID );
int AS608_number_of_fingers();
void AS608_Add_Fingerprint();
void AS608_Find_Fingerprint();
void AS608_Delete_All_Fingerprint();
void Device_Check(void);

#endif