#ifndef LCD_H
#define LCD_H

#include "i2c.h"

#define LCD_BACKPACK_ADDRESS 0x70 //Slave address for .056" Adafruit 7-segment LED HT16K33 backpack
static const uint8_t numbertable[] = {
    0x3F, /* 0 */
	0x06, /* 1 */
	0x5B, /* 2 */
	0x4F, /* 3 */
	0x66, /* 4 */
	0x6D, /* 5 */
	0x7D, /* 6 */
	0x07, /* 7 */
	0x7F, /* 8 */
	0x6F, /* 9 */
	0x77, /* a */
	0x7C, /* b */
	0x39, /* C */
	0x5E, /* d */
	0x79, /* E */
	0x71, /* F */
};

void turnDisplayOn();

void turnDisplayOff();

void displayValue(float data);

void setDisplayBuffer(float num, uint8_t * displayBuffer);

void clearDisplay();

#endif