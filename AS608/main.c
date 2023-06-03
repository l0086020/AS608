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
			Uart_Init();                     																					   //初始化串口
			Key_Init();                      																		           //初始化按键
			Delay_ms(5000);         																											 //延时500MS，等待指纹模块复位
			Device_Check();                      																			     //校对指纹模块是否接入正确，液晶做出相应的提示
			Delay_ms(1000);                  																				       //对接成功界面停留一定时间
			while(1)
			{
	/***********************************进入主功能界面*********************************************/
						display(0,1,"Search finger ");          																	 //第一排显示搜索指纹
						display(1,1,"Add finger    ");
						display(2,1,"Delete all    ");     																				   //添加和删除指纹
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
	/***************************************确认键**************************************************/
						if(KEY_OK == 0)
						{
						Delay_ms(5);
						if(KEY_OK == 0)
						{         
							while(KEY_OK == 0);																										//等待松开按键                                                               
							switch(local_date)
							{
							case 0:  																															//搜索指纹        
											flag=1;                                       
											AS608_Find_Fingerprint();   
							break;        
						 
							case 1:       																											  //添加指纹
											flag=1;       																							  //flag=1，若指纹库为空，则可以直接添加指纹                                
											if(AS608_number_of_fingers())
											{
												flag=0;																											//flag置0由两重作用：
																																										//1、指纹库中已有指纹，则需要搜索匹配成功，由AS608_Find_Fingerprint()将flag置1，才能添加指纹
																																										//2、flag=0，则在搜索指纹成功后不执行开锁操作
												AS608_Find_Fingerprint();
											}
											if(flag)
											{
												AS608_Add_Fingerprint();
											}
							break;                                         
							
							case 2:       																											  //清空指纹
											flag=0;                                                       //1、在搜索指纹成功后不执行开锁操作；2、若搜索不成功，不执行清空操作
											AS608_Find_Fingerprint();																			//搜索匹配成功后，函数内部将flag置1，才能清空指纹库
											if(flag)
											{
												AS608_Delete_All_Fingerprint();
											}
							break;
										}
								}
						}
	/***************************************切换键**************************************************/
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
										Delay_ms(10);										//延时判断100MS检测一次               
										State = 0;
				}
	}
}

/*void NVIC(void) interrupt 0
{
}*/