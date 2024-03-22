#include "i2c.h"

I2cWithRegs i2c;

void i2c_reqEv() { I2cWithRegs::requestEvent(i2c); }
void i2c_rcvEv(int howMany) { I2cWithRegs::receiveEvent(i2c); }
