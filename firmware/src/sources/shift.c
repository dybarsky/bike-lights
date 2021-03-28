#include <msp430g2553.h>
#include "shift.h"

#define CLOCK BIT0
#define LATCH BIT1
#define DATA  BIT2

void configure_shift() {
    P2DIR |= (CLOCK + DATA + LATCH);
    P2OUT = 0;
}

void shift(char byte) {
	P2OUT &= ~LATCH;					// Latch is down to start shifting
    int bit;
    for (bit = 0; bit < 8; bit ++) {
        int data = byte & (1 << bit);
        if (data) {
           	P2OUT |= DATA;
        } else {
            P2OUT &= ~DATA;
        }
        P2OUT |= CLOCK;					// Clock tick
        P2OUT &= ~CLOCK;
    }
    P2OUT |= LATCH;						// Latch is up to apply shifted data
    P2OUT &= ~LATCH;
}
