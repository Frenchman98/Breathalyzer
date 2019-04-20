#ifndef LCD_H
#define LCD_H

#include "i2c.h"

#define LCD_BACKPACK_ADDRESS 0x70 //Slave address for .056" Adafruit 7-segment LED HT16K33 backpack

void turnDisplayOn();

void turnDisplayOff();

#endif