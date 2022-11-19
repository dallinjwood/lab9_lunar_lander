#include "interrupts.h"
#include "intervalTimer.h"
#include <stdbool.h>
#include <stdio.h>

#define TICK_PERIOD 50E-3

// game isr that calls lunar_control_tick every 50ms.
// TODO: We might need to go faster, we should see how fast the game plays this
// way.
void game_isr() {
  intervalTimer_ackInterrupt(INTERVAL_TIMER_0);
  lander_control_tick();
}

int main() {

  display_init();
  lander_control_init();

  // Initialize timer interrupts
  interrupts_init();
  interrupts_register(INTERVAL_TIMER_0_INTERRUPT_IRQ, game_isr);
  interrupts_irq_enable(INTERVAL_TIMER_0_INTERRUPT_IRQ);

  intervalTimer_initCountDown(INTERVAL_TIMER_0, TICK_PERIOD);
  intervalTimer_enableInterrupt(INTERVAL_TIMER_0);
  intervalTimer_start(INTERVAL_TIMER_0);

  // Main game loop
  while (1)
    ;
  return 0;
}