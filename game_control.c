#include "game_control.h"
#include "buttons.h"
#include "display.h"
#include "lander.h"
#include "maps.h"
#include "switches.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define THRUST_SCALER 0.1
#define gravity 0.02
#define FUEL_TEXT_CURSOR_X 30
#define FUEL_TEXT_CURSOR_Y 25
#define FUEL_TEXT "Fuel: "
#define FUEL_SCALAR 1
#define MAX_OFFSCREEN_CONSTANT 900
#define DEFAULT_ERROR_MSG "Error: could not enter any state.\n"
#define TRANSITION_TIME 3
#define SET_X_CURSOR 20
#define SET_Y_CURSOR 30
#define LEVEL_CURSOR_X 120
#define LEVEL_CURSOR_Y 100
#define LEVEL_SIZE 2


static bool lastDrawLeft = false;
static bool lastDrawRight = false;
static bool lastDrawTop = false;
static double triangle_scalar = 1;
static double x0 = 320;
static double y_point0 = 0;
static double x1 = 330;
static double y_point1 = 0;
static double x2 = 330;
static double y2 = 10;
static double x3 = 320;
static double y3 = 10;
static int16_t level = 1;
static double y_velocity = 0.9;
static double x_velocity = -1;
static bool tick_is_odd = true;
static uint64_t third_tick = 0;
static int8_t tick_fourth = 0;
static int8_t rotate = 0;

static bool gameover_control = false;
static bool win_control = false;
static bool next_level = false;
static bool announcement_drawn = false;
static bool gameover_drawn = false;

static double thrust_x = 0.;
static double thrust_y = 0.;

static struct lander_t the_lander;

static enum gameControl_sm_t {
  MENU,       // Opening menu to start game
  TRANSITION, // Transition between gameplay and menu with a level announcement
  GAMEPLAY,   // The screen is being pressed and waiting until a half
              // second has passed
  GAMEOVER,   // Updates the clock at a faster rate.
} currentState;

static uint16_t led_value = 0;
static uint16_t transition_cnt = 0;
static uint16_t transition_num_ticks = 0;
static uint8_t button_value = 0;

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
}

// Initialize the game control logic
// This function will initialize the lander and the map.
void gameControl_init(double period_s) {
  // initialize the lander
  lander_init(&the_lander);
  // the_lander.fuel = 10000;
  switches_init();
  display_fillScreen(DISPLAY_BLACK);
  buttons_init();
  display_setCursor(SET_X_CURSOR + 50, SET_Y_CURSOR);
  display_setTextSize(6);
  display_setTextColor(DISPLAY_WHITE);
  display_println("LUNAR");
  display_setCursor(SET_X_CURSOR + 35, SET_Y_CURSOR + 50);
  display_setTextSize(6);
  display_setTextColor(DISPLAY_WHITE);
  display_println("LANDER");
  display_setCursor(SET_X_CURSOR - 5, SET_Y_CURSOR + 170);
  display_setTextSize(2);
  display_setTextColor(DISPLAY_WHITE);
  display_println("Flip Switch 0 up to Start");
  transition_cnt = 0;
  transition_num_ticks = TRANSITION_TIME / period_s;
}

