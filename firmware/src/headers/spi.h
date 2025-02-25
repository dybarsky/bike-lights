/*
 * SN74HC595N shift register control. Turns on and off leds.
 */

#ifndef HEADER_SPI
#define HEADER_SPI

// control functions
void configure_spi();
void send_to_back(unsigned char data);
void send_to_front(unsigned char data);

#endif // HEADER_SPI