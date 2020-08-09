/*
  TinyStepper - 3 Stepper Motor Robotic Arm Test
  by Jason A. Cox - @jasonacox
  Date: 19 July 2020

  Robotic Arm with 3 Stepper Motors based on Thingiverse project: https://www.thingiverse.com/thing:2838859
  Test cycles each stepper and then responds to user switches (up/down) for stepper motion.

  Arduino Microcontroller (e.g. Mega2560)
  3 x 28BYJ-48 Stepper Motors
  3 x ULN2003 Driver Board
  6 x Microswitches
  6 x 61k Ohm Resistors (pull up resistor for switches)
  5V Power Supply (do not power steppers with Arduino)

  Video Demo: https://www.youtube.com/watch?v=fzrtDgM6CLM&feature=youtu.b
*/

#include <TinyStepper.h>

#define HALFSTEPS 4096  // Number of half-steps for a full rotation

#define MOTIONTEST false    // Cycle arm on startup (set to false for button control only)
#define DELTA 0.125         // Stepper degrees to change per button press loop
#define STEPWAIT 1          // Time to wait for motor to move between steps (-Speed vs Torque+)

// Motion control microswitches
#define UP1 26
#define DOWN1 27
#define UP2 28
#define DOWN2 29
#define UP3 30
#define DOWN3 31

// Arduino Pin Outputs to to the ULN2003 for the 28BYJ-48 Stepper Motors
//                             IN1   IN2   IN3   IN4
TinyStepper stepper1(HALFSTEPS,  8,   9,   10,   11);
TinyStepper stepper2(HALFSTEPS,  4,   5,    6,    7);
TinyStepper stepper3(HALFSTEPS, 22,  23,   24,   25);

void setup()
{
  Serial.begin(38400);
  stepper1.Enable();
  stepper2.Enable();
  stepper3.Enable();
  delay(1000);

  pinMode(UP1, INPUT);
  pinMode(DOWN1, INPUT);
  pinMode(UP2, INPUT);
  pinMode(DOWN2, INPUT);
  pinMode(UP3, INPUT);
  pinMode(DOWN3, INPUT);

  if (MOTIONTEST) {
    Serial.println("Stepper 1 Motion Test");
    stepper1.AccelMove(180);
    stepper1.AccelMove(-180);

    Serial.println("Stepper 2 Motion Test");
    stepper2.AccelMove(180);
    stepper2.AccelMove(-180);

    Serial.println("Stepper 3 Motion Test");
    stepper3.AccelMove(180);
    stepper3.AccelMove(-180);
  }
}


void loop() {
  
  if (digitalRead(UP1) == LOW) {
    stepper1.Move(DELTA, STEPWAIT);
    Serial.println("UP1");
  }
  if (digitalRead(DOWN1) == LOW) {
    stepper1.Move(-DELTA, STEPWAIT);
    Serial.println("DOWN1");
  }

  if (digitalRead(UP2) == LOW) {
    stepper2.Move(DELTA, STEPWAIT);
    Serial.println("UP2");
  }
  if (digitalRead(DOWN2) == LOW) {
    stepper2.Move(-DELTA, STEPWAIT);
    Serial.println("DOWN2");
  }

  if (digitalRead(UP3) == LOW) {
    stepper3.Move(DELTA, STEPWAIT);
    Serial.println("UP3");
  }
  if (digitalRead(DOWN3) == LOW) {
    stepper3.Move(-DELTA, STEPWAIT);
    Serial.println("DOWN3");
  }
}
