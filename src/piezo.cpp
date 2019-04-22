#include "piezo.h"

void initPiezo(){
    //Timer 3, output A
    DDRE |= (1 << DDE3);

    //Set to FAST PWM 8-bit mode, non inverting
    TCCR3A |= (1 << COM3A1) | (1 << WGM30);
    TCCR3A |= (1 << WGM31);
    TCCR3B &= ~(1 << WGM32);
    TCCR3B |= (1 << CS31) | (1 << CS30);

    //Initialize duty cycle to 0%
    OCR3A = 0;
}

void toneOnce(){
    OCR3A = (int) ((.5) * 255 );    //Turn of buzzer 
    delayMs(500);                   //Wait for half a second
    OCR3A = 0;                      //Turn of buzzer
}

void toneTwice(){
    toneOnce();
    toneOnce();
}