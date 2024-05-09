#ifndef COMPONENTS_H
#define COMPONENTS_H
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
//----------------------------------------END----------------------------------------//
#endif