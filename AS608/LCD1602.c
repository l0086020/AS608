#include <LCD1602.h>
#include <delay.h>

/***************************************写命令*********************************************/
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
/***************************************写数据*********************************************/
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
/***********************************液晶繁忙检测*******************************************/
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
/**********************************液晶初始化函数*****************************************/
void LCD1602_Init(void)  
{
        Delay_ms(15);                      //上电延时15ms
          LCD1602_WriteCMD(0x38); //写显示指令(不检测忙信号)
          Delay_ms(5);
          LCD1602_CheckBusy();
          LCD1602_WriteCMD(0x38); //写显示指令
          LCD1602_CheckBusy();
          LCD1602_WriteCMD(0x01); //清屏
          LCD1602_CheckBusy();
          LCD1602_WriteCMD(0x06); //显示光标移动设置
          LCD1602_CheckBusy();
          LCD1602_WriteCMD(0x0c); //显示开及光标设置  
}

/***********************************液晶显示函数*****************************************/
void LCD1602_Display(unsigned char addr,unsigned char* pointer,unsigned char index,unsigned char num)    //入口参数：addr起始地址，pointer指针地址，index下标，num个数
{
          unsigned char i;
          LCD1602_CheckBusy();        //判断忙信号
          LCD1602_WriteCMD(addr);        //写入地址
          for(i=0;i<num;i++)                //写入数据
          {
             LCD1602_CheckBusy();                           //判断忙信号
             LCD1602_WriteDAT(pointer[index+i]);//写入数据     
          }
}
