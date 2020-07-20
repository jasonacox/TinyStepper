/*
  TinyStepper - Stepper Motor Test

  by Jason A. Cox - @jasonacox

  Date: 19 July 2020

*/

#include <TinyStepper.h>

// Define Arduino Pin Outputs to to the ULN2003 Darlington Array to drive a 28BYJ-48 Stepper Motor
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// Init the TinyStepper Class
TinyStepper stepper(4096, IN1, IN2, IN3, IN4);

void setup()
{
  Serial.begin(38400);
  stepper.Enable();
  delay(1000);
}

void loop() {

  // Random back and forth
  Serial.println("Random Test");
  stepper.Move(45);
  stepper.Move(-90);
  stepper.Move(120);
  stepper.Move(-15);
  stepper.Move(30);
  stepper.Move(-300);
  stepper.Move(600);
  stepper.Move(-100);
  delay(2000);

  // Accelerate/decelerate 360 full rotation - both directions
  Serial.println("Full Rotation");
  stepper.AccelMove(360);
  stepper.AccelMove(-360, 1, 10);
  delay(2000);
}
