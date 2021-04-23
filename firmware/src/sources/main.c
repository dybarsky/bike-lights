#include <msp430g2553.h>
#include "timer.h"
#include "shift.h"
#include "servo.h"
#include "state.h"
#include "switch.h"

void configure() {
    WDTCTL = WDTPW + WDTHOLD;                   // turn off watchdog

    BCSCTL1 = CALBC1_8MHZ;                      // use frequency 1 MHz
    DCOCTL = CALDCO_8MHZ;

    P1OUT = 0;                                  // all pins off
    P2OUT = 0;
}

int main(void) {
    configure();
    configure_shift();
    configure_timer();
    configure_servo();
    configure_switch();

    state_idle();

	// low power mode + enable interruptions
    _BIS_SR(LPM0_bits + GIE);
}

// callbacks implementation

void event_switch_left() {
	state_left();
}

void event_switch_right() {
	state_right();
}

void event_switch_middle() {
	state_idle();
}

void event_timer() {
	next_led();
}

