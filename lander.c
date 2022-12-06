#include "lander.h"

// TODO:: #define for init values
// TODO:: #define for angel ranges?

// TODO:: there is a bug where if theta is 90 degrees it still changes the
// x_velocity when it should be zero at that angle
static double cos_degrees(double theta) {

  // convert radians to degrees

  theta = theta * (3.14 / 180);
  // printf("cos_degrees %f\n", cos(theta));
  if (theta == 90) {
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
  lander->angle = ANGLE_90;
  lander->position = POS_0;
  lander->has_landed = false;

  //Set intial ciritical point values
  lander->top_left.x = TOP_LEFT_X_INIT;
  lander->top_left.y = TOP_Y_INIT;
  lander->top_right.x = TOP_RIGHT_X_INIT;
  lander->top_right.y = TOP_Y_INIT;
  lander->bottom_right.x = BOTTOM_RIGHT_X_INIT;
  lander->bottom_right.y = BOTTOM_Y_INIT;
  lander->bottom_left.x = BOTTOM_LEFT_X_INIT;
  lander->bottom_left.y = BOTTOM_Y_INIT;

  //set intial velocities
  lander->vertical_velocity = 1;
  lander->horizontal_velocity = 0;
  
  lander->fuel = 1000;

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

void draw_lander_pos_Neg4(struct lander_t *lander, bool erase) {

  //Erase
  if (erase) {
    display_drawFastHLine(lander->bottom_right.x - P_6, lander->bottom_right.y + P_0, P_7, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_8, lander->bottom_right.y + P_1, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_9, lander->bottom_right.y + P_2, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_9, lander->bottom_right.y + P_3, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_9, lander->bottom_right.y + P_4, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_9, lander->bottom_right.y + P_5, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_9, lander->bottom_right.y + P_6, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_9, lander->bottom_right.y + P_7, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_8, lander->bottom_right.y + P_8, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_6, lander->bottom_right.y + P_9, P_7, LANDER_BLACK);
  }

  //Draw
  else {
    //Draw critical points
    display_drawPixel(lander->top_left.x, lander->top_left.y, LANDER_YELLOW);
    display_drawPixel(lander->top_right.x, lander->top_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_right.x, lander->bottom_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_left.x, lander->bottom_left.y, LANDER_YELLOW);

    //Draw everything else

    //Line 1
    display_drawPixel(lander->bottom_right.x - P_1, lander->bottom_right.y, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y, LANDER_DARK_GRAY);
    //Line 2
    display_drawPixel(lander->bottom_right.x - P_1, lander->bottom_right.y + P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_1, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_8, lander->bottom_right.y + P_1, LANDER_DARK_GRAY);
    //Line 3
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_2, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_9, lander->bottom_right.y + P_2, LANDER_DARK_GRAY);
    //Line 4
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_3, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_8, lander->bottom_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_9, lander->bottom_right.y + P_3, LANDER_DARK_GRAY);
    //Line 5
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_4, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_8, lander->bottom_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_9, lander->bottom_right.y + P_4, LANDER_DARK_GRAY);
    //Line 6
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_5, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_8, lander->bottom_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_9, lander->bottom_right.y + P_5, LANDER_DARK_GRAY);
    //Line 7
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_8, lander->bottom_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_9, lander->bottom_right.y + P_6, LANDER_DARK_GRAY);
    //Line 8
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_7, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_9, lander->bottom_right.y + P_7, LANDER_DARK_GRAY);
    //Line 9
    display_drawPixel(lander->bottom_right.x - P_1, lander->bottom_right.y + P_8, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_8, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_8, lander->bottom_right.y + P_8, LANDER_DARK_GRAY);
    //Line 10
    display_drawPixel(lander->bottom_right.x - P_1, lander->bottom_right.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_9, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_9, LANDER_DARK_GRAY);
  }
}

