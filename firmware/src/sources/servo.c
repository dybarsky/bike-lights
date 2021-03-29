/*
 * frequency = 1 Mhz
 * clock rate = 1 000 000
 *
 * pwm frequency = 50 Hz (1/50 sec)
 * pwm period = 1 000 000 / 50 = 20 000
 */

#include <msp430g2553.h>
#include "servo.h"

#define OUT_PORT    P1OUT
#define OUT_DIR     P1DIR
#define SERVO_F     BIT6
#define SERVO_B     BIT7

#define PWM_PERIOD_TIME 20000
#define PWM_MAX_TIME 4800           // 2400 microsec
#define PWM_MIN_TIME 1000           // 500 microsec
#define PWM_MED_TIME 2900           // 1450 microsec

int pwm[2];
int current;

void configure_servo() {
    OUT_PORT = 0;                               // turn off port
    OUT_DIR = SERVO_F + SERVO_B;                // setup pin output

    TA0CCR0 = PWM_PERIOD_TIME;                   // pwm period
    TA0CCR1 = PWM_MIN_TIME;                      // pwm duty part
    TA0CCTL0 = CCIE;                             // enable interruption of timer when CCR0 is reached
    TA0CCTL1 = CCIE;                             // enable interruption of timer when CCR1 is reached
    TA0CTL = TASSEL_2 + ID_2 + MC_1 + TACLR;     // sub-mainClock + divider 4 + up mode + init
}

void servo_middle() {
    pwm[0] = PWM_MED_TIME;
    pwm[1] = PWM_MED_TIME;
    TA0CCR1 = PWM_MED_TIME;
    current = 0;
}

void servo_left() {
    pwm[0] = PWM_MIN_TIME;
    pwm[1] = PWM_MAX_TIME;
    TA0CCR1 = PWM_MIN_TIME;
    current = 0;
}

void servo_right() {
    pwm[0] = PWM_MAX_TIME;
    pwm[1] = PWM_MIN_TIME;
    TA0CCR1 = PWM_MAX_TIME;
    current = 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void on_timer_a0_callback(void) {
    if (current == 0) {
        OUT_PORT |= SERVO_F;
    } else {
        OUT_PORT |= SERVO_B;
    }
    TA0CCR1 = pwm[current];
    TA0CCTL0 &= ~CCIFG;                         // reset interruption flag
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void on_timer_a1_callback(void) {
	if (current == 0) {
    	OUT_PORT &= ~SERVO_F;                   // turn off port
	} else {
    	OUT_PORT &= ~SERVO_B;                   // turn off port
	}
    current = current == 0;
    TA0CCTL1 &= ~CCIFG;                         // reset interruption flag
}
