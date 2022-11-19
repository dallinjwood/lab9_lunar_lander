#include "game_control.h"
#include "display.h"
#include "stdio.h"

int16_t x0 = 160;
int16_t ytest = 0;
int16_t width = 10;
int16_t height = 10;
int16_t x_origin = 0;
int16_t y_origin = 120;
#define gravity 0.01
double velocity = 0.98;
bool tick_is_odd = true;

void map1() {
  display_drawLine(0, 240, 100, 200, DISPLAY_WHITE);
  display_drawLine(100, 200, 160, 220, DISPLAY_WHITE);
  display_drawLine(160, 220, 190, 220, DISPLAY_DARK_YELLOW);
  display_drawLine(190, 220, 300, 160, DISPLAY_WHITE);
  display_drawLine(300, 160, 320, 240, DISPLAY_WHITE);
}

// Initialize the game control logic
// This function will initialize the lander and the map.
void gameControl_init() {
  display_fillScreen(DISPLAY_BLACK);
  display_drawRect(x0, ytest, width, height, DISPLAY_CYAN);
  map1();
}

// Tick the game control logic
//
// This function should tick the lander and check for wins on the game
void gameControl_tick() {
  // if (tick_is_odd) {
  //   velocity = velocity + gravity;
  // }
  if (ytest <= 220) {
    display_drawRect(x0, ytest, width, height, DISPLAY_BLACK);
    ytest = ytest + (int)velocity;
    display_drawRect(x0, ytest, width, height, DISPLAY_CYAN);
    velocity = velocity + gravity;
  }
  tick_is_odd = !tick_is_odd;

  // printf("Test");
}