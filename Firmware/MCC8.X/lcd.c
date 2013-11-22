#include <stdint.h>         // uint8_t definitions
#include <xc.h>

#include "config.h"
//#include "spi.h"
#include "lcd.h"

#define LCD_C 0         // Command mode
#define LCD_D 1         // Data mode



#ifdef EN_LCD_LOGO
const uint8_t logo[489] = {
    0x42, 0xEC, 0x42, 0x03, 0x42, 0xEC, 0x42, 0x03, 0xF8, 0xFE, 0xFE, 0x42, 0xE6, 0x7F, 0x42, 0xE7,
    0xFE, 0xFC, 0xF0, 0x42, 0x03, 0xF8, 0xFE, 0xFE, 0x42, 0xE6, 0x7F, 0x42, 0xE7, 0xFE, 0xFC, 0xF0,
    0x00, 0x00, 0xE0, 0xFC, 0xFE, 0xFE, 0x42, 0xE6, 0x7F, 0x42, 0xE6, 0xFE, 0xFE, 0xFC, 0xE0, 0x42,
    0xED, 0x00, 0x42, 0xED, 0x42, 0x03, 0x42, 0xE9, 0x00, 0x00, 0x42, 0xE9, 0x42, 0x03, 0x42, 0xE9,
    0x00, 0x00, 0x42, 0xE9, 0x00, 0x00, 0x7F, 0x42, 0xE8, 0x81, 0x00, 0x81, 0x42, 0xE8, 0x7F, 0x42,
    0xE8, 0x7F, 0x42, 0xE4, 0xC0, 0x42, 0xED, 0x42, 0x03, 0x42, 0xE9, 0x00, 0x00, 0x42, 0x29, 0x42,
    0x03, 0x42, 0xE9, 0x00, 0x00, 0x42, 0x29, 0x42, 0x03, 0x83, 0xC7, 0xEF, 0x42, 0xED, 0xEF, 0xC7,
    0x83, 0x00, 0x42, 0xE8, 0x00, 0x42, 0xE9, 0x00, 0x42, 0xE8, 0x42, 0x03, 0x42, 0xE9, 0x00, 0x00,
    0x42, 0xC9, 0x42, 0x03, 0x42, 0xE9, 0x00, 0x00, 0x42, 0xC9, 0x00, 0x00, 0xFC, 0x42, 0xE8, 0x03,
    0x01, 0x03, 0x42, 0xE8, 0xFC, 0x42, 0xE8, 0x00, 0x01, 0x42, 0xE7, 0x01, 0x00, 0x42, 0xE8, 0x42,
    0x03, 0x42, 0xE9, 0xF0, 0xF0, 0x42, 0xE9, 0x42, 0x03, 0x42, 0xE9, 0xF0, 0xF0, 0x42, 0xE9, 0x00,
    0x00, 0x1F, 0x42, 0xE8, 0xF8, 0xF0, 0xF8, 0x42, 0xE8, 0x1F, 0x42, 0x44, 0x8F, 0x8F, 0x8F, 0x8F,
    0x00, 0x00, 0x80, 0x8F, 0x0F, 0x8F, 0x8F, 0x0F, 0x00, 0x80, 0x80, 0x0F, 0x0F, 0x8F, 0x8F, 0x8F,
    0x8F, 0x0F, 0x0F, 0x42, 0x03, 0x01, 0x03, 0x07, 0x8F, 0x8F, 0x8F, 0x42, 0x4A, 0x87, 0x87, 0x83,
    0x80, 0x42, 0x03, 0x81, 0x83, 0x87, 0x42, 0x43, 0x8F, 0x8F, 0x8F, 0x8F, 0x42, 0x44, 0x8F, 0x8F,
    0x87, 0x87, 0x03, 0x00, 0x00, 0x80, 0x80, 0x81, 0x07, 0x07, 0x0F, 0x8F, 0x8F, 0x42, 0x45, 0x8F,
    0x8F, 0x8F, 0x8F, 0x8F, 0x07, 0x07, 0x01, 0x42, 0x04, 0x3F, 0x7F, 0x61, 0x61, 0x61, 0x00, 0x00,
    0x7F, 0x7F, 0x0C, 0x7F, 0x7F, 0x00, 0x00, 0x7F, 0x7F, 0x00, 0x00, 0x7F, 0x7F, 0x0D, 0x0F, 0x07,
    0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x00, 0x33, 0x7F, 0x6D, 0x7F, 0x33, 0x42, 0x08, 0x3F, 0x7F, 0x61,
    0x61, 0x61, 0x00, 0x00, 0x3F, 0x7F, 0x61, 0x7F, 0x3F, 0x00, 0x00, 0x7F, 0x7F, 0x01, 0x7F, 0x7F,
    0x00, 0x00, 0x67, 0x6F, 0x6D, 0x7D, 0x39, 0x00, 0x00, 0x3F, 0x7F, 0x61, 0x7F, 0x3F, 0x00, 0x00,
    0x7F, 0x7F, 0x60, 0x60, 0x60, 0x00, 0x00, 0x7F, 0x7F, 0x6D, 0x6D, 0x61, 0x42, 0x0A, 0x70, 0x88,
    0x88, 0x88, 0x88, 0x88, 0x10, 0x00, 0xC0, 0x42, 0x83, 0x80, 0x42, 0x83, 0x80, 0x00, 0x00, 0x42,
    0x83, 0x80, 0x00, 0xF8, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xF8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70,
    0x00, 0x80, 0x42, 0x83, 0x80, 0x00, 0x80, 0x42, 0x83, 0x80, 0x00, 0xC0, 0x42, 0x83, 0x80, 0x42,
    0x83, 0x80, 0x00, 0xF8, 0x42, 0x07, 0x42, 0x83, 0x80, 0x00, 0xF8, 0x42, 0x84, 0x80, 0x00, 0x80,
    0x42, 0x83, 0x80, 0x42, 0x0B, 0x04, 0x42, 0x65, 0x07, 0x00, 0x0F, 0x42, 0x03, 0x0F, 0x42, 0x03,
    0x0F, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x42,
    0x05, 0x0F, 0x00, 0x07, 0x42, 0x63, 0x07, 0x00, 0x07, 0x42, 0x63, 0x07, 0x00, 0x0F, 0x42, 0x03,
    0x0F, 0x42, 0x03, 0x0F, 0x00, 0x0F, 0x42, 0x65, 0x00, 0x06, 0x09, 0x09, 0x09, 0x0F, 0x00, 0x0F,
    0x42, 0x64, 0x07, 0x00, 0x04, 0x09, 0x09, 0x0A, 0x04
 };
