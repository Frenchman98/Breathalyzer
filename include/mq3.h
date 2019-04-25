#ifndef MQ3_H
#define MQ3_H

#define MQ3_MAX_LEVEL 1023
#define MQ3_MIN_LEVEL 0
#define MQ3_BASE_READING 50
#define MQ3_NUM_READINGS 5

#include <avr/io.h>
#include <stdbool.h>
#include "timer.h"
#include <math.h>

void initMQ3();

float getBAC();

bool isBACNew(float oldBAC, float newBAC);

bool isAlcDetected();

#endif