# Robotic Arm

![RoboticArm](RoboticArm.png)

Robotic Arm with 3 Stepper Motors based on Thingiverse project: <https://www.thingiverse.com/thing:2838859>

[Arduino Code](RobotArm.ino) for control board. Test cycles each stepper and then responds to user switches (up/down) for stepper motion.

* Arduino Microcontroller (e.g. Mega2560)
* 3 x 28BYJ-48 Stepper Motors
* 3 x ULN2003 Driver Board
* 6 x Microswitches
* 6 x 61k Ohm Resistors (pull up resistor for switches)
* 5V Power Supply (do not power steppers with Arduino)
