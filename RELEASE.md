# Release Notes for TinyStepper

## v1.2.0 - Enable Fix

- Moved pin initialization to `Enable()` function and added `Begin()` as alias.
- Either `Enable()` or `Begin()` should be called at least once in `setup()` to initialize pins and stepper motors.

## v1.1.0 - Example Sketches

Updated and added example Arduino sketches:

- TinyStepper-Test - Basic Test
- ATtiny85 Test - Simple single stepper example tested with an ATtiny85
- Laser Gimbal - A two stepper gimbal for a laser pointer
- Robotic Arm - A three stepper robotic arm

## v1.0.0

- Initial Release.
