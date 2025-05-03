#ifndef REED_SWITCH_H
#define REED_SWITCH_H

#include <Arduino.h>
#define REED_SWITCH_PIN 2
volatile byte reed_switch_callback_counter = 0;

inline void reed_switch_callback() {
    reed_switch_callback_counter++;
}

void setup_reed_switch() {
    pinMode(REED_SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(REED_SWITCH_PIN), reed_switch_callback, FALLING);
}

#endif  // REED_SWITCH_H
