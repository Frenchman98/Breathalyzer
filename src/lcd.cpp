#include "lcd.h"

void turnDisplayOn(){
    beginTransmission(LCD_BACKPACK_ADDRESS);
    write(0x20 | 1);
    endTransmission();

    beginTransmission(LCD_BACKPACK_ADDRESS);
    write(0x81);
    endTransmission();
}

void turnDisplayOff(){
    beginTransmission(LCD_BACKPACK_ADDRESS);
    write(0x80);
    endTransmission();

    beginTransmission(LCD_BACKPACK_ADDRESS);
    write(0x20);
    endTransmission();
}