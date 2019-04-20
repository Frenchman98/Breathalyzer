#ifndef I2C_H
#define I2C_H

#define I2C_READ 1
#define I2C_WRITE 0

#include <avr/io.h>

void initI2C();

void beginTransmission(int8_t register_address);

void endTransmission();

void write(int8_t data);

#endif