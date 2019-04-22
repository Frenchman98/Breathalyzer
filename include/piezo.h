#ifndef PIEZO_H
#define PIEZO_H

#include <avr/io.h>
#include "timer.h"

void initPiezo();

void toneOnce();

void toneTwice();

#endif