#include <AS608.h>

volatile unsigned char AS608_RECEICE_BUFFER[32]; //volatile:系统总是重新从它所在的内存读取数据，即使它前面的指令刚刚从该处读取过数据

//FINGERPRINT通信协议定义
code unsigned char AS608_Get_Device[10] ={0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};//口令验证
code unsigned char AS608_Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};  //协议包头
code unsigned char AS608_Get_Img[6] = {0x01,0x00,0x03,0x01,0x00,0x05};    //获得指纹图像
code unsigned char AS608_Get_Templete_Count[6] ={0x01,0x00,0x03,0x1D,0x00,0x21 }; //获得模版总数
code unsigned char AS608_Search[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x03,0xE7,0x00,0xF8}; //搜索指纹搜索范围0 - 999,使用BUFFER1中的特征码搜索
code unsigned char AS608_Search_0_9[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x00,0x13,0x00,0x21}; //搜索0-9号指纹
code unsigned char AS608_Img_To_Buffer1[7]={0x01,0x00,0x04,0x02,0x01,0x00,0x08}; //将图像放入到BUFFER1
code unsigned char AS608_Img_To_Buffer2[7]={0x01,0x00,0x04,0x02,0x02,0x00,0x09}; //将图像放入到BUFFER2
code unsigned char AS608_Reg_Model[6]={0x01,0x00,0x03,0x05,0x00,0x09}; //将BUFFER1跟BUFFER2合成特征模版
code unsigned char AS608_Delete_All_Model[6]={0x01,0x00,0x03,0x0d,0x00,0x11};//删除指纹模块里所有的模版
volatile unsigned char  AS608_Save_Finger[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//将BUFFER1中的特征码存放到指定的位置

//发送包头
void AS608_Cmd_Send_Pack_Head(void)
{
        int i;        
        for(i=0;i<6;i++) //包头
        {
                Uart_Send_Byte(AS608_Pack_Head[i]);   
        }               
}

//发送指令
void AS608_Cmd_Check(void)
{
        int i=0;
        AS608_Cmd_Send_Pack_Head(); //发送通信协议包头
        for(i=0;i<10;i++)
        {               
                Uart_Send_Byte(AS608_Get_Device[i]);
        }
}

//接收反馈数据缓冲
void AS608_Receive_Data(unsigned char ucLength)
{
        unsigned char i;                                 
        for (i=0;i<ucLength;i++)
                AS608_RECEICE_BUFFER[i] = Uart_Receive_Byte();
}

//FINGERPRINT_获得指纹图像命令
void AS608_Cmd_Get_Img(void)
{
    unsigned char i;
    AS608_Cmd_Send_Pack_Head(); //发送通信协议包头
    for(i=0;i<6;i++) //发送命令 0x1d
        {
       Uart_Send_Byte(AS608_Get_Img[i]);
        }
}

//将图像转换成特征码存放在Buffer1中
void FINGERPRINT_Cmd_Img_To_Buffer1(void)
{
         unsigned char i;
        AS608_Cmd_Send_Pack_Head(); //发送通信协议包头      
           for(i=0;i<7;i++)   //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
        {
                Uart_Send_Byte(AS608_Img_To_Buffer1[i]);
        }
}
//将图像转换成特征码存放在Buffer2中
void FINGERPRINT_Cmd_Img_To_Buffer2(void)
{
        unsigned char i;
        AS608_Cmd_Send_Pack_Head(); //发送通信协议包头
        for(i=0;i<7;i++)   //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
        {
                Uart_Send_Byte(AS608_Img_To_Buffer2[i]);
        }
}

//搜索全部用户999枚
void AS608_Cmd_Search_Finger(void)
{
        unsigned char i;                       
        AS608_Cmd_Send_Pack_Head(); //发送通信协议包头
        for(i=0;i<11;i++)
        {
                Uart_Send_Byte(AS608_Search[i]);   
        }
}

//转换成特征码
void AS608_Cmd_Reg_Model(void)
{
        unsigned char i;                              
        AS608_Cmd_Send_Pack_Head(); //发送通信协议包头
        for(i=0;i<6;i++)
        {
                Uart_Send_Byte(AS608_Reg_Model[i]);   
        }
}

//删除指纹模块里的所有指纹模版
void FINGERPRINT_Cmd_Delete_All_Model(void)
{
        unsigned char i;   
    AS608_Cmd_Send_Pack_Head(); //发送通信协议包头   
    for(i=0;i<6;i++) //命令删除指纹模版
        {
              Uart_Send_Byte(AS608_Delete_All_Model[i]);   
        }        
}

//保存指纹
void AS608_Cmd_Save_Finger( unsigned int storeID )
{
        unsigned long temp = 0;
        unsigned char i;
        AS608_Save_Finger[5] =(storeID&0xFF00)>>8;
        AS608_Save_Finger[6] = (storeID&0x00FF);
        for(i=0;i<7;i++)   //计算校验和
                temp = temp + AS608_Save_Finger[i];
        AS608_Save_Finger[7]=(temp & 0x00FF00) >> 8; //存放校验数据
        AS608_Save_Finger[8]= temp & 0x0000FF;                  
        AS608_Cmd_Send_Pack_Head(); //发送通信协议包头        
        for(i=0;i<9;i++)  
                Uart_Send_Byte(AS608_Save_Finger[i]);      //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
}

//查看当前指纹库中指纹模板数
int AS608_number_of_fingers()
{
         int num=1;//默认模板库中有一个模板
        uchar i=0;
        AS608_Cmd_Send_Pack_Head(); //发送通信协议包头
        for(i=0;i<6;i++)
        {
                  Uart_Send_Byte(AS608_Get_Templete_Count[i]);
        }
        AS608_RECEICE_BUFFER[9]=1;//方便后续判断是否接收成功
        AS608_Receive_Data(14);//接收数据
        if(AS608_RECEICE_BUFFER[9]==0) //接收成功
        {
                 num=AS608_RECEICE_BUFFER[10]*256+AS608_RECEICE_BUFFER[11];//拼接模板总个数                        
        }
        return num;
}
//另一种方法查看指纹库中是否有模板 //本来应该查看所有1000个模板位置是否存在模板，但一般只用得到前256个，故从简
/*
uchar AS608_notEmpty()
{
         uchar exist=0;
        char i=0;
        AS608_Cmd_Send_Pack_Head(); //发送通信协议包头
        for(i=0;i<7;i++)
        {
                  Uart_Send_Byte(AS608_num_of_finger_in_lib1[i]);
        }
        AS608_Receive_Data(10);//接收前10byte数据,除第10字节的确认码外，其余全部丢弃
        if(AS608_RECEICE_BUFFER[9]==0) //接收成功
        {
        AS608_Receive_Data(32);//接收后续32byte数据，此即0~255个模板为是否存在指纹模板的数据
        for(i=0;i<32;i++)//查看这32byte数据，任何一个位置存在模板则返回值为真，否则为假
        {
                 if(AS608_RECEICE_BUFFER[i])
                        exist=1;
        }
        return exist;
        }
}
*/
//添加指纹
void AS608_Add_Fingerprint()
{ 
				lcd_wcmd(0x01);
				Delay_ms(1000);
        while(1)
        {
                display(1,0,"   Add finger   ");
                display(2,0,"   ID  is       ");
                if(KEY_CANCEL == 0)
                {
                         Delay_ms(5);
                         if(KEY_CANCEL == 0)
                         {
                                 while(KEY_CANCEL==0);
                                 break;
                         }         
                }

                if(KEY_UP == 0)
                {
									Delay_ms(5);
									if(KEY_UP == 0)
									{
										while(KEY_UP==0);
										if(finger_id == 1000)
										{
												finger_id = 1;
										}
										else
										{
												finger_id = finger_id + 1;
										}
									}               
                }
								 if(KEY_DOWN == 0)
								 {
							    	Delay_ms(5);
										if(KEY_DOWN == 0)
										{
											while(KEY_DOWN==0);
											if(finger_id == 1)
											{
													finger_id = 1000;
											}
											else
											{
													finger_id = finger_id - 1;
											}
										}               
									}
//									lcd_wcmd(0x8d);
//									lcd_wdat(12);
                 //按确认键开始录入指纹信息                                          
                 if(KEY_OK == 0)
                 {
                 Delay_ms(5);
                 if(KEY_OK == 0)
                  {        
                                while(KEY_OK==0);
                                  display(1,0," Please  finger ");
                                  display(2,0,"                ");
                                while(KEY_CANCEL == 1)
                                  {
                                          //按下返回键退出录入返回fingerID调整状态   
                                        if(KEY_CANCEL == 0)
                                         {
                                                  Delay_ms(5);
                                                if(KEY_CANCEL == 0)
                                                {
                                                        while(KEY_CANCEL==0);
                                                          break;
                                                }
                                                
                                          }
                                        AS608_Cmd_Get_Img(); //获得指纹图像
                                        AS608_Receive_Data(12);
                                        //判断接收到的确认码,等于0指纹获取成功
                                        if(AS608_RECEICE_BUFFER[9]==0)
                                         {
                                                Delay_ms(100);
                                                FINGERPRINT_Cmd_Img_To_Buffer1();
																								AS608_Receive_Data(12);
                                                display(2,0,"Successful entry");
                                                Beep_Times(1);
                                                Delay_ms(10000);
                                                display(1,0,"   Try  again   ");
                                                display(2,0,"                ");
                                                while(1)
                                                {
                                                        if(KEY_CANCEL == 0)
                                                         {
                                                                  Delay_ms(5);
                                                                if(KEY_CANCEL == 0)
                                                                {
                                                                        while(KEY_CANCEL==0);
                                                                          break;
                                                                }
                                                          }
                                                         AS608_Cmd_Get_Img(); //获得指纹图像
                                                         AS608_Receive_Data(12);
                                                        //判断接收到的确认码,等于0指纹获取成功
                                                        if(AS608_RECEICE_BUFFER[9]==0)
                                                        {
                                                        Delay_ms(200);
                                                        display(2,0,"Successful entry");
																												Delay_ms(20000);
                                                        display(2,5,"    ID is       ");
                                                         //指纹iD值显示处理
//                                                         LCD1602_WriteCMD(0xc0+10);
//                                                         LCD1602_WriteDAT(finger_id/100+48);
//                                                         LCD1602_WriteDAT(finger_id%100/10+48);
//                                                         LCD1602_WriteDAT(finger_id%100%10+48);
                                                         FINGERPRINT_Cmd_Img_To_Buffer2();
                                                         AS608_Receive_Data(12);
                                                         AS608_Cmd_Reg_Model();//转换成特征码
																										   	AS608_Receive_Data(12);
                                                         AS608_Cmd_Save_Finger(finger_id);                                         
                                                         AS608_Receive_Data(12);
                                                         Beep_Times(1);
                                                         Delay_ms(1000);
                                                         finger_id=finger_id+1;
                                                    break;
                                                          }
                                                   }
                                                   break;
                                        }
                                }
                }
                }
        }
}

//搜索指纹
void AS608_Find_Fingerprint()
{
	unsigned int find_fingerid = 0;
	display(0,0,"                ");
	display(1,0," Please  finger ");
	display(2,0,"                ");
	display(3,0,"                ");
	do
	{
		AS608_Cmd_Get_Img();
		AS608_Receive_Data(12);               
		if(AS608_RECEICE_BUFFER[9]==0)
		{                        
			Delay_ms(100);
			FINGERPRINT_Cmd_Img_To_Buffer1();
			AS608_Receive_Data(12);               
			AS608_Cmd_Search_Finger();
			AS608_Receive_Data(16);                        
			if(AS608_RECEICE_BUFFER[9] == 0)
			{
				display(2,0," Search success");
				Beep_Times(1);                                       
				//find_fingerid = AS608_RECEICE_BUFFER[10]*256 + AS608_RECEICE_BUFFER[11];                                      
				if(flag)
				{
					P1 = 0xfe;
					Delay_ms(10000);
					P1 = 0xff;
				}
				flag=1;
				Delay_ms(3000);
				break;                                                        
			}
			else
			{
				display(2,0," Search  failed ");
				Beep_Times(3);
			}
		}
	}
	while(KEY_CANCEL == 1);
}
//删除所有存贮的指纹库
void AS608_Delete_All_Fingerprint()
{
                unsigned char i=0;
                                display(1,0,"   Empty  all   ");
                                display(2,0,"   Yes or no ?  ");
                do
                 {
                        if(KEY_OK==0)
                        {
                        Delay_ms(5);
                        if(KEY_OK==0)
                        {
                                while(KEY_OK==0);
                                display(2,0,"   Emptying     ");
                                Delay_ms(300);
//                                LCD1602_WriteCMD(0xc0);
//                                for(i=0;i<16;i++)
//                                 {
//                                        LCD1602_WriteDAT(42);// 即'*'
//                                        Delay_ms(100);
//                                 }
                                FINGERPRINT_Cmd_Delete_All_Model();
                                AS608_Receive_Data(12);
                                display(2,0,"   All empty    ");
																Delay_ms(10000);
                                Beep_Times(3);
                                break;
                        }
                        }
                 }while(KEY_CANCEL==1);
}

void Device_Check(void)
{
		unsigned char i=0;
		AS608_RECEICE_BUFFER[9]=1;                                     			      //串口数组第九位可判断是否通信正常
		display(2,2,"Loading...");                   																//设备加载中界面                                                           			
		Delay_ms(5000);
		display(2,0,"Docking  failure");       											//液晶先显示对接失败，如果指纹模块插对的话会将其覆盖        
		AS608_Cmd_Check();                                                        //单片机向指纹模块发送校对命令
		AS608_Receive_Data(12);								//将串口接收到的数据转存
		if(AS608_RECEICE_BUFFER[9] == 0)                                	        //判断数据低第9位是否接收到0
		{
			display(2,0,"Docking  success"); 						        //符合成功条件则显示对接成功
		}
		Delay_ms(5000);
		lcd_wcmd(0x01);
}