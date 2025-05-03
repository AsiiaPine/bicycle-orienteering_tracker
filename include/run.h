#ifndef RUN_H
#define RUN_H

#include <Arduino.h>
#include <parameters.h>
#include <reed_switch.h>
#define PI 3.1415926535897932384626433832795


struct ResetData {
    uint16_t begin_distance;
    uint16_t distance_from_reset;
};

struct RunData {
 public:
    void set_wheel_diameter(uint16_t wheel_diameter) {
        wheel_diameter_mm = wheel_diameter;
    }

    void start_run(ParametersInterface *param_int) {
        scale = param_int->get(ParametersNames::SCALE);
        start_time = millis() / 1000;
        distance_m = 0;
        total_distance_m = param_int->get(ParametersNames::DISTANCE_KM) * 1000;
        time_limit_s = param_int->get(ParametersNames::TIME_LIMIT_H) * 3600;
        if (time_limit_s == 0) {
            desired_mean_speed_m_per_s = 0;
        } else {
            desired_mean_speed_m_per_s = total_distance_m / time_limit_s;
        }
        reed_switch_callback_counter = 0;

        Serial.println("Run started\n");
    }

    void update() {
        distance_m = reed_switch_callback_counter * wheel_diameter_mm * PI / 1000;
    }

    /**
     * Makes a reset
     */
    void make_reset() {
        last_reset_data.begin_distance = distance_m;
        last_reset_data.distance_from_reset = 0;
        Serial.println("Reset made\n");
    }

    uint16_t get_last_reset_distance() {
        return last_reset_data.begin_distance;
    }

    uint16_t get_last_reset_distance_scaled() {
        if (scale == 0) {
            return 0;
        }
        return last_reset_data.begin_distance / scale;
    }


    void get_total_time(uint16_t *hours, uint16_t *minutes) {
        *hours = time_limit_s / 3600;
        *minutes = time_limit_s / 60 % 60;
    }

    /**
     * Returns the distance in meters
     */
    uint16_t get_remaining_distance() {
        return total_distance_m - distance_m;
    }

    /**
     * Returns the time in seconds
     */
    uint16_t get_remaining_time() {
        return (time_limit_s + start_time) - millis() / 1000;
    }

    /**
     * Returns the distance in meters
     */
    uint16_t get_distance_from_start() {
        return distance_m;
    }

    /**
     * Returns the difference between desired distance and actual distance
     */
    int8_t get_percent() {
        auto run_time = millis() / 1000 - start_time;
        auto desired = desired_mean_speed_m_per_s * run_time;
        return (int8_t)(distance_m - desired)  * 100 / (desired);
    }

 private:
    ResetData last_reset_data;
    uint16_t wheel_diameter_mm;
    uint32_t start_time;
    uint32_t distance_m;
    uint32_t total_distance_m;
    uint32_t desired_mean_speed_m_per_s;
    uint32_t time_limit_s;
    uint8_t scale;
};

#endif  // RUN_H
