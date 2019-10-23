
#include "DHT.h"
#include <LiquidCrystal.h>
//Set Pins for LCD Screen
LiquidCrystal lcd(22,23,5,18,19,21);

#define DHTPIN 25     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
char data_1[20];
char data_2[20] ;

void setup(){
    Serial.begin(115200);
    dht.begin();
    lcd.begin(16, 2);
}

void loop(){
  int soil = analogRead(36); //Read Soil moisture probe
  int  s = map(soil, 0, 3400, 0, 100); //Change soil moisture probe percentage level, this is what needs to be calibrated
  float h = dht.readHumidity(); //Read Humidity
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature(); //Read Temperature
    if (isnan(h) || isnan(t)) { //Check Sensor is working
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  lcd.clear(); //Clear previous readings
  int l = analogRead(39); //Read light sensor
  sprintf(data_1, "T:%.1f, H:%.1f %",t,h); //Convert sensor data to a String required for LCD
  lcd.print(data_1); //Display sensor data 
  lcd.setCursor(0,1);  //Sets cursor to second line of LCD screen
  sprintf(data_2, "S:%.1f %, L:%.1f %",s,l); //Convert remaining sensor data to a String
  lcd.print(data_2); //Diplay sensor data on line 2 of LCD
  delay(500); //Delay for 500milliseconds before taking sensor readings again and repeating process


}
