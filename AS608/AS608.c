#include <AS608.h>

volatile unsigned char AS608_RECEICE_BUFFER[32]; //volatile:ϵͳ�������´������ڵ��ڴ��ȡ���ݣ���ʹ��ǰ���ָ��ոմӸô���ȡ������

//FINGERPRINTͨ��Э�鶨��
code unsigned char AS608_Get_Device[10] ={0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};//������֤
code unsigned char AS608_Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};  //Э���ͷ
code unsigned char AS608_Get_Img[6] = {0x01,0x00,0x03,0x01,0x00,0x05};    //���ָ��ͼ��
code unsigned char AS608_Get_Templete_Count[6] ={0x01,0x00,0x03,0x1D,0x00,0x21 }; //���ģ������
code unsigned char AS608_Search[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x03,0xE7,0x00,0xF8}; //����ָ��������Χ0 - 999,ʹ��BUFFER1�е�����������
code unsigned char AS608_Search_0_9[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x00,0x13,0x00,0x21}; //����0-9��ָ��
code unsigned char AS608_Img_To_Buffer1[7]={0x01,0x00,0x04,0x02,0x01,0x00,0x08}; //��ͼ����뵽BUFFER1
code unsigned char AS608_Img_To_Buffer2[7]={0x01,0x00,0x04,0x02,0x02,0x00,0x09}; //��ͼ����뵽BUFFER2
code unsigned char AS608_Reg_Model[6]={0x01,0x00,0x03,0x05,0x00,0x09}; //��BUFFER1��BUFFER2�ϳ�����ģ��
code unsigned char AS608_Delete_All_Model[6]={0x01,0x00,0x03,0x0d,0x00,0x11};//ɾ��ָ��ģ�������е�ģ��
volatile unsigned char  AS608_Save_Finger[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//��BUFFER1�е��������ŵ�ָ����λ��

//���Ͱ�ͷ
void AS608_Cmd_Send_Pack_Head(void)
{
        int i;        
        for(i=0;i<6;i++) //��ͷ
        {
                Uart_Send_Byte(AS608_Pack_Head[i]);   
        }               
}

//����ָ��
void AS608_Cmd_Check(void)
{
        int i=0;
        AS608_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
        for(i=0;i<10;i++)
        {               
                Uart_Send_Byte(AS608_Get_Device[i]);
        }
}

//���շ������ݻ���
void AS608_Receive_Data(unsigned char ucLength)
{
        unsigned char i;                                 
        for (i=0;i<ucLength;i++)
                AS608_RECEICE_BUFFER[i] = Uart_Receive_Byte();
}

//FINGERPRINT_���ָ��ͼ������
void AS608_Cmd_Get_Img(void)
{
    unsigned char i;
    AS608_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
    for(i=0;i<6;i++) //�������� 0x1d
        {
       Uart_Send_Byte(AS608_Get_Img[i]);
        }
}

//��ͼ��ת��������������Buffer1��
void FINGERPRINT_Cmd_Img_To_Buffer1(void)
{
         unsigned char i;
        AS608_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ      
           for(i=0;i<7;i++)   //�������� ��ͼ��ת���� ������ ����� CHAR_buffer1
        {
                Uart_Send_Byte(AS608_Img_To_Buffer1[i]);
        }
}
//��ͼ��ת��������������Buffer2��
void FINGERPRINT_Cmd_Img_To_Buffer2(void)
{
        unsigned char i;
        AS608_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
        for(i=0;i<7;i++)   //�������� ��ͼ��ת���� ������ ����� CHAR_buffer1
        {
                Uart_Send_Byte(AS608_Img_To_Buffer2[i]);
        }
}

//����ȫ���û�999ö
void AS608_Cmd_Search_Finger(void)
{
        unsigned char i;                       
        AS608_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
        for(i=0;i<11;i++)
        {
                Uart_Send_Byte(AS608_Search[i]);   
        }
}

//ת����������
void AS608_Cmd_Reg_Model(void)
{
        unsigned char i;                              
        AS608_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
        for(i=0;i<6;i++)
        {
                Uart_Send_Byte(AS608_Reg_Model[i]);   
        }
}

//ɾ��ָ��ģ���������ָ��ģ��
void FINGERPRINT_Cmd_Delete_All_Model(void)
{
        unsigned char i;   
    AS608_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ   
    for(i=0;i<6;i++) //����ɾ��ָ��ģ��
        {
              Uart_Send_Byte(AS608_Delete_All_Model[i]);   
        }        
}

//����ָ��
void AS608_Cmd_Save_Finger( unsigned int storeID )
{
        unsigned long temp = 0;
        unsigned char i;
        AS608_Save_Finger[5] =(storeID&0xFF00)>>8;
        AS608_Save_Finger[6] = (storeID&0x00FF);
        for(i=0;i<7;i++)   //����У���
                temp = temp + AS608_Save_Finger[i];
        AS608_Save_Finger[7]=(temp & 0x00FF00) >> 8; //���У������
        AS608_Save_Finger[8]= temp & 0x0000FF;                  
        AS608_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ        
        for(i=0;i<9;i++)  
                Uart_Send_Byte(AS608_Save_Finger[i]);      //�������� ��ͼ��ת���� ������ ����� CHAR_buffer1
}

//�鿴��ǰָ�ƿ���ָ��ģ����
int AS608_number_of_fingers()
{
         int num=1;//Ĭ��ģ�������һ��ģ��
        uchar i=0;
        AS608_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
        for(i=0;i<6;i++)
        {
                  Uart_Send_Byte(AS608_Get_Templete_Count[i]);
        }
        AS608_RECEICE_BUFFER[9]=1;//��������ж��Ƿ���ճɹ�
        AS608_Receive_Data(14);//��������
        if(AS608_RECEICE_BUFFER[9]==0) //���ճɹ�
        {
                 num=AS608_RECEICE_BUFFER[10]*256+AS608_RECEICE_BUFFER[11];//ƴ��ģ���ܸ���                        
        }
        return num;
}
//��һ�ַ����鿴ָ�ƿ����Ƿ���ģ�� //����Ӧ�ò鿴����1000��ģ��λ���Ƿ����ģ�壬��һ��ֻ�õõ�ǰ256�����ʴӼ�
/*
uchar AS608_notEmpty()
{
         uchar exist=0;
        char i=0;
        AS608_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
        for(i=0;i<7;i++)
        {
                  Uart_Send_Byte(AS608_num_of_finger_in_lib1[i]);
        }
        AS608_Receive_Data(10);//����ǰ10byte����,����10�ֽڵ�ȷ�����⣬����ȫ������
        if(AS608_RECEICE_BUFFER[9]==0) //���ճɹ�
        {
        AS608_Receive_Data(32);//���պ���32byte���ݣ��˼�0~255��ģ��Ϊ�Ƿ����ָ��ģ�������
        for(i=0;i<32;i++)//�鿴��32byte���ݣ��κ�һ��λ�ô���ģ���򷵻�ֵΪ�棬����Ϊ��
        {
                 if(AS608_RECEICE_BUFFER[i])
                        exist=1;
        }
        return exist;
        }
}
*/
//���ָ��
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
                 //��ȷ�ϼ���ʼ¼��ָ����Ϣ                                          
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
                                          //���·��ؼ��˳�¼�뷵��fingerID����״̬   
                                        if(KEY_CANCEL == 0)
                                         {
                                                  Delay_ms(5);
                                                if(KEY_CANCEL == 0)
                                                {
                                                        while(KEY_CANCEL==0);
                                                          break;
                                                }
                                                
                                          }
                                        AS608_Cmd_Get_Img(); //���ָ��ͼ��
                                        AS608_Receive_Data(12);
                                        //�жϽ��յ���ȷ����,����0ָ�ƻ�ȡ�ɹ�
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
                                                         AS608_Cmd_Get_Img(); //���ָ��ͼ��
                                                         AS608_Receive_Data(12);
                                                        //�жϽ��յ���ȷ����,����0ָ�ƻ�ȡ�ɹ�
                                                        if(AS608_RECEICE_BUFFER[9]==0)
                                                        {
                                                        Delay_ms(200);
                                                        display(2,0,"Successful entry");
																												Delay_ms(20000);
                                                        display(2,5,"    ID is       ");
                                                         //ָ��iDֵ��ʾ����
//                                                         LCD1602_WriteCMD(0xc0+10);
//                                                         LCD1602_WriteDAT(finger_id/100+48);
//                                                         LCD1602_WriteDAT(finger_id%100/10+48);
//                                                         LCD1602_WriteDAT(finger_id%100%10+48);
                                                         FINGERPRINT_Cmd_Img_To_Buffer2();
                                                         AS608_Receive_Data(12);
                                                         AS608_Cmd_Reg_Model();//ת����������
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

//����ָ��
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
//ɾ�����д�����ָ�ƿ�
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
//                                        LCD1602_WriteDAT(42);// ��'*'
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
		AS608_RECEICE_BUFFER[9]=1;                                     			      //��������ھ�λ���ж��Ƿ�ͨ������
		display(2,2,"Loading...");                   																//�豸�����н���                                                           			
		Delay_ms(5000);
		display(2,0,"Docking  failure");       											//Һ������ʾ�Խ�ʧ�ܣ����ָ��ģ���ԵĻ��Ὣ�串��        
		AS608_Cmd_Check();                                                        //��Ƭ����ָ��ģ�鷢��У������
		AS608_Receive_Data(12);								//�����ڽ��յ�������ת��
		if(AS608_RECEICE_BUFFER[9] == 0)                                	        //�ж����ݵ͵�9λ�Ƿ���յ�0
		{
			display(2,0,"Docking  success"); 						        //���ϳɹ���������ʾ�Խӳɹ�
		}
		Delay_ms(5000);
		lcd_wcmd(0x01);
}