#include <stdlib.h>
#include <stdint.h>         // uint8_t definitions
#include <stdbool.h>        // true/false definitions
#include <stdio.h>

#include <xc.h>
#include "config.h"
#include "oled.h"
#include "eeprom.h"
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
 *
 * LCD display is 128x64 pixels so each CHIP-8 pixel can be 2x2 pixels
 * on the display
 *
*/



//
//
//
uint8_t ShowGameMenu(void) {
    uint8_t i;
    uint8_t mnu=0;
    uint8_t realKey;

    for (;;) {
        OledClear();
        if (mnu==0) {
            for (i=0; i<8; i++) {
                OledXY(0,i*8);
                OledCharacter((char)49+i);
                OledXY(10,i*8);
                OledString(gameName[i]);
            }
        }
        if (mnu==1) {
            for (i=0; i<8; i++) {
                OledXY(0,i*8);
                OledCharacter((char)49+i);
                OledXY(10,i*8);
                OledString(gameName[i+8]);
            }
        }
        if (mnu==2) {
            for (i=0; i<7; i++) {
                OledXY(0,i*8);
                OledCharacter(49+i);
                OledXY(10,i*8);
                OledString(gameName[i+16]);
            }
        }
        if (mnu==3) {
            OledXY(0,0);
            OledCharacter('F');
            OledXY(10,0);
            OledString("Toggle Debug");
        }
        OledRefresh();
        for(;;) {
            KeyScan();
            realKey=KeyTranslateKeys(keys);
            if (keysX&KEY_MU) {
                mnu++;
                if (mnu>3) mnu=0;
                OledClear();
                OledRefresh();
                KeyWaitForRelease();
                break;
            }
            if (mnu==0 && realKey>0 && realKey<9) return realKey+0-1;
            if (mnu==1 && realKey>0 && realKey<9) return realKey+8-1;
            if (mnu==2 && realKey>0 && realKey<8) return realKey+16-1;
        }

    }
    return 0;
}

//char gameName[23][9] = {
//const unsigned char *gamePtr[23] = {
//const uint16_t gameLength[23] = {

//
//
//
void InitTimer1(void) {
  T1CON	 = 0x8010;
  _T1IE	 = 1;
  _T1IF	 = 0;
  IPC0	 = IPC0 | 0x1000;
  PR1	 = 8333;
}



//
// Timer 1 interrupt service routine
//
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void) {
    IFS0bits.T1IF = 0;      // Clear Timer 1 interrupt flag
    Chip8HandleTimers();
}





//
//
//
int main(void) {
    uint8_t res;

    AD1PCFG=0xEFFF;         // All pins are Digital

    // Set pins as output mode
    OLED_DC_TRIS=0;
    OLED_CS_TRIS=0;
    OLED_RES_TRIS=0;
    EE_CS_TRIS=0;
    PIEZO_TRIS=0;

    // Disable CS for both devices on the SPI bus
    OLED_CS=1;
    EE_CS=1;

    SPI1Init();             // Initialize the SPI1 port
    OledInit();             // Initialize/Reset the OLED display
    OledRefresh();
    InitTimer1();           // Start the 60 Hz chip-8 timer
    KeyInit();
    __delay_ms(100);

    chip8debug=0;
    
    for (;;) {
        res=ShowGameMenu();
        Chip8Reset(gamePtr[res], gameLength[res]);
//        LcdFill();
        Chip8RefreshScreen();
        res=Chip8Emulate();
    }
}
