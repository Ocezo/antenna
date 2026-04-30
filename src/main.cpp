#include <Arduino.h>
#include <AccelStepper.h>

#define DIR_PIN 2
#define STEP_PIN 3
#define ENABLE_PIN 4

// Driver mode (STEP + DIR)
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW); // Enable driver

  Serial.begin(9600);
  delay(1000);

  Serial.println("Stepper Motor Test");

  // Réglages SAFE pour commencer
  stepper.setMaxSpeed(1000);        // steps/sec   : 300 -> 1000
  stepper.setAcceleration(500);    // steps/sec^2 : 100 -> 500

  stepper.setCurrentPosition(0);   // reset position
}

void loop() {
  const int target = 4000; // mouvement visible

  // Aller
  Serial.println("Moving to target...");
  stepper.moveTo(target);

  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  Serial.println("Target reached");
  delay(1000);

  // Retour
  Serial.println("Returning to zero...");
  stepper.moveTo(0);

  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  Serial.println("Back to zero");
  delay(1000);
}