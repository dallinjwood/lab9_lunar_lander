#include "game_control.h"
#include "buttons.h"
#include "display.h"
#include "lander.h"
#include <stdio.h>

#define THRUST_SCALER 0.15
#define gravity 0.025

int16_t x0 = 320;
int16_t y_point0 = 0;
int16_t x1 = 330;
int16_t y_point1 = 0;
int16_t x2 = 330;
int16_t y2 = 10;
int16_t x3 = 320;
int16_t y3 = 10;
int16_t x_origin = 0;
int16_t y_origin = 120;
double y_velocity = 0.9;
double x_velocity = -1;
bool tick_is_odd = true;
int8_t tick_fourth = 0;
int8_t rotate = 0;

double thrust_x = 0.;
double thrust_y = 0.;

struct lander_t the_lander;
 
//TODO:: change the 

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
  // initialize the lander
  lander_init(&the_lander);

  display_fillScreen(DISPLAY_BLACK);
  buttons_init();
  display_drawLine(x0, y_point0, x1, y_point1, DISPLAY_GREEN);
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

  // printf("vertical thrust: %f\n",get_thrust_y(&the_lander));
  // printf("horizontal thrust: %f\n\n",get_thrust_x(&the_lander));
  printf("vertical velocity: %f\n", y_velocity);
  printf("Theta: %f\n", the_lander.angle);
  printf("horizontal velocity: %f\n\n", x_velocity);

  if ((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) {
    lean_right(&the_lander);
    // printf("%d\n",the_lander.angle);
  } else if ((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) {
    lean_left(&the_lander);
    // printf("%d\n",the_lander.angle);
  }

  // testing rotations given preset rotation values
  if (y_point0 <= 230) {

    //erasing the box
    display_drawLine(x0, y_point0, x1, y_point1, DISPLAY_BLACK);
    display_drawLine(x1, y_point1, x2, y2, DISPLAY_BLACK);
    display_drawLine(x2, y2, x3, y3, DISPLAY_BLACK);
    display_drawLine(x3, y3, x0, y_point0, DISPLAY_BLACK);
    display_drawPixel(x0, y_point0, DISPLAY_BLACK);


    //

    //Testing the idea of incrementing every other tick to solve the  stand still issue
    if (tick_is_odd && (y_velocity < 1) && (y_velocity > 0)){ // if tick_is_odd and the velocity falls in the correct range, then add to y_velocity
    y_point0 = y_point0 + 1;
    y_point1 = y_point1 + 1;
    y2 = y2 + 1;
    y3 = y3 + 1;
    x0 = x0 + (int)x_velocity;
    x1 = x1 + (int)x_velocity;
    x2 = x2 + (int)x_velocity;
    x3 = x3 + (int)x_velocity;
    
    } else if (tick_is_odd && (y_velocity > -1) && (y_velocity < 0)){
    y_point0 = y_point0 - 1;
    y_point1 = y_point1 - 1;
    y2 = y2 - 1;
    y3 = y3 - 1;
    x0 = x0 + (int)x_velocity;
    x1 = x1 + (int)x_velocity;
    x2 = x2 + (int)x_velocity;
    x3 = x3 + (int)x_velocity;
    
    }else{
    y_point0 = y_point0 + (int)y_velocity;
    y_point1 = y_point1 + (int)y_velocity;
    y2 = y2 + (int)y_velocity;
    y3 = y3 + (int)y_velocity;
    x0 = x0 + (int)x_velocity;
    x1 = x1 + (int)x_velocity;
    x2 = x2 + (int)x_velocity;
    x3 = x3 + (int)x_velocity;
    }

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

    if ((x0 <= -10) || (x3 <= -10)) {
      x0 = x0 + 320;
      x1 = x1 + 320;
      x2 = x2 + 320;
      x3 = x3 + 320;
    } else if ((x1 >= 330) || (x2 >= 330)) {
      x0 = x0 - 320;
      x1 = x1 - 320;
      x2 = x2 - 320;
      x3 = x3 - 320;
    }
    display_drawLine(x0, y_point0, x1, y_point1, DISPLAY_RED);
    display_drawLine(x1, y_point1, x2, y2, DISPLAY_CYAN);
    display_drawLine(x2, y2, x3, y3, DISPLAY_CYAN);
    display_drawLine(x3, y3, x0, y_point0, DISPLAY_CYAN);
    display_drawPixel(x0, y_point0, DISPLAY_YELLOW);
    y_velocity = y_velocity + gravity - (THRUST_SCALER * thrust_y);
    x_velocity = x_velocity + (THRUST_SCALER * thrust_x);
    map1();
  }

  // change thrust value if button 1 is being pressed
  if (((button_value & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK)) {
    thrust_x = get_thrust_x(&the_lander);
    thrust_y = get_thrust_y(&the_lander);
  } else {
    thrust_x = 0;
    thrust_y = 0;
  }
  tick_is_odd = !tick_is_odd;
}