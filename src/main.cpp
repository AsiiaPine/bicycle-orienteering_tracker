#include <display.h>
#include <input.h>
#include <state.h>

#define INT0_PIN 5

#define SCL_PIN A5
#define SDA_PIN A4

void setup() {
  Serial.begin(9600);
  Serial.println("setup()");

  STATE.load_parameters();

  // --- Use this section to reset parameters to default---
  // STATE.scale = 25;
  // STATE.wheel_diameter = 2200;
  // STATE.time_limit = 300;
  // STATE.total_distance = 10000;

  // initialize with the I2C addr 0x3D (for the 128x64)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);

  setup_input();
  run_reset();
}

void loop() {
  run_update();
  handle_buttons();
  draw_frame();
}
