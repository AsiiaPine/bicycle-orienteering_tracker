/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Anastasiia Stepanova <asiiapine@gmail.com>
 * Copyright (c) 2025
 */

#pragma once

#include <Arduino.h>
#include <state.h>


#define PI 3.1415926535897932384626433832795

uint16_t last_counter = 0;

// Update run data based on interrupts counter
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

// Reset (or lap) maker
void run_reset() {
  STATE.lap_distance = 0;
  STATE.passed_distance = 0;
  STATE.start_time = millis() / 1000;
}
