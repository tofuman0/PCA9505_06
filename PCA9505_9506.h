/************************************************************** 
  This is a library for the PCA9505/06 40bit i2c port expander
 *************************************************************/

#ifndef _PCA9505_H_
#define _PCA9505_H_
#include <Wire.h>

class PCA9505_06 {
public:
  void begin(uint8_t addr);
  void begin(void);

  void pinMode(uint8_t p, uint8_t d);
  uint8_t getPinMode(uint8_t p);
  void portMode(uint8_t port, uint8_t d);
  uint8_t getPortMode(uint8_t port);
  void ioMode(uint8_t io0, uint8_t io1, uint8_t io2, uint8_t io3, uint8_t io4);
  uint64_t getIoMode();

  void digitalWrite(uint8_t p, uint8_t d);
  void digitalPortWrite(uint8_t p, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
  void digitalIOWrite(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4);

  uint8_t digitalRead(uint8_t p);
  uint8_t digitalPortRead(uint8_t port);
  uint64_t digitalIORead();
 
  void setPinInterrupt(uint8_t p);
  void setPortInterrupt(uint8_t port, uint8_t flags);
  void setIOInterrupt(uint8_t flags0, uint8_t flags1, uint8_t flags2, uint8_t flags3, uint8_t flags4);
  void clearInterrupt();
  void setPolarity(uint8_t port, uint8_t flags);
  void setPolarities(uint8_t flags0, uint8_t flags1, uint8_t flags2, uint8_t flags3, uint8_t flags4);

private:
  uint8_t getPort(uint8_t p);
  uint8_t getBit(uint8_t p);
  uint8_t i2caddr;
};

#define PCA9505_AI_ON				0x80
#define PCA9505_AI_OFF				0x00

// Addressing
#define PCA9505_BASE_ADDRESS		0x20
#define PCA9505_A0					0x01
#define PCA9505_A1					0x02
#define PCA9505_A2					0x04

// Registers
#define PCA9505_IP0					0x00
#define PCA9505_IP1					0x01
#define PCA9505_IP2					0x02
#define PCA9505_IP3					0x03
#define PCA9505_IP4					0x04
#define PCA9505_OP0					0x08
#define PCA9505_OP1					0x09
#define PCA9505_OP2					0x0A
#define PCA9505_OP3					0x0B
#define PCA9505_OP4					0x0C
#define PCA9505_PI0					0x10
#define PCA9505_PI1					0x11
#define PCA9505_PI2					0x12
#define PCA9505_PI3					0x13
#define PCA9505_PI4					0x14
#define PCA9505_IOC0				0x18
#define PCA9505_IOC1				0x19
#define PCA9505_IOC2				0x1A
#define PCA9505_IOC3				0x1B
#define PCA9505_IOC4				0x1C
#define PCA9505_MSK0				0x20
#define PCA9505_MSK1				0x21
#define PCA9505_MSK2				0x22
#define PCA9505_MSK3				0x23
#define PCA9505_MSK4				0x24

#endif