void draw_lander_pos_Neg3(struct lander_t *lander, bool erase) {
  //Erase
  if (erase) {
    display_drawFastHLine(lander->bottom_right.x - P_7, lander->bottom_right.y - P_1, P_6, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_7, lander->bottom_right.y + P_0, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_8, lander->bottom_right.y + P_1, P_9, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_8, lander->bottom_right.y + P_2, P_7, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_9, lander->bottom_right.y + P_3, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_9, lander->bottom_right.y + P_4, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_9, lander->bottom_right.y + P_5, P_7, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_9, lander->bottom_right.y + P_6, P_7, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_8, lander->bottom_right.y + P_7, P_6, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_4, lander->bottom_right.y + P_8, P_4, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_right.x - P_3, lander->bottom_right.y + P_9, P_3, LANDER_BLACK);
  }

  //Draw
  else {
    //Draw critical points
    display_drawPixel(lander->top_left.x, lander->top_left.y, LANDER_YELLOW);
    display_drawPixel(lander->top_right.x, lander->top_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_right.x, lander->bottom_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_left.x, lander->bottom_left.y, LANDER_YELLOW);

    //Draw everything else

    //Line 1
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y - P_1, LANDER_GRAY);
    //Line 2
    display_drawPixel(lander->bottom_right.x - P_1, lander->bottom_right.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_0, LANDER_LIGHT_GRAY);
    //Line 3
    display_drawPixel(lander->bottom_right.x - P_0, lander->bottom_right.y + P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_1, lander->bottom_right.y + P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_9, lander->bottom_right.y + P_1, LANDER_GRAY);
    //Line 4
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_2, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_8, lander->bottom_right.y + P_2, LANDER_GRAY);
    //Line 5
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_3, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_8, lander->bottom_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_9, lander->bottom_right.y + P_3, LANDER_DARK_GRAY);
    //Line 6
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_4, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_8, lander->bottom_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_9, lander->bottom_right.y + P_4, LANDER_DARK_GRAY);
    //Line 7
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_5, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_8, lander->bottom_right.y + P_5, LANDER_LIGHT_GRAY);
    //Line 8
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_8, lander->bottom_right.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->bottom_right.x - P_9, lander->bottom_right.y + P_6, LANDER_DARK_GRAY);
    //Line 9
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_6, lander->bottom_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_7, lander->bottom_right.y + P_7, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_8, lander->bottom_right.y + P_7, LANDER_DARK_GRAY);
    //Line 10
    display_drawPixel(lander->bottom_right.x - P_2, lander->bottom_right.y + P_8, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_5, lander->bottom_right.y + P_8, LANDER_DARK_GRAY);
    //Line 11
    display_drawPixel(lander->bottom_right.x - P_3, lander->bottom_right.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_right.x - P_4, lander->bottom_right.y + P_9, LANDER_DARK_GRAY);
  }
}

void draw_lander_pos_Neg2(struct lander_t *lander, bool erase) {

  //Erase
  if (erase) {
    display_drawFastHLine(lander->top_right.x - P_1, lander->top_right.y + P_0, P_3,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_2, lander->top_right.y + P_1, P_6,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_3, lander->top_right.y + P_2, P_8,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_3, lander->top_right.y + P_3, P_10, LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_4, lander->top_right.y + P_4, P_12, LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_4, lander->top_right.y + P_5, P_12, LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_4, lander->top_right.y + P_6, P_8,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_3, lander->top_right.y + P_7, P_6,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_2, lander->top_right.y + P_8, P_5,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_1, lander->top_right.y + P_9, P_4,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_0, lander->top_right.y + P_10, P_2, LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x + P_1, lander->top_right.y + P_11, P_1, LANDER_BLACK);
  }

  //Draw
  else {
    //Draw critical points
    display_drawPixel(lander->top_left.x, lander->top_left.y, LANDER_YELLOW);
    display_drawPixel(lander->top_right.x, lander->top_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_right.x, lander->bottom_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_left.x, lander->bottom_left.y, LANDER_YELLOW);

    //Draw everything else

    //Line 1
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_0, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_0, LANDER_DARK_GRAY);
    //Line 2
    display_drawPixel(lander->top_right.x + P_3, lander->top_right.y + P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_1, LANDER_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_1, LANDER_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_1, LANDER_DARK_GRAY);
    //Line 3
    display_drawPixel(lander->top_right.x + P_4, lander->top_right.y + P_2, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_3, lander->top_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_2, LANDER_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_2, LANDER_DARK_GRAY);
    //Line 4
    display_drawPixel(lander->top_right.x + P_6, lander->top_right.y + P_3, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_5, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_4, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_3, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_3, LANDER_GRAY);
    //Line 5
    display_drawPixel(lander->top_right.x + P_7, lander->top_right.y + P_4, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_6, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_5, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_4, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_3, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_4, lander->top_right.y + P_4, LANDER_DARK_GRAY);    
    //Line 6
    display_drawPixel(lander->top_right.x + P_6, lander->top_right.y + P_5, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_5, lander->top_right.y + P_5, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_4, lander->top_right.y + P_5, LANDER_GRAY);
    display_drawPixel(lander->top_right.x + P_3, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    //Line 7
    display_drawPixel(lander->top_right.x + P_3, lander->top_right.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_right.x - P_4, lander->top_right.y + P_6, LANDER_DARK_GRAY);
    //Line 8
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_7, LANDER_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_7, LANDER_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_7, LANDER_DARK_GRAY);
    //Line 9
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_8, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_8, LANDER_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_8, LANDER_DARK_GRAY);
    //Line 10
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_9, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_9, LANDER_GRAY);
    //Line 11
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_10, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_0, lander->top_right.y + P_10, LANDER_DARK_GRAY);
  }
}

