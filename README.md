# Tiny Stepper #

[![arduino-library-badge](https://www.ardu-badge.com/badge/TinyStepper.svg?)](https://www.ardu-badge.com/TinyStepper)
[![Build Status](https://travis-ci.org/jasonacox/TinyStepper.svg?branch=master)](https://travis-ci.org/jasonacox/TinyStepper)

Arduino library to drive stepper motors. Small and easy to use.

## Description ##

Simple library to drive a 4-phase stepper motor using simple Move(), AccelMove() and Disable() functions. Works well with 28BYJ-48 stepper motor and UNL2003 module. Focus is on controlling steppers with basic Move(x) commands where x is positive or negative value (in degrees). Uses half-step for more torque and smoother motion.

## Hardware ##

A Stepper Motor is typically driven by a ULN2003A which provides an array of seven NPN Darlington transistors capable of 500 mA, 50 V output, great for driving inductive loads like a motor.

![28BYJ-48](examples/Stepper28BYJ-48.png)

The stepper motor has 4 different position coils, ABCD.  In half step mode, you energize the adjacent coil before disengaging the previous coil.  The transition steps would be these 8 patterns: A, AB, B, BC, C, CD, D, DA:

```text
  Phase ABCD Coils
  0     1000  A
  1     1100  AB
  2     0100   B
  3     0110   BC
  4     0010    C
  5     0011    CD
  6     0001     D
  7     1001  A  D
```

The ABCD coils map to IN1, IN2, IN3, and IN4 that will be connected to the Arduino digital outputs.

Power Note: You should not drive the stepper motor power with the Arduino.  The power to the UNL2003 module should come from the main power adapter that also feeds the Arduino.

## Installation ##

This library is available via the Arduino IDE.  Install this library via `Tools`, `Manage Libraries`, search for "TinyStepper" and click `Install`.

You can also install the latest version manually by cloning this repo into your Arduino library folder (e.g. `~/Documents/Arduino/libraries`).  

## Usage ##

The library provides a single class named TinyStepper with the following functions:

* `Move` - Move the stepper motor specified in degrees (positive or negative)
* `AccelMove` - Move the stepper motor specified in degrees but accelerate and decelerate.
* `Enable` - Enable/lock the stepper motor 
* `Disable` - Disable/unlock the stepper motor (free spin)


## Example Code ##

```cpp
#include <TinyStepper.h>

// Define Arduino Pin Outputs
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define HALFSTEPS 4096  // Number of half-steps for a full rotation

// Init the TinyStepper Class
TinyStepper stepper(HALFSTEPS, IN1, IN2, IN3, IN4);

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
```

Refer to [TinyStepper.h](src/TinyStepper.h) for information on available functions. See also [Examples](examples) for more demonstration.

