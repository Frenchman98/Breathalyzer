#include "lcd.h"

void turnDisplayOn(){

    //Turning on internal clock
    beginTransmission(LCD_BACKPACK_ADDRESS);
    write(0x20 | 1);
    endTransmission();

    //Setting dimming (0xEX, X = 0-F with 0 begin dimmest)
    beginTransmission(LCD_BACKPACK_ADDRESS);
    write(0xE0);
    endTransmission();

    //Turning on the display without blinking
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

void displayValue(float data){
    uint8_t displayBuffer[9];
    setDisplayBuffer(data, displayBuffer);
    for (uint8_t i = 0; i <= 8; i = i + 2){
        beginTransmission(LCD_BACKPACK_ADDRESS);
        write(i);
        write(displayBuffer[i]);
        endTransmission();
    }
}

void setDisplayBuffer(float num, uint8_t * displayBuffer){
    int intpart = (int)num;
    double decpart = num - intpart;
    int decpartAsInt = (int)(decpart*100); 
    int tens, ones, tenths, hundredths; 

    tens = (intpart/10)%10;
    ones = (intpart%10);
    tenths = (decpartAsInt/10)%10;
    hundredths = (decpartAsInt%10);

    displayBuffer[0] = numbertable[tens];
    displayBuffer[1] = numbertable[0];
    displayBuffer[2] = numbertable[ones] + (uint8_t)0x80;
    displayBuffer[3] = numbertable[0];
    displayBuffer[4] = (uint8_t)0x00;
    displayBuffer[5] = numbertable[0];
    displayBuffer[6] = numbertable[tenths];
    displayBuffer[7] = numbertable[0];
    displayBuffer[8] = numbertable[hundredths];   
}

void clearDisplay(){
    for (uint8_t i = 0; i < 16; i = i + 2){
        beginTransmission(LCD_BACKPACK_ADDRESS);
        write(i);
        write(0x3F);
        endTransmission();
    }
}