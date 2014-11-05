#include <stdint.h>
#include "pps.h"
#include "spi.h"


#define  PPRE_DIV1      0x03    // Primary Prescale 1:1
#define  PPRE_DIV4      0x02    // Primary Prescale 4:1
#define  PPRE_DIV16     0x01    // Primary Prescale 16:1
#define  PPRE_DIV64     0x00    // Primary Prescale 64:1

#define  SPRE_DIV1      0x07    // Secondary Prescale 1:1
#define  SPRE_DIV2      0x06    // Secondary Prescale 2:1
#define  SPRE_DIV3      0x05    // Secondary Prescale 3:1
#define  SPRE_DIV4      0x04    // Secondary Prescale 4:1
#define  SPRE_DIV5      0x03    // Secondary Prescale 5:1
#define  SPRE_DIV6      0x02    // Secondary Prescale 6:1
#define  SPRE_DIV7      0x01    // Secondary Prescale 7:1
#define  SPRE_DIV8      0x00    // Secondary Prescale 8:1



//
//
//
void SPI1Init(void) {
    // Remap SPI1 pins
    PPSUnLock;
    PPSInput(PPS_SDI1, PPS_RP4);        // MISO <-- Change this
    PPSOutput(PPS_RP8, PPS_SDO1) ;      // MOSI <-- Change this
    PPSOutput(PPS_RP9, PPS_SCK1OUT);    // CLK  <-- Change this
    PPSLock;

    //config SPI1
    SPI1STATbits.SPIEN      = 0;            // disable SPI port
    SPI1STATbits.SPISIDL    = 0;            // Continue module operation in Idle mode
    SPI1BUF                 = 0;            // clear SPI buffer
    IFS0bits.SPI1IF         = 0;            // clear interrupt flag
    IEC0bits.SPI1IE         = 0;            // disable interrupt
    SPI1CON1bits.DISSCK     = 0;            // Internal SPIx clock is enabled
    SPI1CON1bits.DISSDO     = 0;            // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16     = 0;            // set in 16-bit mode, clear in 8-bit mode
    SPI1CON1bits.SMP        = 0;            // Input data sampled at middle of data output time
    SPI1CON1bits.CKP        = 1;            // CKP and CKE is subject to change ...
    SPI1CON1bits.CKE        = 0;            // ... based on your communication mode.
    SPI1CON1bits.MSTEN      = 1;            // 1 =  Master mode; 0 =  Slave mode
    SPI1CON1bits.SPRE       = SPRE_DIV2;    // Secondary Prescaler
    SPI1CON1bits.PPRE       = PPRE_DIV4;    // Primary Prescaler
    SPI1CON2                = 0;            // non-framed mode
    SPI1STATbits.SPIEN      = 1;            // enable SPI port, clear status
}


//
//
//
uint8_t SPI1Write(uint8_t data) {
    SPI1BUF=data;
    while(!SPI1STATbits.SPIRBF);
    return SPI1BUF;
}
