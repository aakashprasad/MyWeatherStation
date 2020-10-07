/*This is Aakash's Weather Station's sketch
 * This the first arduino project that I have made, I hope you like it :-}
 * To build this project you need:
 * Arduino Uno/Arduino Mega
 * 3.5 inch TFT Display
 * DHT11 sensor-Temperature and Humidity sensor
 * MQ2 sensor-Gas sensor checks for lpg,co and smoke concentration in the air
 * The connections are as follows:
 * LCD Reset-RESET, LCD CS-A3, LCD RS-A2,LCD WR-A1, LCD RD-A0
 * LCD D0-8,LCD D1-9,LCD D2-2, LCD D3-3, LCD D4-4, LCD D5-5, LCD D6-6, LCD D7-7
 * CONNECT DATA PIN OF DHT11 TO A4
 * CONNECT AO PIN OF MQ2 TO A5
 */
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>// library for 3.5 inch tft
#include <dht.h>//library for dht11- temperature and humidity sensor
#include <MQ2.h>//library for mq2- gas sensor which checks for lpg, carbon monoxide and smoke

#define  BLACK   0x0000    /*definitions for color hex values*/
#define CYAN    0x07FF
#define WHITE   0xFFFF
#define tempAndHumDataPin A4 // defining  data pin for dht11
#define gasDataPin A5//defining data pin for mq2



MCUFRIEND_kbv tft;
dht dhtDevice;
MQ2 mq2(gasDataPin);

void disp()// this function displays the static parts of the screen
{
  tft.begin(0x9486);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(20, 0);
  tft.println("Aakash's Weather Station");
  tft.setTextSize(3);
  tft.setCursor(0,50);
  tft.println("Temp:");
  tft.setTextSize(2);
  tft.setCursor(0,200);
  tft.println("Humidity:");
  tft.setCursor(0,250);
  tft.println("Indoor Pollution:");
  tft.setCursor(0,280);
  tft.setTextSize(2);
  tft.print("CO:");
  tft.setTextSize(1);
  tft.print("        PPM");
  tft.setTextSize(2);
  tft.setCursor(130,280);
  tft.print("Smoke:");
  tft.setTextSize(1);
  tft.print("        PPM");
}
void senseTempAndHum()//senses temperature and humidity using the dht11 sensor
{
  int readData = dhtDevice.read11(tempAndHumDataPin);
  float t = dhtDevice.temperature;
  float h = dhtDevice.humidity; 
  tft.setTextSize(3);
  tft.fillRect(130,35,135,45,BLACK);
  tft.setCursor(150,50);
  tft.print(t);
  tft.fillRect(130,190,135,45,BLACK);
  tft.setCursor(150,200);
  tft.print(h);


}
void senseGas()//senses concentration of co and smoke in the air using mq2 sensor
{
  int co, smoke;
  float* values= mq2.read(false); 
  co = mq2.readCO();
  smoke = mq2.readSmoke();
  tft.setCursor(35,280);
  tft.fillRect(35,280,45,30,BLACK);
  tft.setTextSize(2);
  tft.print(co);
  tft.setCursor(200,280);
  tft.fillRect(200,280,45,30,BLACK);
  tft.print(smoke);
  
}

void setup() { 
 mq2.begin();
 disp();

  

}

void loop() {
  senseTempAndHum();
  senseGas();
  delay(10000);

}