void draw_lander_pos_Neg1(struct lander_t *lander, bool erase) {

  //Erase
  if (erase) {
    display_drawFastHLine(lander->top_right.x - P_2, lander->top_right.y + P_0, P_4,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_4, lander->top_right.y + P_1, P_7,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_6, lander->top_right.y + P_2, P_9,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_6, lander->top_right.y + P_3, P_9,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_6, lander->top_right.y + P_4, P_10, LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_6, lander->top_right.y + P_5, P_10, LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_6, lander->top_right.y + P_6, P_11, LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_6, lander->top_right.y + P_7, P_6,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x + P_3, lander->top_right.y + P_7, P_1,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_5, lander->top_right.y + P_8, P_2,  LANDER_BLACK);
    display_drawFastHLine(lander->top_right.x - P_4, lander->top_right.y + P_9, P_1,  LANDER_BLACK);
  }

  //Draw
  else {
    //Draw critical points
    display_drawPixel(lander->top_left.x, lander->top_left.y, LANDER_YELLOW);
    display_drawPixel(lander->top_right.x, lander->top_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_right.x, lander->bottom_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_left.x, lander->bottom_left.y, LANDER_YELLOW);

    //Draw everything else

    //Line 1
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_0, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_0, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_0, LANDER_DARK_GRAY);
    //Line 2
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_1, LANDER_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_1, LANDER_GRAY);
    display_drawPixel(lander->top_right.x - P_4, lander->top_right.y + P_1, LANDER_GRAY);
    //Line 3
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_2, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_4, lander->top_right.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_6, lander->top_right.y + P_2, LANDER_GRAY);
    //Line 4
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_4, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_5, lander->top_right.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_6, lander->top_right.y + P_3, LANDER_DARK_GRAY);
    //Line 5
    display_drawPixel(lander->top_right.x + P_3, lander->top_right.y + P_4, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_4, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_5, lander->top_right.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_6, lander->top_right.y + P_4, LANDER_DARK_GRAY);
    //Line 6
    display_drawPixel(lander->top_right.x + P_3, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_4, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_5, lander->top_right.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_6, lander->top_right.y + P_5, LANDER_DARK_GRAY);
    //Line 7
    display_drawPixel(lander->top_right.x + P_4, lander->top_right.y + P_6, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_3, lander->top_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x + P_2, lander->top_right.y + P_6, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x + P_1, lander->top_right.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_right.x - P_0, lander->top_right.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_4, lander->top_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_5, lander->top_right.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_6, lander->top_right.y + P_6, LANDER_DARK_GRAY);
    //Line 8
    display_drawPixel(lander->top_right.x + P_3, lander->top_right.y + P_7, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x - P_1, lander->top_right.y + P_7, LANDER_GRAY);
    display_drawPixel(lander->top_right.x - P_2, lander->top_right.y + P_7, LANDER_GRAY);
    display_drawPixel(lander->top_right.x - P_3, lander->top_right.y + P_7, LANDER_DARK_GRAY);    
    display_drawPixel(lander->top_right.x - P_4, lander->top_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_5, lander->top_right.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_right.x - P_6, lander->top_right.y + P_7, LANDER_DARK_GRAY);
    //Line 9
    display_drawPixel(lander->top_right.x - P_4, lander->top_right.y + P_8, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_right.x - P_5, lander->top_right.y + P_8, LANDER_LIGHT_GRAY);
    //Line 10
    display_drawPixel(lander->top_right.x - P_4, lander->top_left.y + P_9, LANDER_DARK_GRAY);
  }
}

void draw_lander_pos_0(struct lander_t *lander, bool erase) {
  //Erase
  if (erase) {
    display_drawFastHLine(lander->top_left.x + P_0, lander->top_left.y - P_1, P_6,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_1, lander->top_left.y + P_0, P_8,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_1, lander->top_left.y + P_1, P_8,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_1, lander->top_left.y + P_2, P_8,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_2, lander->top_left.y + P_3, P_10, LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_2, lander->top_left.y + P_4, P_10, LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_2, lander->top_left.y + P_5, P_10, LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_2, lander->top_left.y + P_6, P_10, LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_2, lander->top_left.y + P_7, P_2,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_2, lander->top_left.y + P_8, P_1,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x + P_6, lander->top_left.y + P_7, P_2,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x + P_7, lander->top_left.y + P_8, P_1,  LANDER_BLACK);
  }

  //Draw
  else {
    //Draw critical points
    display_drawPixel(lander->top_left.x, lander->top_left.y, LANDER_YELLOW);
    display_drawPixel(lander->top_right.x, lander->top_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_right.x, lander->bottom_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_left.x, lander->bottom_left.y, LANDER_YELLOW);

    //Draw everything else

    //Line 0
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y - P_1, LANDER_DARK_GRAY);
    //Line 1
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_0, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_0, LANDER_DARK_GRAY);
    //Line 2
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_1, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_1, LANDER_GRAY);
    //Line 3
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    //Line 4
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_3, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_7, lander->top_left.y + P_3, LANDER_DARK_GRAY);
    //Line 5
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_4, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_7, lander->top_left.y + P_4, LANDER_DARK_GRAY);
    //Line 6
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_7, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    //Line 7
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_7, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    //Line 8
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_7, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_7, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_7, lander->top_left.y + P_7, LANDER_LIGHT_GRAY);
  }
}

