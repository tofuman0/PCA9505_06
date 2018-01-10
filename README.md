# PCA9505 / PCA9506 Arduino Library
Arduino library for the 40bit PCA9505/06 I2C IO Expander
 
These chips use I2C to communicate, and have interupt, reset and output enable controls. A 3bit
configurable addressing is supported ranging from 0x20 to 0x27 enabling upto 8 40bit IO on one bus.

The PCA9505 has internal 100k pullup resistors where as the PCA9506 does not. This is the only difference
between the 2 chips.

The chip operates between 2.3v and 5.5v. All IO are 5.5v tolerant.

All IO are defaulted as inputs on power on.

Output enable disables outputs on ALL IO configured as outputs and could be used to send an PWM signal
to dim LED's connected to outputs.

Interupt is active LOW when a pin's state has changed.
