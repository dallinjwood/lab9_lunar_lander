#ifndef LANDER
#define LANDER

#include "display.h"
#include "buttons.h"
#include "math.h"
#include <stdbool.h>

struct lander_t{
    double angle;
    display_point_t location;
    int32_t vertical_velocity;
    int32_t horizontal_velocity;
    bool has_landed;
};

void lander_init();

//calculates the x and y thrust values given the current angle
double get_thrust_y();
double get_thrust_x();

//draw the lander at the current angle
void draw_lander(display_point_t corner);

//incrimient the angle 
void lean_left();

//decrement the angle
void lean_right();

void thrust();

void draw_lander();

display_point_t get_location();

#endif /* LANDER */