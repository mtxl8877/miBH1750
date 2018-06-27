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

#include "miBH1750.h"

//Set-up the default constructor
//aadrPin: the pin on Arduino connected with ADD pin on device
//addrVal: address of the device, choose between addr_H and addr_L
//mode: measuring mode, there're 6 modes, 3 continuous and 3 one-time
BH1750::BH1750(byte addrPin, byte addrVal, byte mode){
    _addrPin=addrPin;

    //Choose address of the device
    switch(addrVal){
    case addr_H:
        _addrVal=addr_H; //Address is 0x5C
        state=true;
        break;
    case addr_L:
        _addrVal=addr_L; //Address is 0x23
        state=false;
        break;
    }

    //Choose the measurement mode
    switch(mode){
    case cont_H_res:
        _mode=cont_H_res; //Continuous High Resolution mode <1Lux>
        break;
    case cont_H_res_2:
        _mode=cont_H_res_2; //Continuous High Resolution mode 2 <0.5Lux>
        break;
    case cont_L_res:
        _mode=cont_L_res; //Continuous Low Resolution mode <4Lux>
        break;
    case oneTime_H_res:
        _mode=oneTime_H_res; //One-time High Resolution mode <1Lux>
        break;
    case oneTime_H_res_2:
        _mode=oneTime_H_res_2; //One-time High Resolution mode 2 <0.5Lux>
        break;
    case oneTime_L_res:
        _mode=oneTime_L_res; //One-time Low Resolution mode <4Lux>
        break;
    }
};

/** Public methods **/

//Initialize the device to use
void BH1750::Init(){
    Wire.begin();
    pinMode(_addrPin, OUTPUT);
    if(state==true)
        digitalWrite(_addrPin, HIGH); //Set the ADD pin state to High, mean device address is 0x5C
    else if(state==false)
        digitalWrite(_addrPin, LOW); //Set the ADD pin state to Low, mean device address is 0x23

    send_data(power_on); //Wake the device up, waiting for measument command
    delay(10);
    send_data(reset); //Clear the data register value on device, can't operate in Shut-down mode
    delay(10);
    send_data(_mode); //Send the measurement mode instruction to device
    delay(180);
};

//Read measurement result and calculate the data
unsigned int BH1750::GetLightIntensity(){
    unsigned int val;
    Wire.beginTransmission(_addrVal);
    Wire.requestFrom(_addrVal, 2); //Request the measurement result, the data's contained in 2 bytes
    val=Wire.read(); //Receive the High byte
    val<<=8; //Create a 16bit register to add the Low byte
    val|=Wire.read(); //Receive the Low byte
    Wire.endTransmission();
    val=val/1.2; //Calculate the data
    return val; //Return the calculated Light Intensity value
}

//Clear the data register
void BH1750::Reset(){
    send_data(power_on);
    send_data(reset);
    delay(10);
};

//Turn off the device
void BH1750::Shut_down(){
    send_data(power_down);
};

/** Pivate method **/

//Transmit data on I2C bus from Arduino to device
void BH1750::send_data(byte data){
    Wire.beginTransmission(_addrVal);
    Wire.write(data);
    Wire.endTransmission();
};
