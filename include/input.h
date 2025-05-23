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
#include <consts.h>
#include <state.h>

#include <run.h>

#define LEFT_TOP_PIN 9    // D11
#define LEFT_BOT_PIN 10   // D12
#define RIGHT_TOP_PIN 12  // D10
#define RIGHT_BOT_PIN 11  // D9

#define REED_SWITCH_PIN 2  // D2

bool LEFT_TOP_PRESSED = LOW;
bool LEFT_BOT_PRESSED = LOW;
bool RIGHT_TOP_PRESSED = LOW;
bool RIGHT_BOT_PRESSED = LOW;

bool LEFT_TOP_STATE = HIGH;
bool LEFT_BOT_STATE = HIGH;
bool RIGHT_TOP_STATE = HIGH;
bool RIGHT_BOT_STATE = HIGH;

// Check if the bottom edge of the button is falling. Then button was just pressed.
bool check_bottom_falling_edge(int pin, bool *last_state) {
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

// Setup buttons pins as input pullup to avoid floating state
inline void setup_buttons() {
  pinMode(LEFT_TOP_PIN, INPUT_PULLUP);
  pinMode(LEFT_BOT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_TOP_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BOT_PIN, INPUT_PULLUP);
}

inline void reed_switch_callback() { reed_switch_callback_counter++; }

// Setup reed switch pin as input pullup to avoid floating state
void setup_reed_switch() {
  pinMode(REED_SWITCH_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(REED_SWITCH_PIN), reed_switch_callback,
                  FALLING);
}

// Setup buttons and reed switch pins
inline void setup_input() {
  setup_buttons();
  setup_reed_switch();
}

// Handle buttons actions on parameters screen
inline void handle_parameters_screen_input(bool right_top_pressed,
                                           bool right_bottom_pressed,
                                           bool left_top_pressed,
                                           bool left_bottom_pressed) {
  if (left_top_pressed) {
    if (STATE.current_row > 0) {
      STATE.current_row--;
    } else {
      STATE.current_row = PARAM_FRAME_ROWS - 1;
    }
    return;
  }
  if (left_bottom_pressed) {
    STATE.current_row++;
    if (STATE.current_row >= PARAM_FRAME_ROWS) {
      STATE.current_row = 0;
    }
    return;
  }

  // Different actions on different parameters screen rows
  if (STATE.current_row == ROW_START) {
    if (right_top_pressed || right_bottom_pressed) {
      run_reset();
      STATE.change_frame();
    }
    return;
  }
  if (STATE.current_row == ROW_CONTINUE) {
    if (right_top_pressed || right_bottom_pressed) {
      STATE.change_frame();
    }
    return;
  }
  if (STATE.current_row == ROW_TIME_LIMIT) {
    if (right_top_pressed) {
      STATE.time_limit += 3600;
    }
    if (right_bottom_pressed) {
      STATE.time_limit -= 3600;
    }

    return;
  }
  if (STATE.current_row == ROW_TOTAL_DISTANCE) {
    if (right_top_pressed) {
      STATE.total_distance += 1000;
    }
    if (right_bottom_pressed) {
      STATE.total_distance -= 1000;
    }

    return;
  }
  if (STATE.current_row == ROW_WHEEL_DIAMETER) {
    if (right_top_pressed) STATE.wheel_diameter += 1;
    if (right_bottom_pressed) STATE.wheel_diameter -= 1;
    return;
  }
  if (STATE.current_row == ROW_MAP_SCALE) {
    if (right_top_pressed) STATE.scale += 1;
    if (right_bottom_pressed) STATE.scale -= 1;
    return;
  }
}

// Handle buttons actions on run screen
inline void handle_run_screen_input(bool right_top_pressed,
                                    bool right_bot_pressed,
                                    bool left_top_pressed,
                                    bool left_bottom_pressed) {
  // Reset lap distance when user presses any right button
  if (right_top_pressed || right_bot_pressed) {
    STATE.lap_distance = 0;
  }
}

// Handle buttons actions
void handle_buttons() {
  // Check if any button is pressed
  bool left_top_pressed =
      check_bottom_falling_edge(LEFT_TOP_PIN, &LEFT_TOP_STATE);
  bool left_bot_pressed =
      check_bottom_falling_edge(LEFT_BOT_PIN, &LEFT_BOT_STATE);
  bool right_top_pressed =
      check_bottom_falling_edge(RIGHT_TOP_PIN, &RIGHT_TOP_STATE);
  bool right_bot_pressed =
      check_bottom_falling_edge(RIGHT_BOT_PIN, &RIGHT_BOT_STATE);
  check_bottom_falling_edge(RIGHT_BOT_PIN, &RIGHT_BOT_STATE);

  // Change frame when both left buttons are pressed
  if (left_top_pressed && left_bot_pressed) {
    STATE.change_frame();
    return;
  }

  if (STATE.current_frame == PARAM_FRAME) {
    handle_parameters_screen_input(right_top_pressed, right_bot_pressed,
                                   left_top_pressed, left_bot_pressed);
    return;
  }
  if (STATE.current_frame == RUN_FRAME) {
    handle_run_screen_input(right_top_pressed, right_bot_pressed,
                            left_top_pressed, left_bot_pressed);
    return;
  }
}
