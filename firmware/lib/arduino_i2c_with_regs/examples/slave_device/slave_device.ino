#include "I2cWithRegs.h"

int i2c_address = 0x30;
int i2c_regs_ammount = 8;

I2cWithRegs i2c;

void i2c_reqEv() { I2cWithRegs::requestEvent(i2c); }
void i2c_rcvEv(int howMany) { I2cWithRegs::receiveEvent(i2c); }

void setup() {
  i2c.Init(i2c_address, i2c_regs_ammount, (void *)i2c_reqEv, (void *)i2c_rcvEv);

}

void loop() {
  // put your main code here, to run repeatedly:

}
