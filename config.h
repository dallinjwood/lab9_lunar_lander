#ifndef CONFIG
#define CONFIG

//Here are any constants that we will define

#define CONFIG_GRAVITY_DISTANCE_PER_SECOND 40
#define CONFIG_PLANE_DISTANCE_PER_TICK                                         \
  (CONFIG_PLANE_DISTANCE_PER_SECOND * CONFIG_GAME_TIMER_PERIOD)



#endif /* CONFIG */