#endif



#ifdef EN_LCD_HUGENUM
const uint8_t chr24x32[] = {
	 0x00,0x00,0x00,0x00,0x00,0xE0,0x07,0x00,0x00,0xFE,0xFF,0x00,0x80,0xFF,0xFF,0x03,0xE0,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0x0F,0xF0,0x1F,0xFE,0x1F,0xF8,0x01,0xBE,0x1F,0xF8,0x00,0x1E,0x1F,0x7C,0x00,0x0F,0x3E,0x3C,0x80,0x07,0x3C,0x3C,0xC0,0x07,0x3C,0x3C,0xC0,0x03,0x3C,0x3C,0xE0,0x01,0x3C,0x7C,0xF0,0x00,0x3E,0x7C,0xF8,0x00,0x1E,0xF8,0x7D,0x80,0x1F,0xF8,0x3F,0xF0,0x0F,0xF0,0xFF,0xFF,0x0F,0xE0,0xFF,0xFF,0x07,0xC0,0xFF,0xFF,0x01,0x00,0xFF,0x7F,0x00,0x00,0xF0,0x0F,0x00,0x00,0x00,0x00,0x00,	// 0
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x3C,0xC0,0x07,0x00,0x3C,0xE0,0x03,0x00,0x3C,0xE0,0x03,0x00,0x3C,0xF0,0x01,0x00,0x3C,0xF0,0x01,0x00,0x3C,0xF8,0x00,0x00,0x3C,0xF8,0x00,0x00,0x3C,0xFC,0xFF,0xFF,0x3F,0xFC,0xFF,0xFF,0x3F,0xFC,0xFF,0xFF,0x3F,0xFC,0xFF,0xFF,0x3F,0xFC,0xFF,0xFF,0x3F,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 1
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x3C,0xF0,0x00,0x00,0x3E,0xF0,0x01,0x00,0x3F,0xF8,0x00,0x80,0x3F,0x78,0x00,0xC0,0x3F,0x7C,0x00,0xE0,0x3F,0x3C,0x00,0xF0,0x3F,0x3C,0x00,0xF8,0x3D,0x3C,0x00,0xFC,0x3C,0x3C,0x00,0x7E,0x3C,0x7C,0x80,0x3F,0x3C,0xFC,0xC0,0x1F,0x3C,0xF8,0xFF,0x0F,0x3C,0xF8,0xFF,0x07,0x3C,0xF0,0xFF,0x03,0x3C,0xF0,0xFF,0x01,0x3C,0xC0,0x7F,0x00,0x3C,0x00,0x0F,0x00,0x3C,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 2
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x78,0x00,0x00,0x1E,0x78,0x00,0x00,0x3C,0x3C,0x00,0x00,0x3C,0x3C,0xE0,0x01,0x3C,0x3C,0xE0,0x01,0x3C,0x3C,0xE0,0x01,0x3C,0x3C,0xE0,0x01,0x3C,0x3C,0xE0,0x01,0x3C,0x3C,0xE0,0x01,0x3C,0x7C,0xF0,0x01,0x3E,0x7C,0xF8,0x03,0x1E,0xF8,0xFF,0x07,0x1F,0xF8,0xBF,0xFF,0x1F,0xF0,0xBF,0xFF,0x0F,0xF0,0x9F,0xFF,0x0F,0xC0,0x0F,0xFF,0x07,0x00,0x00,0xFE,0x01,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 3
	 0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0xFF,0x00,0x00,0x80,0xFF,0x00,0x00,0xE0,0xFF,0x00,0x00,0xF8,0xF7,0x00,0x00,0xFC,0xF1,0x00,0x00,0xFF,0xF0,0x00,0xC0,0x3F,0xF0,0x00,0xE0,0x1F,0xF0,0x00,0xF8,0x07,0xF0,0x00,0xFC,0x01,0xF0,0x00,0xFC,0x00,0xF0,0x00,0xFC,0xFF,0xFF,0x3F,0xFC,0xFF,0xFF,0x3F,0xFC,0xFF,0xFF,0x3F,0xFC,0xFF,0xFF,0x3F,0xFC,0xFF,0xFF,0x3F,0x00,0x00,0xF0,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,	// 4
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFF,0x00,0x1E,0xFC,0xFF,0x00,0x3C,0xFC,0xFF,0x00,0x3C,0xFC,0xFF,0x00,0x3C,0xFC,0xFF,0x00,0x3C,0x3C,0xF0,0x00,0x3C,0x3C,0xF0,0x00,0x3C,0x3C,0xF0,0x00,0x3C,0x3C,0xF0,0x00,0x3C,0x3C,0xF0,0x01,0x1E,0x3C,0xF0,0x01,0x1E,0x3C,0xE0,0x03,0x1F,0x3C,0xE0,0xFF,0x0F,0x3C,0xE0,0xFF,0x0F,0x3C,0xC0,0xFF,0x07,0x3C,0x80,0xFF,0x03,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 5
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x1F,0x00,0x00,0xFC,0xFF,0x01,0x00,0xFF,0xFF,0x03,0xC0,0xFF,0xFF,0x0F,0xE0,0xFF,0xFF,0x0F,0xF0,0xFF,0xFF,0x1F,0xF0,0xE3,0x01,0x1F,0xF8,0xE0,0x00,0x3E,0x78,0xF0,0x00,0x3C,0x78,0xF0,0x00,0x3C,0x3C,0xF0,0x00,0x3C,0x3C,0xF0,0x00,0x3C,0x3C,0xF0,0x00,0x3C,0x3C,0xF0,0x01,0x3E,0x3C,0xF0,0x03,0x1F,0x3C,0xE0,0xFF,0x1F,0x3C,0xE0,0xFF,0x0F,0x3C,0xC0,0xFF,0x07,0x00,0x80,0xFF,0x03,0x00,0x00,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 6
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x3C,0x00,0x00,0x20,0x3C,0x00,0x00,0x3C,0x3C,0x00,0x00,0x3F,0x3C,0x00,0xC0,0x3F,0x3C,0x00,0xF0,0x3F,0x3C,0x00,0xFC,0x3F,0x3C,0x00,0xFF,0x0F,0x3C,0xC0,0xFF,0x01,0x3C,0xF8,0x7F,0x00,0x3C,0xFE,0x1F,0x00,0xBC,0xFF,0x07,0x00,0xFC,0xFF,0x01,0x00,0xFC,0x7F,0x00,0x00,0xFC,0x1F,0x00,0x00,0xFC,0x03,0x00,0x00,0xFC,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 7
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x80,0x0F,0xF8,0x07,0xE0,0x1F,0xFC,0x0F,0xF0,0x3F,0xFE,0x1F,0xF8,0x7F,0xFE,0x1F,0xF8,0xFF,0x3F,0x1F,0x7C,0xF8,0x0F,0x3E,0x3C,0xF0,0x07,0x3C,0x3C,0xF0,0x03,0x3C,0x3C,0xE0,0x03,0x3C,0x3C,0xE0,0x03,0x3C,0x3C,0xE0,0x07,0x3C,0x3C,0xF0,0x07,0x3C,0x7C,0xF8,0x0F,0x3E,0xF8,0xFE,0x1F,0x1F,0xF8,0x7F,0xFF,0x1F,0xF8,0x3F,0xFF,0x0F,0xF0,0x1F,0xFE,0x0F,0xE0,0x07,0xFC,0x07,0x00,0x00,0xF0,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 8
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0xC0,0xFF,0x01,0x3C,0xE0,0xFF,0x03,0x3C,0xF0,0xFF,0x07,0x3C,0xF8,0xFF,0x07,0x3C,0xF8,0xC0,0x0F,0x3C,0x7C,0x80,0x0F,0x3C,0x3C,0x00,0x0F,0x3C,0x3C,0x00,0x0F,0x3C,0x3C,0x00,0x0F,0x3C,0x3C,0x00,0x0F,0x1E,0x3C,0x00,0x0F,0x1E,0x7C,0x80,0x07,0x1F,0xF8,0x80,0xC7,0x0F,0xF8,0xFF,0xFF,0x0F,0xF0,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0x03,0xC0,0xFF,0xFF,0x00,0x80,0xFF,0x3F,0x00,0x00,0xF0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 9
};
#endif

