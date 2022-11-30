#include "lander.h"

//TODO:: there is a bug where if theta is 90 degrees it still changes the x_velocity when it should be zero at that angle
static double cos_degrees(double theta) {

  // convert radians to degrees

  theta = theta * (3.14 / 180);
  // printf("cos_degrees %f\n", cos(theta));
  if(theta == 90){
    return 0;
  } else {
  return cos(theta);
  }
}

static double sin_degrees(double theta) {

  // convert radians to degrees
  theta = theta * (3.14 / 180);
  // printf("sin_degrees %f\n", sin(theta));
  return sin(theta);
}

void lander_init(struct lander_t *lander) {

  lander->angle = 90;
  lander->has_landed = false;
  lander->location.x = 160;
  lander->location.y = 0;
  lander->vertical_velocity = 1;
  lander->horizontal_velocity = 0;
  printf("angle: %f\n", lander->angle);
}

// calculates the x and y thrust values given the current angle
double get_thrust_y(struct lander_t *lander) {
  return sin_degrees(lander->angle);
}

double get_thrust_x(struct lander_t *lander) {
  return cos_degrees(lander->angle);
}

// incrimient the angle
void lean_left(struct lander_t *lander) {
  if (lander->angle < 180) {
    lander->angle += 20;
  }
}

// decrement the angle
void lean_right(struct lander_t *lander) {
  if (lander->angle > 0) {
    lander->angle -= 20;
  }
}

void thrust(struct lander_t *lander);

// draw the lander at the current angle
void draw_lander(struct lander_t *lander) {}

display_point_t get_location();