// Tick the game control logic
//
// This function should tick the lander and check for wins on the game
void gameControl_tick() {

  led_value = switches_read();

  // state transitions
  switch (currentState) {
  // menu state transitions
  case MENU:
    if ((led_value & SWITCHES_SW0_MASK) == SWITCHES_SW0_MASK) {
      currentState = TRANSITION;
      // erase menu code
      display_setCursor(SET_X_CURSOR + 50, SET_Y_CURSOR);
      display_setTextSize(6);
      display_setTextColor(DISPLAY_BLACK);
      display_println("LUNAR");
      display_setCursor(SET_X_CURSOR + 35, SET_Y_CURSOR + 50);
      display_setTextSize(6);
      display_setTextColor(DISPLAY_BLACK);
      display_println("LANDER");
      display_setCursor(SET_X_CURSOR - 5, SET_Y_CURSOR + 170);
      display_setTextSize(2);
      display_setTextColor(DISPLAY_BLACK);
      display_println("Flip Switch 0 up to Start");
    }
    break;
  // transition state  transitions
  case TRANSITION:
    if (transition_cnt == transition_num_ticks) {
      transition_cnt = 0;
      currentState = GAMEPLAY;
      if ((level == 1) && (announcement_drawn)) {
        // erase level announcement
        display_setCursor(LEVEL_CURSOR_X, LEVEL_CURSOR_Y);
        display_setTextSize(LEVEL_SIZE);
        display_setTextColor(DISPLAY_BLACK);
        display_println("Level 1");
        announcement_drawn = false;
        map1();
      } else if ((level == 2) && (announcement_drawn)) {
        // erase level announcement
        display_setCursor(LEVEL_CURSOR_X, LEVEL_CURSOR_Y);
        display_setTextSize(LEVEL_SIZE);
        display_setTextColor(DISPLAY_BLACK);
        display_println("Level 2");
        announcement_drawn = false;
        gameControl_init_next_level();
        map2();
      } else if ((level == 3) && (announcement_drawn)) {
        // erase level announcement
        display_setCursor(LEVEL_CURSOR_X, LEVEL_CURSOR_Y);
        display_setTextSize(LEVEL_SIZE);
        display_setTextColor(DISPLAY_BLACK);
        display_println("Level 3");
        announcement_drawn = false;
        gameControl_init_next_level();
        map3();
      }
      lander_init(&the_lander);
      display_drawLine(x0, y_point0, x1, y_point1, DISPLAY_GREEN);
      display_drawLine(x1, y_point1, x2, y2, DISPLAY_CYAN);
      display_drawLine(x2, y2, x3, y3, DISPLAY_CYAN);
      display_drawLine(x3, y3, x0, y_point0, DISPLAY_CYAN);
      display_drawPixel(x0, y_point0, DISPLAY_DARK_GREEN);
    }
    break;
  // INC_DEC transitions
  case GAMEPLAY:
    if (gameover_control) {
      win_control = didPlayerWin();
      if (win_control) {
        display_fillScreen(DISPLAY_GREEN);
        level++;
        gameover_control = false;
        win_control = false;
        next_level = true;
        currentState = TRANSITION;
        display_fillScreen(DISPLAY_BLACK);
      } else if (!win_control) {
        currentState = GAMEOVER;
        gameover_control = false;
        win_control = false;
        next_level = true;
      }
    }
    break;
  // fast delay transition
  case GAMEOVER:
    if ((led_value & SWITCHES_SW0_MASK) != SWITCHES_SW0_MASK) {

      currentState = MENU;
      // erase game over
      display_setCursor(SET_X_CURSOR + 60, SET_Y_CURSOR);
      display_setTextSize(6);
      display_setTextColor(DISPLAY_BLACK);
      display_println("GAME");
      display_setCursor(SET_X_CURSOR + 60, SET_Y_CURSOR + 50);
      display_setTextSize(6);
      display_setTextColor(DISPLAY_BLACK);
      display_println("OVER");
      display_setCursor(SET_X_CURSOR + 8, SET_Y_CURSOR + 170);
      display_setTextSize(2);
      display_setTextColor(DISPLAY_BLACK);
      display_println("Flip Switch 0 down to");
      display_setCursor(SET_X_CURSOR + 90, SET_Y_CURSOR + 190);
      display_setTextSize(2);
      display_setTextColor(DISPLAY_BLACK);
      display_println("restart");
      gameover_drawn = false;
      level = 1;
      gameControl_init_next_level();

      // draw menu
      display_setCursor(SET_X_CURSOR + 50, SET_Y_CURSOR);
      display_setTextSize(6);
      display_setTextColor(DISPLAY_WHITE);
      display_println("LUNAR");
      display_setCursor(SET_X_CURSOR + 35, SET_Y_CURSOR + 50);
      display_setTextSize(6);
      display_setTextColor(DISPLAY_WHITE);
      display_println("LANDER");
      display_setCursor(SET_X_CURSOR - 5, SET_Y_CURSOR + 170);
      display_setTextSize(2);
      display_setTextColor(DISPLAY_WHITE);
      display_println("Flip Switch 0 up to Start");
    }
    break;
  // default to catch errors
  default:
    printf(DEFAULT_ERROR_MSG);
    break;
  }

  // state Actions
  switch (currentState) {
  // menu state actions
  case MENU:

    break;
  // transition state actions
  case TRANSITION:

    if ((level == 1) && (!announcement_drawn)) {
      // draw level announcement
      display_setCursor(LEVEL_CURSOR_X, LEVEL_CURSOR_Y);
      display_setTextSize(LEVEL_SIZE);
      display_setTextColor(DISPLAY_WHITE);
      display_println("Level 1");
      announcement_drawn = true;
    } else if ((level == 2) && (!announcement_drawn)) {
      // draw level announcement
      display_setCursor(LEVEL_CURSOR_X, LEVEL_CURSOR_Y);
      display_setTextSize(LEVEL_SIZE);
      display_setTextColor(DISPLAY_WHITE);
      display_println("Level 2");
      announcement_drawn = true;
    } else if ((level == 3) && (!announcement_drawn)) {
      // draw level announcement
      display_setCursor(LEVEL_CURSOR_X, LEVEL_CURSOR_Y);
      display_setTextSize(LEVEL_SIZE);
      display_setTextColor(DISPLAY_WHITE);
      display_println("Level 3");
      announcement_drawn = true;
    }
    transition_cnt++;

    break;
  // gameplay actions
  case GAMEPLAY:
    button_value = buttons_read();

    // printf("vertical thrust: %f\n",get_thrust_y(&the_lander));
    // printf("horizontal thrust: %f\n\n",get_thrust_x(&the_lander));
    printf("vertical velocity: %f\n", y_velocity);
    printf("Theta: %f\n", the_lander.angle);
    printf("horizontal velocity: %f\n\n", x_velocity);
    printf("NOT DEAD\n");

    // fuel text cursor
    display_setTextColor(DISPLAY_WHITE);
    display_setTextSize(1);
    display_setCursor(FUEL_TEXT_CURSOR_X, FUEL_TEXT_CURSOR_Y);
    display_println(FUEL_TEXT);

    // actual fuel cursor
    display_setCursor(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y);

    uint8_t button_value = buttons_read();

    // change fuel text color based in how much fuel is left
    if (the_lander.fuel > 500) {
      display_drawRoundRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y + 10, the_lander.fuel / 10, 10, 2, DISPLAY_WHITE);
      display_fillRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y, 30, 10,
                       DISPLAY_BLACK);
      display_printDecimalInt(the_lander.fuel);
    } else if (the_lander.fuel > 300 && the_lander.fuel <= 500) {
      display_drawRoundRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y + 10, the_lander.fuel / 10, 10, 2, DISPLAY_YELLOW);
      display_setTextColor(DISPLAY_YELLOW);
      display_fillRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y, 30, 10,
                       DISPLAY_BLACK);
      display_printDecimalInt(the_lander.fuel);

    } else if (the_lander.fuel >= 0 && the_lander.fuel <= 300) {
      display_drawRoundRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y + 10, the_lander.fuel / 10, 10, 2, DISPLAY_RED);
      display_setTextColor(DISPLAY_RED);
      display_fillRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y, 30, 10,
                       DISPLAY_BLACK);
      display_printDecimalInt(the_lander.fuel);

    }

    printf("Fuel: %d \n", the_lander.fuel);
    // decrease fuel when button is being pressed
    if ((button_value & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK &&
        (the_lander.fuel > 0)) {
      the_lander.fuel = the_lander.fuel - 10;
    } else if ((button_value & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK &&
               (the_lander.fuel <= 0)) {

      the_lander.fuel = 0;
    }

    // testing rotations given preset rotation values
    if (y_point0 <= 240) {
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
            (y_velocity > 0.1)) { // if tick_is_odd and the velocity falls in
                                  // the correct range, then add to y_velocity
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
                   (y_velocity <
                    -0.1)) { // if tick_is_odd and the velocity falls in the
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

        // incrementing by 0.5 for  the x_velcoty
        if (tick_is_odd && (x_velocity < 1) &&
            (x_velocity > 0.2)) { // if tick_is_odd and the velocity falls in
                                  // the correct range, then add to y_velocity
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
      
      //offscreen inidication

      //erase the triangle
      if(lastDrawLeft) {
        
        display_fillRect(0, 0, 25, DISPLAY_HEIGHT, DISPLAY_BLACK);
        
        lastDrawLeft = false;

      } else if (lastDrawRight){
        
        display_fillRect(DISPLAY_WIDTH - 25, 0, 25, DISPLAY_HEIGHT, DISPLAY_BLACK);
        
        lastDrawRight = false;

      } else if (lastDrawTop){
        display_fillRect(0,0,DISPLAY_WIDTH, 20, DISPLAY_BLACK);
        lastDrawTop = false;
      }


      if ((x0 <= -10) || (x3 <= -10)) {
        //set triangle scalar
        if(x0 >= -MAX_OFFSCREEN_CONSTANT){
          triangle_scalar = (MAX_OFFSCREEN_CONSTANT - triangle_scalar + (int) x0) / 30 ;
        }

        display_fillTriangle(0 ,
                            (int)y_point0,
                            15 + (triangle_scalar / 4),
                            (int)y_point0 + 5 + triangle_scalar,
                            15 + (triangle_scalar / 4),
                            (int)y_point0 - 5 - triangle_scalar,
                            DISPLAY_WHITE);

        // display_fillTriangle(5,
        //                     (int)y_point0,
        //                     15 ,
        //                     (int)y_point0 + 5,
        //                     15 ,
        //                     (int)y_point0 - 5,
        //                     DISPLAY_WHITE);


        // display_fillRect(0, 0, 25, DISPLAY_HEIGHT, DISPLAY_BLACK);
      lastDrawLeft = true;
        
      } else if ((x1 >= 330) || (x2 >= 330)) {
        //set triangle scalar
        if(x0 <= MAX_OFFSCREEN_CONSTANT){
          triangle_scalar = (MAX_OFFSCREEN_CONSTANT + triangle_scalar - (int) x0) / 30 ;
        }

        display_fillTriangle(DISPLAY_WIDTH ,
                            (int)y_point0,
                            DISPLAY_WIDTH - 15 - (triangle_scalar / 4),
                            (int)y_point0 - 5 - triangle_scalar,
                            DISPLAY_WIDTH - 15 - (triangle_scalar / 4),
                            (int)y_point0 + 5 + triangle_scalar,
                            DISPLAY_WHITE);

        lastDrawRight = true;
      } else if((y_point0 <= -10) || (y3 <= -10)){
        if(y_point0 <= -MAX_OFFSCREEN_CONSTANT + 400){
           triangle_scalar = (MAX_OFFSCREEN_CONSTANT - triangle_scalar + (int) y_point0) / 30 ;
        }

        // display_fillTriangle(0 ,
        //                     (int)y_point0,
        //                     15 + (triangle_scalar / 4),
        //                     (int)y_point0 + 5 + triangle_scalar,
        //                     15 + (triangle_scalar / 4),
        //                     (int)y_point0 - 5 - triangle_scalar,
        //                     DISPLAY_WHITE);

        display_fillTriangle((int)x0,
                          0,
                          (int)x0 - 15 - triangle_scalar ,
                          15 - (triangle_scalar / 4),
                          (int)x0 + 15 + triangle_scalar,
                          15 - (triangle_scalar / 4),
                          DISPLAY_WHITE);
        
        lastDrawTop = true;
      }

      
      
      

        //update and erase the box
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
          gameover_control = map1_collide(x0, x1, x2, x3, y_point0, y_point1,
                                          y2, y3, y_velocity);
        } else if (level == 2) {
          map2();
          gameover_control = map2_collide(x0, x1, x2, x3, y_point0, y_point1,
                                          y2, y3, y_velocity);
        } else if (level == 3) {
          map3();
          gameover_control = map3_collide(x0, x1, x2, x3, y_point0, y_point1,
                                          y2, y3, y_velocity);
        }
      }
    }
    // change thrust value if button 1 is being pressed
    if (((button_value & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK) &&
        the_lander.fuel > 0) {
      thrust_x = get_thrust_x(&the_lander);
      thrust_y = get_thrust_y(&the_lander);
    } else {
      thrust_x = 0;
      thrust_y = 0;
    }
    // helper variable for the speed ranges between 0 and 1
    third_tick++;
    break;
  // fast delay transition
  case GAMEOVER:
    if (!gameover_drawn) {
      display_fillScreen(DISPLAY_BLACK);
      buttons_init();
      display_setCursor(SET_X_CURSOR + 60, SET_Y_CURSOR);
      display_setTextSize(6);
      display_setTextColor(DISPLAY_RED);
      display_println("GAME");
      display_setCursor(SET_X_CURSOR + 60, SET_Y_CURSOR + 50);
      display_setTextSize(6);
      display_setTextColor(DISPLAY_RED);
      display_println("OVER");
      display_setCursor(SET_X_CURSOR + 8, SET_Y_CURSOR + 170);
      display_setTextSize(2);
      display_setTextColor(DISPLAY_WHITE);
      display_println("Flip Switch 0 down to");
      display_setCursor(SET_X_CURSOR + 90, SET_Y_CURSOR + 190);
      display_setTextSize(2);
      display_setTextColor(DISPLAY_WHITE);
      display_println("restart");
      gameover_drawn = true;
    }
    break;
  // default to catch errors
  default:
    printf(DEFAULT_ERROR_MSG);
    break;
  }

  //-----------------------------------------------------------------------------------------------------------------------------------------
}