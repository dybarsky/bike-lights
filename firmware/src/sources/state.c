#include "shift.h"
#include "servo.h"
#include "timer.h"
#include "state.h"
#include "switch.h"

void state_idle() {
    shift(0);
    servo_middle();
}

void state_() {
	
}