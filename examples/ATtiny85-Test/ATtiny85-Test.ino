/*
  TinyStepper - Stepper Motor Test using ATtiny85
  by Jason A. Cox - @jasonacox

  Date: 1 August 2020

  Tested with ATtiny85 with ATtinyCore core at 8 MHz (internal) 
*/

#include <TinyStepper.h>

// Define ATtiny85 Pin Outputs to to the ULN2003 Darlington Array to drive a 28BYJ-48 Stepper Motor
#define IN1 1
#define IN2 2
#define IN3 3
#define IN4 4

#define HALFSTEPS 4096  // Number of half-steps for a full rotation

// Initialize the TinyStepper Class
TinyStepper stepper(HALFSTEPS, IN1, IN2, IN3, IN4);

void setup()
{
  stepper.Enable();
  delay(1000);
}

void loop() {

  // Random back and forth
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
  stepper.AccelMove(360);
  stepper.AccelMove(-360, 1, 10);
  delay(2000);
}
