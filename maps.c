#include "maps.h"
#include "lander.h"

#include "display.h"
#include <stdint.h>
#include <stdio.h>

bool win = false;

void map1() {
  display_drawLine(0, 240, 106, 220, DISPLAY_WHITE);
  display_drawLine(106, 220, 133, 220, DISPLAY_WHITE);
  display_drawLine(133, 220, 187, 220, DISPLAY_DARK_YELLOW);
  display_drawLine(187, 220, 214, 220, DISPLAY_WHITE);
  display_drawLine(214, 220, 320, 240, DISPLAY_WHITE);
}

void map2() {
  display_drawLine(0, 240, 100, 200, DISPLAY_WHITE);
  display_drawLine(100, 200, 160, 220, DISPLAY_WHITE);
  display_drawLine(160, 220, 190, 220, DISPLAY_DARK_YELLOW);
  display_drawLine(190, 220, 300, 160, DISPLAY_WHITE);
  display_drawLine(300, 160, 320, 240, DISPLAY_WHITE);
}

void map3() {
  display_drawLine(0, 35, 50, 35, DISPLAY_WHITE);
  display_drawLine(50, 35, 50, 180, DISPLAY_WHITE);
  display_drawLine(50, 180, 100, 215, DISPLAY_WHITE);
  display_drawLine(100, 215, 140, 230, DISPLAY_WHITE);
  display_drawLine(140, 230, 160, 230, DISPLAY_DARK_YELLOW);
  display_drawLine(160, 230, 200, 215, DISPLAY_WHITE);
  display_drawLine(200, 215, 250, 180, DISPLAY_WHITE);
  display_drawLine(250, 180, 280, 180, DISPLAY_WHITE);
  display_drawLine(280, 180, 300, 50, DISPLAY_WHITE);
  display_drawLine(300, 50, 320, 50, DISPLAY_WHITE);
}

