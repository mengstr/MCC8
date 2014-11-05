#include <stdint.h>         // uint8_t definitions
#include <xc.h>


#include "config.h"
#include "key.h"


#define TOUCHNO     9       // Number of touch channels to use
#define TOUCHAVGCNT 32      // Number of sample to average to get base readings
#define THRESHOLD 50        // Readings less than this is not touched


uint16_t keys;           // The bits corresponds to keypad 0..F
uint8_t keysX;           // The first four bits here is set as the control keys OK,PLUS,AD,MU
uint16_t touchBase[TOUCHNO];

//
// AN0  AN1  AN2  AN3  AN4  AN5  AN9  AN10 AN11
// RA0  RA1  RB0  RB1  RB2  RB3  RB15 RB14 RB13
//
int ADCHANNELS[TOUCHNO] = {0,1,2,3,4,5,9,10,11};

unsigned int     ADSELECT[16] = {0x0001, 0x0002, 0x0004, 0x0008,
                                          0x0010, 0x0020, 0x0040, 0x0080,
                                          0x0100, 0x0200, 0x0400, 0x0800,
                                          0x1000, 0x2000, 0x4000, 0x8000};

// AD 27
// OK 47
// +  57
// MU 67
// 1  28
// 2  23
// 3  02
// C  12
// 4  48
// 5  34
// 6  04
// D  14
// 7  58
// 8  35
// 9  05
// E  15
// A  68
// 0  36
// B  06
// F  16



//
//
//
static void GroundAllChannels(void) {
    TOUCH0_TRIS=0;  // Set pins as OUTPUT
    TOUCH1_TRIS=0;
    TOUCH2_TRIS=0;
    TOUCH3_TRIS=0;
    TOUCH4_TRIS=0;
    TOUCH5_TRIS=0;
    TOUCH6_TRIS=0;
    TOUCH7_TRIS=0;
    TOUCH8_TRIS=0;

    TOUCH0=0;       // Set LOW level at pin
    TOUCH1=0;
    TOUCH2=0;
    TOUCH3=0;
    TOUCH4=0;
    TOUCH5=0;
    TOUCH6=0;
    TOUCH7=0;
    TOUCH8=0;

}





void CtmuInit(void) {
    //CTMUCON
    CTMUCONbits.CTMUEN = 0;     // make sure CTMU is disabled
    CTMUCONbits.CTMUSIDL = 0;   // CTMU continues to run in idle mode
    CTMUCONbits.TGEN = 0;       // disable edge delay generation mode of the CTMU
    CTMUCONbits.EDGEN = 0;      // edges are blocked
    CTMUCONbits.EDGSEQEN = 0;   // edge sequence not needed
    CTMUCONbits.IDISSEN = 0;    // Do not ground the current source
    CTMUCONbits.CTTRIG = 0;     // Trigger Output is disabled
    CTMUCONbits.EDG2POL = 0;
    CTMUCONbits.EDG2SEL = 0x3;  // Edge2 Src = OC1 (don?t care)
    CTMUCONbits.EDG1POL = 1;
    CTMUCONbits.EDG1SEL = 0x3;  // Edge1 Src = Timer1 (don?t care)

    //CTMUICON
    CTMUICON = 0x300;           // 55uA
    CTMUICON = 0x200;           // 5.5uA

    //setup A/D converter
    AD1PCFGL = 0x0000;
    AD1CON1 = 0x0000;
    AD1CHS = 0x0000;            // select the analog channel 0
    AD1CSSL=0x0000;
    AD1CON1bits.FORM = 0x0;     // Unsigned fractional format
    AD1CON3 = 0x0000;           // bits.ADRC=0;
    AD1CON2 = 0x0000;
    AD1CON1bits.ADON = 1;       // Turn On A/D

    CTMUCONbits.CTMUEN = 1;     // Enable CTMU
}