#ifdef EN_LCD_BIGNUM
const uint8_t chr12x16[] = {
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x00,0xFF,0x33,0xFF,0x33,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // !
	 0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // "
	 0x00,0x00,0x00,0x02,0x10,0x1E,0x90,0x1F,0xF0,0x03,0x7E,0x02,0x1E,0x1E,0x90,0x1F,0xF0,0x03,0x7E,0x02,0x1E,0x00,0x10,0x00, // #
	 0x00,0x00,0x00,0x00,0x78,0x04,0xFC,0x0C,0xCC,0x0C,0xFF,0x3F,0xFF,0x3F,0xCC,0x0C,0xCC,0x0F,0x88,0x07,0x00,0x00,0x00,0x00, // $
	 0x00,0x00,0x00,0x30,0x38,0x38,0x38,0x1C,0x38,0x0E,0x00,0x07,0x80,0x03,0xC0,0x01,0xE0,0x38,0x70,0x38,0x38,0x38,0x1C,0x00, // %
	 0x00,0x00,0x00,0x00,0x00,0x1F,0xB8,0x3F,0xFC,0x31,0xC6,0x21,0xE2,0x37,0x3E,0x1E,0x1C,0x1C,0x00,0x36,0x00,0x22,0x00,0x00, // &
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x27,0x00,0x3F,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // '
	 0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x03,0xFC,0x0F,0xFE,0x1F,0x07,0x38,0x01,0x20,0x01,0x20,0x00,0x00,0x00,0x00,0x00,0x00, // (
	 0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x20,0x01,0x20,0x07,0x38,0xFE,0x1F,0xFC,0x0F,0xF0,0x03,0x00,0x00,0x00,0x00,0x00,0x00, // )
	 0x00,0x00,0x00,0x00,0x98,0x0C,0xB8,0x0E,0xE0,0x03,0xF8,0x0F,0xF8,0x0F,0xE0,0x03,0xB8,0x0E,0x98,0x0C,0x00,0x00,0x00,0x00, // *
	 0x00,0x00,0x00,0x00,0x80,0x01,0x80,0x01,0x80,0x01,0xF0,0x0F,0xF0,0x0F,0x80,0x01,0x80,0x01,0x80,0x01,0x00,0x00,0x00,0x00, // +
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB8,0x00,0xF8,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ,
	 0x00,0x00,0x00,0x00,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x00,0x00,0x00,0x00, // -
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .
	 0x00,0x00,0x00,0x18,0x00,0x1C,0x00,0x0E,0x00,0x07,0x80,0x03,0xC0,0x01,0xE0,0x00,0x70,0x00,0x38,0x00,0x1C,0x00,0x0E,0x00, // /
	 0x00,0x00,0xF8,0x07,0xFE,0x1F,0x06,0x1E,0x03,0x33,0x83,0x31,0xC3,0x30,0x63,0x30,0x33,0x30,0x1E,0x18,0xFE,0x1F,0xF8,0x07, // 0
	 0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x30,0x0C,0x30,0x0E,0x30,0xFF,0x3F,0xFF,0x3F,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x00, // 1
	 0x00,0x00,0x1C,0x30,0x1E,0x38,0x07,0x3C,0x03,0x3E,0x03,0x37,0x83,0x33,0xC3,0x31,0xE3,0x30,0x77,0x30,0x3E,0x30,0x1C,0x30, // 2
	 0x00,0x00,0x0C,0x0C,0x0E,0x1C,0x07,0x38,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xE7,0x39,0x7E,0x1F,0x3C,0x0E, // 3
	 0x00,0x00,0xC0,0x03,0xE0,0x03,0x70,0x03,0x38,0x03,0x1C,0x03,0x0E,0x03,0x07,0x03,0xFF,0x3F,0xFF,0x3F,0x00,0x03,0x00,0x03, // 4
	 0x00,0x00,0x3F,0x0C,0x7F,0x1C,0x63,0x38,0x63,0x30,0x63,0x30,0x63,0x30,0x63,0x30,0x63,0x30,0xE3,0x38,0xC3,0x1F,0x83,0x0F, // 5
	 0x00,0x00,0xC0,0x0F,0xF0,0x1F,0xF8,0x39,0xDC,0x30,0xCE,0x30,0xC7,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x39,0x80,0x1F,0x00,0x0F, // 6
	 0x00,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x30,0x03,0x3C,0x03,0x0F,0xC3,0x03,0xF3,0x00,0x3F,0x00,0x0F,0x00,0x03,0x00, // 7
	 0x00,0x00,0x00,0x0F,0xBC,0x1F,0xFE,0x39,0xE7,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xE7,0x30,0xFE,0x39,0xBC,0x1F,0x00,0x0F, // 8
	 0x00,0x00,0x3C,0x00,0x7E,0x00,0xE7,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x38,0xC3,0x1C,0xC3,0x0E,0xE7,0x07,0xFE,0x03,0xFC,0x00, // 9
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // :
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x9C,0x70,0xFC,0x70,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ;
	 0x00,0x00,0x00,0x00,0xC0,0x00,0xE0,0x01,0xF0,0x03,0x38,0x07,0x1C,0x0E,0x0E,0x1C,0x07,0x38,0x03,0x30,0x00,0x00,0x00,0x00, // <
	 0x00,0x00,0x00,0x00,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x00,0x00, // =
	 0x00,0x00,0x00,0x00,0x03,0x30,0x07,0x38,0x0E,0x1C,0x1C,0x0E,0x38,0x07,0xF0,0x03,0xE0,0x01,0xC0,0x00,0x00,0x00,0x00,0x00, // >
	 0x00,0x00,0x1C,0x00,0x1E,0x00,0x07,0x00,0x03,0x00,0x83,0x37,0xC3,0x37,0xE3,0x00,0x77,0x00,0x3E,0x00,0x1C,0x00,0x00,0x00, // ?
	 0x00,0x00,0xF8,0x0F,0xFE,0x1F,0x07,0x18,0xF3,0x33,0xFB,0x37,0x1B,0x36,0xFB,0x37,0xFB,0x37,0x07,0x36,0xFE,0x03,0xF8,0x01, // @
	 0x00,0x00,0x00,0x38,0x00,0x3F,0xE0,0x07,0xFC,0x06,0x1F,0x06,0x1F,0x06,0xFC,0x06,0xE0,0x07,0x00,0x3F,0x00,0x38,0x00,0x00, // A
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xE7,0x30,0xFE,0x39,0xBC,0x1F,0x00,0x0F,0x00,0x00, // B
	 0x00,0x00,0xF0,0x03,0xFC,0x0F,0x0E,0x1C,0x07,0x38,0x03,0x30,0x03,0x30,0x03,0x30,0x07,0x38,0x0E,0x1C,0x0C,0x0C,0x00,0x00, // C
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x03,0x30,0x03,0x30,0x03,0x30,0x03,0x30,0x07,0x38,0x0E,0x1C,0xFC,0x0F,0xF0,0x03,0x00,0x00, // D
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0x03,0x30,0x03,0x30,0x00,0x00, // E
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0x03,0x00,0x03,0x00,0x00,0x00, // F
	 0x00,0x00,0xF0,0x03,0xFC,0x0F,0x0E,0x1C,0x07,0x38,0x03,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC7,0x3F,0xC6,0x3F,0x00,0x00, // G
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xFF,0x3F,0xFF,0x3F,0x00,0x00, // H
	 0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x30,0x03,0x30,0xFF,0x3F,0xFF,0x3F,0x03,0x30,0x03,0x30,0x00,0x00,0x00,0x00,0x00,0x00, // I
	 0x00,0x00,0x00,0x0E,0x00,0x1E,0x00,0x38,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x38,0xFF,0x1F,0xFF,0x07,0x00,0x00, // J
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC0,0x00,0xE0,0x01,0xF0,0x03,0x38,0x07,0x1C,0x0E,0x0E,0x1C,0x07,0x38,0x03,0x30,0x00,0x00, // K
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x00, // L
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x1E,0x00,0x78,0x00,0xE0,0x01,0xE0,0x01,0x78,0x00,0x1E,0x00,0xFF,0x3F,0xFF,0x3F,0x00,0x00, // M
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x0E,0x00,0x38,0x00,0xF0,0x00,0xC0,0x03,0x00,0x07,0x00,0x1C,0xFF,0x3F,0xFF,0x3F,0x00,0x00, // N
	 0x00,0x00,0xF0,0x03,0xFC,0x0F,0x0E,0x1C,0x07,0x38,0x03,0x30,0x03,0x30,0x07,0x38,0x0E,0x1C,0xFC,0x0F,0xF0,0x03,0x00,0x00, // O
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x83,0x01,0x83,0x01,0x83,0x01,0x83,0x01,0x83,0x01,0xC7,0x01,0xFE,0x00,0x7C,0x00,0x00,0x00, // P
	 0x00,0x00,0xF0,0x03,0xFC,0x0F,0x0E,0x1C,0x07,0x38,0x03,0x30,0x03,0x36,0x07,0x3E,0x0E,0x1C,0xFC,0x3F,0xF0,0x33,0x00,0x00, // Q
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x83,0x01,0x83,0x01,0x83,0x03,0x83,0x07,0x83,0x0F,0xC7,0x1D,0xFE,0x38,0x7C,0x30,0x00,0x00, // R
	 0x00,0x00,0x3C,0x0C,0x7E,0x1C,0xE7,0x38,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC7,0x39,0x8E,0x1F,0x0C,0x0F,0x00,0x00, // S
	 0x00,0x00,0x00,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0xFF,0x3F,0xFF,0x3F,0x03,0x00,0x03,0x00,0x03,0x00,0x00,0x00,0x00,0x00, // T
	 0x00,0x00,0xFF,0x07,0xFF,0x1F,0x00,0x38,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x38,0xFF,0x1F,0xFF,0x07,0x00,0x00, // U
	 0x00,0x00,0x07,0x00,0x3F,0x00,0xF8,0x01,0xC0,0x0F,0x00,0x3E,0x00,0x3E,0xC0,0x0F,0xF8,0x01,0x3F,0x00,0x07,0x00,0x00,0x00, // V
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x00,0x1C,0x00,0x06,0x80,0x03,0x80,0x03,0x00,0x06,0x00,0x1C,0xFF,0x3F,0xFF,0x3F,0x00,0x00, // W
	 0x00,0x00,0x03,0x30,0x0F,0x3C,0x1C,0x0E,0x30,0x03,0xE0,0x01,0xE0,0x01,0x30,0x03,0x1C,0x0E,0x0F,0x3C,0x03,0x30,0x00,0x00, // X
	 0x00,0x00,0x03,0x00,0x0F,0x00,0x3C,0x00,0xF0,0x00,0xC0,0x3F,0xC0,0x3F,0xF0,0x00,0x3C,0x00,0x0F,0x00,0x03,0x00,0x00,0x00, // Y
	 0x00,0x00,0x03,0x30,0x03,0x3C,0x03,0x3E,0x03,0x33,0xC3,0x31,0xE3,0x30,0x33,0x30,0x1F,0x30,0x0F,0x30,0x03,0x30,0x00,0x00, // Z
	 0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x03,0x30,0x03,0x30,0x03,0x30,0x03,0x30,0x00,0x00,0x00,0x00,0x00,0x00, // [
	 0x00,0x00,0x0E,0x00,0x1C,0x00,0x38,0x00,0x70,0x00,0xE0,0x00,0xC0,0x01,0x80,0x03,0x00,0x07,0x00,0x0E,0x00,0x1C,0x00,0x18, // backslash
	 0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x30,0x03,0x30,0x03,0x30,0x03,0x30,0xFF,0x3F,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00, // ]
	 0x00,0x00,0x60,0x00,0x70,0x00,0x38,0x00,0x1C,0x00,0x0E,0x00,0x07,0x00,0x0E,0x00,0x1C,0x00,0x38,0x00,0x70,0x00,0x60,0x00, // ^
	 0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30, // _
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x00,0x7E,0x00,0x4E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // `
	 0x00,0x00,0x00,0x1C,0x40,0x3E,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0xE0,0x3F,0xC0,0x3F,0x00,0x00, // a
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC0,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0xE0,0x38,0xC0,0x1F,0x80,0x0F,0x00,0x00, // b
	 0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0x38,0x60,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0xC0,0x18,0x80,0x08,0x00,0x00, // c
	 0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0x38,0x60,0x30,0x60,0x30,0x60,0x30,0xE0,0x30,0xC0,0x30,0xFF,0x3F,0xFF,0x3F,0x00,0x00, // d
	 0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0x3B,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0xC0,0x13,0x80,0x01,0x00,0x00, // e
	 0x00,0x00,0xC0,0x00,0xC0,0x00,0xFC,0x3F,0xFE,0x3F,0xC7,0x00,0xC3,0x00,0xC3,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // f
	 0x00,0x00,0x80,0x03,0xC0,0xC7,0xE0,0xCE,0x60,0xCC,0x60,0xCC,0x60,0xCC,0x60,0xCC,0x60,0xE6,0xE0,0x7F,0xE0,0x3F,0x00,0x00, // g
	 0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC0,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0xE0,0x00,0xC0,0x3F,0x80,0x3F,0x00,0x00,0x00,0x00, // h
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x60,0x30,0xEC,0x3F,0xEC,0x3F,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00, // i
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0xE0,0x00,0xC0,0x60,0xC0,0xEC,0xFF,0xEC,0x7F,0x00,0x00,0x00,0x00,0x00,0x00, // j
	 0x00,0x00,0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x00,0x03,0x80,0x07,0xC0,0x0F,0xE0,0x1C,0x60,0x38,0x00,0x30,0x00,0x00,0x00,0x00, // k
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x03,0x30,0xFF,0x3F,0xFF,0x3F,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00, // l
	 0x00,0x00,0xE0,0x3F,0xC0,0x3F,0xE0,0x00,0xE0,0x00,0xC0,0x3F,0xC0,0x3F,0xE0,0x00,0xE0,0x00,0xC0,0x3F,0x80,0x3F,0x00,0x00, // m
	 0x00,0x00,0x00,0x00,0xE0,0x3F,0xE0,0x3F,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0xE0,0x00,0xC0,0x3F,0x80,0x3F,0x00,0x00, // n
	 0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0x38,0x60,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0xE0,0x38,0xC0,0x1F,0x80,0x0F,0x00,0x00, // o
	 0x00,0x00,0xE0,0xFF,0xE0,0xFF,0x60,0x0C,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0xE0,0x1C,0xC0,0x0F,0x80,0x07,0x00,0x00, // p
	 0x00,0x00,0x80,0x07,0xC0,0x0F,0xE0,0x1C,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x0C,0xE0,0xFF,0xE0,0xFF,0x00,0x00, // q
	 0x00,0x00,0x00,0x00,0xE0,0x3F,0xE0,0x3F,0xC0,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0xE0,0x00,0xC0,0x00,0x00,0x00, // r
	 0x00,0x00,0xC0,0x11,0xE0,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x3F,0x40,0x1E,0x00,0x00,0x00,0x00,0x00,0x00, // s
	 0x00,0x00,0x60,0x00,0x60,0x00,0xFE,0x1F,0xFE,0x3F,0x60,0x30,0x60,0x30,0x60,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00, // t
	 0x00,0x00,0xE0,0x0F,0xE0,0x1F,0x00,0x38,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x18,0xE0,0x3F,0xE0,0x3F,0x00,0x00, // u
	 0x00,0x00,0x60,0x00,0xE0,0x01,0x80,0x07,0x00,0x1E,0x00,0x38,0x00,0x38,0x00,0x1E,0x80,0x07,0xE0,0x01,0x60,0x00,0x00,0x00, // v
	 0x00,0x00,0xE0,0x07,0xE0,0x1F,0x00,0x38,0x00,0x1C,0xE0,0x0F,0xE0,0x0F,0x00,0x1C,0x00,0x38,0xE0,0x1F,0xE0,0x07,0x00,0x00, // w
	 0x00,0x00,0x60,0x30,0xE0,0x38,0xC0,0x1D,0x80,0x0F,0x00,0x07,0x80,0x0F,0xC0,0x1D,0xE0,0x38,0x60,0x30,0x00,0x00,0x00,0x00, // x
	 0x00,0x00,0x00,0x00,0x60,0x00,0xE0,0x81,0x80,0xE7,0x00,0x7E,0x00,0x1E,0x80,0x07,0xE0,0x01,0x60,0x00,0x00,0x00,0x00,0x00, // y
	 0x00,0x00,0x60,0x30,0x60,0x38,0x60,0x3C,0x60,0x36,0x60,0x33,0xE0,0x31,0xE0,0x30,0x60,0x30,0x20,0x30,0x00,0x00,0x00,0x00, // z
	 0x00,0x00,0x00,0x00,0x80,0x00,0xC0,0x01,0xFC,0x1F,0x7E,0x3F,0x07,0x70,0x03,0x60,0x03,0x60,0x03,0x60,0x00,0x00,0x00,0x00, // {
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // |
	 0x00,0x00,0x00,0x00,0x03,0x60,0x03,0x60,0x03,0x60,0x07,0x70,0x7E,0x3F,0xFC,0x1F,0xC0,0x01,0x80,0x00,0x00,0x00,0x00,0x00, // }
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ~
	 0x00,0x00,0x00,0x00,0x3F,0x00,0x3F,0xC0,0x01,0xF8,0x01,0x3E,0xBF,0x27,0xBF,0x27,0x01,0x3E,0x01,0xF8,0x3F,0xC0,0x3E,0x00, // 
};
#endif



