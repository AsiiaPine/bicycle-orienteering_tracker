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
#include <storage.h>

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
  uint32_t passed_distance = 0;  // in millimeters
  uint32_t lap_distance = 0;     // in millimeters
  uint16_t start_time = 0;       // in seconds

  // --- parameters screen ---
  uint8_t current_row;

  // Save parameters to EEPROM
  void save_parameters() {
    save_uint16(wheel_diameter, 0);
    save_uint32(time_limit, 2);
    save_uint16(scale, 6);
    save_uint32(total_distance, 8);
  }

  // Load parameters from EEPROM
  void load_parameters() {
    wheel_diameter = load_uint16(0);
    time_limit = load_uint32(2);
    scale = load_uint16(6);
    total_distance = load_uint32(8);
  }

  // Compute desired mean speed based on total distance and time limit (m/s)
  inline void compute_desired_mean_speed() {
    desired_mean_speed = static_cast<float>(total_distance) / time_limit;
  }

  // Change current frame, on parameters screen, change to run screen and save parameters
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
