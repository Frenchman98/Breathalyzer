#include "timer.h"

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
    //Set timer0 register to CTC mode based on datasheet
    TCCR0A &= ~(1<<WGM00);
    TCCR0A |= (1<<WGM01);
    TCCR0B &= ~(1<<WGM02);

    //Set prescalar to 256 (100 from data sheet)
    TCCR0B &= ~(1<<CS02);
    TCCR0B |= (1<<CS01);
    TCCR0B |= (1<<CS00);

    //To Timer Count = (Required delay/(clock-period * prescalar)) - 1
    //For 1 ms, 249 = (1ms/ (62.5ns * 64)) - 1

    //Specifing compare value to get 1ms timer
    OCR0A = 249;
}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-200 milliseconds
*/
void delayMs(unsigned int delay){

    //Used from lecture slides to set the timer flag down
    unsigned int delayCnt = 0;
    TIFR0 |= (1<<OCF0A);
    TCNT0 = 0;

    //Once flag is flipped, we have reached our desired delay
    while(delayCnt < delay) {
        if(TIFR0 & (1<<OCF0A)) {
            delayCnt++;
            TIFR0 |= (1<<OCF0A);
        }
    }
}
