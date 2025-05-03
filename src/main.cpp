
#include <drawings.h>
#include <buttons.h>
#include <parameters.h>
#include <run.h>
#include <reed_switch.h>
#include <parameters_frame.h>
#include <buttons_actions.h>
// #if (SH1106_LCDHEIGHT != 64)
// #error("Height incorrect, please fix Adafruit_SH1106.h!");
// #endif
#define INT0_PIN 5
// #define LED_PIN   13
#define SCL_PIN   A5
#define SDA_PIN   A4
#define PI 3.1415926535897932384626433832795
volatile byte counter = 0;


RunData run_data;
ParametersInterface param_int;
RunFrameData run_frame = {0};
ParametersFrameData parameters_frame;
ButtonsActions buttons_actions;

void setup() {
  setup_buttons();
  Serial.begin(9600);

  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  setup_display();
  setup_reed_switch();
  buttons_actions.setup(&run_data, &param_int, &run_frame, &parameters_frame);
}

void start_run() {
  run_data.start_run(&param_int);
  reed_switch_callback_counter = 0;
}

void RunData::update() {
  distance_m = reed_switch_callback_counter * (param_int.wheel_diameter_mm * PI) / 1000;
}

void loop() {
  buttons_actions.update();
  // run_frame.draw();
  run_data.update();
  // run_frame.update();
  // char str[100];
  // snprintf(str, sizeof(str), "Hello, world! %d", counter);
  // write_string(str);
  // delay(100);
}
