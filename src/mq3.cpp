#include "mq3.h"

#include "Arduino.h"

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

  Serial.println(intVoltage);

  /*
    BAC Calculation: Typically the MQ3 alcohol sensor outputs an analog value between 0 and 1023 with 1023 being the highest
    level of alcohol detection. However, the MQ3 sensor is connected to a FC-22 SBX controller which is not designed for the MQ3,
    but is rather designed for the MQ2 (at least datasheets only exist for a FC-22 and MQ2 combination. FC-22 SBX doesn't appear
    in any google search). This is causing the sensor to behave inversely of what we expect. Exposed to just air, the sensor outputs
    a value between 950 and 1000. When exposed directly to 70 proof (35% by volume) vodka, it outputs 20-70. To compensate for this
    the math to convert the analog reading to BAC is as follows:
        BAC = MQ3_MAX_LEVEL - inputVoltage;   *This flips the voltage to match the datasheet for the MQ3 sensor
        BAC = BAC - MQ3_BASE_READING;         *This substracts the level measured when reading air without alcohol.
        BAC = BAC / MQ3_MAX_LEVEL;            *This step and the next are taken from online to convert between ppm and BAC.
        BAC = BAC * .21;
  */
  intVoltage = MQ3_MAX_LEVEL - intVoltage;
  intVoltage = intVoltage - MQ3_BASE_READING; 
  float floatVoltage = (float) intVoltage;
  floatVoltage = floatVoltage / 1023;  
  float BAC = floatVoltage * .21;

  Serial.println(BAC);
  return BAC;
}