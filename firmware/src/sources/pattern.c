
#include "pattern.h"

static unsigned char backward[LENGTH] = {
	0b10000000,
	0b10000001,	
	0b10000011,
	0b10000111,
	0b10001111,
	0b10011111,
	0b10111111,
	0b11111111,
	0b00000000,
};

static unsigned char forward[LENGTH] = {
	0b01000000,
	0b01100000,
	0b01110000,
	0b01111000,
	0b01111100,
	0b01111110,
	0b01111111,
	0b11111111,
	0b00000000,
};

pattern get_left_pattern() {
	pattern result;
	result.front = forward;
	result.back = backward;
	return result;
}

pattern get_right_pattern() {
	pattern result;
	result.front = backward;
	result.back = forward;
	return result;
}
