#pragma once

#include <Arduino.h>

#include "state.h"

#define PI 3.1415926535897932384626433832795

uint16_t last_counter = 0;

inline void compute_desired_mean_speed() {
  STATE.desired_mean_speed = STATE.total_distance / STATE.time_limit;
}

void run_update() {
  if (reed_switch_callback_counter == last_counter) {
    return;
  }

  Serial.println(reed_switch_callback_counter);

  uint8_t delta_count = reed_switch_callback_counter - last_counter;

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
  STATE.lap_distance = 0;
  STATE.passed_distance = 0;
  STATE.start_time = millis() / 1000;
  compute_desired_mean_speed();
}

// struct ResetData {
//     uint16_t begin_distance;
//     uint16_t distance_from_reset;
// };

// struct RunData {
//  public:
//     void set_wheel_diameter(uint16_t wheel_diameter) {
//         wheel_diameter_mm = wheel_diameter;
//     }

//     void start_run(ParametersInterface *param_int) {
//         scale = param_int->get(ParametersNames::SCALE);
//         start_time = millis() / 1000;
//         distance_m = 0;
//         total_distance_m = param_int->get(ParametersNames::DISTANCE_KM) *
//         1000; time_limit_s = param_int->get(ParametersNames::TIME_LIMIT_H) *
//         3600; if (time_limit_s == 0) {
//             desired_mean_speed_m_per_s = 0;
//         } else {
//             desired_mean_speed_m_per_s = total_distance_m / time_limit_s;
//         }
//         reed_switch_callback_counter = 0;

//         Serial.println("Run started\n");
//     }

//     void update() {
//         // distance_m = reed_switch_callback_counter * wheel_diameter_mm * PI
//         / 1000;
//     }

//     /**
//      * Makes a reset
//      */
//     void make_reset() {
//         last_reset_data.begin_distance = distance_m;
//         last_reset_data.distance_from_reset = 0;
//         Serial.println("Reset made\n");
//     }

//     uint16_t get_last_reset_distance() {
//         return last_reset_data.begin_distance;
//     }

//     uint16_t get_last_reset_distance_scaled() {
//         if (scale == 0) {
//             return 0;
//         }
//         return last_reset_data.begin_distance / scale;
//     }

//     void get_total_time(uint16_t *hours, uint16_t *minutes) {
//         *hours = time_limit_s / 3600;
//         *minutes = time_limit_s / 60 % 60;
//     }

//     /**
//      * Returns the distance in meters
//      */
//     uint16_t get_remaining_distance() {
//         return total_distance_m - distance_m;
//     }

//     /**
//      * Returns the time in seconds
//      */
//     uint16_t get_remaining_time() {
//         return (time_limit_s + start_time) - millis() / 1000;
//     }

//     /**
//      * Returns the distance in meters
//      */
//     uint16_t get_distance_from_start() {
//         return distance_m;
//     }

//     /**
//      * Returns the difference between desired distance and actual distance
//      */
//     int8_t get_percent() {
//         auto run_time = millis() / 1000 - start_time;
//         auto desired = desired_mean_speed_m_per_s * run_time;
//         return (int8_t)(distance_m - desired)  * 100 / (desired);
//     }

//  private:
//     ResetData last_reset_data;
//     uint16_t wheel_diameter_mm;
//     uint32_t start_time;
//     uint32_t distance_m;
//     uint32_t total_distance_m;
//     uint32_t desired_mean_speed_m_per_s;
//     uint32_t time_limit_s;
//     uint8_t scale;
// };

// RunData run_data;
