#include "mq3.h"

void initMQ3(){
  //Set pin into input for DOUT of MQ3 sensor
  //Initialize pull-resistor
  DDRA  &= ~(1 << DDA1);
  PORTA |= (1 << PORTA1);

  //Setting up ADC for AOUT of MQ3 sensor
  // set voltage references to be AVCC
  ADMUX |= (1 << REFS0);
  ADMUX &= ~(1 << REFS1);

  // ADLAR = 0 (RIGHT JUSTIFIED)
  ADMUX &= ~(1 << ADLAR);

  /*// Set ADC0 as single-ended input with MUX[5:0] = 0b000111
  ADMUX &= 0b11000000;
  */
  ADMUX &= ~((1<<MUX4) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));
  ADCSRB &= ~(1<<MUX5);

  // set Auto Trigger Source Selection
  // set to free-running mode ADTS[2:0] = 0b000
  // 
  ADCSRB &= ~(1 << ADTS2 | 1 << ADTS1 | 1 << ADTS0);

  // enable auto-triggering and turn-on ADC
  ADCSRA |= (1 << ADATE) | (1 << ADEN);

  // set the pre-scaler to 128
  // ADC clock frequency is 16 Mhz divided by pre-scaler = 125KHz
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // disable ADC0 pin digital input - pin A0 on board
  DIDR0 |= (1 << ADC0D);

  // start the first conversion
  ADCSRA |= (1 << ADSC);
}

float getBAC(){
int intVoltage = 0;
  //Get lower bits first and then upper of the conversion
  intVoltage = ADCL;
  intVoltage |= ADCH << 8;

  //Change to float for setting the PW
  float floatVoltage = (float) intVoltage;
  floatVoltage = floatVoltage / 1023;  //Divide by 1023 since mq3 outputs between 0 and 1023
  float BAC = floatVoltage * .21;

  return BAC;
}