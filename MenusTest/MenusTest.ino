#include <Wire.h>
//#include "SSD1306Wire.h" // Display SSD1306 - 0.96 Inches
#include "SH1106Wire.h" //Display SH1106 - 1.3 Inches

#include "OLEDDisplayUi.h"  // Ui lib, frames and menus options
#include "images.h"  // Bitmaps for the app icons
#include "fonts.h" // Bitmaps for the app titles

/* DISPLAY SELECTION */
// SSD1306 128x64 displays:
//SSD1306Wire display(0x3c, SDA, SCL);  // ADDRESS, SDA, SCL

// SSD1306 128x32 displays:
//SSD1306Wire display(0x3c, D1, D2, GEOMETRY_128_32); // ADDRESS, SDA, SCL, GEOMETRY_128_32

// SH1106 128x64 displays:
SH1106Wire display(0x3c, SDA, SCL);  // ADDRESS, SDA, SCL
OLEDDisplayUi ui( &display );

// Initializing Leds:
const byte LED_Y = 0; // Port D3
const byte LED_R = 2; // Port D4 

// Initializing button:
const byte BUT_1 = 12; // Port D6
const byte BUT_2 = 13; // Port D7
const byte BUT_3 = 15; // Port D8

int BUT_1_STAT;
int BUT_2_STAT;
int BUT_3_STAT;

int current_screen = 0;
int vez = 1;

void tela_inicial() {
  display.drawXbm(0,0, logo_inicial_width, logo_inicial_height, bitmap_logo_Inicial);
  display.display();
  delay(1500);
  }

void info(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->clear();
  display->drawXbm(x+48, y+10, icons_width, icons_height, icons[1]);
  display->setFont(Roboto_Medium_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(64, 42,"Info");
  }

void button(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->clear();
  display->drawXbm(x+48, y+10, icons_width, icons_height, icons[0]);
  display->setFont(Roboto_Medium_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(64, 42,"Botão");
  }

void radarguru(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->clear();
  display->drawXbm(x+48, y+10, icons_width, icons_height, icons[3]);
  display->setFont(Roboto_Medium_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(64, 42,"RadarGuru");
  }

void leds(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->clear();
  display->drawXbm(x+48, y+10, icons_width, icons_height, icons[2]);
  display->setFont(Roboto_Medium_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(64, 42,"Leds");
  }

void satellite(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->clear();
  display->drawXbm(x+48, y+10, icons_width, icons_height, icons[4]);
  display->setFont(Roboto_Medium_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(64, 42,"Satélite");
  
  }
// This array keeps function pointers to all frames
// frames are the single views that slide in
FrameCallback frames[] = {radarguru, leds, satellite, button, info};
int frameCount = 5;

// BUTTON PREVIOUS
void previous() {
if (BUT_1_STAT == LOW) {
  display.clear();
  ui.previousFrame();
  ui.update();
  }
  }
// BUTTON NEXT
void next() {
if (BUT_2_STAT == LOW) { 
  display.clear();
  ui.nextFrame();
  ui.update();
   }
  }
// BUTTON SELECT
void select() {
  if (BUT_3_STAT == LOW) { 
  display.clear();
  ui.update();
  }
}
void setup() {

  Serial.begin(115200);

  // Buttons
  pinMode(BUT_1, INPUT_PULLUP);
  pinMode(BUT_2, INPUT_PULLUP);
  pinMode(BUT_3, INPUT_PULLUP);

  // The ESP is capable of rendering 60fps in 80Mhz mode
  // but that won't give you much time for anything else
  // run it in 160Mhz mode or just set it to 30 fps
  ui.setTargetFPS(60);
  ui.setFrameAnimation(SLIDE_LEFT);
  
  // Page indicator, Scrool
  ui.setIndicatorPosition(TOP);
  // Defines where the first frame is located in the bar.
  ui.setIndicatorDirection(LEFT_RIGHT);

  // Add frames
  ui.setFrames(frames, frameCount);
  // Initializing the UI
  ui.init();
  display.flipScreenVertically();
  ui.disableAutoTransition();
}
void loop() { 
  // Intro with the logo
  if (vez == 1) {
    tela_inicial();
    display.clear();
    vez += 1;
    delay(1500);
    ui.update();
  }
  
  BUT_1_STAT = digitalRead(BUT_1);
  BUT_2_STAT = digitalRead(BUT_2);
  BUT_3_STAT = digitalRead(BUT_3);

  previous();
  next();
  select();
}
  
