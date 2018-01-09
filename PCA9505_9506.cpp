/************************************************************** 
  This is a library for the PCA9505/06 40bit i2c port expander
 *************************************************************/

#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif
#include "PCA9505_9506.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

void PCA9505_06::begin(uint8_t addr) {
	i2caddr = addr;

	Wire.begin();
	
	setIOInterrupt(
		0xFF /* Port 0 */,
		0xFF /* Port 1 */,
		0xFF /* Port 2 */,
		0xFF /* Port 3 */,
		0xFF /* Port 4 */
	);
	
	setPolarities(
		0x00 /* Port 0 */,
		0x00 /* Port 1 */,
		0x00 /* Port 2 */,
		0x00 /* Port 3 */,
		0x00 /* Port 4 */
	);
}

void PCA9505_06::begin(void) {
	begin(PCA9505_BASE_ADDRESS);
}

uint8_t PCA9505_06::getPort(uint8_t p) {
	return (p % 8) / 40;
}

uint8_t PCA9505_06::getBit(uint8_t p) {
	return p % 8;
}

void PCA9505_06::pinMode(uint8_t p, uint8_t d) {
	uint8_t command = (PCA9505_IOC0 + getPort(p)) | PCA9505_AI_OFF;
	uint8_t set = 0;
	
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.endTransmission();
	
	Wire.requestFrom(i2caddr, 1);
	set = Wire.read();
	
	bitWrite(set, getBit(p), d ? 0 : 1);

	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.write(set);
	Wire.endTransmission();
}

uint8_t PCA9505_06::getPinMode(uint8_t p) {
	uint8_t command = (PCA9505_IOC0 + getPort(p)) | PCA9505_AI_OFF;
	
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.endTransmission();
	
	Wire.requestFrom(i2caddr, 1);
	
	return (Wire.read() & (1 << getBit(p))) ? INPUT : OUTPUT;
}

void PCA9505_06::portMode(uint8_t port, uint8_t d) {
	uint8_t command = (PCA9505_IOC0 + (port % 5)) | PCA9505_AI_OFF;
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.write(d ? 0x00 : 0xFF);
	Wire.endTransmission();
}

uint8_t PCA9505_06::getPortMode(uint8_t port) {
	uint8_t command = (PCA9505_IOC0 + (port % 5)) | PCA9505_AI_OFF;
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.endTransmission();
	
	Wire.requestFrom(i2caddr, 1);
	
	return Wire.read();
}

void PCA9505_06::ioMode(uint8_t io0, uint8_t io1, uint8_t io2, uint8_t io3, uint8_t io4) {
	uint8_t command = PCA9505_IOC0 | PCA9505_AI_ON;
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.write(~io0);
	Wire.write(~io1);
	Wire.write(~io2);
	Wire.write(~io3);
	Wire.write(~io4);
	Wire.endTransmission();
}

uint64_t PCA9505_06::getIoMode() {
	uint8_t command = PCA9505_IOC0 | PCA9505_AI_ON;
	uint64_t result = 0;
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.endTransmission();
	
	Wire.requestFrom(i2caddr, 5);
	
	result |=  Wire.read();
	result = result << 8;
	result |=  Wire.read();
	result = result << 8;
	result |=  Wire.read();
	result = result << 8;
	result |=  Wire.read();
	result = result << 8;
	result |=  Wire.read();
	result = result << 8;
	
	return result;
}

void PCA9505_06::digitalWrite(uint8_t p, uint8_t d) {
	uint8_t command = (PCA9505_OP0 + getPort(p)) | PCA9505_AI_OFF;
	uint8_t set = 0;
	
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.endTransmission();
	
	Wire.requestFrom(i2caddr, 1);
	set = Wire.read();
	
	bitWrite(set, getBit(p), d);

	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.write(set);
	Wire.endTransmission();
}

