#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

// #define LEFT_TOP_PIN  12  // D11
// #define LEFT_BOT_PIN  11  // D12
// #define RIGHT_TOP_PIN 9  // D10
// #define RIGHT_BOT_PIN 10   // D9
#define LEFT_TOP_PIN  9  // D11
#define LEFT_BOT_PIN  10  // D12
#define RIGHT_TOP_PIN 12  // D10
#define RIGHT_BOT_PIN 11   // D9


volatile byte LEFT_TOP_PRESSED = LOW;
volatile byte LEFT_BOT_PRESSED = LOW;
volatile byte RIGHT_TOP_PRESSED = LOW;
volatile byte RIGHT_BOT_PRESSED = LOW;

volatile bool LEFT_TOP_STATE = HIGH;
volatile bool LEFT_BOT_STATE = HIGH;
volatile bool RIGHT_TOP_STATE = HIGH;
volatile bool RIGHT_BOT_STATE = HIGH;


inline bool check_bottom_falling_edge(int pin, volatile bool* last_state) {
    bool state = digitalRead(pin);
    if (state == *last_state) {
        return false;
    }
    *last_state = state;
    if (state == LOW) {
        return true;
    }
    return false;
}

void setup_buttons() {
    pinMode(LEFT_TOP_PIN, INPUT_PULLUP);
    pinMode(LEFT_BOT_PIN, INPUT_PULLUP);
    pinMode(RIGHT_TOP_PIN, INPUT_PULLUP);
    pinMode(RIGHT_BOT_PIN, INPUT_PULLUP);
}

#endif  // BUTTONS_H
