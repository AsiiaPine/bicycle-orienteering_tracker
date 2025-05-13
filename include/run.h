#pragma once

#include <Arduino.h>
#include <state.h>


#define PI 3.1415926535897932384626433832795

uint16_t last_counter = 0;


void run_update() {
  if (reed_switch_callback_counter == last_counter) {
    return;
  }

  Serial.println(reed_switch_callback_counter);

  uint8_t delta_count = reed_switch_callback_counter - last_counter;
  // the counter can go up to 255 and then it goes back to 0. So, we need to
  // catch the moment when it reaches 127 to not loose any interrupt
  // because I assume that you will not be able to reach 255 counts until next run_update call.)
  // It's like 127 * wheel_diameter * PI meters should be passed before next run_update call.
  // E.g. wheel_diameter is 0.7 m, then this may happen if you ride a 279 meters
  // before next function call (around 0.05 seconds).

  if (reed_switch_callback_counter > 127) {
    reed_switch_callback_counter = 0;
    last_counter = 0;
  } else {
    last_counter = reed_switch_callback_counter;
  }

  uint16_t delta_distance_m = delta_count * STATE.wheel_diameter * PI / 1000;
  STATE.lap_distance += delta_distance_m;
  STATE.passed_distance += delta_distance_m;
}

void run_reset() {
  // Reset (or lap) maker
  STATE.lap_distance = 0;
  STATE.passed_distance = 0;
  STATE.start_time = millis() / 1000;
}
