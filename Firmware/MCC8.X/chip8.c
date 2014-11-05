#include <stdlib.h>
#include <stdint.h>         
#include <stdbool.h>        
#include <stdio.h>

#include <xc.h>
#include "config.h"
#include "oled.h"
#include "key.h"
#include "chip8.h"

uint8_t     c8screen[64*32/8];  // 64 x 32 pixels 1bpp screen buffer
uint8_t     c8ram[4096];        // RAM for chip-8 code, execution starts at 0x200
uint8_t     c8reg[16];          // The sixteen chip-8 working registers
uint16_t    c8i;                // The chip-8 index I register
volatile uint8_t c8dt;          // Delay timer, decrements down to 0 @ 60Hz
volatile uint8_t c8st;          // Sound timer, decrements down to 0 @ 60Hz
uint16_t    c8stack[16];        // Sixteen level deep stack for chip-8
uint8_t     c8sp;               // Stack pointer for chip-8
uint16_t    c8pc;               // Program counter for chip-8
uint8_t     chip8debug;         // 0=Normal, 1=Debuginfo & slow, 2=Single step

const uint8_t c8charset[] = {
  0xf0,0x90,0x90,0x90,0xf0,
  0x20,0x60,0x20,0x20,0x70,
  0xf0,0x10,0xf0,0x80,0xf0,
  0xf0,0x10,0xf0,0x10,0xf0,
  0x90,0x90,0xf0,0x10,0x10,
  0xf0,0x80,0xf0,0x10,0xf0,
  0xf0,0x80,0xf0,0x90,0xf0,
  0xf0,0x10,0x20,0x40,0x40,
  0xf0,0x90,0xf0,0x90,0xf0,
  0xf0,0x90,0xf0,0x10,0xf0,
  0xf0,0x90,0xf0,0x90,0x90,
  0xe0,0x90,0xe0,0x90,0xe0,
  0xf0,0x80,0x80,0x80,0xf0,
  0xe0,0x90,0x90,0x90,0xe0,
  0xf0,0x80,0xf0,0x80,0xf0,
  0xf0,0x80,0xf0,0x80,0x80
};


//
//
//
static uint8_t Chip8TestPixelXY(uint8_t x, uint8_t y) {
    uint8_t v;
    uint8_t mask;
    v=c8screen[(x+y*64)/8];
    mask=1<<(7-(x&0x07));
    return v&mask;
}


//
//
//
void Chip8RefreshScreen(void) {
    uint8_t x,y;

    OledClear();
    for (y=0; y<32; y++) {
        for (x=0; x<64; x++) {
            if (Chip8TestPixelXY(x,y)) {
                OledPixel(x*2,   y*2,   WHITE);
                OledPixel(x*2+1, y*2,   WHITE);
                OledPixel(x*2,   y*2+1, WHITE);
                OledPixel(x*2+1, y*2+1, WHITE);
            }
        }
    }
    OledRefresh();
}



//
//
//
void Chip8Reset(uint8_t *pLoad, uint16_t lenLoad) {
    uint16_t i;

    for (i=0; i<16; i++) {                  // Clear registers and stack
        c8reg[i]=0;
        c8stack[i]=0;
    }
    for (i=0; i<sizeof(c8screen); i++) {    // Clear screen
        c8screen[i]=0x00;
    }
    for (i=0; i<sizeof(c8ram); i++) {       // Clear ram
        c8ram[i]=0;
    }
    for (i=0; i<sizeof(c8charset); i++) {   // Copy charset into ram
        c8ram[0x50+i]=c8charset[i];
    }
    for (i=0; i<lenLoad; i++) {
        c8ram[0x0200+i]=*pLoad;
        pLoad++;
    }


    c8i=0;                                  // Clear index I reg
    c8dt=0;                                 // Clear delay timer
    c8st=0;                                 // Clear sound timer
    c8sp=0;                                 // Clear stack pointer
    c8pc=0x200;                             // Set program counter to start-of-program
}





