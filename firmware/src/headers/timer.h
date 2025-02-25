/*
 * Timer usage for led stripe blinking.
 */

#ifndef HEADER_TIMER
#define HEADER_TIMER

// control functions 
void configure_timer();
void start_timer();
void stop_timer();
// callback functions
void event_timer();

#endif // HEADER_TIMER