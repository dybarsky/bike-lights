#include <msp430g2553.h>

#include "pattern.h"
#include "spi.h"
#include "timer.h"
#include "switch.h"

void configure() {
	// turn off watchdog
	WDTCTL = WDTPW + WDTHOLD;
	// use frequency 1 MHz
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	// all pins off
	P1OUT = 0;
	P2OUT = 0;
}

int main(void) {
	// configure MCU
	configure();
	// configure peripherals
	configure_spi();
	configure_timer();
	configure_switch();
	// low power mode + enable interruptions
	_BIS_SR(LPM0_bits + GIE);
}

// main logic and callbacks implementation

static char counter;
static pattern current;

void event_timer() {
	if (counter >= LENGTH) {
		counter = 0;
	}
	send_to_front(*current.front + counter);
	send_to_back(*current.back + counter);
	counter++;
}

void event_switch_left() {
	counter = 0;
	current = get_left_pattern();
	start_timer();
}

void event_switch_right() {
	counter = 0;
	current = get_right_pattern();
	start_timer();
}

void event_switch_middle() {
	stop_timer();
	send_to_front(0);
	send_to_back(0);
}
