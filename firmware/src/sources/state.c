#include "shift.h"
#include "servo.h"
#include "timer.h"
#include "state.h"

#define LED_COUNT 7

#define STATE_IDLE  1
#define STATE_LEFT  2
#define STATE_RIGHT 3

int state = 0;
int count = 0;
int skip = 0;
unsigned int leds = 0;

// Skip first HALF of second. 
static int should_skip() {
	if (skip == 0) {
		return 0;
	}
	if (count ++ >= LED_COUNT / 2) {
		skip = 0;
		count = 0;
	}
	return skip;
}

// Called by timer
void next_led() {
	if (should_skip()) {
		return;
	}
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
	count = 0;
	leds = 0;
    servo_middle();
    stop_timer();
    shift(0);
}

void state_left() {
	if (state != STATE_IDLE) {
		return;
	}
	state = STATE_LEFT;
	skip = 1;
	servo_left();
	start_timer();
}

void state_right() {
	if (state != STATE_IDLE) {
		return;
	}
	state = STATE_RIGHT;
	skip = 1;
	servo_right();
	start_timer();
}
