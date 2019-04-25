#ifndef PIEZO_H
#define PIEZO_H
#define PIEZO_440_HZ 70
#define PIEZO_880_HZ 35

#include <avr/io.h>
#include "timer.h"

void toneOnce(int frequency);

void toneTwice(int frequency);

#endif