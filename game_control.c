#include "game_control.h"
#include "buttons.h"
#include "display.h"
#include "stdio.h"

int16_t x0 = -10;
int16_t y_point0 = 0;
int16_t x1 = 0;
int16_t y_point1 = 0;
int16_t x2 = 0;
int16_t y2 = 10;
int16_t x3 = -10;
int16_t y3 = 10;
int16_t x_origin = 0;
int16_t y_origin = 120;
#define gravity 0.01
double y_velocity = 0.98;
double x_velocity = 2;
bool tick_is_odd = true;
int8_t tick_fourth = 0;
int8_t rotate = 0;

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
  buttons_init();
  display_drawLine(x0, y_point0, x1, y_point1, DISPLAY_CYAN);
  display_drawLine(x1, y_point1, x2, y2, DISPLAY_CYAN);
  display_drawLine(x2, y2, x3, y3, DISPLAY_CYAN);
  display_drawLine(x3, y3, x0, y_point0, DISPLAY_CYAN);
  display_drawPixel(x0, y_point0, DISPLAY_DARK_GREEN);
  map1();
}

// Tick the game control logic
//
// This function should tick the lander and check for wins on the game
void gameControl_tick() {
  // if (tick_is_odd) {
  //   velocity = velocity + gravity;
  // }
  uint8_t button_value = buttons_read();
  if (y_point0 <= 220) {
    display_drawLine(x0, y_point0, x1, y_point1, DISPLAY_BLACK);
    display_drawLine(x1, y_point1, x2, y2, DISPLAY_BLACK);
    display_drawLine(x2, y2, x3, y3, DISPLAY_BLACK);
    display_drawLine(x3, y3, x0, y_point0, DISPLAY_BLACK);
    display_drawPixel(x0, y_point0, DISPLAY_BLACK);
    y_point0 = y_point0 + (int)y_velocity;
    y_point1 = y_point1 + (int)y_velocity;
    y2 = y2 + (int)y_velocity;
    y3 = y3 + (int)y_velocity;
    x0 = x0 + x_velocity;
    x1 = x1 + x_velocity;
    x2 = x2 + x_velocity;
    x3 = x3 + x_velocity;
    if (tick_fourth == 1) {
      tick_fourth = 0;
      // if statements to turn left
      if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
          (rotate == 0)) {
        x0 = x0 + 3;
        y_point0 = y_point0 - 1;
        x1 = x1 + 1;
        y_point1 = y_point1 + 3;
        x2 = x2 - 3;
        y2 = y2 + 1;
        x3 = x3 - 1;
        y3 = y3 - 3;
        rotate++;
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 (rotate == 1)) {
        x0 = x0 + 2;
        y_point0 = y_point0 - 1;
        x1 = x1 + 1;
        y_point1 = y_point1 + 2;
        x2 = x2 - 2;
        y2 = y2 + 1;
        x3 = x3 - 1;
        y3 = y3 - 2;
        rotate++;
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 (rotate == 2)) {
        x0 = x0 + 2;
        y_point0 = y_point0 + 1;
        x1 = x1 - 1;
        y_point1 = y_point1 + 2;
        x2 = x2 - 2;
        y2 = y2 - 1;
        x3 = x3 + 1;
        y3 = y3 - 2;
        rotate++;
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 (rotate == 3)) {
        x0 = x0 + 3;
        y_point0 = y_point0 + 1;
        x1 = x1 - 1;
        y_point1 = y_point1 + 3;
        x2 = x2 - 3;
        y2 = y2 - 1;
        x3 = x3 + 1;
        y3 = y3 - 3;
        rotate++;
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 (rotate == -1)) {
        x0 = x0 + 1;
        y_point0 = y_point0 - 3;
        x1 = x1 + 3;
        y_point1 = y_point1 + 1;
        x2 = x2 - 1;
        y2 = y2 + 3;
        x3 = x3 - 3;
        y3 = y3 - 1;
        rotate++;
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 (rotate == -2)) {
        x0 = x0 + 1;
        y_point0 = y_point0 - 2;
        x1 = x1 + 2;
        y_point1 = y_point1 + 1;
        x2 = x2 - 1;
        y2 = y2 + 2;
        x3 = x3 - 2;
        y3 = y3 - 1;
        rotate++;
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 (rotate == -3)) {
        x0 = x0 - 1;
        y_point0 = y_point0 - 2;
        x1 = x1 + 2;
        y_point1 = y_point1 - 1;
        x2 = x2 + 1;
        y2 = y2 + 2;
        x3 = x3 - 2;
        y3 = y3 + 1;
        rotate++;
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 (rotate == -4)) {
        x0 = x0 - 1;
        y_point0 = y_point0 - 3;
        x1 = x1 + 3;
        y_point1 = y_point1 - 1;
        x2 = x2 + 1;
        y2 = y2 + 3;
        x3 = x3 - 3;
        y3 = y3 + 1;
        rotate++;
      }

      // turn right calculations:
      else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
               (rotate == 1)) {
        x0 = x0 - 3;
        y_point0 = y_point0 + 1;
        x1 = x1 - 1;
        y_point1 = y_point1 - 3;
        x2 = x2 + 3;
        y2 = y2 - 1;
        x3 = x3 + 1;
        y3 = y3 + 3;
        rotate--;
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 (rotate == 2)) {
        x0 = x0 - 2;
        y_point0 = y_point0 + 1;
        x1 = x1 - 1;
        y_point1 = y_point1 - 2;
        x2 = x2 + 2;
        y2 = y2 - 1;
        x3 = x3 + 1;
        y3 = y3 + 2;
        rotate--;
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 (rotate == 3)) {
        x0 = x0 - 2;
        y_point0 = y_point0 - 1;
        x1 = x1 + 1;
        y_point1 = y_point1 - 2;
        x2 = x2 + 2;
        y2 = y2 + 1;
        x3 = x3 - 1;
        y3 = y3 + 2;
        rotate--;
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 (rotate == 4)) {
        x0 = x0 - 3;
        y_point0 = y_point0 - 1;
        x1 = x1 + 1;
        y_point1 = y_point1 - 3;
        x2 = x2 + 3;
        y2 = y2 + 1;
        x3 = x3 - 1;
        y3 = y3 + 3;
        rotate--;
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 (rotate == 0)) {
        x0 = x0 - 1;
        y_point0 = y_point0 + 3;
        x1 = x1 - 3;
        y_point1 = y_point1 - 1;
        x2 = x2 + 1;
        y2 = y2 - 3;
        x3 = x3 + 3;
        y3 = y3 + 1;
        rotate--;
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 (rotate == -1)) {
        x0 = x0 - 1;
        y_point0 = y_point0 + 2;
        x1 = x1 - 2;
        y_point1 = y_point1 - 1;
        x2 = x2 + 1;
        y2 = y2 - 2;
        x3 = x3 + 2;
        y3 = y3 + 1;
        rotate--;
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 (rotate == -2)) {
        x0 = x0 + 1;
        y_point0 = y_point0 + 2;
        x1 = x1 - 2;
        y_point1 = y_point1 + 1;
        x2 = x2 - 1;
        y2 = y2 - 2;
        x3 = x3 + 2;
        y3 = y3 - 1;
        rotate--;
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 (rotate == -3)) {
        x0 = x0 + 1;
        y_point0 = y_point0 + 3;
        x1 = x1 - 3;
        y_point1 = y_point1 + 1;
        x2 = x2 - 1;
        y2 = y2 - 3;
        x3 = x3 + 3;
        y3 = y3 - 1;
        rotate--;
      }
    }

    display_drawLine(x0, y_point0, x1, y_point1, DISPLAY_CYAN);
    display_drawLine(x1, y_point1, x2, y2, DISPLAY_CYAN);
    display_drawLine(x2, y2, x3, y3, DISPLAY_CYAN);
    display_drawLine(x3, y3, x0, y_point0, DISPLAY_CYAN);
    display_drawPixel(x0, y_point0, DISPLAY_YELLOW);
    y_velocity = y_velocity + gravity;
  }
  tick_is_odd = !tick_is_odd;
  tick_fourth++;

  // printf("Test");
}