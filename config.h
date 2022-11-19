#ifndef CONFIG
#define CONFIG

//TODO:: change these for our game to be slower these were copy pasted from the missiile command congif.h
#define CONFIG_TOUCHSCREEN_TIMER_PERIOD 10.0E-3
#define CONFIG_GAME_TIMER_PERIOD 45.0E-3

//Here are any constants that we will define

#define CONFIG_GRAVITY_DISTANCE_PER_SECOND 3
#define CONFIG_GRAVITY_DISTANCE_PER_TICK (CONFIG_GRAVITY_DISTANCE_PER_SECOND * CONFIG_GAME_TIMER_PERIOD)


// #define CONFIG_PLANE_DISTANCE_PER_TICK                                      
//   (CONFIG_PLANE_DISTANCE_PER_SECOND * CONFIG_GAME_TIMER_PERIOD)



#endif /* CONFIG */
