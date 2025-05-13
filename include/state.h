#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include <storage.h>
// #include <parameters.h>
// #include <parameters_frame.h>
// #include <run.h>
// #include <run_frame.h>

volatile uint8_t reed_switch_callback_counter = 0;

enum FrameNum { PARAM_FRAME, RUN_FRAME };

struct State {
  // --- constants ---
  uint16_t wheel_diameter;      // in millimeters
  uint32_t time_limit;          // in seconds
  uint16_t scale;               // meters/centimeters
  uint32_t total_distance;      // in meters
  float desired_mean_speed;  // in meters per second

  // --- variables ---
  FrameNum current_frame = PARAM_FRAME;
  uint16_t passed_distance = 0;  // in meters
  uint16_t lap_distance = 0;     // in meters
  uint16_t start_time = 0;       // in seconds

  // --- parameters screen ---
  uint8_t current_row;

  void save_parameters() {
    save_uint16(wheel_diameter, 0);
    save_uint32(time_limit, 2);
    save_uint16(scale, 6);
    save_uint32(total_distance, 8);
  }

  void load_parameters() {
    wheel_diameter = load_uint16(0);
    time_limit = load_uint32(2);
    scale = load_uint16(6);
    total_distance = load_uint32(8);
  }

  inline void compute_desired_mean_speed() {
    desired_mean_speed = static_cast<float>(total_distance) / time_limit;
  }

  void change_frame() {
    if (current_frame == PARAM_FRAME) {
      current_frame = RUN_FRAME;
      save_parameters();
      compute_desired_mean_speed();

    } else {
      current_frame = PARAM_FRAME;
      current_row = 0;
    }
  }

};

State STATE;

#endif  // STATE_H
