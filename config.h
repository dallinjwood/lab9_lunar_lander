#ifndef CONFIG
#define CONFIG

//TODO:: change these for our game to be slower these were copy pasted from the missiile command congif.h
#define CONFIG_TOUCHSCREEN_TIMER_PERIOD 10.0E-3
#define CONFIG_GAME_TIMER_PERIOD 45.0E-3

//Here are any constants that we will define

#define CONFIG_GRAVITY_DISTANCE_PER_SECOND 3
#define CONFIG_GRAVITY_DISTANCE_PER_TICK (CONFIG_GRAVITY_DISTANCE_PER_SECOND * CONFIG_GAME_TIMER_PERIOD)


//Initial critical point values
#define TOP_LEFT_X_INIT 320
#define TOP_RIGHT_X_INIT 325
#define TOP_Y_INIT 0 
#define BOTTOM_RIGHT_X_INIT 327 
#define BOTTOM_LEFT_X_INIT 318
#define BOTTOM_Y_INIT 8

//Angle ranges for positioning
#define ANGLE_0   0
#define ANGLE_20  20
#define ANGLE_40  40
#define ANGLE_60  60
#define ANGLE_80  80
#define ANGLE_90  90
#define ANGLE_100 100
#define ANGLE_120 120
#define ANGLE_140 140
#define ANGLE_160 160
#define ANGLE_180 180

//Positions
#define POS_NEG4 -4
#define POS_NEG3 -3
#define POS_NEG2 -2
#define POS_NEG1 -1
#define POS_0 0
#define POS_1 1
#define POS_2 2
#define POS_3 3
#define POS_4 4

//Pixel shifting
#define P_0  0
#define P_1  1
#define P_2  2
#define P_3  3
#define P_4  4
#define P_5  5
#define P_6  6
#define P_7  7
#define P_8  8
#define P_9  9
#define P_10 10
#define P_11 11
#define P_12 12

//Colors
#define LANDER_BLACK        DISPLAY_BLACK

#define LANDER_GRAY         DISPLAY_GRAY
#define LANDER_DARK_GRAY    DISPLAY_DARK_GRAY
#define LANDER_LIGHT_GRAY   DISPLAY_LIGHT_GRAY

#define LANDER_YELLOW       DISPLAY_YELLOW

#define LANDER_BLUE         DISPLAY_BLUE
#define LANDER_DARK_MAGENTA DISPLAY_DARK_MAGENTA

#endif /* CONFIG */
