#include <stdlib.h>
#include <stdint.h>         // uint8_t definitions
#include <stdbool.h>        // true/false definitions

#include <xc.h>
#include "config.h"
#include <libpic30.h>
#include "utils.h"



//
// Waits the specified number of 10mS units
//
void Delay10mS(uint8_t cnt) {
    while (cnt--) __delay_ms(10);
}


//
//
//
void Delay100uS(void) {
    __delay_us(100);
}


//
//
//
void Delay10uS(void) {
    __delay_us(10);
}

