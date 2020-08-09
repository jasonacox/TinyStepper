/*
  TinyStepper - 2 Stepper Motor Laser Gimbal
  by Jason A. Cox - @jasonacox
  Date: 19 July 2020

  Laser Gimbal with 2 Stepper Motors based on Thingiverse project: https://www.thingiverse.com/thing:794786
  Test cycles each stepper then draws a circle with the laser pointer.  Switches allow users to move the
  center of the circle (up/down/left/right).

  Arduino Microcontroller (e.g. Uno)
  2 x 28BYJ-48 Stepper Motors
  2 x ULN2003 Driver Board
  1 x Laser (e.g. 5V 650nm 5mW Red Dot Diode Laser)
  4 x Microswitches
  4 x 61k Ohm Resistors (pull up resistor for switches)
  5V Power Supply (do not power steppers with Arduino)

*/

#include <TinyStepper.h>

// Number of half-steps for a full rotation
#define HALFSTEPS 4096

#define FACTOR 5      // Size of circle
#define STEPWAIT 2    // Time to wait for motor to move between steps (-Speed vs Smooth+)
#define RESOLUTION 10 // Increase to smooth circle by staggering stepper updates

// Motion control microswitches
#define UP1 2
#define DOWN1 3
#define UP2 12
#define DOWN2 13

// Arduino Pin Outputs to to the ULN2003 for the 28BYJ-48 Stepper Motors
//                             IN1   IN2   IN3   IN4
TinyStepper stepper1(HALFSTEPS,  8,   9,   10,   11);
TinyStepper stepper2(HALFSTEPS,  4,   5,    6,    7);

// Global variables
float dx;
float dy;
float t;
int buttondown = 0;

void setup()
{
  Serial.begin(38400);
  stepper1.Enable();
  stepper2.Enable();
  delay(1000);

  pinMode(UP1, INPUT);
  pinMode(DOWN1, INPUT);

  pinMode(UP2, INPUT);
  pinMode(DOWN2, INPUT);

  Serial.println("Stepper 1 Motion Test");
  stepper1.AccelMove(20);
  stepper1.AccelMove(-20);

  Serial.println("Stepper 2 Motion Test");
  stepper2.AccelMove(20);
  stepper2.AccelMove(-20);

  dx = 0.0;
  dy = 0.0;
  t = 0.0;

  Serial.println("Starting Circle Test Loop");
}


void loop() {

  if (buttondown == 0) {    // if button pressed stop circle
    dx = (FACTOR * sin(t));
    dy = (FACTOR * cos(t));
    delay(10);

    t = t + 0.1;
    Serial.print(">> x=");
    Serial.print(dx);
    Serial.print(" y=");
    Serial.print(dy);
    Serial.print(" t=");
    Serial.println(t);

    // Draw circle with laser pointer
    for (int x = 0; x < RESOLUTION; x++) {
      stepper1.Move(dx / RESOLUTION, STEPWAIT);
      stepper2.Move(dy / RESOLUTION, STEPWAIT);
    }
  }
  else {
    buttondown--;   // Countdown to start circle drawing
    delay(1);
  }
  
  // Allow user to adjust pointer location
  if (digitalRead(UP1) == LOW) {
    buttondown = 100;
    stepper1.Move(0.1);
    Serial.println("UP1");
  }
  if (digitalRead(DOWN1) == LOW) {
    buttondown = 100;
    stepper1.Move(-0.1);
    Serial.println("DOWN1");
  }
  if (digitalRead(UP2) == LOW) {
    buttondown = 100;
    stepper2.Move(0.1);
    Serial.println("UP2");
  }
  if (digitalRead(DOWN2) == LOW) {
    buttondown = 100;
    stepper2.Move(-0.1);
    Serial.println("DOWN2");
  }

}
