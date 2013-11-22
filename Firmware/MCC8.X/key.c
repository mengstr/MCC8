#include <stdint.h>         // uint8_t definitions

#include "config.h"
#include "utils.h"
#include "key.h"

uint16_t keys;           // The bits corresponds to keypad 0..F
uint8_t keysX;           // The first four bits here is set as the control keys OK,PLUS,AD,MU

void KeyInit(void) {
    KEY_O1_TRIS=0;
    KEY_O2_TRIS=0;
    KEY_O3_TRIS=0;
    KEY_O4_TRIS=0;
    KEY_Ox_TRIS=0;
    KEY_I5_TRIS=1;
    KEY_I6_TRIS=1;
    KEY_I7_TRIS=1;
    KEY_I8_TRIS=1;

    KEY_O1=1;
    KEY_O2=1;
    KEY_O3=1;
    KEY_O4=1;
    KEY_Ox=1;
    
    keys=0;
    keysX=0;
}


uint16_t KeyScan(void) {
    keys=0;
    keysX=0;

    KEY_O1=0;
    Delay10uS();
    if (!KEY_I5) keys|=0x0002;  // 1
    if (!KEY_I6) keys|=0x0004;  // 2
    if (!KEY_I7) keys|=0x0008;  // 3
    if (!KEY_I8) keys|=0x1000;  // C
    KEY_O1=1;

    KEY_O2=0;
    Delay10uS();
    if (!KEY_I5) keys|=0x0010;  // 4
    if (!KEY_I6) keys|=0x0020;  // 5
    if (!KEY_I7) keys|=0x0040;  // 6
    if (!KEY_I8) keys|=0x2000;  // D
    KEY_O2=1;

    KEY_O3=0;
    Delay10uS();
    if (!KEY_I5) keys|=0x0080;  // 7
    if (!KEY_I6) keys|=0x0100;  // 8
    if (!KEY_I7) keys|=0x0200;  // 9
    if (!KEY_I8) keys|=0x4000;  // E
    KEY_O3=1;

    KEY_O4=0;
    Delay10uS();
    if (!KEY_I5) keys|=0x0400;  // A
    if (!KEY_I6) keys|=0x0001;  // 0
    if (!KEY_I7) keys|=0x0800;  // B
    if (!KEY_I8) keys|=0x8000;  // F
    KEY_O4=1;

    KEY_Ox=0;
    Delay10uS();
    if (!KEY_I5) keysX|=KEY_PLUS;
    if (!KEY_I6) keysX|=KEY_AD;
    if (!KEY_I7) keysX|=KEY_MU;
    if (!KEY_I8) keysX|=KEY_OK;
    KEY_Ox=1;

    return keys;
}



//
//
//
void KeyWaitForRelease(void) {
    for (;;) {
        Delay10mS(10);
        KeyScan();
        if (keys+keysX==0) break;
    }
}




//
//
//
uint8_t KeyTranslateKeys(uint16_t k) {
    if (k&1) return 0;
    if (k&2) return 1;
    if (k&4) return 2;
    if (k&8) return 3;
    if (k&16) return 4;
    if (k&32) return 5;
    if (k&64) return 6;
    if (k&128) return 7;
    if (k&256) return 8;
    if (k&512) return 9;
    if (k&1024) return 10;
    if (k&2048) return 11;
    if (k&2048) return 12;
    if (k&8192) return 13;
    if (k&16384) return 14;
    if (k&32768) return 15;
    return 255;
}
