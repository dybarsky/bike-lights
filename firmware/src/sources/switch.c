#include <msp430g2553.h>
#include "switch.h"

#define SWITCH_1 BIT1
#define SWITCH_2 BIT2

void position_a_listen_off();
void position_a_listen_off();
void position_b_listen_on();
void position_b_listen_off();

void configure_switch() {
    P1REN |= SWITCH_1;          // enable pulling
    P1OUT |= SWITCH_1;          // pull up

    P1REN |= SWITCH_2;          // enable pulling
    P1OUT |= SWITCH_2;          // pull up

    position_a_listen_off();
  	position_b_listen_off();
}

void position_a_listen_on() {
    P1IES &= ~SWITCH_1;         // interruptions from 0 to 1
    P1IFG &= ~SWITCH_1;         // reset interruption flag to avoid false call
    P1IE |= SWITCH_1;           // enable interruptions for bit
}

void position_a_listen_off() {
    P1IES |= SWITCH_1;          // interruptions from 1 to 0
    P1IFG &= ~SWITCH_1;         // reset interruption flag to avoid false call
    P1IE |= SWITCH_1;           // enable interruptions for bit
}

void position_b_listen_on() {
    P1IES &= ~SWITCH_2;         // interruptions from 0 to 1
    P1IFG &= ~SWITCH_2;         // reset interruption flag to avoid false call
    P1IE |= SWITCH_2;           // enable interruptions for bit
}

void position_b_listen_off() {
    P1IES |= SWITCH_2;          // interruptions from 1 to 0
    P1IFG &= ~SWITCH_2;         // reset interruption flag to avoid false call
    P1IE |= SWITCH_2;           // enable interruptions for bit
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
		// servo_middle();
		position_a_listen_off();
		position_b_listen_off();
		// stop_blinking();
		P1IFG = 0;
		return;
	}
	/* First switch is activated (off) */
    if (switch1 == SWITCH_1) {
        off = 1;
        event_switch_left();
        // servo_left();
        // start_blinking(-1);
        position_a_listen_on();
        P1IFG &= ~SWITCH_1;
        return;
    }
    /* Second switch is activated (off) */
    if (switch2 == SWITCH_2) {
        off = 1;
        event_switch_right();
        // servo_right();
        // start_blinking(-1);
        position_b_listen_on();
        P1IFG &= ~SWITCH_2;
        return;
    }
	P1IFG = 0;
}
