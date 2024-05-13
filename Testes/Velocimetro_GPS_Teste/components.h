#ifndef COMPONENTS_H
#define COMPONENTS_H
//----------------------------------------LIBRARIES----------------------------------------//
#include <TinyGPSPlus.h>                                                                      // Library for parsing NMEA data from GPS modules.
#include <SoftwareSerial.h>                                                                   // Library for creating software serial communication ports.
#include <Wire.h>                                                                             // Library for I2C communication.
#include "SH1106Wire.h"                                                                       // Display SH1106 - 1.3 Inches  <switch to #include "SSD1306Wire.h" if you are using a SSD1306 128x64 display>.
#include "OLEDDisplayUi.h"                                                                    // Library for UI elements.
//----------------------------------------OBJECTS----------------------------------------//
TinyGPSPlus gps;                                                                              // The TinyGPSPlus object.
SoftwareSerial ss(2, 0);                                                                      // RXPin 2, TXPin 0 = The serial connection to the GPS device.
SH1106Wire display(0x3c, SDA, SCL);                                                           // Display object (ADDRESS, SDA(D2), SCL(D1)) <switch to 'SSD1306Wire display(0x3c, SDA, SCL);' if you are using a SSD1306 128x64 display>.
OLEDDisplayUi ui(&display);                                                                   // UI object.
#define GPSBaud = 9600;                                                                       // This GPS module have a 9600 baud rate.
//----------------------------------------BUTTONS----------------------------------------//
const byte BUT_1 = 12;                                                                        // Port D6.
const byte BUT_2 = 13;                                                                        // Port D7.
const byte BUT_3 = 15;                                                                        // Port D8.

void previous() {
  pinMode(BUT_1, INPUT_PULLUP);
  if (digitalRead(BUT_1) == LOW) {
    display.clear();
    ui.previousFrame();
    ui.update();
  }
}

void next() {
  pinMode(BUT_2, INPUT_PULLUP);
  if (digitalRead(BUT_2) == LOW) {
    display.clear();
    ui.nextFrame();
    ui.update();
  }
}

void select() {
  pinMode(BUT_3, INPUT_PULLUP);
  if (digitalRead(BUT_3) == LOW) {
    display.clear();
    ui.update();
  }
}
//----------------------------------------END----------------------------------------//
#endif
