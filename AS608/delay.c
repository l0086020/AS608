#include <delay.h>

void Delay_ms(uint ms)
{
     uint i;
     do{
					i = MAIN_Fosc / 96000;
					while(--i);   //96T per loop
     }while(--ms);
}