void draw_lander_pos_1(struct lander_t *lander, bool erase) {

  //Erase
  if (erase) {
    display_drawFastHLine(lander->top_left.x - P_1, lander->top_left.y + P_0, P_4,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_2, lander->top_left.y + P_1, P_7,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_2, lander->top_left.y + P_2, P_9,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_2, lander->top_left.y + P_3, P_9,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_3, lander->top_left.y + P_4, P_10, LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_3, lander->top_left.y + P_5, P_10, LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_4, lander->top_left.y + P_6, P_11, LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x + P_1, lander->top_left.y + P_7, P_6,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_3, lander->top_left.y + P_7, P_1,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x + P_4, lander->top_left.y + P_8, P_2,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x + P_4, lander->top_left.y + P_9, P_1,  LANDER_BLACK);
  }

  //Draw
  else {
    //Draw critical points
    display_drawPixel(lander->top_left.x, lander->top_left.y, LANDER_YELLOW);
    display_drawPixel(lander->top_right.x, lander->top_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_right.x, lander->bottom_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_left.x, lander->bottom_left.y, LANDER_YELLOW);

    //Draw everything else

    //Line 1
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_0, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_0, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_0, LANDER_DARK_GRAY);
    //Line 2
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_1, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_1, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_1, LANDER_GRAY);
    //Line 3
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_2, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_2, LANDER_GRAY);
    //Line 4
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_3, LANDER_DARK_GRAY);
    //Line 5
    display_drawPixel(lander->top_left.x - P_3, lander->top_left.y + P_4, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_4, LANDER_DARK_GRAY);
    //Line 6
    display_drawPixel(lander->top_left.x - P_3, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_5, LANDER_DARK_GRAY);
    //Line 7
    display_drawPixel(lander->top_left.x - P_4, lander->top_left.y + P_6, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_3, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_6, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_6, LANDER_DARK_GRAY);
    //Line 8
    display_drawPixel(lander->top_left.x - P_3, lander->top_left.y + P_7, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_7, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_7, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_7, LANDER_DARK_GRAY);    
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_6, lander->top_left.y + P_7, LANDER_DARK_GRAY);
    //Line 9
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_8, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_5, lander->top_left.y + P_8, LANDER_LIGHT_GRAY);
    //Line 10
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_9, LANDER_DARK_GRAY);
  }
}

void draw_lander_pos_2(struct lander_t *lander, bool erase) {

  //Erase
  if (erase) {
    display_drawFastHLine(lander->top_left.x - P_1, lander->top_left.y + P_0, P_3,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_3, lander->top_left.y + P_1, P_6,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_4, lander->top_left.y + P_2, P_8,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_6, lander->top_left.y + P_3, P_10, LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_7, lander->top_left.y + P_4, P_12, LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_7, lander->top_left.y + P_5, P_12, LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_3, lander->top_left.y + P_6, P_8,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_2, lander->top_left.y + P_7, P_6,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_2, lander->top_left.y + P_8, P_5,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_2, lander->top_left.y + P_9, P_4,  LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_1, lander->top_left.y + P_10, P_2, LANDER_BLACK);
    display_drawFastHLine(lander->top_left.x - P_1, lander->top_left.y + P_11, P_1, LANDER_BLACK);
  }

  //Draw
  else {
    //Draw critical points
    display_drawPixel(lander->top_left.x, lander->top_left.y, LANDER_YELLOW);
    display_drawPixel(lander->top_right.x, lander->top_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_right.x, lander->bottom_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_left.x, lander->bottom_left.y, LANDER_YELLOW);

    //Draw everything else

    //Line 1
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_0, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_0, LANDER_DARK_GRAY);
    //Line 2
    display_drawPixel(lander->top_left.x - P_3, lander->top_left.y + P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_1, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_1, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_1, LANDER_DARK_GRAY);
    //Line 3
    display_drawPixel(lander->top_left.x - P_4, lander->top_left.y + P_2, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_3, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_2, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_2, LANDER_DARK_GRAY);
    //Line 4
    display_drawPixel(lander->top_left.x - P_6, lander->top_left.y + P_3, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_5, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_4, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_3, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_3, LANDER_GRAY);
    //Line 5
    display_drawPixel(lander->top_left.x - P_7, lander->top_left.y + P_4, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_6, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_5, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_4, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_3, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_4, LANDER_DARK_GRAY);    
    //Line 6
    display_drawPixel(lander->top_left.x - P_6, lander->top_left.y + P_5, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_5, lander->top_left.y + P_5, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_4, lander->top_left.y + P_5, LANDER_GRAY);
    display_drawPixel(lander->top_left.x - P_3, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_5, LANDER_LIGHT_GRAY);
    //Line 7
    display_drawPixel(lander->top_left.x - P_3, lander->top_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_4, lander->top_left.y + P_6, LANDER_DARK_GRAY);
    //Line 8
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_7, LANDER_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_7, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_3, lander->top_left.y + P_7, LANDER_DARK_GRAY);
    //Line 9
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_8, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_8, LANDER_GRAY);
    display_drawPixel(lander->top_left.x + P_2, lander->top_left.y + P_8, LANDER_DARK_GRAY);
    //Line 10
    display_drawPixel(lander->top_left.x - P_2, lander->top_left.y + P_9, LANDER_DARK_GRAY);
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_0, lander->top_left.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x + P_1, lander->top_left.y + P_9, LANDER_GRAY);
    //Line 11
    display_drawPixel(lander->top_left.x - P_1, lander->top_left.y + P_10, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->top_left.x - P_0, lander->top_left.y + P_10, LANDER_DARK_GRAY);
  }
}

