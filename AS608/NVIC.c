#include <NVIC.h>

void NVIC_Init(void)
{
	EA = 1;
	EX0 = 1;
	IT0 = 0;
}