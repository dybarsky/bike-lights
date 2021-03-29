/*
 frequency = 1 Mhz
 clock rate = 1 000 000

 pwm frequency = 50 Hz (1/50 sec)
 pwm period = 1 000 000 / 50 = 20 000
*/

#include <msp430g2553.h>
#include "servo.h"

#define OUT_PORT    P1OUT
#define OUT_DIR     P1DIR
#define SERVO       BIT6

#define PWM_PERIOD_TIME 20000
#define PWM_MAX_TIME 2400           // 2400 microsec
#define PWM_MIN_TIME 500            // 500 microsec
#define PWM_MED_TIME 1450           // 1450 microsec

void configure_servo() {
    OUT_PORT = 0;                               // turn off port
    OUT_DIR = SERVO;                            // setup pin output

    TA0CCR0 = PWM_PERIOD_TIME;                   // pwm period
    TA0CCR1 = PWM_MIN_TIME;                      // pwm duty part
    TA0CCTL0 = CCIE;                             // enable interruption of timer when CCR0 is reached
    TA0CCTL1 = CCIE;                             // enable interruption of timer when CCR1 is reached
    TA0CTL = TASSEL_2 + ID_3 + MC_1 + TACLR;     // sub-mainClock + divider 1 + up mode + init
}

void servo_middle() {
    TA0CCR1 = PWM_MED_TIME;
}

void servo_left() {
    TA0CCR1 = PWM_MIN_TIME;
}

void servo_right() {
    TA0CCR1 = PWM_MAX_TIME;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void on_timer_a0_callback(void) {
    OUT_PORT = SERVO;                           // turn on port
    TA0CCTL0 &= ~CCIFG;                         // reset interruption flag
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void on_timer_a1_callback(void) {
    OUT_PORT = 0;                               // turn off port
    TA0CCTL1 &= ~CCIFG;                         // reset interruption flag
}
