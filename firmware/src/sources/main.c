#include <msp430g2553.h>
#include "shift.h"
#include "servo.h"
#include "timer.h"

void configure() {
    WDTCTL = WDTPW + WDTHOLD;                   // turn off watchdog

    BCSCTL1 = CALBC1_8MHZ;                      // use frequency 1 MHz
    DCOCTL = CALDCO_8MHZ;

    P1OUT = 0;                                  // all pins off
    P2OUT = 0;
}

int main(void) {
    configure();     
    configure_shift();
    configure_timer();
    configure_servo();

    // servo_left();
    servo_right();
	//start_blinking(3);

    _BIS_SR(LPM0_bits + GIE);                   // low power mode + enable interruptions
}
