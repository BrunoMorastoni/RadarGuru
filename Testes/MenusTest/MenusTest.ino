//----------------------------------------PACKAGES----------------------------------------//
#include "components.h"
#include "images.h"
#include "fonts.h"
//----------------------------------------VARS----------------------------------------//
int current_screen = 0;
int vez = 1;
//----------------------------------------SCREENS----------------------------------------//
void tela_inicial() {
  display.drawXbm(0, 0, logo_inicial_width, logo_inicial_height, bitmap_logo_Inicial);
  display.display();
  delay(1500);
}

void drawScreen(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y, const char* label, uint8_t iconIndex) {
  display->clear();
  display->drawXbm(x + 48, y + 10, icons_width, icons_height, icons[iconIndex]);
  display->setFont(Roboto_Medium_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(64, 48, label);
}

void info(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  drawScreen(display, state, x, y, "Informações", 1);
}

void button(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  drawScreen(display, state, x, y, "Botão", 0);
}

void radarguru(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  drawScreen(display, state, x, y, "RadarGuru", 3);
}

void leds(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  drawScreen(display, state, x, y, "Leds", 2);
}

void satellite(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  drawScreen(display, state, x, y, "Satélite", 4);
}

void config(OLEDDisplay* display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  drawScreen(display, state, x, y, "Configurações", 5);
}
//----------------------------------------SCREENS CONFIGS----------------------------------------//
FrameCallback frames[] = {radarguru, leds, satellite, button, info, config};
int frameCount = 6;
//----------------------------------------SETUP----------------------------------------//
void setup() {
  Serial.begin(115200);
  ui.setTargetFPS(60);
  ui.setFrameAnimation(SLIDE_LEFT);
  ui.setIndicatorPosition(TOP);
  ui.setIndicatorDirection(LEFT_RIGHT);
  ui.setFrames(frames, frameCount);
  ui.init();
  display.flipScreenVertically();
  ui.disableAutoTransition();
}
//----------------------------------------LOOP----------------------------------------//
void loop() { 
  if (vez == 1) {
    tela_inicial();
    display.clear();
    vez += 1;
    delay(1500);
    ui.update();
  }
  
  previous();
  next();
  select();
}
