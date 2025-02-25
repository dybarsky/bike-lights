/**
 * Switch (2 buttons basically) is pulled UP.
 * When moved into one or another position - is connected to ground.
 * This triggers corresponding callback invocation. 
 */

#include <msp430g2553.h>
#include "switch.h"

#define LEFT BIT0
#define RIGHT BIT3

static void position_left_listen_on();
static void position_left_listen_off();
static void position_right_listen_on();
static void position_right_listen_off();

void configure_switch() {
	// enable pulling
    P1REN |= LEFT + RIGHT;
    // pull up
    P1OUT |= LEFT + RIGHT;
	// initial position
    position_left_listen_on();
  	position_right_listen_on();
}

static void position_left_listen_off() {
	// interruptions from 0 to 1
    P1IES &= ~LEFT;
	// reset interruption flag to avoid false call
    P1IFG &= ~LEFT;
    // enable interruptions for bit
    P1IE |= LEFT;
}

static void position_left_listen_on() {
	// interruptions from 1 to 0
    P1IES |= LEFT;
    // reset interruption flag to avoid false call
    P1IFG &= ~LEFT;
    // enable interruptions for bit
    P1IE |= LEFT;
}

static void position_right_listen_off() {
	// interruptions from 0 to 1
    P1IES &= ~RIGHT;
    // reset interruption flag to avoid false call
    P1IFG &= ~RIGHT;
	// enable interruptions for bit
   	P1IE |= RIGHT;
}

static void position_right_listen_on() {
	// interruptions from 1 to 0
    P1IES |= RIGHT;
    // reset interruption flag to avoid false call
    P1IFG &= ~RIGHT;
    // enable interruptions for bit
    P1IE |= RIGHT;
}

typedef enum { OFF, ON } state;
static state current = OFF;

#pragma vector = PORT1_VECTOR
__interrupt void on_switch_moved() {
    unsigned char switch_left = P1IFG & LEFT;
    unsigned char switch_right = P1IFG & RIGHT;

	switch(current) {

		case ON:
			event_switch_middle();
			position_left_listen_on();
			position_right_listen_on();
			current = OFF;
			P1IFG &= ~(LEFT + RIGHT);
			break;

		case OFF:
			if (switch_left == LEFT) {
				event_switch_left();
				position_left_listen_off();
			}
			if (switch_right == RIGHT) {
				event_switch_right();
				position_right_listen_off();
			}
			current = ON;
			P1IFG &= ~(LEFT + RIGHT);
			break;
	}
}
