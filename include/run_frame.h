#ifndef RUN_FRAME_H
#define RUN_FRAME_H

#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <drawings.h>
#include <run.h>

struct RunFrameData {
    Time time_left = {0, 0};
    Time time_from_start = {0, 0};
    uint16_t distance_from_reset;
    uint16_t distance_from_reset_scaled;
    uint16_t distance_from_start;
    int8_t  percent;
    uint16_t distance_remaining;

 public:
    void draw() {
      display.clearDisplay();
      draw_first_line();
      draw_second_line();
      draw_third_line();
      display.display();
    }

    void update(RunData run_data) {
        // auto run_time = millis() / 1000 - run_data.get_remaining_time();
        // time_from_start.hour = run_time / 3600;
        // time_from_start.minute = (run_time / 60) % 60;
        // distance_from_start = run_data.get_remaining_distance();
        // distance_from_reset = run_data.get_last_reset_distance();
        // distance_from_reset_scaled = run_data.get_last_reset_distance_scaled();
        // percent = run_data.get_percent();
        // distance_remaining = run_data.get_remaining_distance();
        draw();
    }

 private:
    void draw_first_line() {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(2, 2);
      if (time_left.hour < 10) display.print("0");
      display.print(time_left.hour);
      display.print(":");
      if (time_left.minute < 10) display.print("0");
      display.print(time_left.minute);

      display.setCursor(64 + 27, 2);
      if (time_from_start.hour < 10) display.print("0");
      display.print(time_from_start.hour);
      display.print(":");
      if (time_from_start.minute < 10) display.print("0");
      display.print(time_from_start.minute);
    }

    void draw_second_line() {
      display.setTextSize(3);
      display.setTextColor(WHITE);
      display.setCursor(2, 16);
      if (distance_from_reset < 100) {
        display.print(0);
      }
      if (distance_from_reset < 10) {
        display.print(0);
      }
      display.print(distance_from_reset);
      display.print("-");
      if (distance_from_reset_scaled < 100) {
        display.print(0);
      }
      if (distance_from_reset_scaled < 10) {
        display.print(0);
      }
      display.print(distance_from_reset_scaled);
    }

  void draw_third_line() {
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 47);
      if (distance_from_start < 100) {
          display.print(0);
      }
      if (distance_from_start < 10) {
          display.print(0);
      }
      display.print(distance_from_start);

      display.setCursor(40, 47);
      uint8_t abs_percent = 0;
      if (percent > 0) {
          display.print(" ");
          abs_percent = percent;
      } else {
          abs_percent = percent * -1;
          display.print("-");
      }
      if (abs_percent < 10) {
          display.print(0);
      }
      display.print(abs_percent);
      display.setTextSize(1);
      display.print("%");
      display.setTextSize(2);

      display.setCursor(90, 47);
      if (distance_remaining < 100) {
          display.print(0);
      }
      if (distance_remaining < 10) {
          display.print(0);
      }
      display.print(distance_remaining);
    }
};

#endif  // RUN_FRAME_H
