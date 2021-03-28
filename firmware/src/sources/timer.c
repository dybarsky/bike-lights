#include <msp430g2553.h>
#include "const.h"
#include "timer.h"
#include "shift.h"

#define PERIOD (unsigned int) 1000000

void configure_timer() {
    TA1CCR0 = PERIOD;
    TA1CTL = TASSEL_2 + ID_1 + MC_2 + TACLR;
}

unsigned int data = 1;
int counter = 0;
int cycle;
int repeats;

void start_blinking(short reps) {
	cycle = 0;
	repeats = reps;
    TA1CCTL0 = CCIE;
}

void stop_blinking() {
	TA1CCTL0 = 0;
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void on_timer_b0_callback(void) {
    if (counter == LED_COUNT) {
    	counter = 0;
    	data = 1;
   		cycle ++;
	    shift(0);
	} else {
    	shift(data);
    	data += 1 << ++ counter;
	}
	if (cycle == repeats) {
		stop_blinking();
	}
    TA0CCTL0 &= ~CCIFG;
}
