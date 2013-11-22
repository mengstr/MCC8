#ifndef KEY_H
#define	KEY_H

#include <stdint.h>         // uint8_t definitions


#define KEY_OK          0x01
#define KEY_PLUS        0x02
#define KEY_AD          0x04
#define KEY_MU          0x08

extern uint16_t keys;           // The bits corresponds to keypad 0..F
extern uint8_t keysX;           // The first four bits here is set as the control keys OK,PLUS,AD,MU

void KeyInit(void);
uint16_t KeyScan(void);
void KeyWaitForRelease(void);


#endif	/* KEY_H */

