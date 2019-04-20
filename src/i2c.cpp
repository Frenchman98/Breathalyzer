#include "i2c.h"

void initI2C(){
    TWSR |= (1 << TWPS0);
    TWSR &= ~(1 << TWPS1); // prescaler = 1
    TWBR = 0x12; // bit rate generator
    TWCR |= (1 << TWINT | 1 << TWEN); // enable two wire interface
}

void beginTransmission(int8_t register_address) {
    //Set the start condition
    TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTA));
    while (!(TWCR & (1 << TWINT)));

    //Send slave address 
    write((register_address << 1) + I2C_WRITE);
}

void endTransmission() {
    //Set the stop condition
    TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTO));
}

void write(int8_t data) {
    TWDR = data;
    TWCR = ((1 << TWEN) | (1 << TWINT));;
    while (!(TWCR & (1 << TWINT)));
}