#include <PCA9505_9506.h>

/*
 *  Interrupt for the PCA9505/06 I/O expander. Attaching an interrupt 
 *  to pin 0. Interrupt is LOW when the status of the pin has changed
 *  and the interrupt will clear when the status returns to original
 *  condition or if the port has been read. clearInterrupt() can be
 *  used.
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
 
 #define INT_PIN	2

PCA9505_06 GPIO;

volatile byte state = LOW;

void setup() {
  GPIO.begin();   //  Default address 0x20
  GPIO.pinMode(0, INPUT);
  GPIO.setPinInterrupt(0);        // Enable interrupt on pin 0
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(INT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INT_PIN), blink, LOW);
}

void loop() {
  digitalWrite(LED_BUILTIN, state);
}

void blink() {
  state = !state;
}