static const int8_t ASCII[][5] ={
    {0x00, 0x00, 0x00, 0x00, 0x00} // 20
    ,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
    ,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
    ,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
    ,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
    ,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
    ,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
    ,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
    ,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
    ,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
    ,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
    ,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
    ,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
    ,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
    ,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
    ,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
    ,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
    ,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
    ,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
    ,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
    ,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
    ,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
    ,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
    ,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
    ,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
    ,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
    ,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
    ,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
    ,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
    ,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
    ,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
    ,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
    ,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
    ,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
    ,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
    ,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
    ,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
    ,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
    ,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
    ,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
    ,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
    ,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
    ,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
    ,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
    ,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
    ,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
    ,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
    ,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
    ,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
    ,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
    ,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
    ,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
    ,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
    ,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
    ,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
    ,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
    ,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
    ,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
    ,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
    ,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
    ,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c �
    ,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
    ,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
    ,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
    ,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
    ,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
    ,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
    ,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
    ,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
    ,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
    ,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
    ,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
    ,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
    ,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
    ,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
    ,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
    ,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
    ,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
    ,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
    ,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
    ,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
    ,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
    ,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
    ,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
    ,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
    ,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
    ,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
    ,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
    ,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
    ,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
    ,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
    ,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
    ,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
    ,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
    ,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ?
    ,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f ?
};