// TODO: once we have an official drawing with x,y points as part of the struct,
// we can change this so it just passes in the struct
bool map1_collide(double x0, double x1, double x2, double x3, double y0,
                  double y1, double y2, double y3, double y_velocity) {

  bool gameover = false;
  if ((y0 >= 240.00) || (y1 >= 240.00) || (y2 >= 240.00) || (y3 >= 240.00)) {
    win = false;
    return true;
  } else if (((x0 >= 0) || (x3 >= 0)) && ((x1 <= 106) || (x2 <= 106))) {
    if ((y0 >= 240.00 - (0.188679 * x0)) || (y1 >= 240.00 - (0.188679 * x1)) ||
        (y2 >= 240.00 - (0.188679 * x2)) || (y3 >= 240.00 - (0.188679 * x3))) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 <= 106) || (x3 <= 106)) && ((x1 >= 106) || (x2 >= 106))) {
    if ((y0 >= 240.00 - (0.188679 * x0)) || (y1 >= 220) || (y2 >= 220) ||
        (y3 >= 240.00 - (0.188679 * x3))) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 > 106) || (x3 > 106)) && ((x1 <= 133) || (x2 <= 133))) {
    if ((y0 >= 220) || (y1 >= 220) || (y2 >= 220) || (y3 >= 220)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 <= 133) || (x3 <= 133)) && ((x1 >= 133) || (x2 >= 133))) {
    if ((y0 >= 220) || (y1 >= 220) || (y2 >= 220) || (y3 >= 220)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 133) || (x3 >= 133)) && ((x1 <= 187) || (x2 <= 187))) {
    if ((y0 >= 220) || (y1 >= 220) || (y2 >= 220) || (y3 >= 220)) {
      if ((y_velocity <= 2.000) && (y3 == y2)) {
        win = true;
        return true;
      } else {
        win = false;
        return true;
      }
    } else {
      return false;
    }
  } else if (((x0 <= 187) || (x3 <= 187)) && ((x1 >= 187) || (x2 >= 187))) {
    if ((y0 >= 220) || (y1 >= 220) || (y2 >= 220) || (y3 >= 220)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 187) || (x3 >= 187)) && ((x1 <= 214) || (x2 <= 214))) {
    if ((y0 >= 220) || (y1 >= 220) || (y2 >= 220) || (y3 >= 220)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 <= 214) || (x3 <= 214)) && ((x1 >= 214) || (x2 >= 214))) {
    if ((y0 >= 220) || (y1 >= (0.188679 * x1) + 179.623) ||
        (y2 >= (0.188679 * x2) + 179.623) || (y3 >= 220)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 214) || (x3 >= 214))) {
    if ((y0 >= (0.188679 * x0) + 179.623) ||
        (y1 >= (0.188679 * x1) + 179.623) ||
        (y2 >= (0.188679 * x2) + 179.623) ||
        (y3 >= (0.188679 * x3) + 179.623)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

// TODO: once we have an official drawing with x,y points as part of the struct,
// we can change this so it just passes in the struct
bool map2_collide(double x0, double x1, double x2, double x3, double y0,
                  double y1, double y2, double y3, double y_velocity) {

  bool gameover = false;
  if ((y0 >= 240.00) || (y1 >= 240.00) || (y2 >= 240.00) || (y3 >= 240.00)) {
    win = false;
    return true;
  } else if (((x0 >= 0) || (x3 >= 0)) && ((x1 <= 100) || (x2 <= 100))) {
    if ((y0 >= 240.00 - (0.4 * x0)) || (y1 >= 240.00 - (0.4 * x1)) ||
        (y2 >= 240.00 - (0.4 * x2)) || (y3 >= 240.00 - (0.4 * x3))) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 <= 100) || (x3 <= 100)) && ((x1 >= 100) || (x2 >= 100))) {
    if ((y0 >= 240.00 - (0.4 * x0)) || (y1 >= 166.667 + (0.3333 * x1)) ||
        (y2 >= 166.667 + (0.3333 * x2)) || (y3 >= 240.00 - (0.4 * x3))) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 100) || (x3 >= 100)) && ((x1 <= 160) || (x2 <= 160))) {
    if ((y0 >= 166.667 + (0.3333 * x0)) || (y1 >= 166.667 + (0.3333 * x1)) ||
        (y2 >= 166.667 + (0.3333 * x2)) || (y3 >= 166.67 + (0.3333 * x3))) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 <= 160) || (x3 <= 160)) && ((x1 >= 160) || (x2 >= 160))) {
    if ((y0 >= 166.667 + (0.3333 * x0)) || (y1 >= 220) || (y2 >= 220) ||
        (y3 >= 166.67 + (0.3333 * x3))) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 160) || (x3 >= 160)) && ((x1 <= 190) || (x2 <= 190))) {
    if ((y0 >= 220) || (y1 >= 220) || (y2 >= 220) || (y3 >= 220)) {
      if ((y_velocity <= 2.00) && (y3 == y2)) {
        win = true;
        return true;
      } else {
        win = false;
        return true;
      }
    } else {
      return false;
    }
  } else if (((x0 <= 190) || (x3 <= 190)) && ((x1 >= 190) || (x2 >= 190))) {
    if ((y0 >= 220) || (y1 >= 323.636 - (0.54545 * x1)) ||
        (y2 >= 323.636 - (0.54545 * x2)) || (y3 >= 220)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 190) || (x3 >= 190)) && ((x1 <= 300) || (x2 <= 300))) {
    if ((y0 >= 323.636 - (0.54545 * x0)) || (y1 >= 323.636 - (0.54545 * x1)) ||
        (y2 >= 323.636 - (0.54545 * x2)) || (y3 >= 323.636 - (0.54545 * x3))) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 <= 300) || (x3 <= 300)) && ((x1 >= 300) || (x2 >= 300))) {
    if ((y0 >= 323.636 - (0.54545 * x0)) || (y1 >= (4.0 * x1) - 1040.00) ||
        (y2 >= (4.0 * x2) - 1040.00) || (y3 >= 323.636 - (0.54545 * x3))) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 300) || (x3 >= 300))) {
    if ((y0 >= (4.0 * x0) - 1040.00) || (y1 >= (4.0 * x1) - 1040.00) ||
        (y2 >= (4.0 * x2) - 1040.00) || (y3 >= (4.0 * x3) - 1040.00)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

// map 3
bool map3_collide(double x0, double x1, double x2, double x3, double y0,
                  double y1, double y2, double y3, double y_velocity) {

  bool gameover = false;
  if ((y0 >= 240.00) || (y1 >= 240.00) || (y2 >= 240.00) || (y3 >= 240.00)) {
    win = false;
    return true;
  } else if (((x0 >= 0) || (x3 >= 0)) && ((x1 <= 50) || (x2 <= 50))) {
    if ((y0 >= 35) || (y1 >= 35) || (y2 >= 35) || (y3 >= 35)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 <= 50) || (x3 <= 50)) && ((x1 >= 50) || (x2 >= 50))) {
    if ((y0 >= 35) || (y1 >= 145.00 + (0.7 * x1)) ||
        (y2 >= 145.00 + (0.7 * x2)) || (y3 >= 35)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 50) || (x3 >= 50)) && ((x1 <= 100) || (x2 <= 100))) {
    if ((y0 >= 145.00 + (0.7 * x0)) || (y1 >= 145.00 + (0.7 * x1)) ||
        (y2 >= 145.00 + (0.7 * x2)) || (y3 >= 145.00 + (0.7 * x3))) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 <= 100) || (x3 <= 100)) && ((x1 >= 100) || (x2 >= 100))) {
    if ((y0 >= 145.00 + (0.7 * x0)) || (y1 >= 177.5 + (0.375 * x1)) ||
        (y2 >= 177.5 + (0.375 * x2)) || (y3 >= 145.00 + (0.7 * x3))) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 100) || (x3 >= 100)) && ((x1 <= 140) || (x2 <= 140))) {
    if ((y0 >= 177.5 + (0.375 * x0)) || (y1 >= 177.5 + (0.375 * x1)) ||
        (y2 >= 177.5 + (0.375 * x3)) || (y3 >= 177.5 + (0.375 * x3))) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 <= 140) || (x3 <= 140)) && ((x1 >= 140) || (x2 >= 140))) {
    if ((y0 >= 177.5 + (0.375 * x0)) || (y1 >= 230.00) || (y2 >= 230.00) ||
        (y3 >= 177.5 + (0.375 * x3))) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 140) || (x3 >= 140)) && ((x1 <= 160) || (x2 <= 160))) {
    if ((y0 >= 230.00) || (y1 >= 230.00) || (y2 >= 230.00) || (y3 >= 230.00)) {
      if ((y_velocity <= 0.6) && (y3 == y2)) {
        win = true;
        return true;
      } else {
        win = false;
        return true;
      }
    } else {
      return false;
    }
  } else if (((x0 <= 160) || (x3 <= 160)) && ((x1 >= 160) || (x2 >= 160))) {
    if ((y0 >= 230.00) || (y1 >= (-0.375 * x1) + 290.00) ||
        (y2 >= (-0.375 * x2) + 290.00) || (y3 >= 230.00)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 160) || (x3 >= 160)) && ((x1 <= 200) || (x2 <= 200))) {
    if ((y0 >= (-0.375 * x0) + 290.00) || (y1 >= (-0.375 * x1) + 290.00) ||
        (y2 >= (-0.375 * x2) + 290.00) || (y3 >= (-0.375 * x3) + 290.00)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 <= 200) || (x3 <= 200)) && ((x1 >= 200) || (x2 >= 200))) {
    if ((y0 >= (-0.375 * x0) + 290.00) || (y1 >= (-0.7 * x1) + 355.00) ||
        (y2 >= (-0.7 * x2) + 355.00) || (y3 >= (-0.375 * x3) + 290.00)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 200) || (x3 >= 200)) && ((x1 <= 250) || (x2 <= 250))) {
    if ((y0 >= (-0.7 * x0) + 355.00) || (y1 >= (-0.7 * x1) + 355.00) ||
        (y2 >= (-0.7 * x2) + 355.00) || (y3 >= (-0.7 * x3) + 355.00)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 <= 250) || (x3 <= 250)) && ((x1 >= 250) || (x2 >= 250))) {
    if ((y0 >= (-0.7 * x0) + 355.00) || (y1 >= 180.00) || (y2 >= 180.00) ||
        (y3 >= (-0.7 * x3) + 355.00)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 250) || (x3 >= 250)) && ((x1 <= 280) || (x2 <= 280))) {
    if ((y0 >= 180.00) || (y1 >= 180.00) || (y2 >= 180.00) || (y3 >= 180.00)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 <= 280) || (x3 <= 280)) && ((x1 >= 280) || (x2 >= 280))) {
    if ((y0 >= 180.00) || (y1 >= (-6.5 * x1) + 2000.00) ||
        (y2 >= (-6.5 * x2) + 2000.00) || (y3 >= 180.00)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 280) || (x3 >= 280)) && ((x1 <= 300) || (x2 <= 300))) {
    if ((y0 >= 50) || (y1 >= 50) || (y2 >= 50) || (y3 >= 50)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else if (((x0 >= 300) || (x3 >= 300))) {
    if ((y0 >= 50) || (y1 >= 50) || (y2 >= 50) || (y3 >= 50)) {
      win = false;
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool didPlayerWin() {
  if (win) {
    return true;
  } else {
    return false;
  }
}