void draw_lander_pos_3(struct lander_t *lander, bool erase) {
  //Erase
  if (erase) {
    display_drawFastHLine(lander->bottom_left.x + P_2, lander->bottom_left.y - P_1, P_6, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_0, lander->bottom_left.y + P_0, P_7, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_0, lander->bottom_left.y + P_1, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_2, lander->bottom_left.y + P_2, P_7, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_2, lander->bottom_left.y + P_3, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_2, lander->bottom_left.y + P_4, P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_3, lander->bottom_left.y + P_5, P_7, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_3, lander->bottom_left.y + P_6, P_7, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_3, lander->bottom_left.y + P_7, P_6, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_2, lander->bottom_left.y + P_8, P_4, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_2, lander->bottom_left.y + P_9, P_3, LANDER_BLACK);
  }

  //Draw
  else {
    //Draw critical points
    display_drawPixel(lander->top_left.x, lander->top_left.y, LANDER_YELLOW);
    display_drawPixel(lander->top_right.x, lander->top_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_right.x, lander->bottom_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_left.x, lander->bottom_left.y, LANDER_YELLOW);

    //Draw everything else

    //Line 1
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y - P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y - P_1, LANDER_GRAY);
    //Line 2
    display_drawPixel(lander->bottom_left.x + P_1, lander->bottom_left.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_0, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_0, LANDER_LIGHT_GRAY);
    //Line 3
    display_drawPixel(lander->bottom_left.x + P_0, lander->bottom_left.y + P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_1, lander->bottom_left.y + P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_9, lander->bottom_left.y + P_1, LANDER_GRAY);
    //Line 4
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_2, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_8, lander->bottom_left.y + P_2, LANDER_GRAY);
    //Line 5
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_3, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_8, lander->bottom_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_9, lander->bottom_left.y + P_3, LANDER_DARK_GRAY);
    //Line 6
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_4, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_8, lander->bottom_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_9, lander->bottom_left.y + P_4, LANDER_DARK_GRAY);
    //Line 7
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_5, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_8, lander->bottom_left.y + P_5, LANDER_LIGHT_GRAY);
    //Line 8
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_8, lander->bottom_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_9, lander->bottom_left.y + P_6, LANDER_DARK_GRAY);
    //Line 9
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_7, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_8, lander->bottom_left.y + P_7, LANDER_DARK_GRAY);
    //Line 10
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_8, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_8, LANDER_DARK_GRAY);
    //Line 11
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_9, LANDER_DARK_GRAY);
  }
}

void draw_lander_pos_4(struct lander_t *lander, bool erase) {

  //Erase
  if (erase) {
    display_drawFastHLine(lander->bottom_left.x + P_0, lander->bottom_left.y + P_0,  P_7, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_1, lander->bottom_left.y + P_1,  P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_2, lander->bottom_left.y + P_2,  P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_2, lander->bottom_left.y + P_3,  P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_2, lander->bottom_left.y + P_4,  P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_2, lander->bottom_left.y + P_5,  P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_2, lander->bottom_left.y + P_6,  P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_2, lander->bottom_left.y + P_7,  P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_1, lander->bottom_left.y + P_8,  P_8, LANDER_BLACK);
    display_drawFastHLine(lander->bottom_left.x + P_0, lander->bottom_left.y + P_10, P_7, LANDER_BLACK);
  }

  //Draw
  else {
    //Draw critical points
    display_drawPixel(lander->top_left.x, lander->top_left.y, LANDER_YELLOW);
    display_drawPixel(lander->top_right.x, lander->top_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_right.x, lander->bottom_right.y, LANDER_YELLOW);
    display_drawPixel(lander->bottom_left.x, lander->bottom_left.y, LANDER_YELLOW);

    //Draw everything else

    //Line 1
    display_drawPixel(lander->bottom_left.x + P_1, lander->bottom_left.y, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y, LANDER_DARK_GRAY);
    //Line 2
    display_drawPixel(lander->bottom_left.x + P_1, lander->bottom_left.y + P_1, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_1, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_1, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_8, lander->bottom_left.y + P_1, LANDER_DARK_GRAY);
    //Line 3
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_2, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_2, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_9, lander->bottom_left.y + P_2, LANDER_DARK_GRAY);
    //Line 4
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_3, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_8, lander->bottom_left.y + P_3, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_9, lander->bottom_left.y + P_3, LANDER_DARK_GRAY);
    //Line 5
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_4, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_8, lander->bottom_left.y + P_4, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_9, lander->bottom_left.y + P_4, LANDER_DARK_GRAY);
    //Line 6
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_5, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_8, lander->bottom_left.y + P_5, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_9, lander->bottom_left.y + P_5, LANDER_DARK_GRAY);
    //Line 7
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_6, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_8, lander->bottom_left.y + P_6, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_9, lander->bottom_left.y + P_6, LANDER_DARK_GRAY);
    //Line 8
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_7, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_7, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_9, lander->bottom_left.y + P_7, LANDER_DARK_GRAY);
    //Line 9
    display_drawPixel(lander->bottom_left.x + P_1, lander->bottom_left.y + P_8, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_8, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_7, lander->bottom_left.y + P_8, LANDER_GRAY);
    display_drawPixel(lander->bottom_left.x + P_8, lander->bottom_left.y + P_8, LANDER_DARK_GRAY);
    //Line 10
    display_drawPixel(lander->bottom_left.x + P_1, lander->bottom_left.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_2, lander->bottom_left.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_3, lander->bottom_left.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_4, lander->bottom_left.y + P_9, LANDER_LIGHT_GRAY);
    display_drawPixel(lander->bottom_left.x + P_5, lander->bottom_left.y + P_9, LANDER_DARK_GRAY);
    display_drawPixel(lander->bottom_left.x + P_6, lander->bottom_left.y + P_9, LANDER_DARK_GRAY);
  }
}