//
//
//
uint16_t CtmuRead(int index) {
    uint16_t value;

    AD1PCFG= 0xFFFF;                         // Set all A/D channels to digital I/O pins
    GroundAllChannels();                     // And ground them for a while to discharge everything
    __delay_us(2);                           // Wait for charge to drain

    switch (index) {                         // Set selectced pin as input
        case 0: TOUCH0_TRIS=1; break;
        case 1: TOUCH1_TRIS=1; break;
        case 2: TOUCH2_TRIS=1; break;
        case 3: TOUCH3_TRIS=1; break;
        case 4: TOUCH4_TRIS=1; break;
        case 5: TOUCH5_TRIS=1; break;
        case 6: TOUCH6_TRIS=1; break;
        case 7: TOUCH7_TRIS=1; break;
        case 8: TOUCH8_TRIS=1; break;
    }
    AD1PCFG = ~ADSELECT[ADCHANNELS[index]]; // Set selected channel to analog A/D input
    __delay_us(1);                          // Wait for A/D to connect to channel
    AD1CHS = ADCHANNELS[index];             // Select A/D channel
    CTMUCONbits.IDISSEN = 1;                // Drain any charge on the A/D circuit
    __delay_us(5);                          // Wait for charge to drain
    
    CTMUCONbits.IDISSEN = 0;                // Stop discharge of A/D circuit
    IFS0bits.AD1IF = 0;                     // Make sure A/D interrupt flag = 0

    AD1CON1bits.SAMP = 1;                   // Manually start sampling
    CTMUCONbits.EDG2STAT = 0;               // Make sure edge2 is 0
    CTMUCONbits.EDG1STAT = 1;               // Set edge1 - Start Charge
    __delay_us(10);                          // Delay for CTMU charge time
    CTMUCONbits.EDG1STAT = 0;               // Clear edge1 - Stop Charge
    IFS0bits.AD1IF = 0;

    AD1CON1bits.SAMP = 0;                   // Begin manual A/D conversion
    while(!IFS0bits.AD1IF);                 // Wait for the A/D conversion to finish
    value = ADC1BUF0;                       // Read the value from the A/D conversion

    AD1CON1bits.SAMP = 0;
    IFS0bits.AD1IF = 0;
    AD1CON1bits.DONE = 0;                   // Make sure A/D bits are cleared

    return value;
}


//
//
//
void CtmuCalibrate() {
    int ch;
    int cnt;

    // Initialize sums
    for (ch=0; ch<TOUCHNO; ch++) {
        touchBase[ch]=0;
    }

    // Sum up N readtings from each channel
    for (cnt=0; cnt<TOUCHAVGCNT; cnt++) {
        __delay_ms(1);
        for (ch=0; ch<TOUCHNO; ch++) {
            touchBase[ch]+=CtmuRead(ch);
        }
    }

    // And make averages of the summed readings
    for (ch=0; ch<TOUCHNO; ch++) {
        touchBase[ch]/=TOUCHAVGCNT;
    }

}


//
//
//
void KeyInit(void) {
    keys=0;
    keysX=0;
    CtmuInit();
    CtmuCalibrate();
}


//
//
//
uint16_t KeyScan(void) {
    int v[TOUCHNO];
    uint8_t ch;
    uint16_t maxch1;
    uint16_t maxch2;
    uint16_t keybits;

    // Get readings from all channels
    for (ch=0; ch<TOUCHNO; ch++) {
        v[ch]=CtmuRead(ch);
        v[ch]=touchBase[ch]-v[ch];
        if (v[ch]<THRESHOLD) v[ch]=0;
    }

    // Find the slot with the largest value
    maxch1=0;
    for (ch=1; ch<TOUCHNO; ch++) {
        if (v[ch]>v[maxch1]) maxch1=ch;
    }

    // Find the slot with the next-to largest value
    maxch2=-1;
    for (ch=0; ch<TOUCHNO; ch++) {
        if (ch!=maxch1) {
            if (maxch2==-1) maxch2=ch;
            if (v[ch]>v[maxch2]) maxch2=ch;
        }
    }
    

    keybits=(1<<maxch1) | (1<<maxch2);
    keys=0;
    keysX=0;

    if (keybits==((1<<2) | (1<<7))) keysX=KEY_AD;
    if (keybits==((1<<4) | (1<<7))) keysX=KEY_OK;
    if (keybits==((1<<5) | (1<<7))) keysX=KEY_PLUS;
    if (keybits==((1<<6) | (1<<7))) keysX=KEY_MU;

    if (keybits==((1<<3) | (1<<6))) keys=(1<<0);
    if (keybits==((1<<2) | (1<<8))) keys=(1<<1);
    if (keybits==((1<<2) | (1<<3))) keys=(1<<2);
    if (keybits==((1<<0) | (1<<2))) keys=(1<<3);
    if (keybits==((1<<4) | (1<<8))) keys=(1<<4);
    if (keybits==((1<<3) | (1<<4))) keys=(1<<5);
    if (keybits==((1<<0) | (1<<4))) keys=(1<<6);
    if (keybits==((1<<5) | (1<<8))) keys=(1<<7);
    if (keybits==((1<<3) | (1<<5))) keys=(1<<8);
    if (keybits==((1<<0) | (1<<5))) keys=(1<<9);
    if (keybits==((1<<6) | (1<<8))) keys=(1<<10);
    if (keybits==((1<<0) | (1<<6))) keys=(1<<11);
    if (keybits==((1<<1) | (1<<2))) keys=(1<<12);
    if (keybits==((1<<1) | (1<<4))) keys=(1<<13);
    if (keybits==((1<<1) | (1<<5))) keys=(1<<14);
    if (keybits==((1<<1) | (1<<6))) keys=(1<<15);

    return keys;
}



//
//
//
void KeyWaitForRelease(void) {
    for (;;) {
        __delay_ms(100);
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
