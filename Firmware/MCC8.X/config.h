#ifndef _CONFIG_H
#define	_CONFIG_H

#include <stdlib.h>
#include <stdint.h>         // uint8_t definitions
#include <stdbool.h>        // true/false definitions
#include <xc.h>

#define _XTAL_FREQ (8000000ULL)
#define FCY (_XTAL_FREQ/2)

#define    SPI_MOSI_TRIS    TRISC7
#define    SPI_MISO_TRIS    TRISB4
#define    SPI_CLK_TRIS     TRISB6

#define    SPI_MOSI         LATCbits.LATC7
#define    SPI_MISO         PORTBbits.RB4
#define    SPI_CLK          LATBbits.LATB6


//    RA0	LCD_RST
//    RA1	LCD_CS
//    RA2	LCD_BACKLIGHT
//    RB2 	LCD_DI
//    RB3 	LCD_CLK

#define LCD_RESET_TRIS  TRISAbits.TRISA0
#define LCD_LIGHT_TRIS  TRISAbits.TRISA2
#define LCD_CE_TRIS     TRISAbits.TRISA1
#define LCD_DI_TRIS     TRISBbits.TRISB2
#define LCD_CLK_TRIS    TRISBbits.TRISB3
#define LCD_RESET       LATAbits.LATA0
#define LCD_LIGHT       LATAbits.LATA2
#define LCD_CE          LATAbits.LATA1
#define LCD_DI          LATBbits.LATB2
#define LCD_CLK         LATBbits.LATB3


//    RA3 	KEY1
//    RB1 	KEYx / PGC
//    RB4 	KEY2
//    RB7 	KEY5 (pullup)
//    RB8 	KEY4
//    RB9 	KEY8 (pullup)
//    RB13 	KEY6 (pullup)
//    RB14 	KEY7 (pullup)
//    RB15 	KEY3

#define KEY_O1_TRIS     TRISAbits.TRISA3
#define KEY_O2_TRIS     TRISBbits.TRISB4
#define KEY_O3_TRIS     TRISBbits.TRISB15
#define KEY_O4_TRIS     TRISBbits.TRISB8
#define KEY_Ox_TRIS     TRISBbits.TRISB1
#define KEY_I5_TRIS     TRISBbits.TRISB7
#define KEY_I6_TRIS     TRISBbits.TRISB13
#define KEY_I7_TRIS     TRISBbits.TRISB14
#define KEY_I8_TRIS     TRISBbits.TRISB9

#define KEY_O1          LATAbits.LATA3
#define KEY_O2          LATBbits.LATB4
#define KEY_O3          LATBbits.LATB15
#define KEY_O4          LATBbits.LATB8
#define KEY_Ox          LATBbits.LATB1
#define KEY_I5          PORTBbits.RB7
#define KEY_I6          PORTBbits.RB13
#define KEY_I7          PORTBbits.RB14
#define KEY_I8          PORTBbits.RB9






#endif	/* CONFIG_H */

