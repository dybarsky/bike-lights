/*
 * MCU frequency = 8 Mhz
 * Divider = 8
 * Clock rate = 1 000 000
 * Counter = 0xFFFF
 * Timer = 1 000 000 / 0xFFFF = 15 times per second
 */
#include <msp430g2553.h>
#include "timer.h"

int skip_next;									// Skip iteration flag

void configure_timer() {
     TA1CTL = TASSEL_2 + ID_3 + MC_2 + TACLR;
}

void start_timer() {
    TA1CCTL0 = CCIE;							// Enable interruptions
}

void stop_timer() {
	TA1CCTL0 = 0;								// Disable interruaption
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void on_timer_b0_callback(void) {
	/* Skip every 2nd iteration (to fit cycle into 1 sec) */
	if (skip_next) {
		skip_next = 0;
	} else {		
		skip_next = 1; 
		event_timer();
	}
    TA1CCTL0 &= ~CCIFG;
}	
