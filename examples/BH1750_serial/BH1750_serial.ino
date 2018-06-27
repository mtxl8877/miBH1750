/*
 * Read the Light Intensity value from BH1750-GY30 module, then send the result via serial line
 * Copyright 2018 Nguyen Trong Nghia <mtxl8877@gmail.com>
 * 
 * ALWAYS connect the module to 3.3V power supply ONLY
 */

#include <miBH1750.h>

#define adrPin 2 //connect the ADD pin on device to pin 2 on Arduino, you can choose any other pin

BH1750 sensor(adrPin, addr_H, cont_H_res);
uint16_t val; 

void setup() {
  Serial.begin(9600); //open serial connection to report result to host
  Serial.println("Starting..."); 
  delay(10);
  sensor.Init(); //initialize the device
  Serial.println("Finish initilization, begin measuring: ");   
}

void loop() {
  val = sensor.GetLightIntensity(); //get the light intensity value
  Serial.println(val); //report to host
  delay(1000);
}
