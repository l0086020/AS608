#include <Beep.h>

void Beep_Times(unsigned char times)
{
        unsigned char i=0;
        for(i=0;i<times;i++)
        {
                 beep=0;
                 Delay_ms(200);
                 beep=1;
                 Delay_ms(200);
        }
}