//Draws fire for lander based on position. Also handles "flickering"
void draw_lander_fire(struct lander_t *lander, bool erase) {

  //This bool will change each call to this function
  static bool flicker = false;

  //Check position of lander, then draw fire accordingly relative to the expected critical points


}

//Set position based on angle ranges, as well as the 4 critical points
void set_position(struct lander_t *lander) {

  //Get button value
  uint8_t button_value = buttons_read();


/////////////////Turning RIGHT///////////////////////
  //Position -4 to -3
  if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) && 
      ((lander->angle >= ANGLE_160) && (lander->angle < ANGLE_180))) {

        //Set position value
        lander->position = POS_NEG3;

        //set critical point values, relative to angle range
        lander->top_left.x     -= P_1;
        lander->top_left.y     -= P_1;
        lander->top_right.x    += P_1;
        lander->top_right.y    -= P_1;
        lander->bottom_right.x += P_0;
        lander->bottom_right.y += P_1;
        lander->bottom_left.x  -= P_2;
        lander->bottom_left.y  += P_1;

        lean_right(lander);
  }
  //Position -3 to -2
  else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) && 
      ((lander->angle >= ANGLE_140) && (lander->angle < ANGLE_160))) {

        //Set position value
        lander->position = POS_NEG2;

        //set critical point values, relative to angle range
        lander->top_left.x     -= P_1;
        lander->top_left.y     -= P_1;
        lander->top_right.x    += P_1;
        lander->top_right.y    -= P_1;
        lander->bottom_right.x += P_1;
        lander->bottom_right.y += P_4;
        lander->bottom_left.x  -= P_3;
        lander->bottom_left.y  += P_1;

        lean_right(lander);
  }
  //Position -2 to -1
  else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) && 
      ((lander->angle >= ANGLE_120) && (lander->angle < ANGLE_140))) {

        //Set position value
        lander->position = POS_NEG1;

        //set critical point values, relative to angle range
        lander->top_left.x     += P_2;
        lander->top_left.y     -= P_3;
        lander->top_right.x    += P_3;
        lander->top_right.y    += P_0;
        lander->bottom_right.x += P_0;
        lander->bottom_right.y += P_2;
        lander->bottom_left.x  -= P_3;
        lander->bottom_left.y  -= P_2;

        lean_right(lander);
  }
  //Position -1 to 0
  else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) && 
      ((lander->angle >= ANGLE_100) && (lander->angle < ANGLE_120))) {

        //Set position value
        lander->position = POS_0;

        //set critical point values, relative to angle range
        lander->top_left.x     += P_1;
        lander->top_left.y     -= P_1;
        lander->top_right.x    += P_1;
        lander->top_right.y    += P_1;
        lander->bottom_right.x -= P_1;
        lander->bottom_right.y += P_2;
        lander->bottom_left.x  -= P_1;
        lander->bottom_left.y  += P_0;

        lean_right(lander);
  }
  //Position 0 to 1
  else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) && 
      ((lander->angle >= ANGLE_80) && (lander->angle <= ANGLE_100))) {

        //Set position value
        lander->position = POS_1;

        //set critical point values, relative to angle range
        lander->top_left.x     += P_1;
        lander->top_left.y     -= P_1;
        lander->top_right.x    += P_1;
        lander->top_right.y    += P_1;
        lander->bottom_right.x -= P_1;
        lander->bottom_right.y += P_0;
        lander->bottom_left.x  -= P_1;
        lander->bottom_left.y  -= P_2;

        lean_right(lander);
  }
  //Position 1 to 2
  else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) && 
      ((lander->angle >= ANGLE_60) && (lander->angle < ANGLE_80))) {

        //Set position value
        lander->position = POS_2;

        //set critical point values, relative to angle range
        lander->top_left.x     += P_3;
        lander->top_left.y     += P_0;
        lander->top_right.x    += P_2;
        lander->top_right.y    += P_3;
        lander->bottom_right.x -= P_3;
        lander->bottom_right.y += P_2;
        lander->bottom_left.x  += P_0;
        lander->bottom_left.y  -= P_2;

        lean_right(lander);
  }
  //Position 2 to 3
  else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) && 
      ((lander->angle >= ANGLE_40) && (lander->angle < ANGLE_60))) {

        //Set position value
        lander->position = POS_3;

        //set critical point values, relative to angle range
        lander->top_left.x     += P_1;
        lander->top_left.y     += P_1;
        lander->top_right.x    -= P_1;
        lander->top_right.y    += P_1;
        lander->bottom_right.x -= P_3;
        lander->bottom_right.y -= P_1;
        lander->bottom_left.x  += P_1;
        lander->bottom_left.y  -= P_4;

        lean_right(lander);
  }
  //Position 3 to 4
  else if (((button_value & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) && 
      ((lander->angle >= ANGLE_20) && (lander->angle < ANGLE_40))) {

        //Set position value
        lander->position = POS_4;

        //set critical point values, relative to angle range
        lander->top_left.x     += P_1;
        lander->top_left.y     += P_1;
        lander->top_right.x    -= P_1;
        lander->top_right.y    += P_1;
        lander->bottom_right.x -= P_2;
        lander->bottom_right.y -= P_1;
        lander->bottom_left.x  += P_0;
        lander->bottom_left.y  -= P_1;

        lean_right(lander);
  }
///////////////Turning LEFT/////////////////////////////
  //Position 4 to 3
  else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) && 
      ((lander->angle >= ANGLE_0) && (lander->angle < ANGLE_20))) {
        
        //Set position value
        lander->position = POS_3;

        //set critical point values, relative to angle range
        lander->top_left.y     -= P_1;
        lander->top_left.x     -= P_1;
        lander->top_right.x    += P_1;
        lander->top_right.y    -= P_1;
        lander->bottom_right.x += P_2;
        lander->bottom_right.y += P_1;
        lander->bottom_left.x  -= P_0;
        lander->bottom_left.y  += P_1;

        lean_left(lander);
  }
  //Position 3 to 2
  else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) && 
      ((lander->angle >= ANGLE_20) && (lander->angle < ANGLE_40))) {
        
        //Set position value
        lander->position = POS_2;

        //set critical point values, relative to angle range
        lander->top_left.x     -= P_1;
        lander->top_left.y     -= P_1;
        lander->top_right.x    += P_1;
        lander->top_right.y    -= P_1;
        lander->bottom_right.x += P_3;
        lander->bottom_right.y += P_1;
        lander->bottom_left.x  -= P_1;
        lander->bottom_left.y  += P_4;

        lean_left(lander);
  }
  //Position 2 to 1
  else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) && 
      ((lander->angle >= ANGLE_40) && (lander->angle < ANGLE_60))) {
        
        //Set position value
        lander->position = POS_1;

        //set critical point values, relative to angle range
        lander->top_left.x     -= P_3;
        lander->top_left.y     -= P_0;
        lander->top_right.x    -= P_2;
        lander->top_right.y    -= P_3;
        lander->bottom_right.x += P_3;
        lander->bottom_right.y -= P_2;
        lander->bottom_left.x  -= P_0;
        lander->bottom_left.y  += P_2;

        lean_left(lander);
  }
  //Position 1 to 0
  else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) && 
      ((lander->angle >= ANGLE_60) && (lander->angle < ANGLE_80))) {
        
        //Set position value
        lander->position = POS_0;

        //set critical point values, relative to angle range
        lander->top_left.x     -= P_1;
        lander->top_left.y     += P_1;
        lander->top_right.x    -= P_1;
        lander->top_right.y    -= P_1;
        lander->bottom_right.x += P_1;
        lander->bottom_right.y -= P_0;
        lander->bottom_left.x  += P_1;
        lander->bottom_left.y  += P_2;

        lean_left(lander);
  }
  //Position 0 to -1
  else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) && 
      ((lander->angle >= ANGLE_80) && (lander->angle < ANGLE_100))) {
        
        //Set position value
        lander->position = POS_NEG1;

        //set critical point values, relative to angle range
        lander->top_left.x     -= P_1;
        lander->top_left.y     += P_1;
        lander->top_right.x    -= P_1;
        lander->top_right.y    -= P_1;
        lander->bottom_right.x += P_1;
        lander->bottom_right.y -= P_2;
        lander->bottom_left.x  += P_1;
        lander->bottom_left.y  -= P_0;

        lean_left(lander);
  }
  //Position -1 to -2
  else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) && 
      ((lander->angle >= ANGLE_100) && (lander->angle < ANGLE_120))) {
        
        //Set position value
        lander->position = POS_NEG2;

        //set critical point values, relative to angle range
        lander->top_left.x     -= P_2;
        lander->top_left.y     += P_3;
        lander->top_right.x    -= P_3;
        lander->top_right.y    -= P_0;
        lander->bottom_right.x -= P_0;
        lander->bottom_right.y -= P_2;
        lander->bottom_left.x  += P_3;
        lander->bottom_left.y  += P_2;

        lean_left(lander);
  }
  //Position -2 to -3
  else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) && 
      ((lander->angle >= ANGLE_120) && (lander->angle < ANGLE_140))) {
        
        //Set position value
        lander->position = POS_NEG3;

        //set critical point values, relative to angle range
        lander->top_left.x     += P_1;
        lander->top_left.y     += P_1;
        lander->top_right.x    -= P_1;
        lander->top_right.y    += P_1;
        lander->bottom_right.x -= P_1;
        lander->bottom_right.y -= P_4;
        lander->bottom_left.x  += P_3;
        lander->bottom_left.y  -= P_1;

        lean_left(lander);
  }
  //Position -3 to -4
  else if (((button_value & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) && 
      ((lander->angle >= ANGLE_140) && (lander->angle < ANGLE_160))) {
        
        //Set position value
        lander->position = POS_NEG4;

        //set critical point values, relative to angle range
        lander->top_left.x     += P_1;
        lander->top_left.y     += P_1;
        lander->top_right.x    -= P_1;
        lander->top_right.y    += P_1;
        lander->bottom_right.x -= P_0;
        lander->bottom_right.y -= P_1;
        lander->bottom_left.x  += P_2;
        lander->bottom_left.y  -= P_1;

        lean_left(lander);
  }

}

