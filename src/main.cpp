
#include <drawings.h>
#include <buttons.h>
#include <parameters.h>
#include <run.h>
#include <parameters_frame.h>
#include <buttons_actions.h>

#include <state.h>

#define INT0_PIN 5

#define SCL_PIN   A5
#define SDA_PIN   A4

volatile byte counter = 0;

// RunData run_data;
// ParametersInterface param_int;
// RunFrameData run_frame;
// ParametersFrameData parameters_frame;
ButtonsActions buttons_actions;

void setup() {
  Serial.begin(9600);

  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  setup_display();
  delay(500);
  Serial.println("Setup display\n");

  setup_buttons();
  Serial.println("Setup buttons\n");
  delay(500);

  state.init();
  Serial.println("State init\n");

  buttons_actions.setup();
  delay(500);
  Serial.println("Run data set\n");
}

void loop() {
  buttons_actions.update_state();
  // run_data.update();
  // delay(1000);
}
