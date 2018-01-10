#include <PCA9505_9506.h>

/*
 *  Output PWM for the PCA9505/06 I/O expander using output enable
 *  PWM signal sent from digital pin 9 of the arduino to the output
 *  enable (OE) pin on PCA9505/06.
 *
 *  Note:
 *		PCA9506 has no pull up resistors.
 *  	The 100k pullup resistors on the PCA9505 aren't configurable
 *		All IO is default as INPUT
 *  
 *  Addressing 0x20 plus:
 *    A0: 001 - 0x01
 *    A1: 010 - 0x02
 *    A2: 100 - 0x04
 *    
 */
#define PWM_PIN		9	// Connect Pin 9 of Arduino to OE pin of PCA9505/06

PCA9505_06 GPIO;

void setup() {
  GPIO.begin();   //  Default address 0x20
  GPIO.ioMode((IOPORTS){0xFF, 0xFF, 0xFF, 0xFF, 0xFF});            // Set all pins as outputs
  GPIO.digitalIOWrite((IOPORTS){0xFF, 0xFF, 0xFF, 0xFF, 0xFF});    // Set all pins HIGH
}

void loop() {
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue++) {
    analogWrite(PWM_PIN, fadeValue);
    delay(2);
  }
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue--) {
    analogWrite(PWM_PIN, fadeValue);
    delay(2);
  }
}