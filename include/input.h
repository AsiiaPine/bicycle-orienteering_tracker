#pragma once

#include <Arduino.h>
#include <consts.h>
#include <state.h>

#include "run.h"

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

inline void setup_buttons() {
  pinMode(LEFT_TOP_PIN, INPUT_PULLUP);
  pinMode(LEFT_BOT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_TOP_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BOT_PIN, INPUT_PULLUP);
}

inline void reed_switch_callback() { reed_switch_callback_counter++; }

void setup_reed_switch() {
  pinMode(REED_SWITCH_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(REED_SWITCH_PIN), reed_switch_callback,
                  FALLING);
}

inline void setup_input() {
  setup_buttons();
  setup_reed_switch();
}

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
    if (right_top_pressed) STATE.wheel_diameter += 10;
    if (right_bottom_pressed) STATE.wheel_diameter -= 10;
    return;
  }
  if (STATE.current_row == ROW_MAP_SCALE) {
    if (right_top_pressed) STATE.scale += 1;
    if (right_bottom_pressed) STATE.scale -= 1;
    return;
  }
}

inline void handle_run_screen_input(bool right_top_pressed,
                                    bool right_bot_pressed,
                                    bool left_top_pressed,
                                    bool left_bottom_pressed) {
  if (right_top_pressed || right_bot_pressed) {
    STATE.lap_distance = 0;
  }
}

void handle_buttons() {
  bool left_top_pressed =
      check_bottom_falling_edge(LEFT_TOP_PIN, &LEFT_TOP_STATE);
  bool left_bot_pressed =
      check_bottom_falling_edge(LEFT_BOT_PIN, &LEFT_BOT_STATE);
  bool right_top_pressed =
      check_bottom_falling_edge(RIGHT_TOP_PIN, &RIGHT_TOP_STATE);
  bool right_bot_pressed =
      check_bottom_falling_edge(RIGHT_BOT_PIN, &RIGHT_BOT_STATE);
  check_bottom_falling_edge(RIGHT_BOT_PIN, &RIGHT_BOT_STATE);

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
