#include "game_control.h"
#include "buttons.h"
#include "display.h"
#include "lander.h"
#include "maps.h"
#include "switches.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define FUEL_TEXT_CURSOR_X 30
#define FUEL_TEXT_CURSOR_Y 20
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
static long double triangle_scalar = 1;
static int16_t level = 5;
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

void draw_Menu() {
  display_setCursor(SET_X_CURSOR + 50, SET_Y_CURSOR);
  display_setTextSize(6);
  display_setTextColor(DISPLAY_WHITE);
  display_println("LUNAR");
  display_setCursor(SET_X_CURSOR + 35, SET_Y_CURSOR + 50);
  display_setTextSize(6);
  display_setTextColor(DISPLAY_WHITE);
  display_println("LANDER");
  display_setCursor(SET_X_CURSOR + 55, SET_Y_CURSOR + 110);
  display_setTextSize(1);
  display_setTextColor(DISPLAY_WHITE);
  display_println("Instructions:");
  display_setCursor(SET_X_CURSOR + 55, SET_Y_CURSOR + 130);
  display_setTextSize(1);
  display_setTextColor(DISPLAY_WHITE);
  display_println("Push Button 0 to Rotate Left");
  display_setCursor(SET_X_CURSOR + 55, SET_Y_CURSOR + 150);
  display_setTextSize(1);
  display_setTextColor(DISPLAY_WHITE);
  display_println("Push Button 3 to Rotate Right");
  display_setCursor(SET_X_CURSOR + 55, SET_Y_CURSOR + 170);
  display_setTextSize(1);
  display_setTextColor(DISPLAY_WHITE);
  display_println("Push Button 1 to Accelerate");
  display_setCursor(SET_X_CURSOR - 10, SET_Y_CURSOR + 190);
  display_setTextSize(2);
  display_setTextColor(DISPLAY_WHITE);
  display_println("Flip Switch 0 up to Start");
}

void erase_Menu() {
  display_setCursor(SET_X_CURSOR + 50, SET_Y_CURSOR);
  display_setTextSize(6);
  display_setTextColor(DISPLAY_BLACK);
  display_println("LUNAR");
  display_setCursor(SET_X_CURSOR + 35, SET_Y_CURSOR + 50);
  display_setTextSize(6);
  display_setTextColor(DISPLAY_BLACK);
  display_println("LANDER");
  display_setCursor(SET_X_CURSOR + 55, SET_Y_CURSOR + 110);
  display_setTextSize(1);
  display_setTextColor(DISPLAY_BLACK);
  display_println("Instructions:");
  display_setCursor(SET_X_CURSOR + 55, SET_Y_CURSOR + 130);
  display_setTextSize(1);
  display_setTextColor(DISPLAY_BLACK);
  display_println("Push Button 0 to Rotate Left");
  display_setCursor(SET_X_CURSOR + 55, SET_Y_CURSOR + 150);
  display_setTextSize(1);
  display_setTextColor(DISPLAY_BLACK);
  display_println("Push Button 3 to Rotate Right");
  display_setCursor(SET_X_CURSOR + 55, SET_Y_CURSOR + 170);
  display_setTextSize(1);
  display_setTextColor(DISPLAY_BLACK);
  display_println("Push Button 1 to Accelerate");
  display_setCursor(SET_X_CURSOR - 10, SET_Y_CURSOR + 190);
  display_setTextSize(2);
  display_setTextColor(DISPLAY_BLACK);
  display_println("Flip Switch 0 up to Start");
}

void draw_GameOver() {
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
}

