#include "config.h"
#include "display.h"
#include "game_control.h"
#include "interrupts.h"
#include "intervalTimer.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// game isr that calls lunar_control_tick every 50ms.
// TODO: We might need to go faster, we should see how fast the game plays this
// way.
void game_isr() {
  intervalTimer_ackInterrupt(INTERVAL_TIMER_0);
  gameControl_tick();
}

int main() {

  double value;
  double result = 69;

  /* Assign the value we will find the tan of */
  value = 0.5;

  /* Calculate the Tangent of value */
  result = tan(value);

  /* Display the result of the calculation */
  printf("The Tangent of %f is %f\n", value, result);

  display_init();
  gameControl_init(TICK_PERIOD);

  // Initialize timer interrupts
  interrupts_init();
  interrupts_register(INTERVAL_TIMER_0_INTERRUPT_IRQ, game_isr);
  interrupts_irq_enable(INTERVAL_TIMER_0_INTERRUPT_IRQ);

  intervalTimer_initCountDown(INTERVAL_TIMER_0, TICK_PERIOD);
  intervalTimer_enableInterrupt(INTERVAL_TIMER_0);
  intervalTimer_start(INTERVAL_TIMER_0);

  // Main game loop
  while (1) {
  }
  return 0;
}