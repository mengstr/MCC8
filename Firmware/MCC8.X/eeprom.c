#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <xc.h>
#include "config.h"
#include "spi.h"
#include "eeprom.h"




uint8_t EeRead(void) {
    uint8_t v;
    uint16_t address=0;
    uint16_t cnt;

    EE_CS = 0;
    SPI1Write(0b00000110);      //  Write Enable
    EE_CS = 1;

    EE_CS = 0;
    SPI1Write(0b00000010);      // Write Data
    SPI1Write(address>>8);
    SPI1Write(address&0xFF);
    v=SPI1Write(0x11);              // Data
    v=SPI1Write(0x22);              // Data
    v=SPI1Write(0x33);              // Data
    v=SPI1Write(0x44);              // Data
    v=SPI1Write(0x55);              // Data
    v=SPI1Write(0x66);              // Data
    v=SPI1Write(0x77);              // Data
    v=SPI1Write(0x88);              // Data
    v=SPI1Write(0x99);              // Data
    EE_CS = 1;


    EE_CS=0;
    SPI1Write(0b00000101);      // GET STATUS
    for (cnt=0; cnt<254; cnt++) {
        v=SPI1Write(0xAA);          // Dummy for read
        if (!(v&0x01)) break;
        __delay_us(100);
    }
    EE_CS=1;


    
    //    Delay10mS(100);

//    EE_CS = 0;
//    SPI1Write(0b00000011);      // READ
//    SPI1Write(address>>8);
//    SPI1Write(address&0xFF);
//    v=SPI1Write(0xAA);          // Dummy for read
//    EE_CS = 1;

    return cnt;
}