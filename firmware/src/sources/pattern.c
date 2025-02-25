
#include "pattern.h"

static unsigned char backward[LENGTH] = {
    0b00000000,
    0b00000001,
    0b00000011,
    0b00000111,
    0b00001111,
    0b00011111,
    0b00111111,
    0b01111111,
    0b11111111,
};

static unsigned char forward[LENGTH] = {
    0b00000000,
    0b10000000,
    0b11000000,
    0b11100000,
    0b11110000,
    0b11111000,
    0b11111100,
    0b11111110,
    0b11111111,
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