void LcdSend(uint8_t cd, uint8_t data) {
    LCD_CE=0;                               // Enable LCD ~CE

//    SPIdisable();
    LCD_DI=cd;                              // Command/Data-bit
     LCD_CLK=1;  LCD_CLK=0;     // Toggle Clock
//    SPIenable();

//    SPIsend(data);

     if (data&0x80) LCD_DI=1; else LCD_DI=0; // D7
     LCD_CLK=1;  LCD_CLK=0;     // Toggle Clock
    if (data&0x40) LCD_DI=1; else LCD_DI=0;
     LCD_CLK=1;  LCD_CLK=0;
    if (data&0x20) LCD_DI=1; else LCD_DI=0;
     LCD_CLK=1;  LCD_CLK=0;
    if (data&0x10) LCD_DI=1; else LCD_DI=0;
     LCD_CLK=1;  LCD_CLK=0;
    if (data&0x08) LCD_DI=1; else LCD_DI=0;
     LCD_CLK=1;  LCD_CLK=0;
    if (data&0x04) LCD_DI=1; else LCD_DI=0;
     LCD_CLK=1;  LCD_CLK=0;
    if (data&0x02) LCD_DI=1; else LCD_DI=0;
     LCD_CLK=1;  LCD_CLK=0;
    if (data&0x01) LCD_DI=1; else LCD_DI=0;
     LCD_CLK=1;  LCD_CLK=0;

     LCD_CE=1;                        // Disable LCD ~CE
}


