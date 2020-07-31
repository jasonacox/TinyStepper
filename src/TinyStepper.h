//  TinyStepper
//  Arduino tiny library for stepper motors
//
//  Author: Jason A. Cox - @jasonacox - https://github.com/jasonacox
//  Date: 19 July 2020
//

#ifndef __TINYSTEPPER__
#define __TINYSTEPPER__

class TinyStepper {

public:
  //! Initialize a TinyStepper object, setting the number of half steps for a revolution and
  //! data pins.
  //!
  //! @param halfsteps - The number of halfsteps for a full revolution (360 degrees)
  //! @param IN1 - The number of the digital pin connected to the IN1 of the ULN2003
  //! @param IN2 - The number of the digital pin connected to the IN2 of the ULN2003
  //! @param IN3 - The number of the digital pin connected to the IN3 of the ULN2003
  //! @param IN4 - The number of the digital pin connected to the IN4 of the ULN2003
  TinyStepper(uint16_t halfsteps, uint8_t IN1, uint8_t IN2, uint8_t IN3, uint8_t IN4);

  //! Move the stepper motor forward or backward specified in degrees (float).
  //!
  //! @param angle - Positive or negative number of degrees to move
  //! @param timedelay - Time in milliseconds to wait for each step (default=1)
  void Move(float angle, uint8_t timedelay = 1 );

  //! Move the stepper motor forward or backward specified in degrees but do so by accelerating
  //! decelerate the motion to create a smoother transition.
  //!
  //! Acceleration happens during first 25% of movement, full speed next 50% and decelerate
  //! happens the last 25%.
  //!
  //! @param angle - Positive or negative number of degrees to move
  //! @param timedelaymin - Time in milliseconds to wait for each step (default=1) at max speed
  //! @param timedelaymax - Time in milliseconds to wait for each step (default=10) at min speed
  void AccelMove(float angle, uint8_t timedelaymin = 1, uint8_t timedelaymax = 10);

  //! Disable stepper motor - remove power and allow free spin
  //!
  //! Removing power will allow the stepper motor to move on its own.  It will not be locked.
  void Disable();

  //! Enable stepper motor - lock stepper motor to current phase
  //!
  //! Stepper motor will be locked until sent a Move command.
  void Enable();

  //! Activate stepper motor and transition to state defined by phase map
  //!
  //! The stepper motor has 4 different position coils, ABCD.  In half step mode, you energize the adjacent coil before
  //! disengaging the previous coil.  The transition steps would be these 8 patterns: A, AB, B, BC, C, CD, D, DA
  //!
  //!   Phase ABCD Coils
  //!   0     1000  A
  //!   1     1100  AB
  //!   2     0100   B
  //!   3     0110   BC
  //!   4     0010    C
  //!   5     0011    CD
  //!   6     0001     D
  //!   7     1001  A  D
  //!
  //! @param phase The phase to transition to for the stepper motor (default=0)
  void SetPhase(int8_t p = 0);

protected:

   // Calculate an acceleration curve - basic sin(x) ramp up and down for first and last 25% of cycle
   int DelayCurve(uint8_t minvalue, uint8_t maxvalue, float percentage);

private:
	uint8_t m_pinIN1;
	uint8_t m_pinIN2;
	uint8_t m_pinIN3;
	uint8_t m_pinIN4;
	int8_t phase;
	uint16_t steps;
  float step_angle;
};

#endif // __TINYSTEPPER__
