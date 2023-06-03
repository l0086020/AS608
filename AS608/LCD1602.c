#include <LCD1602.h>
#include <delay.h>

/***************************************д����*********************************************/
void LCD1602_WriteCMD(unsigned char cmd)  
{
          EN=0;
          RS=0;
          RW=0;
          Delay_us(10);
          EN=1;
          Delay_us(10);
          DataPort=cmd;
          Delay_us(10);
          EN=0;
}
/***************************************д����*********************************************/
void LCD1602_WriteDAT(unsigned char dat)
{
          EN=0;
          RS=1;
          RW=0;
          Delay_us(10);
          EN=1;
          Delay_us(10);
          DataPort=dat;
          Delay_us(10);
          EN=0;
}
/***********************************Һ����æ���*******************************************/
void LCD1602_CheckBusy(void)
{
        
        uchar busy;
        DataPort=0xff;
        RS=0;
        RW=1;
        do
        {
                EN=1;
                busy=DataPort;
                EN=0;
        }while(busy&0x80);
        
}
/**********************************Һ����ʼ������*****************************************/
void LCD1602_Init(void)  
{
        Delay_ms(15);                      //�ϵ���ʱ15ms
          LCD1602_WriteCMD(0x38); //д��ʾָ��(�����æ�ź�)
          Delay_ms(5);
          LCD1602_CheckBusy();
          LCD1602_WriteCMD(0x38); //д��ʾָ��
          LCD1602_CheckBusy();
          LCD1602_WriteCMD(0x01); //����
          LCD1602_CheckBusy();
          LCD1602_WriteCMD(0x06); //��ʾ����ƶ�����
          LCD1602_CheckBusy();
          LCD1602_WriteCMD(0x0c); //��ʾ�����������  
}

/***********************************Һ����ʾ����*****************************************/
void LCD1602_Display(unsigned char addr,unsigned char* pointer,unsigned char index,unsigned char num)    //��ڲ�����addr��ʼ��ַ��pointerָ���ַ��index�±꣬num����
{
          unsigned char i;
          LCD1602_CheckBusy();        //�ж�æ�ź�
          LCD1602_WriteCMD(addr);        //д���ַ
          for(i=0;i<num;i++)                //д������
          {
             LCD1602_CheckBusy();                           //�ж�æ�ź�
             LCD1602_WriteDAT(pointer[index+i]);//д������     
          }
}
