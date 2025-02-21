#include <msp430g2553.h>
#include "timer.h"
#include "shift.h"
#include "state.h"
#include "switch.h"

void configure() {
	// turn off watchdog
    WDTCTL = WDTPW + WDTHOLD;

	// use frequency 8 MHz
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL = CALDCO_8MHZ;

	// all pins off
    P1OUT = 0;
    P2OUT = 0;
}

int main(void) {
	// configure MCU
    configure();

	// configure peripherals
    configure_shift();
    configure_timer();
    configure_switch();

	// inital state
    state_idle();

	// low power mode + enable interruptions
    _BIS_SR(LPM0_bits + GIE);
}

/* 
 * callbacks implementation
 */

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
