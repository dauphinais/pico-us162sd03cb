/*
	Simple demo file for the pico-us162sd03cb library

	This demonstration:
		demonstrates how to create and start a US162SD03CB
		prints multiple strings to the display
		demonstrates the current method to move the cursor while no move_cursor function exists.
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "us162sd03cb.h"

#define VFD_CLOCK 18
#define VFD_DATA 19
#define VFD_RESET 20

int main () {
	US162SD03CB display = vfd_init(VFD_CLOCK, VFD_DATA, VFD_RESET);
	vfd_begin(display, 16, 2);

	while (1) {
		vfd_write_string(display, "Pico US162SD03CB");
		sleep_ms(5000);

		vfd_clear(display);
		sleep_ms(1000);

		vfd_write_string(display, "Print");
		sleep_ms(1000);

		// Move cursor to start of second line
		vfd_write_character_direct(display, SET_CURSOR_POSITION);
		vfd_write_character_direct(display, 0x11);

		vfd_write_string(display, "Test");
		sleep_ms(5000);

		vfd_clear(display);
		sleep_ms(1000);

		vfd_write_string(display, "Basic VFD       library");
		sleep_ms(5000);

		vfd_clear(display);
		sleep_ms(1000);
	}
	return 0;
}
