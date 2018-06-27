/**
* BH1750FVI Digital Ambient Light Sensor Library
* Created in 2018 by Nguyen Trong Nghia <mtxl8877@gmail.com>, based on previous work of Mohannad Rawashdeh <www.genotronex.com>
* Manage to communicate between Sensor and Arduino through I2C Interface, SDA and SCL pins are needed
* Pin cofinguratuon on Sensor module:
    VCC: Power supply pin, need 3.3V
    SCL: CLOCK pin of I2C, pin A5 on Uno R3 and Nano / pin 21 on Mega250 or ADK
    SDA: DATA pin of I2C, pin A4 on Uno R3 and Nano / pin 20 on Mega2560 or ADK
    ADD: Choose address of the module, 0x23 if connect to GND / 0x5C if connect to VCC
    GND: Ground pin
**/

#ifndef MIBH1750_H
#define MIBH1750_H

#include "Arduino.h"
#include "Wire.h"

//Define the address of device on I2C communication
#define addr_L          0x23 //Device's address when ADD pin connected to GND
#define addr_H          0x5C //Device's address when ADD pin connected to VCC

//Define the commands to communicate with device, taken from datasheet
#define power_down      0x00 //Waiting for measurement command
#define power_on        0x01 //No active state
#define reset           0x07 //Reset data registger value, this command is not acceptable in Power down mode
#define cont_H_res      0x10 //Start measurement at 1Lux resolution, need typically 120ms to measure
#define cont_H_res_2    0x11 //Start measurement at 0.5Lux resolution, need typically 120ms to measure
#define cont_L_res      0x13 //Start measurement at 4Lux resolution, need typically 16ms to measure
#define oneTime_H_res   0x20 //Start measurement at 0.5Lux resolution, need typically 120ms to measure, automatically set device to Power down mode after measuring
#define oneTime_H_res_2 0x21 //Start measurement at 0.5Lux resolution, need typically 120ms to measure, automatically set device to Power down mode after measuring
#define oneTime_L_res   0x23 //Start measurement at 4Lux resolution, need typically 16ms to measure, automatically set device to Power down mode after measuring

class BH1750{
public:
    BH1750(byte addrPin, byte addrVal, byte mode);
    void Init();
    void Shut_down();
    void Reset();
    unsigned int GetLightIntensity();
private:
    byte _addrPin;
    byte _addrVal;
    byte _mode;
    boolean state;
    void send_data(byte data);
};

#endif // MIBH1750_H
