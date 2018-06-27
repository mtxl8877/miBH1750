/*
 * Read the Light Intensity value from BH1750-GY30 module, then display the result on LCD
 * Copyright 2018 Nguyen Trong Nghia <mtxl8877@gmail.com>
 * 
 * ALWAYS connect the module to 3.3V power supply ONLY
 */

#include <miBH1750.h>
#include <LiquidCrystal_I2C.h>

#define adrPin 2 //connect the ADD pin on device to pin 2 on Arduino, you can choose any other pin

LiquidCrystal_I2C lcd(0x3f, 20, 4); //set-up the lcd at address 0x3f and type 20 collumns + 4 rows using PCF8574A
BH1750 sensor(adrPin, addr_H, cont_H_res);
uint16_t val; 

void setup() {
  lcd.init(); 
  lcd.backlight();
  lcd.home();
  lcd.print("Device testing");
  lcd.setCursor(0,1);
  lcd.print("Light intensity");
  lcd.setCursor(0,2);
  lcd.print("Module BH1750-GY30");
  lcd.setCursor(0,3);
  lcd.print("By Nguyen T. Nghia");
  delay(4000);
  lcd.clear();
  lcd.print("Starting device...");
  delay(100);
  
  sensor.Init(); //initialize the device   
  
  lcd.setCursor(0,1);
  lcd.print("Finish Initializing");
  lcd.setCursor(0,2);
  lcd.print("Begin measuring now");
  delay(4000);
}

void loop() {
  val = sensor.GetLightIntensity(); //get the light intensity value
  lcd.clear();
  lcd.print("Measurement result:");
  lcd.setCursor(3,1);
  lcd.print(val, DEC); //show the value in decimal form on LCD
  lcd.setCursor(9,1);
  lcd.print("Lux");
  delay(1000);
}
