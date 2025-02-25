/*
 * Array and api for led blinking pattern
 */

#ifndef HEADERS_PATTERN
#define HEADERS_PATTERN

#define LENGTH 9

typedef struct {
	unsigned char * back;
	unsigned char * front;
} pattern;

pattern get_left_pattern();
pattern get_right_pattern();

#endif // HEADERS_PATTERN
