#include "game_control.h"
#include "buttons.h"
#include "display.h"
#include "lander.h"
#include "maps.h"
#include <stdio.h>

#define THRUST_SCALER 0.15
#define gravity 0.02
#define FUEL_TEXT_CURSOR_X 20
#define FUEL_TEXT_CURSOR_Y 10
#define FUEL_TEXT "Fuel: "
#define FUEL_SCALAR 1
#define MAX_OFFSCREEN_CONSTANT 800

double x0 = 320;
double y_point0 = 0;
double x1 = 330;
double y_point1 = 0;
double x2 = 330;
double y2 = 10;
double x3 = 320;
double y3 = 10;
int16_t level = 1;
double y_velocity = 0.9;
double x_velocity = -0.5;
bool tick_is_odd = true;
uint64_t third_tick = 0;
int8_t tick_fourth = 0;
int8_t rotate = 0;

bool gameover_control = false;
bool win_control = false;
bool next_level = false;

double thrust_x = 0.;
double thrust_y = 0.;
double triangle_scalar = 1;

struct lander_t the_lander;

void gameControl_init_next_level() {
  x0 = 320;
  y_point0 = 0;
  x1 = 330;
  y_point1 = 0;
  x2 = 330;
  y2 = 10;
  x3 = 320;
  y3 = 10;
  y_velocity = 0.9;
  x_velocity = -1;
  display_fillScreen(DISPLAY_BLACK);
}

// Initialize the game control logic
// This function will initialize the lander and the map.
void gameControl_init() {
  // initialize the lander
  lander_init(&the_lander);
  the_lander.fuel = 10000;
  //set up the fuel indicator text  
  // display_setTextColorBg(DISPLAY_WHITE, DISPLAY_BLACK);


  display_fillScreen(DISPLAY_BLACK);
  buttons_init();
  display_drawLine(x0, y_point0, x1, y_point1, DISPLAY_GREEN);
  display_drawLine(x1, y_point1, x2, y2, DISPLAY_CYAN);
  display_drawLine(x2, y2, x3, y3, DISPLAY_CYAN);
  display_drawLine(x3, y3, x0, y_point0, DISPLAY_CYAN);
  display_drawPixel(x0, y_point0, DISPLAY_DARK_GREEN);
}

