#include "maps.h"

#include "display.h"
#include <stdint.h>
#include <stdio.h>

void map1() {
  display_drawLine(0, 240, 100, 200, DISPLAY_WHITE);
  display_drawLine(100, 200, 160, 220, DISPLAY_WHITE);
  display_drawLine(160, 220, 190, 220, DISPLAY_DARK_YELLOW);
  display_drawLine(190, 220, 300, 160, DISPLAY_WHITE);
  display_drawLine(300, 160, 320, 240, DISPLAY_WHITE);
}

void map1_collide(int16_t x0, int16_t x1, int16_t x2, int16_t x3, int16_t y0,
                  int16_t y1, int16_t y2, int16_t y3) {}