#ifndef MQ3_H
#define MQ3_H

#define MQ3_MAX_LEVEL 1023
#define MQ3_MIN_LEVEL 0
#define MQ3_BASE_READING 50
#include <avr/io.h>

void initMQ3();

float getBAC();

#endif