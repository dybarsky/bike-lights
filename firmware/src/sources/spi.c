#include <msp430g2553.h>
#include "spi.h"

#define DATA	    BIT4
#define CLOCK	    BIT3
#define LATCH_FRONT	BIT2
#define LATCH_BACK	BIT5

static void transmit(unsigned char data);

void configure_spi() {
    P1SEL &= ~(CLOCK + DATA + LATCH_FRONT + LATCH_BACK);
    P1DIR |= CLOCK + DATA + LATCH_FRONT + LATCH_BACK;
    P1OUT = 0;
}

void send_to_front(unsigned char data) {
    // latch is down to start receiving
    P1OUT &= ~LATCH_FRONT;
    // transmit data to bus
    transmit(data);
    // latch is up to apply shifted data
    P1OUT |= LATCH_FRONT;
}

void send_to_back(unsigned char data) {
    // latch is down to start receiving
    P1OUT &= ~LATCH_BACK;
    // transmit data to bus
    transmit(data);
    // latch is up to apply shifted data
    P1OUT |= LATCH_BACK;
}

static void transmit(const unsigned char data) {
    for (char count = 0; count < 8; count ++) {
        const char bytes = 1 << count & data;
        if (bytes) {
            P1OUT |= DATA;
        } else {
            P1OUT &= ~DATA;
        }
        // clock tick
        P1OUT |= CLOCK;
        P1OUT &= ~CLOCK;
    }
}