//
//
//
void LcdInit(void){
    LCD_LIGHT_TRIS=0;       // Set LCD pins as outputs
    LCD_CE_TRIS=0;
    LCD_RESET_TRIS=0;
  LCD_DI_TRIS=0;
  LCD_CLK_TRIS=0;

    LcdBacklight(true);
    LCD_RESET=1;
    LCD_CE=1;
  LCD_CLK=0;
  LCD_DI=0;

    LcdSend(LCD_C, 0xE2);  // Software Reset
    LcdSend(LCD_C, 0x3D);  // Charge pump ON
    LcdSend(LCD_C, 0x01);  // Charge pump=4
    LcdSend(LCD_C, 0xA4);  // Display all points = OFF
    LcdSend(LCD_C, 0x2F);  // Booster=ON, Voltage Reg=ON, Voltage Follower=ON

    LcdSend(LCD_C, 0xAF);  // Display ON

    //  LcdSend(LCD_C, 0xA7);  // Inverted display
    LcdSend(LCD_C, 0xA6);  // Normal display

    LcdSend(LCD_C, 0xC0);  // Normal screen up/down
    //LcdSend(LCD_C, 0xCF);  // Mirror screen up/down

    LcdSend(LCD_C, 0xA0);  // Normal screen left/right
    //LcdSend(LCD_C, 0xA1);  // Mirror screen left/right

//    LcdClear();
}


