#include "switch.h"
/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPB3(){
   //Set pin into input
  //Initialize pull-resistor
  DDRB  &= ~(1 << DDB3);
  PORTB |= (1 << PORTB3);

  // enable pin-change interrupts
  // enable interrupts on PB3
  PCICR  |= (1 << PCIE0);  // Enable PCINT for 7-0
  PCMSK0 |= (1 << PCINT3); // enable PCINT3 (PB3)
}