#include <msp430g2553.h>
#include "shift.h"

#define CLOCK_PORT 	P1OUT
#define LATCH_PORT	P1OUT
#define DATA_PORT 	P2OUT

#define CLOCK_DIR	P1DIR
#define LATCH_DIR	P1DIR
#define DATA_DIR	P2DIR

#define CLOCK_BIT	BIT7
#define LATCH_BIT 	BIT6
#define DATA_BIT 	BIT4

void configure_shift() {
	CLOCK_DIR |= CLOCK_BIT;
	LATCH_DIR |= LATCH_BIT;
    DATA_DIR |= DATA_BIT;
    CLOCK_PORT = 0;
    LATCH_PORT = 0;
    DATA_PORT = 0;
}

void shift(unsigned int byte) {
	// Latch is down to start shifting
	LATCH_PORT &= ~LATCH_BIT;

    int bit;
    for (bit = 0; bit < 8; bit ++) {
        int data = byte & (1 << bit);
        if (data) {
           	DATA_PORT |= DATA_BIT;
        } else {
            DATA_PORT &= ~DATA_BIT;
        }
        // Clock tick
        CLOCK_PORT |= CLOCK_BIT;
        CLOCK_PORT &= ~CLOCK_BIT;
    }
    // Latch is up to apply shifted data
    LATCH_PORT |= LATCH_BIT;
    LATCH_PORT &= ~LATCH_BIT;
}
