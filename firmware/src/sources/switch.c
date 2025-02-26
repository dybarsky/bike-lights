/**
 * Switch (2 buttons basically) is pulled UP.
 * When moved into one or another position - is connected to ground.
 * This triggers corresponding callback invocation. 
 */

#include <msp430g2553.h>
#include "switch.h"

#define LEFT	BIT3
#define RIGHT	BIT4

static void position_left_listen_on();
static void position_left_listen_off();
static void position_right_listen_on();
static void position_right_listen_off();

void configure_switch() {
	// setup pin direction
	P2DIR &= ~(LEFT + RIGHT);
	// enable pulling
	P2REN |= LEFT + RIGHT;
	// pull up
	P2OUT |= LEFT + RIGHT;
	// initial position
	position_left_listen_on();
	position_right_listen_on();
}

static void position_left_listen_off() {
	// interruptions from 0 to 1
	P2IES &= ~LEFT;
	// reset interruption flag to avoid false call
	P2IFG &= ~LEFT;
	// enable interruptions for bit
	P2IE |= LEFT;
}

static void position_left_listen_on() {
	// interruptions from 1 to 0
	P2IES |= LEFT;
	// reset interruption flag to avoid false call
	P2IFG &= ~LEFT;
	// enable interruptions for bit
	P2IE |= LEFT;
}

static void position_right_listen_off() {
	// interruptions from 0 to 1
	P2IES &= ~RIGHT;
	// reset interruption flag to avoid false call
	P2IFG &= ~RIGHT;
	// enable interruptions for bit
	P2IE |= RIGHT;
}

static void position_right_listen_on() {
	// interruptions from 1 to 0
	P2IES |= RIGHT;
	// reset interruption flag to avoid false call
	P2IFG &= ~RIGHT;
	// enable interruptions for bit
	P2IE |= RIGHT;
}

typedef enum { OFF, ON } state;
static state current = OFF;

#pragma vector = PORT2_VECTOR
__interrupt void on_switch_moved() {
	unsigned char switch_left = P2IFG & LEFT;
	unsigned char switch_right = P2IFG & RIGHT;

	switch(current) {

		case ON:
			event_switch_middle();
			position_left_listen_on();
			position_right_listen_on();
			current = OFF;
			P2IFG &= ~(LEFT + RIGHT);
			break;

		case OFF:
			if (switch_left) {
				event_switch_left();
				position_left_listen_off();
			}
			if (switch_right) {
				event_switch_right();
				position_right_listen_off();
			}
			current = ON;
			P2IFG &= ~(LEFT + RIGHT);
			break;
	}
}
