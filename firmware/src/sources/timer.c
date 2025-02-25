/*
 * Frequency = 1 Mhz
 * Divider = 8
 * Clock rate = 1 000 000 / 8 = 125 000
 * 0.1 seconds = 12 500
 */
#include <msp430g2553.h>
#include "timer.h"

#define COUNTER 12500

void configure_timer() {
	TA1CCR0 = COUNTER;
}

void start_timer() {
	// sum-main clock + freq divider 4 + up mode + init
	TA1CTL = TASSEL_2 + ID_3 + MC_1 + TACLR;
	// enable timer interruptions
	TA1CCTL0 = CCIE;
}

void stop_timer() {
	// disable timer interruptions
	TA1CCTL0 = ~CCIE;
	// stop timer
	TA1CTL &= ~MC_3;
	// set stop mode
	TA1CTL |= MC_0;
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void on_timer_a0_callback(void) {
	event_timer();
	// Reset interruptions
    TA1CCTL0 &= ~CCIFG;
}	