//
//
//
void LcdXY(uint8_t x, uint8_t y){
  LcdSend(LCD_C,0xB0 | (y & 0x0F));
  LcdSend(LCD_C,0x10 | ((x >> 4) & 0x07));
  LcdSend(LCD_C,0x00 | (x & 0x0F));
}

//
//
//
void LcdClear(void){
uint16_t i;
    for (i=0; i<864 ; i++) {
        LcdSend(LCD_D, 0x00);
    }
}
//
//
//
void LcdFill(void){
uint16_t i;
    for (i=0; i<864 ; i++) {
        LcdSend(LCD_D, 0xff);
    }
}

//
//
//
void LcdCharacter(int8_t character) {
    int index;

    LcdSend(LCD_D, 0x00);
    for (index= 0; index < 5; index++) {
        LcdSend(LCD_D, ASCII[character - 0x20][index]);
    }
}

//
//
//
void LcdString(int8_t *characters){
    while (*characters) {
        LcdCharacter(*characters++);
    }
}



//
//
//
void LcdBacklight(bool on){
    LCD_LIGHT=on;
};




#ifdef EN_LCD_BIGNUM
void LcdBigNum(uint8_t n, uint8_t x, uint8_t y) {
    uint8_t *p;
    uint8_t i;

    LcdXY(96-12-x,1);
    p=chr12x16;
    p=p+n*24+23;

    for (i=0; i<12; i++) {
        LcdSend(LCD_D,*p);
        p-=2;
    }
    p+=23;
    LcdXY(96-12-x,0);
    for (i=0; i<12; i++) {
        LcdSend(LCD_D,*p);
        p-=2;
    }

}
#endif


