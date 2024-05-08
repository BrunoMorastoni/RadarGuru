//----------------------------------------GPS MODULE----------------------------------------//
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#define GPSBaud = 9600;                                                                     // This GPS module have a 9600 baud rate
TinyGPSPlus gps;                                                                            // The TinyGPSPlus object
#define RXPin 2                                                                             // Ports: RX=D3(0)
#define TXPin 0                                                                             // Ports: TX=D4(2)
SoftwareSerial ss(RXPin, TXPin);                                                            // The serial connection to the GPS device
//----------------------------------------DISPLAY MODULE----------------------------------------//
#include <Wire.h>
#include "SH1106Wire.h"                                                                         // Display SH1106 - 1.3 Inches  <switch to #include "SSD1306Wire.h" if you are using a SSD1306 128x64 display>
#include "OLEDDisplayUi.h"                                                                      // UI library
SH1106Wire display(0x3c, SDA, SCL);                                                             // Display object (ADDRESS, SDA(D2), SCL(D1)) <switch to 'SSD1306Wire display(0x3c, SDA, SCL);' if you are using a SSD1306 128x64 display>
OLEDDisplayUi ui( &display );                                                                   // UI object
//----------------------------------------BITMAP----------------------------------------//
// 'icon_satellite', 16x16px
const unsigned char bitmap_icon_satellite [] PROGMEM = {
	0x00, 0x00, 0x0c, 0x00, 0x3e, 0x08, 0x7c, 0x1c, 0x38, 0x3e, 0x50, 0x1f, 0x80, 0x0f, 0xc0, 0x07, 
	0xe0, 0x03, 0xf2, 0x15, 0xe6, 0x38, 0x54, 0x3c, 0x08, 0x78, 0x36, 0x70, 0x66, 0x20, 0x00, 0x00
};
//----------------------------------------BUTTONS----------------------------------------//
const byte BUT_1 = 12;                                                                   // Port D6
const byte BUT_2 = 13;                                                                   // Port D7
const byte BUT_3 = 15;                                                                   // Port D8
                                           
int BUT_1_STAT;                                                                          // Status variable, to know if is pressed or not
int BUT_2_STAT;                            
int BUT_3_STAT;                             
                                           
// BUTTON PREVIOUS                         
void previous(bool active = false) {                          
pinMode(BUT_1, INPUT_PULLUP);                                                            
if (BUT_1_STAT == LOW) {
  active = true;
  display.clear();
  ui.previousFrame();
  ui.update();
  }
  }
// BUTTON NEXT
void next(bool active = false) {
pinMode(BUT_2, INPUT_PULLUP);
if (BUT_2_STAT == LOW) { 
  active = true;
  display.clear();
  ui.nextFrame();
  ui.update();
   }
  }
// BUTTON SELECT
void select(bool active = false) {
  pinMode(BUT_3, INPUT_PULLUP);
  if (BUT_3_STAT == LOW) {
  active = true;
  display.clear();
  ui.update();
  }
}
//----------------------------------------SPEED FUNCTION----------------------------------------//
void fspeed() {
  String gps_speed = String(gps.speed.kmph(), 0);
  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 40, gps_speed); 

  // KM/H PRINT
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 48, "KM/H");
}
//----------------------------------------SATELLITES FUNCTION----------------------------------------//
void fsatellites() {
  String satellites = String(gps.satellites.value(), 3);
  display.drawXbm(112, 0, 16, 16, bitmap_icon_satellite);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(91,0,satellites);
}
//----------------------------------------ALTITUDE----------------------------------------//
void faltitude() {
  String altitude = String(gps.altitude.meters(), 2);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0,22,"ALT:");
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(25,22, altitude+" m");
}
//----------------------------------------LATITUDE AND LONGITUDE FUNCTION----------------------------------------//
void faltitude_longitude() {

  //LATITUDE//
  String latitude = String(gps.location.lat(), 6);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0,0,"LAT:");
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(25,0,latitude);

  //LONGITUDE//
  String longitude = String(gps.location.lng(), 6);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0,12,"LNG:");
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(25,12,longitude);

  //LATITIDE AND LONGITUDE SERIAL PRINT//
  Serial.print("Latitude: "+latitude);
  Serial.println(" Longitude: "+longitude);
  Serial.print("");
  Serial.println("------------------------------------------");
  Serial.print("");
}
//----------------------------------------SETUP----------------------------------------//
void setup() {
  Serial.begin(115200);                                                                // Serial initialization 115200 baund rate
  ss.begin(9600);                                                                      // GPS initialization 9600 baund rate

  if (!display.init())                                                                 // If display does not detect will print a serial menssage
  {                                        
    Serial.println(F("Check Wiring!"));
    Serial.print(F("Display not allocated"));
    for (;;);
  } 
  display.clear();
  display.init();
  display.flipScreenVertically();
}
//----------------------------------------LOOP----------------------------------------//
void loop() {
  boolean newData = false;                                                            // Variable to indicate if a newdata was inserted
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      if (gps.encode(ss.read()))
      {
        newData = true;
      }
    }
  }
    if (gps.speed.isValid()) {

      fspeed();
      fsatellites();
      //faltitude();
      faltitude_longitude();

      display.display();
      delay(100);
      display.clear();
    } 
    else {
      display.setFont(ArialMT_Plain_16);
      display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
      display.drawString(64, 23, "No Data");
      display.drawString(64, 41, "Please Wait");

      display.display();
      delay(1500);
      display.clear();
    }
  }
