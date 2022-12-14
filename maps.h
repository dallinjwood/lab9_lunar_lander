#ifndef MAPS
#define MAPS

#include "lander.h"
#include <stdint.h>

void map1();

void map2();

void map3();

void map4();

void map5();

bool map1_collide(double x0, double x1, double x2, double x3, double y0,
                  double y1, double y2, double y3, double y_velocity);

bool map2_collide(double x0, double x1, double x2, double x3, double y0,
                  double y1, double y2, double y3, double y_velocity);

bool map3_collide(double x0, double x1, double x2, double x3, double y0,
                  double y1, double y2, double y3, double y_velocity);
                  
bool map4_collide(double x0, double x1, double x2, double x3, double y0,
                  double y1, double y2, double y3, double y_velocity);

bool map5_collide(double x0, double x1, double x2, double x3, double y0,
                  double y1, double y2, double y3, double y_velocity);

bool didPlayerWin();

#endif /* MAPS */