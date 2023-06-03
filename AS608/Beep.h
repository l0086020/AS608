#ifndef _BEEP_H_
#define _BEEP_H_
#include <delay.h>
#include <reg52.h>

sbit beep=P2^6;

void Beep_Times(unsigned char times);

#endif