//Gets current position of lander
int8_t get_position(struct lander_t *lander) {
  return lander->position;  
};

//Top level draw function. Draw the lander at the current position.
void draw_lander(struct lander_t *lander) {

  //Helper variable to switch between erasing and drawing
  bool erase = true;

  //Erase previous lander
  //If thrust is activated, draw with fire
  if ((buttons_read() & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK) {
    if (get_position(lander) == POS_NEG4) {
      draw_lander_pos_Neg4(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_NEG3) {
      draw_lander_pos_Neg3(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_NEG2) {
      draw_lander_pos_Neg2(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_NEG1) {
      draw_lander_pos_Neg1(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_0) {
      draw_lander_pos_0(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_1) {
      draw_lander_pos_1(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_2) {
      draw_lander_pos_2(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_3) {
      draw_lander_pos_3(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_4) {
      draw_lander_pos_4(lander, erase);
      draw_lander_fire(lander, erase);
    }
  }

  //Otherwise, draw lander without fire
  else {
    if (get_position(lander) == POS_NEG4) {
      draw_lander_pos_Neg4(lander, erase);
    }
    else if (get_position(lander) == POS_NEG3) {
      draw_lander_pos_Neg3(lander, erase);
    }
    else if (get_position(lander) == POS_NEG2) {
      draw_lander_pos_Neg2(lander, erase);
    }
    else if (get_position(lander) == POS_NEG1) {
      draw_lander_pos_Neg1(lander, erase);
    }
    else if (get_position(lander) == POS_0) {
      draw_lander_pos_0(lander, erase);
    }
    else if (get_position(lander) == POS_1) {
      draw_lander_pos_1(lander, erase);
    }
    else if (get_position(lander) == POS_2) {
      draw_lander_pos_2(lander, erase);
    }
    else if (get_position(lander) == POS_3) {
      draw_lander_pos_3(lander, erase);
    }
    else if (get_position(lander) == POS_4) {
      draw_lander_pos_4(lander, erase);
    }
  }

  //Set position
  set_position(lander);
  erase = false;

  //If thrust is activated, draw with fire
  if ((buttons_read() & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK) {
    if (get_position(lander) == POS_NEG4) {
      draw_lander_pos_Neg4(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_NEG3) {
      draw_lander_pos_Neg3(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_NEG2) {
      draw_lander_pos_Neg2(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_NEG1) {
      draw_lander_pos_Neg1(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_0) {
      draw_lander_pos_0(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_1) {
      draw_lander_pos_1(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_2) {
      draw_lander_pos_2(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_3) {
      draw_lander_pos_3(lander, erase);
      draw_lander_fire(lander, erase);
    }
    else if (get_position(lander) == POS_4) {
      draw_lander_pos_4(lander, erase);
      draw_lander_fire(lander, erase);
    }
  }

  //Otherwise, draw lander without fire
  else {
    if (get_position(lander) == POS_NEG4) {
      draw_lander_pos_Neg4(lander, erase);
    }
    else if (get_position(lander) == POS_NEG3) {
      draw_lander_pos_Neg3(lander, erase);
    }
    else if (get_position(lander) == POS_NEG2) {
      draw_lander_pos_Neg2(lander, erase);
    }
    else if (get_position(lander) == POS_NEG1) {
      draw_lander_pos_Neg1(lander, erase);
    }
    else if (get_position(lander) == POS_0) {
      draw_lander_pos_0(lander, erase);
    }
    else if (get_position(lander) == POS_1) {
      draw_lander_pos_1(lander, erase);
    }
    else if (get_position(lander) == POS_2) {
      draw_lander_pos_2(lander, erase);
    }
    else if (get_position(lander) == POS_3) {
      draw_lander_pos_3(lander, erase);
    }
    else if (get_position(lander) == POS_4) {
      draw_lander_pos_4(lander, erase);
    }
  }
}

