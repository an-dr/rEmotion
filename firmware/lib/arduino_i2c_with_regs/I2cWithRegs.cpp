#include "I2cWithRegs.h"
#include <Wire.h>

#define DEBUG 0

#if DEBUG
#warning "In debug mode I2cWithRegs works non-stable"
#define LOG(...) (printf(__VA_ARGS__))
#else
#define LOG(...)
#endif

I2cWithRegs::I2cWithRegs(uint32_t address, uint32_t regs_num, void * requestEvent, void * receiveEvent) {
    Init(address, regs_num, requestEvent, receiveEvent);
}

void I2cWithRegs::Init(uint32_t address, uint32_t regs_num, void * requestEvent, void * receiveEvent) {
    this->addr = address;
    this->regs.Init(regs_num);
    Wire.begin((int)address);
    this->SetEvents(requestEvent, receiveEvent);
}

void I2cWithRegs::PrintRegsContent(void) {
#if DEBUG
    printf("Registers:");
    uint8_t *reg_arr = regs.GetRegs();
    for (uint32_t i = 0; i < regs.GetRegsAmmount(); i++) {
        printf(" %lx:0x%x", i, reg_arr[i]);
    }
    printf("\n");
#endif
}

void I2cWithRegs::SetEvents(void *requestEvent, void *receiveEvent) {
    Wire.onRequest((void (*)())requestEvent);    // register event
    Wire.onReceive((void (*)(int))receiveEvent); // register event
}

void I2cWithRegs::SelectReg(uint32_t num) {
    this->regs.SelectReg(num);
    LOG("[I2cWithRegs] Selected reg: 0x%lx\n", this->regs.GetSelectedRegNum());
}

void I2cWithRegs::SelectNextReg(void) {
    this->regs.SelectNextReg();
    LOG("[I2cWithRegs] Selected reg: 0x%lx\n", this->regs.GetSelectedRegNum());
}

void I2cWithRegs::SetReg(uint8_t byte) {
    this->regs.SetReg(byte);
    LOG("[I2cWithRegs] Wrote 0x%x to reg 0x%lx\n", byte, regs.GetSelectedRegNum());
}

void I2cWithRegs::SetRegAndNext(uint8_t byte) {
    this->SetReg(byte);
    this->SelectNextReg();
}

uint8_t I2cWithRegs::GetReg(void) {
    return this->regs.GetReg();
}

uint8_t I2cWithRegs::GetRegAndNext(void) {
    return this->regs.GetRegAndNext();
}

uint8_t I2cWithRegs::WriteReg(void) {
    uint8_t reg_val = this->regs.GetReg();
    Wire.write(&reg_val, (size_t)1);
    LOG("[I2cWithRegs] Sent: %x\n", reg_val);
    return reg_val;
}

uint8_t I2cWithRegs::WriteRegAndNext(void) {
    uint8_t reg_val = this->WriteReg();
    this->SelectNextReg();
    return reg_val;
}

uint8_t I2cWithRegs::ReadToReg(void) {
    uint8_t val = Wire.read();
    regs.SetReg(val);
    return val;
}

uint8_t I2cWithRegs::ReadToRegAndNext(void) {
    uint8_t val = this->ReadToReg();
    this->SelectNextReg();
    return val;
}

void I2cWithRegs::Set(uint32_t reg_number, uint8_t value){
    if(reg_number>= this->regs.GetRegsAmmount()){
        return;
    } else{
        uint8_t *reg_arr = this->regs.GetRegs();
        reg_arr[reg_number] = value;
    }
}
uint8_t I2cWithRegs::Get(uint32_t reg_number){
    if(reg_number>= this->regs.GetRegsAmmount()){
        return 0;
    } else{
        uint8_t *reg_arr = this->regs.GetRegs();
        return reg_arr[reg_number];
    }
}
void I2cWithRegs::Print(void){
    printf("Registers:");
    uint8_t *reg_arr = this->regs.GetRegs();
    for (uint32_t i = 0; i < this->regs.GetRegsAmmount(); i++) {
        printf(" %lx:0x%x", i, reg_arr[i]);
    }
    printf("\n");
}

void I2cWithRegs::requestEvent(I2cWithRegs & i2c_instance) {
    i2c_instance.WriteRegAndNext();
}

void I2cWithRegs::receiveEvent(I2cWithRegs & i2c_instance) {
    uint32_t reg_num = (uint32_t)Wire.read();
    i2c_instance.SelectReg(reg_num); // set reg num

    if(Wire.available()){ // if extra data
        while (Wire.available()) { // if we have a multiple bytes
            i2c_instance.ReadToRegAndNext();
        }
    }
}