//
//
//
static uint8_t C8XorPixelXY(uint8_t x, uint8_t y) {
    uint8_t wasset=0;
    uint8_t mask;
    mask=1<<(7-(x&0x07));
    if (c8screen[y*8+x/8]&mask) wasset=1;
    c8screen[y*8+x/8]^=mask;
    return wasset;
}


//
//    Dxyn - DRW Vx, Vy, nibble
//    Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
//
//    The interpreter reads n bytes from memory, starting at the address stored in I. These bytes are then displayed as
//    sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen. If this causes any pixels to be
//    erased, VF is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates
//    of the display, it wraps around to the opposite side of the screen. See instruction 8xy3 for more information on XOR, and
//    section 2.4, Display, for more information on the Chip-8 screen and sprites.
//
static void C8DRWvx_vy_nib(uint8_t vx, uint8_t vy, uint8_t nibble) {
    uint8_t pixels,yline,xline;

    c8reg[15]=0;
    for (yline = 0; yline<nibble; yline++) {
        pixels=c8ram[c8i+yline];
        for (xline=0; xline<8; xline++) {
            if((pixels & (0x80>>xline))!=0) {
                if (C8XorPixelXY(c8reg[vx]+xline, c8reg[vy]+yline)) c8reg[0x0F]=1;
            }
        }
    }
    Chip8RefreshScreen();
}




//
//
//
void Chip8HandleTimers(void) {
    if (c8dt>0) c8dt--;
    if (c8st>0) c8st--;
}

