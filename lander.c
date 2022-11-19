#include "lander.h"

lander_t the_lander;

static double cos_degrees(double theta){
    
    //convert radians to degrees
    theta = theta * (3.14 / 180);
    return cos(theta);

}

static double sin_degrees(double theta){
    
    //convert radians to degrees
    theta = theta * (3.14 / 180);
    return sin(theta);

}

void lander_init(){

    the_lander.angle = 90;
    the_lander.has_landed = false;
    the_lander.location = {160, 0};
    the_lander.vertical_velocity = 1;
    the_lander.horizontal_velocity = 0;
}

//calculates the x and y thrust values given the current angle
double get_thrust_y(){
    return sin_degrees(the_lander.angle);
}

double get_thrust_x(){
    return cos_degrees(the_lander.angle);
}


//incrimient the angle 
void lean_left(){
    if(the_lander.angle < 180){
    the_lander.angle += 1
    }
}

//decrement the angle
void lean_right(){
    if(the_lander.angle > 0){
    the_lander.angle -= 1
    }
}

void thrust();

//draw the lander at the current angle
void draw_lander(){
    
}


display_point_t get_location();