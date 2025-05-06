
// #include <drawings.h>
// #include <buttons.h>
// #include <parameters.h>
// #include <run.h>
// #include <parameters_frame.h>
// #include <buttons_actions.h>

#include "display.h"
#include "input.h"
#include "state.h"

#define INT0_PIN 5

#define SCL_PIN A5
#define SDA_PIN A4

volatile byte counter = 0;

// RunData run_data;
// ParametersInterface param_int;
// RunFrameData run_frame;
// ParametersFrameData parameters_frame;
// ButtonsActions buttons_actions;

void setup() {
  Serial.begin(9600);
  Serial.println("setup()");
  // delay(500);

  STATE.load_parameters();

  // --- Use this section to reset parameters ---
  // STATE.scale = 25;
  // STATE.wheel_diameter = 2200;

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
