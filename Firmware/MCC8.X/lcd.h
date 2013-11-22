#ifndef LCD_H
#define	LCD_H

#include <stdint.h>         // uint8_t definitions

#define EN_LCD_LOGO
//#define EN_LCD_BIGNUM
//#define EN_LCD_HUGENUM



void LcdSend(uint8_t cd, uint8_t data);
void LcdXY(uint8_t x, uint8_t y);
void LcdClear(void);
void LcdFill(void);
void LcdInit(void);
void LcdCharacter(int8_t character);
void LcdString(int8_t *characters);
void LcdBacklight(bool on);

#ifdef EN_LCD_HUGENUM
void LcdHugeNum(uint8_t n, uint8_t x, uint8_t y);
#endif

#ifdef EN_LCD_BIGNUM
void LcdBigNum(uint8_t n, uint8_t x, uint8_t y);
#endif

#ifdef EN_LCD_LOGO
void LcdLogo(void);
#endif


#endif	/* LCD_H */

