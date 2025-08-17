#ifndef _DEF_H_
#define _DEF_H_

#include <Wire.h>
#include <NewPing.h>

#define MAX_DISTANCE       100   // max distance to read
#define range_cm_collision 30    // obstacle range in cm

// Each sensor's trigger pin, echo pin, and max distance to ping
NewPing sonar[4] = {
    NewPing(9, 10, MAX_DISTANCE),
    NewPing(7, 8,  MAX_DISTANCE),
    NewPing(11,12, MAX_DISTANCE),
    NewPing(5, 6,  MAX_DISTANCE),
};

volatile uint8_t range_cm[4];      // true range to obstacles
char RANGE[4] = {0, 0, 0, 0};      // obstacle flags
#define intOutPin 4

// function prototypes
void reqEvent(int bytes);
void sendInt();

#endif
