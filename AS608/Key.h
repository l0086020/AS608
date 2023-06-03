#ifndef _KEY_H_
#define _KEY_H_

#include <reg52.h>

sbit KEY_DOWN=P2^4;
sbit KEY_UP=P2^6;
sbit KEY_OK=P2^2;
sbit KEY_CANCEL=P2^0;

void Key_Init(void);

#endif