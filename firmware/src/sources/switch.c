#include <msp430g2553.h>
#include "switch.h"
#include "servo.h"
#include "shift.h"

#define SWITCH_1 BIT1
#define SWITCH_2 BIT2

void configure_switch() {
    P1REN |= SWITCH_1;          // enable pulling
    P1OUT |= SWITCH_1;          // pull up

    P1REN |= SWITCH_2;          // enable pulling
    P1OUT |= SWITCH_2;          // pull up

    position1_listen_off();
    position2_listen_off();
}

void position1_listen_on() {
    P1IES &= ~SWITCH_1;         // interruptions from 0 to 1
    P1IFG &= ~SWITCH_1;         // reset interruption flag to avoid false call
    P1IE |= SWITCH_1;           // enable interruptions for bit
}

void position1_listen_off() {
    P1IES |= SWITCH_1;          // interruptions from 1 to 0
    P1IFG &= ~SWITCH_1;         // reset interruption flag to avoid false call
    P1IE |= SWITCH_1;           // enable interruptions for bit
}

void position2_listen_on() {
    P1IES &= ~SWITCH_2;         // interruptions from 0 to 1
    P1IFG &= ~SWITCH_2;         // reset interruption flag to avoid false call
    P1IE |= SWITCH_2;           // enable interruptions for bit
}

void position2_listen_off() {
    P1IES |= SWITCH_2;          // interruptions from 1 to 0
    P1IFG &= ~SWITCH_2;         // reset interruption flag to avoid false call
    P1IE |= SWITCH_2;           // enable interruptions for bit
}

int off = 0;

#pragma vector = PORT1_VECTOR
__interrupt void on_switch_moved() {
    int switch1 = P1IFG & SWITCH_1;
    int switch2 = P1IFG & SWITCH_2;

	if (off) {
		off = 0;
		servo_middle();
		position1_listen_off();
		position2_listen_off();
		start_blinking(3);
		P1IFG = 0;
		return;
	}
    if (switch1 == SWITCH_1) {
        off = 1;
        servo_left();
        position1_listen_on();
        P1IFG &= ~SWITCH_1;
        return;
    }
    if (switch2 == SWITCH_2) {
        off = 1;
        servo_right();
        position2_listen_on();
        P1IFG &= ~SWITCH_2;
        return;
    }
    P1IFG = 0;
}
