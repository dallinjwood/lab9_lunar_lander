#ifndef LANDER
#define LANDER

#include "buttons.h"
#include "display.h"
#include "math.h"
#include <stdbool.h>
#include <stdio.h>
#include "config.h"



typedef struct {
  double x;
  double y;
} display_point_double_t;

struct lander_t {
  double angle;
  int8_t position;
  int16_t fuel;
  display_point_double_t top_left;
  display_point_double_t top_right;
  display_point_double_t bottom_right;
  display_point_double_t bottom_left;
  double velocity_y;
  double velocity_x;
  bool has_landed;
  double thrust_x;
  double thrust_y;

};


void lander_init(struct lander_t *lander);

// calculates the x and y thrust values given the current angle
double get_thrust_y(struct lander_t *lander);
double get_thrust_x(struct lander_t *lander);

// draw the lander at the current angle
// void draw_lander(display_point_t corner);

// incrimient the angle
void lean_left(struct lander_t *lander);

// decrement the angle
void lean_right(struct lander_t *lander);

void set_position(struct lander_t *lander);

int8_t get_position(struct lander_t *lander);

void draw_lander(struct lander_t *lander);

void draw_lander_pos_Neg4(struct lander_t *lander, bool erase);

void draw_lander_pos_Neg3(struct lander_t *lander, bool erase);

void draw_lander_pos_Neg2(struct lander_t *lander, bool erase);

void draw_lander_pos_Neg1(struct lander_t *lander, bool erase);

void draw_lander_pos_0(struct lander_t *lander, bool erase);

void draw_lander_pos_1(struct lander_t *lander, bool erase);

void draw_lander_pos_2(struct lander_t *lander, bool erase);

void draw_lander_pos_3(struct lander_t *lander, bool erase);

void draw_lander_pos_4(struct lander_t *lander, bool erase);

#endif /* LANDER */