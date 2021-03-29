/*
 *
 *
 */
#include <msp430g2553.h>
#include "const.h"
#include "timer.h"
#include "shift.h"

void configure_timer() {
    TA1CTL = TASSEL_2 + ID_3 + MC_2 + TACLR;
}

unsigned int data;
int counter;
int repeats;
int cycle;
int skip;

void start_blinking(short reps) {
	data = 0;
	cycle = 0;
	counter = 0;
	repeats = reps;
    TA1CCTL0 = CCIE;
}

void stop_blinking() {
	TA1CCTL0 = 0;
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void on_timer_b0_callback(void) {
	if (cycle == repeats) {
		stop_blinking();
		return;
	}
	if (skip) {
		skip = 0;
		return;
	} else {
		skip = 1;
	}
    if (counter == LED_COUNT) {
    	counter = 0;
    	data = 0;
   		cycle ++;
	    shift(0);
	} else {
    	data += 1 << counter ++;
    	shift(data);
	}
    TA0CCTL0 &= ~CCIFG;
}
