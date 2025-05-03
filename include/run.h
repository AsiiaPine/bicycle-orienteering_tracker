#ifndef RUN_H
#define RUN_H

#include <Arduino.h>
#include <parameters.h>


struct ResetData {
    uint16_t begin_distance;
    uint16_t distance_from_reset;
};

struct RunData {
 public:
    void start_run(ParametersInterface *param_int) {
        scale = param_int->scale;
        start_time = millis() / 1000;
        distance_m = 0;
        total_distance_m = param_int->distance_km * 1000;
        time_limit_s = param_int->time_limit_h * 3600;
        desired_mean_speed_m_per_s = total_distance_m / time_limit_s;
    }

    void update();
    /**
     * Makes a reset
     */
    void make_reset() {
        last_reset_data.begin_distance = distance_m;
        last_reset_data.distance_from_reset = 0;
    }

    uint16_t get_last_reset_distance() {
        return last_reset_data.begin_distance;
    }

    uint16_t get_last_reset_distance_scaled() {
        return last_reset_data.begin_distance / scale;
    }

    // ResetData get_last_reset_data() {
    //     return last_reset_data;
    // }

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
    uint32_t start_time;
    uint32_t distance_m;
    uint32_t total_distance_m;
    uint32_t desired_mean_speed_m_per_s;
    uint32_t time_limit_s;
    uint8_t scale;
};

#endif  // RUN_H
