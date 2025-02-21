#include "shift.h"
#include "timer.h"
#include "state.h"

#define LED_COUNT 7

#define STATE_IDLE  1
#define STATE_LEFT  2
#define STATE_RIGHT 3

unsigned int state = 0;
unsigned char leds = 0;

unsigned char count = 0;

// Called by timer
void next_led() {
	if (count >= LED_COUNT) {
		count = 0;
		leds = 0;
	} else {
		leds += 1 << count ++;
	}
	shift(leds);
} 

void state_idle() {
	if (state == STATE_IDLE) {
		return;
	}
	state = STATE_IDLE;
	leds = 0;
	stop_timer();
	shift(0);
}

void state_left() {
	if (state != STATE_IDLE) {
		return;
	}
	state = STATE_LEFT;
	start_timer();
}

void state_right() {
	if (state != STATE_IDLE) {
		return;
	}
	state = STATE_RIGHT;
	start_timer();
}
