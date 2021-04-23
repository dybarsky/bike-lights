/*
 * frequency = 1 Mhz
 * clock rate = 1 000 000
 *
 * pwm frequency = 50 Hz (1/50 sec)
 * pwm period = 1 000 000 / 50 = 20 000
 */

#include <msp430g2553.h>
#include "servo.h"

#define SERVO_F_PORT    P1OUT
#define SERVO_B_PORT    P2OUT
#define SERVO_F_DIR     P1DIR
#define SERVO_B_DIR     P2DIR
#define SERVO_F_BIT   	BIT5
#define SERVO_B_BIT    	BIT2

#define PWM_PERIOD_TIME 20000
#define PWM_MAX_TIME 4800       // 2400 microsec
#define PWM_MIN_TIME 1000       // 500 microsec
#define PWM_MED_TIME 2900       // 1450 microsec

int pwm[2];
int current;

void configure_servo() {
	// turn off port
    SERVO_F_PORT = 0;
    SERVO_B_PORT = 0;
	// setup pin output
    SERVO_F_DIR |= SERVO_F_BIT;
    SERVO_B_DIR |= SERVO_B_BIT;
	// pwm period
    TA0CCR0 = PWM_PERIOD_TIME;
	// pwm duty cycle
    TA0CCR1 = PWM_MIN_TIME;
	// enable interruption of timer when CCR0 is reached
    TA0CCTL0 = CCIE;
	// enable interruption of timer when CCR1 is reached
    TA0CCTL1 = CCIE; 
	// sub-mainClock + divider 4 + up mode + init
    TA0CTL = TASSEL_2 + ID_2 + MC_1 + TACLR;
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
        SERVO_F_PORT |= SERVO_F_BIT;
    } else {
        SERVO_B_PORT |= SERVO_B_BIT;
    }
    TA0CCR1 = pwm[current];
	// reset interruption flag
    TA0CCTL0 &= ~CCIFG;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void on_timer_a1_callback(void) {
	if (current == 0) {
		// turn off port for front servo
    	SERVO_F_PORT &= ~SERVO_F_BIT;
	} else {
		// turn off port for back servo
    	SERVO_B_PORT &= ~SERVO_B_BIT;
	}
    current = current == 0;
   	// reset interruption flag
    TA0CCTL1 &= ~CCIFG;
}