#ifdef EN_LCD_HUGENUM
void LcdHugeNum(uint8_t n, uint8_t x, uint8_t y) {
    uint8_t *p;
    uint8_t i;

    p=chr24x32+n*96;

    LcdXY(x,0+y);
    for (i=0; i<24; i++) {
        LcdSend(LCD_D,*p);
        p+=4;
    }

    p-=95;
    LcdXY(x,1+y);
    for (i=0; i<24; i++) {
        LcdSend(LCD_D,*p);
        p+=4;
    }

    p-=95;
    LcdXY(x,2+y);
    for (i=0; i<24; i++) {
        LcdSend(LCD_D,*p);
        p+=4;
    }

    p-=95;
    LcdXY(x,3+y);
    for (i=0; i<24; i++) {
        LcdSend(LCD_D,*p);
        p+=4;
    }
}
#endif


#ifdef EN_LCD_LOGO
//
//
//
void LcdLogo(void) {
    uint16_t i,j;
    LcdXY(0,0);
    for (i=0; i<sizeof(logo); i++) {
        if (logo[i]==0x42) {
            i++;
            if (logo[i]==0x42) {
                LcdSend(LCD_D, logo[i]);
            } else {
                for (j=0; j<(logo[i]&0x1F); j++) {
                    if ((logo[i]&0xE0)==0x00) LcdSend(LCD_D, 0x00); //Code 0x00
                    if ((logo[i]&0xE0)==0x20) LcdSend(LCD_D, 0x07); //Code 0x20
                    if ((logo[i]&0xE0)==0x40) LcdSend(LCD_D, 0x0F); //Code 0x40
                    if ((logo[i]&0xE0)==0x60) LcdSend(LCD_D, 0x08); //Code 0x60
                    if ((logo[i]&0xE0)==0x80) LcdSend(LCD_D, 0x40); //Code 0x80
                                                                    //Code 0xA0
                    if ((logo[i]&0xE0)==0xC0) LcdSend(LCD_D, 0xFE); //Code 0xC0
                    if ((logo[i]&0xE0)==0xE0) LcdSend(LCD_D, 0xFF); //Code 0xE0
                }
            }

        } else {
            LcdSend(LCD_D, logo[i]);
        }
    }
}
#endif