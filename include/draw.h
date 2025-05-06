#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

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

// struct Time {
//   uint8_t hour;
//   uint8_t minute;
// };

// void write_string(const char *str) {
//   display.setTextSize(1);
//   display.setTextColor(WHITE);
//   display.setCursor(0, 0);
//   display.print(str);
//   display.display();
// }

void test_draw_circle() {
  for (int16_t i = 0; i < display.height(); i += 2) {
    display.drawCircle(display.width() / 2, display.height() / 2, i, WHITE);
    display.display();
  }
}

// inline void setup_display() {
//   display.clearDisplay();
//   test_draw_circle();
// }