void erase_GameOver() {
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
  draw_Menu();
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
      erase_Menu();
    }
    break;
  // transition state  transitions
  case TRANSITION:
    if ((led_value & SWITCHES_SW0_MASK) != SWITCHES_SW0_MASK) {
      currentState = MENU;
      gameControl_init(TICK_PERIOD);
      announcement_drawn = false;
      level = 5;
    }
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
        lander_init(&the_lander);
        map1();
      } else if ((level == 2) && (announcement_drawn)) {
        // erase level announcement
        display_setCursor(LEVEL_CURSOR_X, LEVEL_CURSOR_Y);
        display_setTextSize(LEVEL_SIZE);
        display_setTextColor(DISPLAY_BLACK);
        display_println("Level 2");
        announcement_drawn = false;
        lander_init(&the_lander);
        map2();
      } else if ((level == 3) && (announcement_drawn)) {
        // erase level announcement
        display_setCursor(LEVEL_CURSOR_X, LEVEL_CURSOR_Y);
        display_setTextSize(LEVEL_SIZE);
        display_setTextColor(DISPLAY_BLACK);
        display_println("Level 3");
        announcement_drawn = false;
        lander_init(&the_lander);
        map3();
      } else if ((level == 4) && (announcement_drawn)) {
        // erase level announcement
        display_setCursor(LEVEL_CURSOR_X, LEVEL_CURSOR_Y);
        display_setTextSize(LEVEL_SIZE);
        display_setTextColor(DISPLAY_BLACK);
        display_println("Level 4");
        announcement_drawn = false;
        lander_init(&the_lander);
        the_lander.top_right.y = 150;
        the_lander.top_left.y = 150;
        the_lander.bottom_left.y = 158;
        the_lander.bottom_right.y = 158;
        the_lander.velocity_x = -0.8;
        map4();
      } else if ((level == 5) && (announcement_drawn)) {
        // erase level announcement
        display_setCursor(LEVEL_CURSOR_X, LEVEL_CURSOR_Y);
        display_setTextSize(LEVEL_SIZE);
        display_setTextColor(DISPLAY_BLACK);
        display_println("Level 5");
        announcement_drawn = false;
        lander_init(&the_lander);
        the_lander.top_right.y = 150;
        the_lander.top_left.y = 150;
        the_lander.bottom_left.y = 158;
        the_lander.bottom_right.y = 158;
        the_lander.velocity_x = -0.8;
        map5();
      }
      // display_drawLine(the_lander.top_left.x, the_lander.top_left.y,
      //                  the_lander.top_right.x, the_lander.top_right.y,
      //                  DISPLAY_GREEN);
      // display_drawLine(the_lander.top_right.x, the_lander.top_right.y,
      //                  the_lander.bottom_right.x, the_lander.bottom_right.y,
      //                  DISPLAY_CYAN);
      // display_drawLine(the_lander.bottom_right.x, the_lander.bottom_right.y,
      //                  the_lander.bottom_left.x, the_lander.bottom_left.y,
      //                  DISPLAY_CYAN);
      // display_drawLine(the_lander.bottom_left.x, the_lander.bottom_left.y,
      //                  the_lander.top_left.x, the_lander.top_left.y,
      //                  DISPLAY_CYAN);
      // display_drawPixel(the_lander.top_left.x, the_lander.top_left.y,
      //                   DISPLAY_DARK_GREEN);
    }
    break;
  // INC_DEC transitions
  case GAMEPLAY:
    if ((led_value & SWITCHES_SW0_MASK) != SWITCHES_SW0_MASK) {
      currentState = MENU;
      gameControl_init(TICK_PERIOD);
      announcement_drawn = false;
      level = 5;
    } else if (gameover_control) {
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
        // draw explosion
        draw_explosion(&the_lander);

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
      erase_GameOver();
      gameover_drawn = false;
      level = 5;
      lander_init(&the_lander);

      // draw menu
      draw_Menu();
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
    } else if ((level == 4) && (!announcement_drawn)) {
      // draw level announcement
      display_setCursor(LEVEL_CURSOR_X, LEVEL_CURSOR_Y);
      display_setTextSize(LEVEL_SIZE);
      display_setTextColor(DISPLAY_WHITE);
      display_println("Level 4");
      announcement_drawn = true;
    } else if ((level == 5) && (!announcement_drawn)) {
      // draw level announcement
      display_setCursor(LEVEL_CURSOR_X, LEVEL_CURSOR_Y);
      display_setTextSize(LEVEL_SIZE);
      display_setTextColor(DISPLAY_WHITE);
      display_println("Level 5");
      announcement_drawn = true;
    }
    transition_cnt++;

    break;
  // gameplay actions
  case GAMEPLAY:
    button_value = buttons_read();

    // printf("vertical thrust: %f\n",get_thrust_y(&the_lander));
    // printf("horizontal thrust: %f\n\n",get_thrust_x(&the_lander));
    printf("vertical velocity: %f\t", the_lander.velocity_y);
    // printf("Theta: %f\n", the_lander.angle);
    // printf("horizontal velocity: %f\n\n", the_lander.velocity_x);
    // printf("NOT DEAD\n");

    // fuel text cursor
    display_setTextColor(DISPLAY_WHITE);
    display_setTextSize(1);
    display_setCursor(FUEL_TEXT_CURSOR_X, FUEL_TEXT_CURSOR_Y);
    display_println(FUEL_TEXT);

    // actual fuel cursor
    display_setCursor(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y);

    uint8_t button_value = buttons_read();

    display_drawRoundRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y + 10, 101,
                          10, 2, DISPLAY_WHITE);

    // change fuel text color based in how much fuel is left
    if (the_lander.fuel > 500) {

      display_fillRoundRect(FUEL_TEXT_CURSOR_X + 35 + the_lander.fuel / 10,
                            FUEL_TEXT_CURSOR_Y + 10, 1, 10, 2, DISPLAY_BLACK);
      display_fillRoundRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y + 10,
                            the_lander.fuel / 10, 10, 2, DISPLAY_WHITE);

      // display fuel number
      display_fillRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y, 30, 10,
                       DISPLAY_BLACK);
      display_printDecimalInt(the_lander.fuel);
    } else if (the_lander.fuel > 300 && the_lander.fuel <= 500) {
      display_fillRoundRect(FUEL_TEXT_CURSOR_X + 35 + the_lander.fuel / 10,
                            FUEL_TEXT_CURSOR_Y + 10, 1, 10, 2, DISPLAY_BLACK);

      display_fillRoundRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y + 10,
                            the_lander.fuel / 10, 10, 2, DISPLAY_YELLOW);

      // display fuel number
      display_setTextColor(DISPLAY_YELLOW);
      display_fillRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y, 30, 10,
                       DISPLAY_BLACK);
      display_printDecimalInt(the_lander.fuel);

    } else if (the_lander.fuel >= 0 && the_lander.fuel <= 300) {
      display_fillRoundRect(FUEL_TEXT_CURSOR_X + 35 + the_lander.fuel / 10,
                            FUEL_TEXT_CURSOR_Y + 10, 1, 10, 2, DISPLAY_BLACK);

      display_fillRoundRect(FUEL_TEXT_CURSOR_X + 35, FUEL_TEXT_CURSOR_Y + 10,
                            the_lander.fuel / 10, 10, 2, DISPLAY_RED);

      // display fuel number
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
    if (the_lander.top_left.y <= 240) {
      if (!gameover_control) {

        draw_lander(&the_lander);

        if (lastDrawLeft) {

          display_fillRect(0, 0, 25, DISPLAY_HEIGHT, DISPLAY_BLACK);

          lastDrawLeft = false;

        } else if (lastDrawRight) {

          display_fillRect(DISPLAY_WIDTH - 25, 0, 25, DISPLAY_HEIGHT,
                           DISPLAY_BLACK);

          lastDrawRight = false;

        } else if (lastDrawTop) {
          display_fillRect(0, 0, DISPLAY_WIDTH, 20, DISPLAY_BLACK);
          lastDrawTop = false;
        }

        if ((the_lander.top_left.x <= -10) ||
            (the_lander.bottom_left.x <= -10)) {
          // set triangle scalar
          if (the_lander.top_left.x >= -MAX_OFFSCREEN_CONSTANT) {
            triangle_scalar = (MAX_OFFSCREEN_CONSTANT - triangle_scalar +
                               (int)the_lander.top_left.x) /
                              30;
          }

          display_fillTriangle(
              0, (int)the_lander.top_left.y, 15 + (triangle_scalar / 4),
              (int)the_lander.top_left.y + 5 + triangle_scalar,
              15 + (triangle_scalar / 4),
              (int)the_lander.top_left.y - 5 - triangle_scalar, DISPLAY_WHITE);

          lastDrawLeft = true;

        } else if ((the_lander.top_right.x >= 330) ||
                   (the_lander.bottom_right.x >= 330)) {
          // set triangle scalar
          if (the_lander.top_left.x <= MAX_OFFSCREEN_CONSTANT) {
            triangle_scalar = (MAX_OFFSCREEN_CONSTANT + triangle_scalar -
                               (int)the_lander.top_left.x) /
                              30;
          }

          display_fillTriangle(DISPLAY_WIDTH, (int)the_lander.top_left.y,
                               DISPLAY_WIDTH - 15 - (triangle_scalar / 4),
                               (int)the_lander.top_left.y - 5 - triangle_scalar,
                               DISPLAY_WIDTH - 15 - (triangle_scalar / 4),
                               (int)the_lander.top_left.y + 5 + triangle_scalar,
                               DISPLAY_WHITE);

          lastDrawRight = true;
        } else if ((the_lander.top_left.y <= -10) ||
                   (the_lander.bottom_left.y <= -10)) {

          printf("triangle_scalar %f\t", triangle_scalar);
          if (the_lander.top_left.y >= -MAX_OFFSCREEN_CONSTANT && 0) {
            triangle_scalar =
                (double)(MAX_OFFSCREEN_CONSTANT - triangle_scalar +
                         (int)the_lander.top_left.y) /
                50.0;
          } else {
            triangle_scalar = 3;
          }

          display_fillTriangle(
              (int)the_lander.top_left.x, 0,
              (int)the_lander.top_left.x + 15 - triangle_scalar,
              18 + (triangle_scalar / 4),
              (int)the_lander.top_left.x - 15 + triangle_scalar,
              18 + (triangle_scalar / 4), DISPLAY_WHITE);

          printf("triangle_scalar %f\t", triangle_scalar);
          lastDrawTop = true;
        }

        y_velocity = y_velocity + gravity - (THRUST_SCALER * thrust_y);
        x_velocity = x_velocity + (THRUST_SCALER * thrust_x);
        // map1();
        if (level == 1) {
          map1();
          gameover_control = map1_collide(
              (double)the_lander.top_left.x, (double)the_lander.top_right.x,
              (double)the_lander.bottom_right.x,
              (double)the_lander.bottom_left.x, (double)the_lander.top_left.y,
              (double)the_lander.top_right.y, (double)the_lander.bottom_right.y,
              (double)the_lander.bottom_left.y, the_lander.velocity_y);
        } else if (level == 2) {
          map2();
          gameover_control =
              map2_collide(the_lander.top_left.x, the_lander.top_right.x,
                           the_lander.bottom_right.x, the_lander.bottom_left.x,
                           the_lander.top_left.y, the_lander.top_right.y,
                           the_lander.bottom_right.y, the_lander.bottom_left.y,
                           the_lander.velocity_y);
        } else if (level == 3) {
          map3();
          gameover_control =
              map3_collide(the_lander.top_left.x, the_lander.top_right.x,
                           the_lander.bottom_right.x, the_lander.bottom_left.x,
                           the_lander.top_left.y, the_lander.top_right.y,
                           the_lander.bottom_right.y, the_lander.bottom_left.y,
                           the_lander.velocity_y);
        } else if (level == 4) {
          map4();
          gameover_control =
              map4_collide(the_lander.top_left.x, the_lander.top_right.x,
                           the_lander.bottom_right.x, the_lander.bottom_left.x,
                           the_lander.top_left.y, the_lander.top_right.y,
                           the_lander.bottom_right.y, the_lander.bottom_left.y,
                           the_lander.velocity_y);
        } else if (level == 5) {
          map5();
          gameover_control =
              map5_collide(the_lander.top_left.x, the_lander.top_right.x,
                           the_lander.bottom_right.x, the_lander.bottom_left.x,
                           the_lander.top_left.y, the_lander.top_right.y,
                           the_lander.bottom_right.y, the_lander.bottom_left.y,
                           the_lander.velocity_y);
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

    break;
  // fast delay transition
  case GAMEOVER:
    if (!gameover_drawn) {
      draw_GameOver();
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