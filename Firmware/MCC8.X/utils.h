#ifndef UTILS_H
#define	UTILS_H

#include <stdint.h>         // uint8_t definitions

#include <xc.h>
#include "config.h"

#define  testbit(var, bit)   ((var) & (1UL <<(bit)))
#define  setbit(var, bit)    ((var) |= (1UL << (bit)))
#define  clrbit(var, bit)    ((var) &= ~(1UL << (bit)))


void Delay10mS(uint8_t cnt);
void Delay100uS(void);
void Delay10uS(void);


#endif	/* UTILS_H */

