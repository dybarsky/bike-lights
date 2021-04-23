/**
 * Switch (2 buttons basically) is pulled UP.
 * When moved into one or another position - is connected to ground.
 * This triggers corresponding callback invocation. 
 */

#include <msp430g2553.h>
#include "switch.h"

#define SWITCH_1 BIT0
#define SWITCH_2 BIT3

static void position_a_listen_off();
static void position_b_listen_on();
static void position_b_listen_off();
static void position_a_listen_off();

void configure_switch() {
	// enable pulling
    P1REN |= SWITCH_1;
    // pull up
    P1OUT |= SWITCH_1;

    // enable pulling
    P1REN |= SWITCH_2;
	// pull up
    P1OUT |= SWITCH_2;

    position_a_listen_off();
  	position_b_listen_off();
}

static void position_a_listen_on() {
	// interruptions from 0 to 1
    P1IES &= ~SWITCH_1;
	// reset interruption flag to avoid false call
    P1IFG &= ~SWITCH_1;
    // enable interruptions for bit
    P1IE |= SWITCH_1;
}

static void position_a_listen_off() {
	// interruptions from 1 to 0
    P1IES |= SWITCH_1;
    // reset interruption flag to avoid false call
    P1IFG &= ~SWITCH_1;
    // enable interruptions for bit
    P1IE |= SWITCH_1;
}

static void position_b_listen_on() {
	// interruptions from 0 to 1
    P1IES &= ~SWITCH_2;
    // reset interruption flag to avoid false call
    P1IFG &= ~SWITCH_2;
	// enable interruptions for bit
   	P1IE |= SWITCH_2;
}

static void position_b_listen_off() {
	// interruptions from 1 to 0
    P1IES |= SWITCH_2;
    // reset interruption flag to avoid false call
    P1IFG &= ~SWITCH_2;
    // enable interruptions for bit
    P1IE |= SWITCH_2;
}

int off = 0;

#pragma vector = PORT1_VECTOR
__interrupt void on_switch_moved() {
    int switch1 = P1IFG & SWITCH_1;
    int switch2 = P1IFG & SWITCH_2;
	/* 
	 * Previous state was off
	 * Current state is deactivated (on)
	 */
	if (off) {
		off = 0;
		event_switch_middle();
		position_a_listen_off();
		position_b_listen_off();
		return;
	}
	// First switch is activated (off)
    if (switch1 == SWITCH_1) {
        off = 1;
        event_switch_left();
        position_a_listen_on();
        P1IFG &= ~SWITCH_1;
        return;
    }
    // Second switch is activated (off)
    if (switch2 == SWITCH_2) {
        off = 1;
        event_switch_right();
        position_b_listen_on();
        P1IFG &= ~SWITCH_2;
        return;
    }
	P1IFG = 0;
}