// Tick the game control logic
//
// This function should tick the lander and check for wins on the game
void gameControl_tick() {
  //fuel text cursor
  display_setCursor(FUEL_TEXT_CURSOR_X, FUEL_TEXT_CURSOR_Y);
  display_println(FUEL_TEXT);

  //actual fuel cursor
  display_setCursor(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y);
  
  uint8_t button_value = buttons_read();

  //change fuel text color based in how much fuel is left
  if(the_lander.fuel > 500){
  display_fillRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y, 30, 10, DISPLAY_BLACK);
  display_printDecimalInt(the_lander.fuel);
  } else if (the_lander.fuel > 300 && the_lander.fuel <= 500){
    display_setTextColor(DISPLAY_YELLOW)  ;
    display_fillRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y, 30, 10, DISPLAY_BLACK);
    display_printDecimalInt(the_lander.fuel);
  } else if (the_lander.fuel >= 0 && the_lander.fuel <= 300){
    display_setTextColor(DISPLAY_RED);
    display_fillRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y, 30, 10, DISPLAY_BLACK);
    display_printDecimalInt(the_lander.fuel);
  }


  printf("Fuel: %d \n", the_lander.fuel);
  //decrease fuel when button is being pressed
  if ((button_value & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK && (the_lander.fuel > 0)) {
    the_lander.fuel = the_lander.fuel - 10;
  } else if ((button_value & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK && (the_lander.fuel <= 0)){
    
    the_lander.fuel = 0;
  }

  //set
  if (level == 1) {
    map1();
  } else if ((level == 2)) {
    if (next_level) {
      gameControl_init_next_level();
      next_level = false;
    }
    map2();
  }

  // printf("vertical thrust: %f\n",get_thrust_y(&the_lander));
  // printf("horizontal thrust: %f\n\n",get_thrust_x(&the_lander));
  printf("vertical velocity: %f\n", y_velocity);
  printf("Theta: %f\n", the_lander.angle);
  printf("horizontal velocity: %f\n\n", x_velocity);
  printf("NOT DEAD\n");

  // testing rotations given preset rotation values
  if (y_point0 <= 230) {
    if (!gameover_control) {
      // erasing the box
      display_drawLine(x0, y_point0, x1, y_point1, DISPLAY_BLACK);
      display_drawLine(x1, y_point1, x2, y2, DISPLAY_BLACK);
      display_drawLine(x2, y2, x3, y3, DISPLAY_BLACK);
      display_drawLine(x3, y3, x0, y_point0, DISPLAY_BLACK);
      display_drawPixel(x0, y_point0, DISPLAY_BLACK);

      // Testing the idea of incrementing every other tick to solve the  stand
      // still issue
      if ((third_tick % 4 < 1) && (y_velocity < 0.35) &&
          (y_velocity > 0.1)) { // if tick_is_odd and the velocity falls in the
                                // correct range, then add to y_velocity
        y_point0 = y_point0 + 1;
        y_point1 = y_point1 + 1;
        y2 = y2 + 1;
        y3 = y3 + 1;
        x0 = x0 + (int)x_velocity;
        x1 = x1 + (int)x_velocity;
        x2 = x2 + (int)x_velocity;
        x3 = x3 + (int)x_velocity;

      } else if ((third_tick % 4 < 2) && (y_velocity < 0.7) &&
          (y_velocity > 0.351)) {
        y_point0 = y_point0 + 1;
        y_point1 = y_point1 + 1;
        y2 = y2 + 1;
        y3 = y3 + 1;
        x0 = x0 + (int)x_velocity;
        x1 = x1 + (int)x_velocity;
        x2 = x2 + (int)x_velocity;
        x3 = x3 + (int)x_velocity;

      } else if ((third_tick % 4 < 3) && (y_velocity < 1) &&
          (y_velocity > 0.71)) {
        y_point0 = y_point0 + 1;
        y_point1 = y_point1 + 1;
        y2 = y2 + 1;
        y3 = y3 + 1;
        x0 = x0 + (int)x_velocity;
        x1 = x1 + (int)x_velocity;
        x2 = x2 + (int)x_velocity;
        x3 = x3 + (int)x_velocity;

      } else if ((third_tick % 4 < 1) && (y_velocity > -0.35) &&
          (y_velocity < -0.1)) { // if tick_is_odd and the velocity falls in the
                                // correct range, then add to y_velocity
        y_point0 = y_point0 - 1;
        y_point1 = y_point1 - 1;
        y2 = y2 - 1;
        y3 = y3 - 1;
        x0 = x0 + (int)x_velocity;
        x1 = x1 + (int)x_velocity;
        x2 = x2 + (int)x_velocity;
        x3 = x3 + (int)x_velocity;

      } else if ((third_tick % 4 < 2) && (y_velocity > -0.7) &&
          (y_velocity < -0.351)) {
        y_point0 = y_point0 - 1;
        y_point1 = y_point1 - 1;
        y2 = y2 - 1;
        y3 = y3 - 1;
        x0 = x0 + (int)x_velocity;
        x1 = x1 + (int)x_velocity;
        x2 = x2 + (int)x_velocity;
        x3 = x3 + (int)x_velocity;

      } else if ((third_tick % 4 < 3) && (y_velocity > -1) &&
          (y_velocity < -0.71)) {
        y_point0 = y_point0 - 1;
        y_point1 = y_point1 - 1;
        y2 = y2 - 1;
        y3 = y3 - 1;
        x0 = x0 + (int)x_velocity;
        x1 = x1 + (int)x_velocity;
        x2 = x2 + (int)x_velocity;
        x3 = x3 + (int)x_velocity;

      } else {
        y_point0 = y_point0 + (int)y_velocity;
        y_point1 = y_point1 + (int)y_velocity;
        y2 = y2 + (int)y_velocity;
        y3 = y3 + (int)y_velocity;
        x0 = x0 + (int)x_velocity;
        x1 = x1 + (int)x_velocity;
        x2 = x2 + (int)x_velocity;
        x3 = x3 + (int)x_velocity;
      }

      //incrementing by 0.5 for  the x_velcoty
      if (tick_is_odd && (x_velocity < 1) &&
          (x_velocity > 0.2)) { // if tick_is_odd and the velocity falls in the
                                // correct range, then add to y_velocity
        y_point0 = y_point0 + (int)y_velocity;
        y_point1 = y_point1 + (int)y_velocity;
        y2 = y2 + (int)y_velocity;
        y3 = y3 + (int)y_velocity;
        x0 = x0 + 1;
        x1 = x1 + 1;
        x2 = x2 + 1;
        x3 = x3 + 1;

      } else if (tick_is_odd && (x_velocity > -1) && (x_velocity < -0.2)) {
        y_point0 = y_point0 + (int)y_velocity;
        y_point1 = y_point1 + (int)y_velocity;
        y2 = y2 + (int)y_velocity;
        y3 = y3 + (int)y_velocity;
        x0 = x0 - 1;
        x1 = x1 - 1;
        x2 = x2 - 1;
        x3 = x3 - 1;

      } else {
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
          ((the_lander.angle >= 80) && (the_lander.angle < 100))) {
        x0 = x0 + 3;
        y_point0 = y_point0 - 1;
        x1 = x1 + 1;
        y_point1 = y_point1 + 3;
        x2 = x2 - 3;
        y2 = y2 + 1;
        x3 = x3 - 1;
        y3 = y3 - 3;
        // rotate++;
        lean_right(&the_lander);
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 ((the_lander.angle >= 60) && (the_lander.angle < 80))) {
        x0 = x0 + 2;
        y_point0 = y_point0 - 1;
        x1 = x1 + 1;
        y_point1 = y_point1 + 2;
        x2 = x2 - 2;
        y2 = y2 + 1;
        x3 = x3 - 1;
        y3 = y3 - 2;
        // rotate++;
        lean_right(&the_lander);
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 ((the_lander.angle >= 40) && (the_lander.angle < 60))) {
        x0 = x0 + 2;
        y_point0 = y_point0 + 1;
        x1 = x1 - 1;
        y_point1 = y_point1 + 2;
        x2 = x2 - 2;
        y2 = y2 - 1;
        x3 = x3 + 1;
        y3 = y3 - 2;
        // rotate++;
        lean_right(&the_lander);
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 ((the_lander.angle >= 20) && (the_lander.angle < 40))) {
        x0 = x0 + 3;
        y_point0 = y_point0 + 1;
        x1 = x1 - 1;
        y_point1 = y_point1 + 3;
        x2 = x2 - 3;
        y2 = y2 - 1;
        x3 = x3 + 1;
        y3 = y3 - 3;
        // rotate++;
        lean_right(&the_lander);
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 ((the_lander.angle >= 100) && (the_lander.angle < 120))) {
        x0 = x0 + 1;
        y_point0 = y_point0 - 3;
        x1 = x1 + 3;
        y_point1 = y_point1 + 1;
        x2 = x2 - 1;
        y2 = y2 + 3;
        x3 = x3 - 3;
        y3 = y3 - 1;
        // rotate++;
        lean_right(&the_lander);
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 ((the_lander.angle >= 120) && (the_lander.angle < 140))) {
        x0 = x0 + 1;
        y_point0 = y_point0 - 2;
        x1 = x1 + 2;
        y_point1 = y_point1 + 1;
        x2 = x2 - 1;
        y2 = y2 + 2;
        x3 = x3 - 2;
        y3 = y3 - 1;
        // rotate++;
        lean_right(&the_lander);
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 ((the_lander.angle >= 140) && (the_lander.angle < 160))) {
        x0 = x0 - 1;
        y_point0 = y_point0 - 2;
        x1 = x1 + 2;
        y_point1 = y_point1 - 1;
        x2 = x2 + 1;
        y2 = y2 + 2;
        x3 = x3 - 2;
        y3 = y3 + 1;
        // rotate++;
        lean_right(&the_lander);
      } else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) &&
                 ((the_lander.angle >= 160) && (the_lander.angle < 180))) {
        x0 = x0 - 1;
        y_point0 = y_point0 - 3;
        x1 = x1 + 3;
        y_point1 = y_point1 - 1;
        x2 = x2 + 1;
        y2 = y2 + 3;
        x3 = x3 - 3;
        y3 = y3 + 1;
        // rotate++;
        lean_right(&the_lander);
      }

      // turn right calculations:
      else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
               ((the_lander.angle >= 60) && (the_lander.angle < 80))) {
        x0 = x0 - 3;
        y_point0 = y_point0 + 1;
        x1 = x1 - 1;
        y_point1 = y_point1 - 3;
        x2 = x2 + 3;
        y2 = y2 - 1;
        x3 = x3 + 1;
        y3 = y3 + 3;
        // rotate--;
        lean_left(&the_lander);
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 ((the_lander.angle >= 40) && (the_lander.angle < 60))) {
        x0 = x0 - 2;
        y_point0 = y_point0 + 1;
        x1 = x1 - 1;
        y_point1 = y_point1 - 2;
        x2 = x2 + 2;
        y2 = y2 - 1;
        x3 = x3 + 1;
        y3 = y3 + 2;
        // rotate--;
        lean_left(&the_lander);
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 ((the_lander.angle >= 20) && (the_lander.angle < 40))) {
        x0 = x0 - 2;
        y_point0 = y_point0 - 1;
        x1 = x1 + 1;
        y_point1 = y_point1 - 2;
        x2 = x2 + 2;
        y2 = y2 + 1;
        x3 = x3 - 1;
        y3 = y3 + 2;
        // rotate--;
        lean_left(&the_lander);
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 ((the_lander.angle >= 0) && (the_lander.angle < 20))) {
        x0 = x0 - 3;
        y_point0 = y_point0 - 1;
        x1 = x1 + 1;
        y_point1 = y_point1 - 3;
        x2 = x2 + 3;
        y2 = y2 + 1;
        x3 = x3 - 1;
        y3 = y3 + 3;
        // rotate--;
        lean_left(&the_lander);
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 ((the_lander.angle >= 80) && (the_lander.angle < 100))) {
        x0 = x0 - 1;
        y_point0 = y_point0 + 3;
        x1 = x1 - 3;
        y_point1 = y_point1 - 1;
        x2 = x2 + 1;
        y2 = y2 - 3;
        x3 = x3 + 3;
        y3 = y3 + 1;
        // rotate--;
        lean_left(&the_lander);
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 ((the_lander.angle >= 100) && (the_lander.angle < 120))) {
        x0 = x0 - 1;
        y_point0 = y_point0 + 2;
        x1 = x1 - 2;
        y_point1 = y_point1 - 1;
        x2 = x2 + 1;
        y2 = y2 - 2;
        x3 = x3 + 2;
        y3 = y3 + 1;
        // rotate--;
        lean_left(&the_lander);
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 ((the_lander.angle >= 120) && (the_lander.angle < 140))) {
        x0 = x0 + 1;
        y_point0 = y_point0 + 2;
        x1 = x1 - 2;
        y_point1 = y_point1 + 1;
        x2 = x2 - 1;
        y2 = y2 - 2;
        x3 = x3 + 2;
        y3 = y3 - 1;
        // rotate--;
        lean_left(&the_lander);
      } else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) &&
                 ((the_lander.angle >= 140) && (the_lander.angle < 160))) {
        x0 = x0 + 1;
        y_point0 = y_point0 + 3;
        x1 = x1 - 3;
        y_point1 = y_point1 + 1;
        x2 = x2 - 1;
        y2 = y2 - 3;
        x3 = x3 + 3;
        y3 = y3 - 1;
        // rotate--;
        lean_left(&the_lander);
      }


      //infinite screen code
      // if ((x0 <= -10) || (x3 <= -10)) {
      //   x0 = x0 + 320;
      //   x1 = x1 + 320;
      //   x2 = x2 + 320;
      //   x3 = x3 + 320;
      // } else if ((x1 >= 330) || (x2 >= 330)) {
      //   x0 = x0 - 320;
      //   x1 = x1 - 320;
      //   x2 = x2 - 320;
      //   x3 = x3 - 320;
      // }

    // offscreen indicator code
      
      
      if ((x0 <= -10) || (x3 <= -10)) {
      //set triangle scalar
      // if(x0 <= MAX_OFFSCREEN_CONSTANT){

      // } else
        triangle_scalar = (MAX_OFFSCREEN_CONSTANT - triangle_scalar + (int) x0) / 50 ;
        display_fillRect(0, 0, 16, DISPLAY_HEIGHT, DISPLAY_BLACK);
        
        display_fillTriangle(5, (int)y_point0, 15, (int)y_point0 + 5 + triangle_scalar, 15, (int)y_point0 - 5 - triangle_scalar, DISPLAY_WHITE);

        // display_fillRect(0, 0, 18, DISPLAY_HEIGHT, DISPLAY_BLACK);
      } else if ((x1 >= 330) || (x2 >= 330)) {
        x0 = x0 - 320;
        x1 = x1 - 320;
        x2 = x2 - 320;
        x3 = x3 - 320;
      } else {
        display_fillRect(0, 0, 18, DISPLAY_HEIGHT, DISPLAY_BLACK);
      }


      display_drawLine(x0, y_point0, x1, y_point1, DISPLAY_RED);
      display_drawLine(x1, y_point1, x2, y2, DISPLAY_CYAN);
      display_drawLine(x2, y2, x3, y3, DISPLAY_CYAN);
      display_drawLine(x3, y3, x0, y_point0, DISPLAY_CYAN);
      display_drawPixel(x0, y_point0, DISPLAY_YELLOW);
      y_velocity = y_velocity + gravity - (THRUST_SCALER * thrust_y);
      x_velocity = x_velocity + (THRUST_SCALER * thrust_x);
      // map1();
      if (level == 1) {
        map1();
        gameover_control = map1_collide(x0, x1, x2, x3, y_point0, y_point1, y2,
                                        y3, y_velocity);
      } else if (level == 2) {
        map2();
        gameover_control = map2_collide(x0, x1, x2, x3, y_point0, y_point1, y2,
                                        y3, y_velocity);
      }
    }
  }

  // change thrust value if button 1 is being pressed
  if (((button_value & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK) && the_lander.fuel > 0) {
    thrust_x = get_thrust_x(&the_lander);
    thrust_y = get_thrust_y(&the_lander);
  } else {
    thrust_x = 0;
    thrust_y = 0;
  }
  tick_is_odd = !tick_is_odd;
  
  //helper variable for the speed ranges between 0 and 1
  third_tick++;
  // if(third_tick == 3){
  //   third_tick = 0;
  // }

  if (gameover_control) {
    win_control = didPlayerWin();
    if (win_control) {
      display_fillScreen(DISPLAY_GREEN);
      level++;
      gameover_control = false;
      win_control = false;
      next_level = true;
    } else if (!win_control) {
      display_fillScreen(DISPLAY_RED);
    }
  }
}