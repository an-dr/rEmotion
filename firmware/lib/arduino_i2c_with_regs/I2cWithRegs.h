#pragma once

#include "VirtualRegs.h"
#include <stdint.h>

class I2cWithRegs {
private:
    uint32_t addr;
    VirtualRegs regs;
    void SelectReg(uint32_t num);
    void SelectNextReg(void);
    void SetReg(uint8_t byte);
    void SetRegAndNext(uint8_t byte);
    uint8_t GetReg(void);
    uint8_t GetRegAndNext(void);
    uint8_t WriteReg(void);
    uint8_t WriteRegAndNext(void);
    uint8_t ReadToReg(void);
    uint8_t ReadToRegAndNext(void);
    void PrintRegsContent(void);

public:
    I2cWithRegs() = default;
    I2cWithRegs(uint32_t address, uint32_t regs_num, void * requestEvent, void * receiveEvent);
    void Init(uint32_t address, uint32_t regs_num, void * requestEvent, void * receiveEvent);
    void SetEvents(void *requestEvent, void *receiveEvent);
    void Set(uint32_t reg_number, uint8_t value);
    uint8_t Get(uint32_t reg_number);
    void Print(void);
    static void requestEvent(I2cWithRegs & i2c_instance);
    static void receiveEvent(I2cWithRegs & i2c_instance);
};