//
//
//
int Chip8Emulate(void) {
    uint16_t    opcode;
    uint8_t     op1, op2;
    uint8_t     vx,vy;
    uint8_t     invalidOp;
    char      tmps[20];
    uint8_t     i;
    uint16_t    j;


    invalidOp=0;
    for(;;){
        op1=c8ram[c8pc];
        op2=c8ram[c8pc+1];
        vx=op1&0x0F;
        vy=(op2>>4)&0x0F;
        opcode=(op1<<8)+op2;

        KeyScan();
        if (keysX&KEY_MU) return KEY_MU;

        if (chip8debug>0) {
            if (keysX&KEY_PLUS) c8dt=2;
            OledXY(0,0);
            sprintf(tmps,"%04x:%04x %02x %02x",c8pc, opcode, c8dt, c8st);
            OledString(tmps);
            OledXY(0,6);
            sprintf(tmps,"%02x%02x%02x%02x%02x%02x%02x%02x",c8reg[0],c8reg[1],c8reg[2],c8reg[3],c8reg[4],c8reg[5],c8reg[6],c8reg[7]);
            OledString(tmps);
            OledXY(0,7);
            sprintf(tmps,"%02x%02x%02x%02x%02x%02x%02x%02x",c8reg[8],c8reg[9],c8reg[10],c8reg[11],c8reg[12],c8reg[13],c8reg[14],c8reg[15]);
            OledString(tmps);
            __delay_ms(100);
        }


        __delay_us(100);

        c8pc+=2;
        switch (opcode&0xF000) {
            case 0x0000:
                switch (opcode&0x00FF) {
//----------------------------------------------------------------------------
                    case 0xE0:  // 00E0 - CLS     Clear the display.
                        for (i=0; i<sizeof(c8screen); i++) {
                            c8screen[i]=0x00;
                        }
                        Chip8RefreshScreen();
                        break;

//----------------------------------------------------------------------------
                    case 0xEE:  // 00EE - RET      Return from a subroutine.
                        // The interpreter sets the program counter to the 
                        // address at the top of the stack, then subtracts 1
                        // from the stack pointer.
                        c8pc=c8stack[c8sp];
                        c8sp--;
                        break;

                    default:
                        invalidOp=1;
                }
                break;

//----------------------------------------------------------------------------
            case 0x1000:    // 1nnn - JP addr      Jump to location nnn.
                // The interpreter sets the program counter to nnn.
                c8pc=opcode&0x0FFF;
                break;

//----------------------------------------------------------------------------
            case 0x2000:    // 2nnn - CALL addr      Call subroutine at nnn.
                // The interpreter increments the stack pointer, then puts the
                // current PC on the top of the stack. The PC is then set to nnn
                c8sp++;
                c8stack[c8sp]=c8pc;
                c8pc=opcode&0xFFF;
                break;

//----------------------------------------------------------------------------
            case 0x3000:    // 3xkk - SE Vx, byte - Skip next instruction if Vx = kk.
                // The interpreter compares register Vx to kk, and if they are 
                // equal, increments the program counter by 2.
                if (c8reg[vx]==op2) c8pc+=2;
                break;

//----------------------------------------------------------------------------
            case 0x4000:    // 4xkk - SNE Vx, byte -  Skip next instruction if Vx != kk.
                // The interpreter compares register Vx to kk, and if they are 
                // not equal, increments the program counter by 2.
                if (c8reg[vx]!=op2) c8pc+=2;
                break;

            case 0x5000:
                switch (opcode&0x000F) {
//----------------------------------------------------------------------------
                    case 0x00:  // 5xy0 - SE Vx, Vy - Skip next instruction if Vx = Vy.
                        // The interpreter compares register Vx to register 
                        // Vy, and if they are equal, increments the program
                        // counter by 2.
                        if (c8reg[vx]==c8reg[vy]) c8pc+=2;
                        break;

                    default:
                        invalidOp=1;

                }
                break;

//----------------------------------------------------------------------------
            case 0x6000:    // 6xkk - LD Vx, byte       Set Vx = kk.
                // The interpreter puts the value kk into register Vx.
                c8reg[vx]=op2;
                break;

//----------------------------------------------------------------------------
            case 0x7000:    // 7xkk - ADD Vx, byte        Set Vx = Vx + kk.
                // Adds the value kk to the value of register Vx, then stores
                // the result in Vx.
                c8reg[vx]+=op2;
                break;

            case 0x8000:
                switch (opcode&0x000F) {

//----------------------------------------------------------------------------
                    case 0x00:  // 8xy0 - LD Vx, Vy       Set Vx = Vy.
                        // Stores the value of register Vy in register Vx.
                        c8reg[vx]=c8reg[vy];
                        break;

//----------------------------------------------------------------------------
                    case 0x01:  // 8xy1 - OR Vx, Vy - Set Vx = Vx OR Vy.
                        // Performs a bitwise OR on the values of Vx and Vy,
                        // then stores the result in Vx.
                        c8reg[vx]|=c8reg[vy];
                        break;

//----------------------------------------------------------------------------
                    case 0x02:  // 8xy2 - AND Vx, Vy        Set Vx = Vx AND Vy.
                        // Performs a bitwise AND on the values of Vx and Vy,
                        // then stores the result in Vx.
                        c8reg[vx]&=c8reg[vy];
                        break;

//----------------------------------------------------------------------------
                    case 0x03:  // 8xy3 - XOR Vx, Vy - Set Vx = Vx XOR Vy.
                        // Performs a bitwise exclusive OR on the values of Vx
                        // and Vy, then stores the result in Vx.
                        c8reg[vx]^=c8reg[vy];
                        break;

//----------------------------------------------------------------------------
                    case 0x04:  // 8xy4 - ADD Vx, Vy      Set Vx = Vx + Vy, set VF = carry.
                        // The values of Vx and Vy are added together. If the
                        // result is greater than 8 bits (i.e., > 255,) VF is
                        // set to 1, otherwise 0. Only the lowest 8 bits of the
                        // result are kept, and stored in Vx.
                        c8reg[15]=0;
                        if (c8reg[vx]+c8reg[vy]>255) c8reg[15]=1;
                        c8reg[vx]+=c8reg[vy];
                        break;

//----------------------------------------------------------------------------
                    case 0x05:  // 8xy5 - SUB Vx, Vy     Set Vx = Vx - Vy, set VF = NOT borrow.
                        // If Vx > Vy, then VF is set to 1, otherwise 0. Then
                        // Vy is subtracted from Vx, and the results stored in Vx.
                        c8reg[15]=0;
                        if (c8reg[vx]>c8reg[vy]) c8reg[15]=1;
                        c8reg[vx]-=c8reg[vy];
                        break;

//----------------------------------------------------------------------------
                    case 0x06:  // 8xy6 - SHR Vx {, Vy}      Set Vx = Vx SHR 1.
                        // If the least-significant bit of Vx is 1, then VF
                        // is set to 1, otherwise 0. Then Vx is divided by 2.
                        c8reg[15]=0;
                        if ((c8reg[vx]&0x01)==0x01) c8reg[15]=1;
                        c8reg[vx]/=2;
                        break;

//----------------------------------------------------------------------------
                    case 0x07:  // 8xy7 - SUBN Vx, Vy      Set Vx = Vy - Vx, set VF = NOT borrow.
                        // If Vy > Vx, then VF is set to 1, otherwise 0. Then
                        // Vx is subtracted from Vy, and the results stored in Vx.
                        c8reg[15]=0;
                        if (c8reg[vy]>c8reg[vx]) c8reg[15]=1;
                        c8reg[vx]=c8reg[vy]-c8reg[vx];
                        break;

//----------------------------------------------------------------------------
                    case 0x0E:  // 8xyE - SHL Vx {, Vy}     Set Vx = Vx SHL 1.
                        // If the most-significant bit of Vx is 1, then VF is
                        // set to 1, otherwise to 0. Then Vx is multiplied by 2.
                        c8reg[15]=0;
                        if ((c8reg[vx]&0x80)==0x80) c8reg[15]=1;
                        c8reg[vx]*=2;
                        break;

                    default:
                        invalidOp=1;
                }
                break;

            case 0x9000:
                switch (opcode&0x000F) {

//----------------------------------------------------------------------------
                    case 0x00:  // 9xy0 - SNE Vx, Vy       Skip next instruction if Vx != Vy.
                        //  The values of Vx and Vy are compared, and if they
                        // are not equal, the program counter is increased by 2.
                        if (c8reg[vx]!=c8reg[vy]) c8pc+=2;
                        break;

                    default:
                        invalidOp=1;
                }
                break;

//----------------------------------------------------------------------------
            case 0xA000:    //  Annn - LD I, addr        Set I = nnn.
                // The value of register I is set to nnn.
                c8i=opcode&0x0FFF;
                break;

//----------------------------------------------------------------------------
            case 0xB000:    // Bnnn - JP V0, addr       Jump to location nnn + V0.
                // The program counter is set to nnn plus the value of V0.
                c8pc=(opcode&0x0FFF)+c8reg[0];
                break;

//----------------------------------------------------------------------------
            case 0xC000:    // Cxkk - RND Vx, byte - Set Vx = random byte AND kk.
                // The interpreter generates a random number from 0 to 255,
                // which is then ANDed with the value kk. The results are stored
                // in Vx.
                c8reg[vx]=rand()&op2;
                break;

//----------------------------------------------------------------------------
            case 0xD000:
                C8DRWvx_vy_nib(vx,vy,opcode&0x0F);
                break;

            case 0xE000:
                switch (opcode&0x00FF) {

//----------------------------------------------------------------------------
                    case 0x9E:  // Ex9E - SKP Vx     Skip next instruction if key with the value of Vx is pressed.
                        // Checks the keyboard, and if the key corresponding
                        // to the value of Vx is currently in the down position
                        // PC is increased by 2.
                        if (keys&(1UL<<c8reg[vx])) c8pc+=2;
                        break;

//----------------------------------------------------------------------------
                    case 0xA1:  // ExA1 - SKNP Vx      Skip next instruction if key with the value of Vx is not pressed.
                        // Checks the keyboard, and if the key corresponding to 
                        // the value of Vx is currently in the up position,
                        //PC is increased by 2.
                        if (!(keys&(1UL<<c8reg[vx]))) c8pc+=2;
                        break;

                    default:
                        invalidOp=1;
                }
                break;
            case 0xF000:
                switch (opcode&0x00FF) {

//----------------------------------------------------------------------------
                    case 0x07:  // Fx07 - LD Vx, DT       Set Vx = delay timer value.
                        // The value of DT is placed into Vx.
                        c8reg[vx]=c8dt;
                        break;

//----------------------------------------------------------------------------
                    case 0x0A:  // Fx0A - LD Vx, K    Wait for a key press, store the value of the key in Vx.
                        // All execution stops until a key is pressed, then
                        // the value of that key is stored in Vx.
                        if (keys==0) {
                            c8pc-=2;  // if no key is pressed then set the
                                      // Program Counter back to this instruction again
                        } else {
                            if (keys==0x0001) c8reg[vx]=0;
                            if (keys==0x0002) c8reg[vx]=1;
                            if (keys==0x0004) c8reg[vx]=2;
                            if (keys==0x0008) c8reg[vx]=3;
                            if (keys==0x0010) c8reg[vx]=4;
                            if (keys==0x0020) c8reg[vx]=5;
                            if (keys==0x0040) c8reg[vx]=6;
                            if (keys==0x0080) c8reg[vx]=7;
                            if (keys==0x0100) c8reg[vx]=8;
                            if (keys==0x0200) c8reg[vx]=9;
                            if (keys==0x0400) c8reg[vx]=10;
                            if (keys==0x0800) c8reg[vx]=11;
                            if (keys==0x1000) c8reg[vx]=12;
                            if (keys==0x2000) c8reg[vx]=13;
                            if (keys==0x4000) c8reg[vx]=14;
                            if (keys==0x8000) c8reg[vx]=15;
                        }
                        break;

//----------------------------------------------------------------------------
                    case 0x15:  // Fx15 - LD DT, Vx      Set delay timer = Vx.
                        // DT is set equal to the value of Vx.
                        c8dt=c8reg[vx];
                        break;

//----------------------------------------------------------------------------
                    case 0x18:  // Fx18 - LD ST, Vx       Set sound timer = Vx.
                        // ST is set equal to the value of Vx.
                        c8st=c8reg[vx];
                        break;

//----------------------------------------------------------------------------
                    case 0x1E:  // Fx1E - ADD I, Vx       Set I = I + Vx.
                        // The values of I and Vx are added, and the results
                        // are stored in I.
                        c8i+=c8reg[vx];
                        break;

//----------------------------------------------------------------------------
                    case 0x29:  // Fx29 - LD F, Vx    Set I = location of sprite for digit Vx.
                        // The value of I is set to the location for the
                        // hexadecimal sprite corresponding to the value of Vx.
                        // See section 2.4, Display, for more information on the
                        // Chip-8 hexadecimal font.
                        c8i=0x50+(vx)*5;
                        break;

//----------------------------------------------------------------------------
                    case 0x33:  // Fx33 - LD B, Vx - Store BCD valye of Vx in memory locations I,I+1,I+2.
                        // The interpreter takes the decimal value of Vx, and
                        // places the hundreds digit in memory at location in I,
                        // the tens digit at location I+1, and the ones digit
                        // at location I+2.
                        c8ram[c8i  ]=(vx/100)%10;
                        c8ram[c8i+1]=(vx/10)%10;
                        c8ram[c8i+2]=(vx)%10;
                        break;

//----------------------------------------------------------------------------
                    case 0x55:  // Fx55 - LD [I], Vx    Store registers V0 through Vx in memory starting at location I.
                        // The interpreter copies the values of registers V0
                        // through Vx into memory, starting at the address in I.
                        for(j=0; j<=(vx); j++) {
                            c8ram[c8i+j]=c8reg[j];
                        }
                        break;

//----------------------------------------------------------------------------
                    case 0x65:  // Fx65 - LD Vx, [I]     Read registers V0 through Vx from memory starting at location I.
                        // The interpreter reads values from memory starting
                        // at location I into registers V0 through Vx.
                        for(j=0; j<=(vx); j++) {
                            c8reg[j]=c8ram[c8i+j];
                        }
                        break;

                    default:
                        invalidOp=1;
                }
                break;
        }

        if (invalidOp) {
            invalidOp=0;
            OledXY(0,7);
            sprintf((char *)tmps,"Err! %04x @ %04x",opcode,c8pc);
            OledString(tmps);
            OledRefresh();
        }
    }   // for(;;)

    return 0;
}