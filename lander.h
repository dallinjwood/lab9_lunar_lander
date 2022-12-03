#ifndef LANDER
#define LANDER

#include "buttons.h"
#include "display.h"
#include "math.h"
#include <stdbool.h>
#include <stdio.h>

struct lander_t {
  double angle;
  int16_t fuel;
  display_point_t top_left;
  display_point_t top_right;
  display_point_t bottom_right;
  display_point_t bottom_left;
  int32_t vertical_velocity;
  int32_t horizontal_velocity;
  bool has_landed;
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

void thrust(struct lander_t *lander);

void draw_lander(struct lander_t *lander);

display_point_t get_location();

#endif /* LANDER */