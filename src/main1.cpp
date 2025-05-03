// #include <Arduino.h>
// #define INT0_PIN 5
// // #define LED_PIN   13
// #define SCL_PIN   A5
// #define SDA_PIN   A4


// volatile byte state = LOW;
// volatile byte counter = 0;

// void INT0_ISR() {
//   state = !state;
//   if (counter == 255) {
//     counter = 0;
//     return;
//   }
//   counter++;
// }

// // // put function declarations here:
// // int myFunction(int, int);

// void setup() {
//   // put your setup code here, to run once:
// //   int result = myFunction(2, 3);
// //   pinMode(LED_PIN, OUTPUT);
//   pinMode(INT0_PIN, INPUT_PULLUP);
//   attachInterrupt(digitalPinToInterrupt(INT0_PIN), INT0_ISR, CHANGE);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }