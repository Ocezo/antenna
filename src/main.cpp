#include <Arduino.h>
#include <AccelStepper.h>

#define ENABLE_PIN 8  // 8
#define STEPX_PIN 2   // 2
#define STEPY_PIN 3   // 3
#define DIRX_PIN 5    // 5
#define DIRY_PIN 6    // 6

// Driver mode (STEP + DIR)
AccelStepper stepper1(AccelStepper::DRIVER, STEPX_PIN, DIRX_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEPY_PIN, DIRY_PIN);

void setup() {
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW); // Enable driver

  Serial.begin(9600);
  delay(1000);

  Serial.println("Stepper Motors 1&2 Test");

  stepper1.setMaxSpeed(1000);       // steps/sec   : 300 -> 1000
  stepper1.setAcceleration(500);    // steps/sec^2 : 100 -> 500
  stepper1.setCurrentPosition(0);   // reset position

  stepper2.setMaxSpeed(300);        // steps/sec   : 300 -> 1000
  stepper2.setAcceleration(100);    // steps/sec^2 : 100 -> 500
  stepper2.setCurrentPosition(0);   // reset position
}

void loop() {
  const int target1 = 4000;
  const int target2 =  200;

  // Aller
  Serial.println("Moving to target1...");
  stepper1.moveTo(target1);
  while (stepper1.distanceToGo() != 0) {
    stepper1.run();
  }

  Serial.println("Moving to target2...");
  stepper2.moveTo(target2);
  while (stepper2.distanceToGo() != 0) {
    stepper2.run();
  }

  delay(1000);

  // Retour
  Serial.println("Returning to zero1...");
  stepper1.moveTo(0);
  while (stepper1.distanceToGo() != 0) {
    stepper1.run();
  }

  Serial.println("Returning to zero2...");
  stepper2.moveTo(0);
  while (stepper2.distanceToGo() != 0) {
    stepper2.run();
  }

  delay(1000);
}