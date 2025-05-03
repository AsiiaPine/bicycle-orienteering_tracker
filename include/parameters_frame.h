#ifndef PARAMETERS_FRAME_H
#define PARAMETERS_FRAME_H
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <drawings.h>
#include <parameters.h>

enum ParametersNames {
  START,
  CONTINUE,
  TIME_LIMIT,
  LENGTH,
  DIAMETER,
  SCALE
};

struct ParametersFrameData {
    void draw() {
      display.clearDisplay();
      draw_rows();
      display.display();
    }

    void update();

    void save_parameters(ParametersInterface *param_int) {
        param_int->distance_km = values[ParametersNames::LENGTH];
        param_int->wheel_diameter_mm = values[ParametersNames::DIAMETER];
        param_int->scale = values[ParametersNames::SCALE];
        param_int->time_limit_h = values[ParametersNames::TIME_LIMIT];
        param_int->save();
    }

    void load_parameters(ParametersInterface *param_int) {
        values[ParametersNames::LENGTH] = param_int->distance_km;
        values[ParametersNames::DIAMETER] = param_int->wheel_diameter_mm;
        values[ParametersNames::SCALE] = param_int->scale;
        values[ParametersNames::TIME_LIMIT] = param_int->time_limit_h;
    }

    void get_parameter(ParametersNames name, uint16_t *value) {
        *value = values[name];
    }

    void set_parameter(ParametersNames name, uint16_t value) {
        values[name] = value;
    }

    void increase_value() {
      if (row < 2) {
        return;
      }
      if (strcmp(names[row], "Diameter, mm")) {
        values[row] += 10;
        return;
      }
      values[row]++;
    }

    void decrease_value() {
      if (row < 2) {
        return;
      }
      if (strcmp(names[row], "Diameter, mm")) {
        values[row] -= 10;
        return;
      }
      values[row]--;
    }

    void prev_row() {
      row--;
      if (row < 0) {
        row = 8;
      }
    }

    void next_row() {
      row++;
      if (row > 8) {
        row = 0;
      }
    }

 private:
    char names[6][LINE_CHAR_LENGTH - 4] =
      {"Start", "Continue", "Time limit, h", "Length, km", "Diameter, mm", "Scale, m/cm"};
    uint16_t values[8];
    const uint8_t values_offset = 80;
    uint8_t row = 0;
    void draw_rows() {
      display.setTextSize(1);
      for (uint8_t i = 0; i < 6; i++) {
        display.setCursor(2, 2+i*8+ 1);
        if (i == row) {
          display.fillRoundRect(0, 2+i*8, DISPLAY_WIDTH, 8, 3, WHITE);
          display.setCursor(2, 2+i*8+ 1);
          display.setTextColor(BLACK);
        }
        display.print(names[i]);
        if (i > 2) {
          display.setCursor(90, 2+i*8+ 1);
          display.print(values[i]);
        }
        display.setTextColor(WHITE);
      }
    }
};

#endif  // PARAMETERS_FRAME_H
