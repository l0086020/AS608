#include<AS608.h>
#include<NVIC.h>

uchar flag=0;
char local_date=0;
uint finger_id = 0;
uchar Buffer [];
uint State = 0;

void main()
{          
		P1 = 0xff;
			lcd_init();
			//NVIC_Init();
			display(1,0,"Fingerprint Test");
			Uart_Init();                     																					   //��ʼ������
			Key_Init();                      																		           //��ʼ������
			Delay_ms(5000);         																											 //��ʱ500MS���ȴ�ָ��ģ�鸴λ
			Device_Check();                      																			     //У��ָ��ģ���Ƿ������ȷ��Һ��������Ӧ����ʾ
			Delay_ms(1000);                  																				       //�Խӳɹ�����ͣ��һ��ʱ��
			while(1)
			{
	/***********************************���������ܽ���*********************************************/
						display(0,1,"Search finger ");          																	 //��һ����ʾ����ָ��
						display(1,1,"Add finger    ");
						display(2,1,"Delete all    ");     																				   //��Ӻ�ɾ��ָ��
						display(3,1,"Exit          ");
						if(local_date==0)
						{
							display(0,0," *");
							display(1,0,"  ");
							display(2,0,"  ");
							display(3,0,"  ");
						}
						else if(local_date==1)
						{
							display(0,0,"  ");
							display(1,0," *");
							display(2,0,"  ");
							display(3,0,"  ");						
						}
						else if(local_date==2)
						{
							display(0,0,"  ");
							display(1,0,"  ");
							display(2,0," *");      
							display(3,0,"  ");
						}   
						else if(local_date==3)
						{
							display(0,0,"  ");
							display(1,0,"  ");
							display(2,0,"  ");      
							display(3,0," *");
						} 					
	/***************************************ȷ�ϼ�**************************************************/
						if(KEY_OK == 0)
						{
						Delay_ms(5);
						if(KEY_OK == 0)
						{         
							while(KEY_OK == 0);																										//�ȴ��ɿ�����                                                               
							switch(local_date)
							{
							case 0:  																															//����ָ��        
											flag=1;                                       
											AS608_Find_Fingerprint();   
							break;        
						 
							case 1:       																											  //���ָ��
											flag=1;       																							  //flag=1����ָ�ƿ�Ϊ�գ������ֱ�����ָ��                                
											if(AS608_number_of_fingers())
											{
												flag=0;																											//flag��0���������ã�
																																										//1��ָ�ƿ�������ָ�ƣ�����Ҫ����ƥ��ɹ�����AS608_Find_Fingerprint()��flag��1���������ָ��
																																										//2��flag=0����������ָ�Ƴɹ���ִ�п�������
												AS608_Find_Fingerprint();
											}
											if(flag)
											{
												AS608_Add_Fingerprint();
											}
							break;                                         
							
							case 2:       																											  //���ָ��
											flag=0;                                                       //1��������ָ�Ƴɹ���ִ�п���������2�����������ɹ�����ִ����ղ���
											AS608_Find_Fingerprint();																			//����ƥ��ɹ��󣬺����ڲ���flag��1���������ָ�ƿ�
											if(flag)
											{
												AS608_Delete_All_Fingerprint();
											}
							break;
										}
								}
						}
	/***************************************�л���**************************************************/
										if(KEY_DOWN == 0)
										{
											Delay_ms(5);
											if(KEY_DOWN == 0)
											{
												 while(KEY_DOWN == 0);	
												 if(local_date<=3)
												 {
														local_date++;
														if(local_date==4) local_date=0;                                                
												 }               
											}
										}
										if(KEY_UP == 0)
										{
											Delay_ms(5);
											if(KEY_UP == 0)
											{
												while(KEY_UP == 0);
												if(local_date>=0)
												{
													local_date--;
													if(local_date == -1) local_date=3;
												}
											
										}
										Delay_ms(10);										//��ʱ�ж�100MS���һ��               
										State = 0;
				}
	}
}

/*void NVIC(void) interrupt 0
{
}*/