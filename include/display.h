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

#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <consts.h>
#include <state.h>
#include <algorithms.h>

// --- Hardware ---
#define OLED_RESET 4
#define SCL_PIN A5
#define SDA_PIN A4
Adafruit_SH1106 display(OLED_RESET);

// --- Display ---
#define DISPLAY_HEIGHT 64
#define DISPLAY_WIDTH 128

// --- Text ---
#define LINE_CHAR_LENGTH 21
#define LINE_CHAR_HEIGHT 8

void draw_parameters_frame() {
  // Draw selected row indicator - round rectangle.
  // The indicator is filled with white color. If the row is selected, the text color is black.
  display.fillRoundRect(0, 1 + STATE.current_row * 10, DISPLAY_WIDTH, 10, 2,
                        WHITE);

  display.setTextSize(1);

  // Start row
  display.setCursor(2, 2 + ROW_START * 10);
  display.setTextColor(STATE.current_row == ROW_START ? BLACK : WHITE);
  display.print("Start");

  // Continue row
  display.setCursor(2, 2 + ROW_CONTINUE * 10);
  display.setTextColor(STATE.current_row == ROW_CONTINUE ? BLACK : WHITE);
  display.print("Continue");

  // Time limit row
  display.setCursor(2, 2 + ROW_TIME_LIMIT * 10);
  display.setTextColor(STATE.current_row == ROW_TIME_LIMIT ? BLACK : WHITE);
  display.print("Time limit");

  display.setCursor(90, 2 + ROW_TIME_LIMIT * 10);
  display.print(STATE.time_limit / 3600);

  // Distance row
  display.setCursor(2, 2 + ROW_TOTAL_DISTANCE * 10);
  display.setTextColor(STATE.current_row == ROW_TOTAL_DISTANCE ? BLACK : WHITE);
  display.print("Distance");

  display.setCursor(90, 2 + ROW_TOTAL_DISTANCE * 10);
  display.print(STATE.total_distance / 1000);

  // Wheel diameter row
  display.setCursor(2, 2 + ROW_WHEEL_DIAMETER * 10);
  display.setTextColor(STATE.current_row == ROW_WHEEL_DIAMETER ? BLACK : WHITE);
  display.print("Wheel diameter");

  display.setCursor(90, 2 + ROW_WHEEL_DIAMETER * 10);
  display.print(STATE.wheel_diameter);

  // Map scale row
  display.setCursor(2, 2 + ROW_MAP_SCALE * 10);
  display.setTextColor(STATE.current_row == ROW_MAP_SCALE ? BLACK : WHITE);
  display.print("Map scale");

  display.setCursor(90, 2 + ROW_MAP_SCALE * 10);
  display.print(STATE.scale);
}

void draw_run_frame() {
  // Calculate printable values
  uint32_t elapsed_seconds = millis() / 1000 - STATE.start_time;
  uint8_t elapsed_hours = elapsed_seconds / 3600;
  uint8_t elapsed_minutes = (elapsed_seconds / 60) % 60;
  uint8_t elapsed_seconds_mod = elapsed_seconds % 60;

  uint16_t remaining_seconds = STATE.time_limit - elapsed_seconds;
  uint8_t remaining_hours = remaining_seconds / 3600;
  uint8_t remaining_minutes = (remaining_seconds / 60) % 60;

  uint16_t lap_distance_scaled = STATE.lap_distance / STATE.scale;
  uint16_t passed_distance_100m = STATE.passed_distance / 100;
  float desired_passed_distance = STATE.desired_mean_speed * elapsed_seconds;

  int8_t percent = 0;
  // If elapsed time is less than 10 seconds, then don't calculate percentage,
  // because desired_passed_distance might be so small that it will be rounded to zero.

  if (elapsed_seconds > 10) {
    auto pct = static_cast<int>(((STATE.passed_distance - desired_passed_distance) * 100) / (desired_passed_distance));
    percent = clamp(pct, -100, 100);
  }

  // First line
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2, 2);
  if (elapsed_hours < 10) display.print("0");
  display.print(elapsed_hours);
  display.print(":");
  if (elapsed_minutes < 10) display.print("0");
  display.print(elapsed_minutes);

  // TODO: remove me if you don't want to see seconds
  display.print(":");
  if (elapsed_seconds_mod < 10) display.print("0");
  display.print(elapsed_seconds_mod);

  display.setCursor(64 + 27, 2);
  if (remaining_hours < 10) display.print("0");
  display.print(remaining_hours);
  display.print(":");
  if (remaining_minutes < 10) display.print("0");
  display.print(remaining_minutes);

  // Second line
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(2, 16);
  // Printing distance in meters
  auto lap_distance = STATE.lap_distance;
  if (lap_distance < 100) {
    display.print(" ");
  }
  if (lap_distance < 10) {
    display.print(" ");
  }

  if (lap_distance > 1000) {
    if (lap_distance / 10000 == 0) {
      display.fillCircle(20, 40, 1, WHITE);
      lap_distance = lap_distance / 10;
    } else {
      display.fillCircle(38, 40, 1, WHITE);
      lap_distance = lap_distance / 100;
      if (lap_distance > 999) {
        lap_distance = 999;
      }
    }
  }
  display.print(lap_distance);

  display.print("-");


  // Printing scaled distance like in map
  if (lap_distance_scaled < 100) {
    display.print(" ");
  }
  if (lap_distance_scaled < 10) {
    display.print(" ");
  }

  if (lap_distance_scaled > 1000) {
    if (lap_distance_scaled / 10000 == 0) {
      display.fillCircle(92, 40, 1, WHITE);
      lap_distance_scaled = lap_distance_scaled / 10;
    } else {
      display.fillCircle(108, 40, 1, WHITE);
      lap_distance_scaled = lap_distance_scaled / 100;
    }
    if (lap_distance_scaled > 999) {
      lap_distance_scaled = 999;
    }
  }

  display.print(lap_distance_scaled);

  // third line
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 47);

  // Printing passed distance in km
  if (passed_distance_100m < 100) {
    display.setCursor(12, 47);
  }
  if (passed_distance_100m < 10) {
    display.print(0);
    display.fillCircle(24, 61, 1, WHITE);
    display.setCursor(24, 47);
  }
  display.print(passed_distance_100m);

  display.setCursor(40, 47);

  // Printing percent
  uint8_t abs_percent = 0;
  if (percent > 0) {
    display.print(" ");
    abs_percent = percent;
  } else {
    abs_percent = percent * -1;
    if (abs_percent < 10) {
      display.print(" ");
    }
    display.print("-");
  }
  display.print(abs_percent);
  display.setTextSize(1);
  display.print("%");
  display.setTextSize(2);

  // Printing distance remaining in km
  uint16_t distance_remaining_100m =
      (STATE.total_distance - STATE.passed_distance) / 100;
  display.setCursor(87, 47);
  if (distance_remaining_100m < 100) {
    display.setCursor(99, 47);
  }
  if (distance_remaining_100m < 10) {
    display.print(0);
    display.fillCircle(111, 61, 1, WHITE);
    display.setCursor(111, 47);
  }

  display.print(distance_remaining_100m);
}

// Draw current frame
void draw_frame() {
  display.clearDisplay();

  // Check which frame to draw
  if (STATE.current_frame == PARAM_FRAME) {
    draw_parameters_frame();
  } else {
    draw_run_frame();
  }

  display.display();
}
