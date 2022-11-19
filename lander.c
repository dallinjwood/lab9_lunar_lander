#include "lander.h"

lander_t the_lander;


void lander_init();

//calculates the x and y thrust values given the current angle
int32_t get_thrust_y();
int32_t get_thrust_x();

//draw the lander at the current angle
void draw_lander(display_point_t corner);

//incrimient the angle 
void lean_left();

//decrement the angle
void lean_right();

void thrust();


display_point_t get_location();