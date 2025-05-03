#ifndef PARAMETERS_FRAME_H
#define PARAMETERS_FRAME_H
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <drawings.h>
#include <parameters.h>

enum RowsNames {
  START,
  CONTINUE,
  TIME_LIMIT,
  LENGTH,
  DIAMETER,
  MAP_SCALE,
  NUM_ROWS
};

struct ParametersFrameData {
  bool ToStart = false;
  bool ToContinue = false;

    void draw() {
      display.clearDisplay();
      draw_rows();
      display.display();
    }

    void update();

    void save_parameters(ParametersInterface *param_int) {
      param_int->set(ParametersNames::DISTANCE_KM, values[RowsNames::LENGTH]);
      param_int->set(ParametersNames::WHEEL_DIAMETER_MM, values[RowsNames::DIAMETER]);
      param_int->set(ParametersNames::SCALE, values[RowsNames::MAP_SCALE]);
      param_int->set(ParametersNames::TIME_LIMIT_H, values[RowsNames::TIME_LIMIT]);
      param_int->save();
    }

    void load_parameters(ParametersInterface *param_int) {
        values[RowsNames::LENGTH] = param_int->get(ParametersNames::DISTANCE_KM);
        values[RowsNames::DIAMETER] = param_int->get(ParametersNames::WHEEL_DIAMETER_MM);
        values[RowsNames::MAP_SCALE] = param_int->get(ParametersNames::SCALE);
        values[RowsNames::TIME_LIMIT] = param_int->get(ParametersNames::TIME_LIMIT_H);
    }

    void get_parameter(RowsNames name, uint16_t *value) {
        *value = values[name];
    }

    void set_parameter(RowsNames name, uint16_t value) {
        values[name] = value;
    }

    void increase_value() {
      if (row < 2) {
        if (row == 0) ToStart = true;
        if (row == 1) ToContinue = true;
        return;
      }
      if (strcmp(names[row], "Diameter, mm") == 0) {
        values[row] += 10;
        return;
      }
      values[row]++;
    }

    void decrease_value() {
      if (row < 2) {
        return;
      }
      if (strcmp(names[row], "Diameter, mm") == 0) {
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
    char names[RowsNames::NUM_ROWS][LINE_CHAR_LENGTH - 4] =
      {"Start", "Continue", "Time limit, h", "Length, km", "Diameter, mm", "Scale, m/cm"};
    uint16_t values[NUM_ROWS];
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
