/*
 * Switch control. Listens for user interaction.
 */

#ifndef HEADER_SWITCH
#define HEADER_SWITCH

// control functions 
void configure_switch();

// callback functions
void event_switch_left();
void event_switch_right();
void event_switch_middle();

#endif // HEADER_SWITCH