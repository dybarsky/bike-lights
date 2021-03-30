/*
 * SN74HC595N shift register control. Turns on and off leds.
 */

#ifndef HEADER_SHIFT
#define HEADER_SHIFT

void configure_shift();
void shift(unsigned int byte);

#endif // HEADER_SHIFT