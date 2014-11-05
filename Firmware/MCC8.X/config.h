#ifndef CONFIG_H_
#define	CONFIG_H_

#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

#define _XTAL_FREQ (8000000ULL)
#define FCY (_XTAL_FREQ/2)

extern void __delay32(unsigned long cycles);

#define __delay_ms(d) \
  { __delay32( (unsigned long) (((unsigned long long) d)*(FCY)/1000ULL)); }


#define __delay_us(d) \
  { __delay32( (unsigned long) (((unsigned long long) d)*(FCY)/1000000ULL)); }

#define  testbit(var, bit)   ((var) & (1UL <<(bit)))
#define  setbit(var, bit)    ((var) |= (1UL << (bit)))
#define  clrbit(var, bit)    ((var) &= ~(1UL << (bit)))


#define OLED_DC_TRIS    TRISBbits.TRISB5
#define OLED_CS_TRIS    TRISAbits.TRISA2
#define OLED_RES_TRIS   TRISAbits.TRISA3
#define EE_CS_TRIS      TRISAbits.TRISA4
#define PIEZO_TRIS      TRISBbits.TRISB7

#define OLED_DC         LATBbits.LATB5
#define OLED_CS         LATAbits.LATA2
#define OLED_RES        LATAbits.LATA3
#define EE_CS           LATAbits.LATA4
#define PIEZO           LATBbits.LATB7

#define TOUCH0_TRIS     TRISAbits.TRISA0
#define TOUCH1_TRIS     TRISAbits.TRISA1
#define TOUCH2_TRIS     TRISBbits.TRISB0
#define TOUCH3_TRIS     TRISBbits.TRISB1
#define TOUCH4_TRIS     TRISBbits.TRISB2
#define TOUCH5_TRIS     TRISBbits.TRISB3
#define TOUCH6_TRIS     TRISBbits.TRISB15
#define TOUCH7_TRIS     TRISBbits.TRISB14
#define TOUCH8_TRIS     TRISBbits.TRISB13

#define TOUCH0          LATAbits.LATA0
#define TOUCH1          LATAbits.LATA1
#define TOUCH2          LATBbits.LATB0
#define TOUCH3          LATBbits.LATB1
#define TOUCH4          LATBbits.LATB2
#define TOUCH5          LATBbits.LATB3
#define TOUCH6          LATBbits.LATB15
#define TOUCH7          LATBbits.LATB14
#define TOUCH8          LATBbits.LATB13

#endif

