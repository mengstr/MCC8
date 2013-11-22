#include <stdlib.h>
#include <stdint.h>         // uint8_t definitions
#include <stdbool.h>        // true/false definitions
#include <stdio.h>

#include <xc.h>
#include "config.h"
#include "utils.h"
#include "lcd.h"
#include "key.h"
#include "games.h"
#include "chip8.h"

/*

 *
 * http://www.pong-story.com/chip8/
 * http://www.zophar.net/pdroms/chip8/chip-8-games-pack.html
 * view-source:http://www.markoskyritsis.com/index.php/open-source-development/chip8-online-emulator
 * http://www.emulator101.com/
 * http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
 * http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.5
 * http://mattmik.com/chip8.html
 * http://newsdee.com/flip8/
 * 

    RA0		LCD_RST
    RA1		LCD_CS
    RA2		LCD_BACKLIGHT
    RA3 	KEY1
    RA4 	(spare2)
    RA5
    RA6
    RA7
    RB0 	PGD
    RB1 	KEYx / PGC
    RB2 	LCD_DI
    RB3 	LCD_CLK
    RB4 	KEY2
    RB5 	(spare1)
    RB6
    RB7 	KEY5 (pullup)
    RB8 	KEY4
    RB9 	KEY8 (pullup)
    RB10 	USB_D+
    RB11 	USB_D-
    RB12
    RB13 	KEY6 (pullup)
    RB14 	KEY7 (pullup)
    RB15 	KEY3
 *
 *
 * LCD display is 96x68
 * CHIP-8 is on a 64x32 grid of pixels
 * 64*1.5=96
 * 32*1.5=48
 *
 *      XXXXXXXXXXXX
 *      XXXXXXXXXXXX
 *      XX--------XX
 *      XX--------XX
 *      XX--------XX
 *      XX--------XX
 *      XXXXXXXXXXXX
 *      XXXXXXXXXXXX
 *      xxxxxxxxxxxx
 *
*/





void test8(void) {
    uint8_t x,y;

    LcdClear();
    for (y=0; y<8; y++) {
        for (x=0; x<96; x++) {
            if (y==0 || y==1 || y==6 || y==7 || x<16 || x>79) {
                if (x&1) LcdSend(LCD_D,0x55); else LcdSend(LCD_D,0xAA);
            } else {
                LcdSend(LCD_D,0x00);
            }
        }
    }
}











int ShowGameMenu(void) {
    uint8_t i;

    LcdClear();
    for (i=0; i<8; i++) {
        LcdXY(0,i);
        LcdCharacter(49+i);
        LcdXY(10,i);
        LcdString(gameName[i]);
    }
    while (!KeyScan());
    return 0;
}

//char gameName[23][9] = {
//const unsigned char *gamePtr[23] = {





//
//
//
int main(void) {
    uint8_t     res;

    AD1PCFG=0xEFFF;         // All pins are Digital
    LcdInit();
    KeyInit();
    Delay10mS(50);

    for (;;) {
        LcdLogo();
        for(;;) {
            KeyScan();
            if (keysX&KEY_MU) break;
        }
        LcdClear();
        KeyWaitForRelease();
        ShowGameMenu();
//      C8Reset(INVADERS, sizeof(INVADERS));
        LcdFill();
        Chip8RefreshScreen();
        res=Chip8Emulate();
    }
}
