#pragma once

#include "consts.h"
#include "draw.h"
#include "state.h"

void draw_parameters_frame() {
  // Draw distance row
  // uint8_t distance_value_km = STATE.total_distance / 1000;
  // display.text(distance_value_km);

  // Draw selected row indicator
  display.fillRoundRect(0, 1 + STATE.current_row * 10, DISPLAY_WIDTH, 10, 2,
                        WHITE);

  // TODO: print values

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
  uint16_t elapsed_seconds = millis() / 1000 - STATE.start_time;
  uint8_t elapsed_hours = elapsed_seconds / 3600;
  uint8_t elapsed_minutes = (elapsed_seconds / 60) % 60;
  uint8_t elapsed_seconds_mod = elapsed_seconds % 60;

  uint16_t remaining_seconds = STATE.time_limit - elapsed_seconds;
  uint8_t remaining_hours = remaining_seconds / 3600;
  uint8_t remaining_minutes = (remaining_seconds / 60) % 60;

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2, 2);
  if (elapsed_hours < 10) display.print("0");
  display.print(elapsed_hours);
  display.print(":");
  if (elapsed_minutes < 10) display.print("0");
  display.print(elapsed_minutes);
  // TODO: remove me plz
  display.print(":");
  if (elapsed_seconds_mod < 10) display.print("0");
  display.print(elapsed_seconds_mod);

  display.setCursor(64 + 27, 2);
  if (remaining_hours < 10) display.print("0");
  display.print(remaining_hours);
  display.print(":");
  if (remaining_minutes < 10) display.print("0");
  display.print(remaining_minutes);

  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(2, 16);
  if (STATE.lap_distance < 100) {
    display.print(" ");
  }
  if (STATE.lap_distance < 10) {
    display.print(" ");
  }
  display.print(STATE.lap_distance);
  display.print("-");

  uint16_t lap_distance_scaled = STATE.lap_distance / STATE.scale;

  if (lap_distance_scaled < 100) {
    display.print(" ");
  }
  if (lap_distance_scaled < 10) {
    display.print(" ");
  }
  display.print(lap_distance_scaled);

  uint16_t passed_distance_100m = STATE.passed_distance / 100;

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.fillCircle(24, 61, 1, WHITE);
  display.setCursor(0, 47);
  if (passed_distance_100m < 100) {
    display.setCursor(12, 47);
  }
  if (passed_distance_100m < 10) {
    display.print(0);
    display.setCursor(24, 47);
  }
  display.print(passed_distance_100m);

  auto desired = STATE.desired_mean_speed * elapsed_seconds;
  int8_t percent = (int8_t)(STATE.passed_distance - desired) * 100 / (desired);

  display.setCursor(40, 47);
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

  uint16_t distance_remaining_100m =
      (STATE.total_distance - STATE.passed_distance) / 100;
  display.fillCircle(111, 61, 1, WHITE);
  display.setCursor(87, 47);
  if (distance_remaining_100m < 100) {
    display.setCursor(99, 47);
  }
  if (distance_remaining_100m < 10) {
    display.print(0);
    display.setCursor(111, 47);
  }

  display.print(distance_remaining_100m);
}

void draw_frame() {
  display.clearDisplay();

  if (STATE.current_frame == PARAM_FRAME) {
    draw_parameters_frame();
  } else {
    draw_run_frame();
  }

  display.display();
}