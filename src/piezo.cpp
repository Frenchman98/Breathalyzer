#include "piezo.h"

void toneOnce(int frequency){
    //Set as output mode
    DDRE |= (1 << DDE3);

    //Set for CTC with prescaler of 256
    TCCR3A |= (1 << COM3A0);
    TCCR3A &= ~((1 << COM3A1) | (1 << WGM31) | (1 << WGM30));

    TCCR3B |= ((1 << CS32) | (1 << WGM32));
    TCCR3B &= ~((1 << CS31) | (1 << CS30) | (1 << WGM33));

    //Initialize duty cycle to input frequency (either 440 HZ or 880 HZ)
    OCR3AL = frequency;
    
    //delay for 200 ms for beep duration
    delayMs(200);

    //Turn off buzzer
    DDRE &= ~(1 << DDE3);
}

void toneTwice(int frequency){
    toneOnce(frequency);
    delayMs(200);
    toneOnce(frequency);
}