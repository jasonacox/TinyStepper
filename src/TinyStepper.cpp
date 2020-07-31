//  TinyStepper
//  Arduino tiny library for stepper motors
//
//  Author: Jason A. Cox - @jasonacox - https://github.com/jasonacox
//  Date: 19 July 2020

// Includes
#include "Arduino.h"
#include "math.h"
#include <TinyStepper.h>

// The Stepper Motor is driven by a ULN2003A which provides an array of seven NPN Darlington transistors 
// capable of 500 mA, 50 V output, great for driving inductive loads like a motor.
//
// The stepper motor has 4 different position coils, ABCD.  In half step mode, you energize the adjacent coil before
// disengaging the previous coil.  The transition steps would be these 8 patterns: A, AB, B, BC, C, CD, D, DA
//
//   Phase ABCD Coils
//   0     1000  A
//   1     1100  AB
//   2     0100   B
//   3     0110   BC
//   4     0010    C
//   5     0011    CD
//   6     0001     D
//   7     1001  A  D
//
// The phase_map[] array is based on the transition steps.  ABCD map to IN1, IN2, IN3, and IN4.

const uint8_t phase_map[] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x09};


TinyStepper::TinyStepper(uint16_t halfsteps, uint8_t IN1, uint8_t IN2, uint8_t IN3, uint8_t IN4)
{
  
  // Copy the pin numbers
  m_pinIN1 = IN1;
  m_pinIN2 = IN2;
  m_pinIN3 = IN3;
  m_pinIN4 = IN4;
  
  steps = halfsteps;
  step_angle = (float)(360.0/steps);
  phase = 0;

  // Set the pins as output
  pinMode(m_pinIN1, OUTPUT);//set the IN1 pin as OUTPUT
  pinMode(m_pinIN2, OUTPUT);//set the IN2 pin as OUTPUT
  pinMode(m_pinIN3, OUTPUT);//set the IN3 pin as OUTPUT
  pinMode(m_pinIN4, OUTPUT);//set the IN4 pin as OUTPUT
}

// Move stepper 'angle' degrees  
void TinyStepper::Move(float angle, uint8_t timedelay ) {
  int halfsteps = abs((int)(angle / step_angle));
  int inc = 1;
  if (angle < 0.0) {
    inc = -1;
  }
  for (int j = 0; j < halfsteps; j++) {
    phase = phase + (inc);
    if (phase < 0) phase = 7;
    if (phase > 7) phase = 0;
    SetPhase(phase);
    delay(timedelay);
  }
}

// Move stepper 'angle' degrees and acceleration and decelleration 
void TinyStepper::AccelMove(float angle, uint8_t timedelaymin, uint8_t timedelaymax ) {
  int halfsteps = abs((int)(angle / step_angle));
  int d;
  int inc = 1;
  if (angle < 0) {
    inc = -1;
  }
  for (int j = 0; j < halfsteps; j++) {
    phase = phase + (inc);
    if (phase < 0) phase = 7;
    if (phase > 7) phase = 0;
    SetPhase(phase);
    d = (DelayCurve(timedelaymin, timedelaymax, ((float)j/(float)halfsteps)));
    delay(d);
  }
}

// Calculate an acceleration curve - basic sin(x) ramp up and down for first and last 25% of cycle
int TinyStepper::DelayCurve(uint8_t minvalue, uint8_t maxvalue, float percentage) {
  float rad;
  char delta = maxvalue - minvalue;
  if(percentage >= 0.25 && percentage <= 0.75) return(minvalue);
  if(percentage < 0.25) rad = (PI/2.0) * (4.0 * percentage);
  if(percentage > 0.75 && percentage <= 1.0) rad = (PI/2.0) + ((percentage-0.75)*4.0)*(PI/2.0);
  
  return(minvalue + delta - (delta * sin(rad)));
}

// Removes power from motor - free spin
void TinyStepper::Disable() {
  digitalWrite(m_pinIN1, 0);
  digitalWrite(m_pinIN2, 0);
  digitalWrite(m_pinIN3, 0);
  digitalWrite(m_pinIN4, 0);
}

// Set motor to current phase - locked
void TinyStepper::Enable() {
  SetPhase(phase);
}

// Activate stepper motor to transition to state defined by phase map
void TinyStepper::SetPhase(int8_t p) {
  phase = p;
  if (phase < 0) phase = 7;
  if (phase > 7) phase = 0;
  digitalWrite(m_pinIN1, ((phase_map[phase] & 0x01) == 0x01 ? true : false));
  digitalWrite(m_pinIN2, ((phase_map[phase] & 0x02) == 0x02 ? true : false));
  digitalWrite(m_pinIN3, ((phase_map[phase] & 0x04) == 0x04 ? true : false));
  digitalWrite(m_pinIN4, ((phase_map[phase] & 0x08) == 0x08 ? true : false));
}