void PCA9505_06::digitalPortWrite(uint8_t p, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
	uint8_t command = (PCA9505_OP0 + getPort(p)) | PCA9505_AI_OFF;
	uint8_t set = 0;
	
	bitWrite(set, 0, d0 & 0x01);
	bitWrite(set, 1, d1 & 0x01);
	bitWrite(set, 2, d2 & 0x01);
	bitWrite(set, 3, d3 & 0x01);
	bitWrite(set, 4, d4 & 0x01);
	bitWrite(set, 5, d5 & 0x01);
	bitWrite(set, 6, d6 & 0x01);
	bitWrite(set, 7, d7 & 0x01);

	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.write(set);
	Wire.endTransmission();
}

void PCA9505_06::digitalIOWrite(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4) {
	uint8_t command = PCA9505_OP0 | PCA9505_AI_ON;

	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.write(p0);
	Wire.write(p1);
	Wire.write(p2);
	Wire.write(p3);
	Wire.write(p4);
	Wire.endTransmission();
}

uint8_t PCA9505_06::digitalRead(uint8_t p) {	
	uint8_t command = (PCA9505_IP0 + getPort(p)) | PCA9505_AI_OFF;
	
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.endTransmission();
	
	Wire.requestFrom(i2caddr, 1);
	return (Wire.read() & (1 << getBit(p))) ? HIGH : LOW;
}

uint8_t PCA9505_06::digitalPortRead(uint8_t p) {
	uint8_t command = (p % 5) | PCA9505_AI_OFF;
	
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.endTransmission();
	
	Wire.requestFrom(i2caddr, 1);
	return Wire.read();
}
  
uint64_t PCA9505_06::digitalIORead() {
	uint8_t command = PCA9505_IP0 | PCA9505_AI_ON;
	uint64_t result = 0;
	
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.endTransmission();
	
	Wire.requestFrom(i2caddr, 5);
	result |= Wire.read();
	result = result << 8;
	result |= Wire.read();
	result = result << 8;
	result |= Wire.read();
	result = result << 8;
	result |= Wire.read();
	result = result << 8;
	result |= Wire.read();
	result = result << 8;
	return result;
}

void PCA9505_06::setPinInterrupt(uint8_t p) {
	uint8_t command = (PCA9505_MSK0 + getPort(p)) | PCA9505_AI_OFF;
	uint8_t set = 0;
	
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.endTransmission();
	
	Wire.requestFrom(i2caddr, 1);
	set = Wire.read();
	
	bitWrite(set, getBit(p), 0);

	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.write(set);
	Wire.endTransmission();
}

void PCA9505_06::setPortInterrupt(uint8_t port, uint8_t flags) {
	uint8_t command = (PCA9505_MSK0 + (port % 5)) | PCA9505_AI_OFF;
	
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.write(flags);
	Wire.endTransmission();
}

void PCA9505_06::setIOInterrupt(uint8_t flags0, uint8_t flags1, uint8_t flags2, uint8_t flags3, uint8_t flags4) {
	uint8_t command = PCA9505_MSK0 | PCA9505_AI_ON;
	
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.write(flags0);
	Wire.write(flags1);
	Wire.write(flags2);
	Wire.write(flags3);
	Wire.write(flags4);
	Wire.endTransmission();
}

void PCA9505_06::clearInterrupt() {
	uint8_t command = PCA9505_IP0 | PCA9505_AI_ON;
	
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.endTransmission();
	
	Wire.requestFrom(i2caddr, 5);
	Wire.read();
	Wire.read();
	Wire.read();
	Wire.read();
	Wire.read();
}

void PCA9505_06::setPolarity(uint8_t port, uint8_t flags) {
	uint8_t command = (PCA9505_PI0 + (port % 5)) | PCA9505_AI_OFF;
	
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.write(flags);
	Wire.endTransmission();
}

void PCA9505_06::setPolarities(uint8_t flags0, uint8_t flags1, uint8_t flags2, uint8_t flags3, uint8_t flags4) {
	uint8_t command = PCA9505_PI0 | PCA9505_AI_ON;
	
	Wire.beginTransmission(i2caddr);
	Wire.write(command);
	Wire.write(flags0);
	Wire.write(flags1);
	Wire.write(flags2);
	Wire.write(flags3);
	Wire.write(flags4);
	Wire.endTransmission();
}