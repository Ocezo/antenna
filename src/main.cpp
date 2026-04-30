#include <Arduino.h>

#define DIR_PIN 2
#define STEP_PIN 3
#define ENABLE_PIN 4

void setup() {
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  digitalWrite(ENABLE_PIN, LOW);   // Enable TMC2209
  digitalWrite(DIR_PIN, HIGH);

  delay(1000);
}

void loop() {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(STEP_PIN, LOW);
  delay(5);   // environ 200 pas/s
}