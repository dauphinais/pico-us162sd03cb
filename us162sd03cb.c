#ifndef _US162SD03CB_C_
#define _US162SD03CB_C_

#include <stdio.h>
#include <stdlib.h>

#include "us162sd03cb.h"

US162SD03CB vfd_init (const uint8_t c, const uint8_t d, const uint8_t r) {

	// Sleep to ensure no funny business ensues
	sleep_ms(10);

	US162SD03CB vfd = {c, d, r};

	// Initialize all VFD pins
	gpio_init(c);
	gpio_init(d);
	gpio_init(r);

	// Set all pins to outputs
	gpio_set_dir(r, GPIO_OUT);
	gpio_set_dir(c, GPIO_OUT);
	gpio_set_dir(d, GPIO_OUT);

	// Set initial values
	gpio_put(c, 1);
	gpio_put(d, 0);
	gpio_put(r, 0);

	// Return address of vfd
	return vfd;
}

void vfd_begin (US162SD03CB vfd, uint8_t columns, uint8_t rows) {
	vfd.columns = columns;
	vfd.rows = rows;
	vfd.total_chars = columns * rows;
	
	vfd_reset(vfd);

	sleep_us(PERIOD_TIME);

	vfd_write_character_direct(vfd, SET_IO_MODE);
	vfd_write_character_direct(vfd, 0);

	vfd_clear(vfd);

	sleep_us(PERIOD_TIME);

	// Display starts two bits out of sync. This corrects it.
	gpio_put(vfd.dat, 0);
	for (int i = 0; i < 2; i++) {
		gpio_put(vfd.clk, 0);
		sleep_us(20);
		gpio_put(vfd.clk, 1);
		sleep_us(20);
	}
}

void vfd_write_character_direct (US162SD03CB vfd, uint8_t character) {
	int i = 0;
	gpio_put(vfd.dat, 0);
	sleep_us(DATA_SET_TIME);
	gpio_put(vfd.clk, 0);
	sleep_us(PROCESS_TIME);
	gpio_put(vfd.clk, 1);
	sleep_us(PROCESS_TIME - DATA_SET_TIME);
	for (uint8_t mask=0b10000000; mask>>=1; mask != 0b00000000) {
		gpio_put(vfd.dat, (character & mask) ? 1 : 0);
		sleep_us(DATA_SET_TIME);
		gpio_put(vfd.clk, 0);
		sleep_us(PROCESS_TIME);
		gpio_put(vfd.clk, 1);
		sleep_us(PROCESS_TIME - DATA_SET_TIME);
	}
	sleep_us(PERIOD_TIME);
}

void vfd_reset (US162SD03CB vfd) {
	gpio_put(vfd.rst, 1);
	sleep_ms(40);
	gpio_put(vfd.rst, 0);
}

void vfd_clear (US162SD03CB vfd) {
	vfd_write_character_direct(vfd, CLEAR_DISPLAY);
}

void vfd_write (US162SD03CB vfd, char character) {
	if (character < ' ') return;
	vfd_write_character_direct(vfd, character);
}

void vfd_write_string (US162SD03CB vfd, char *string) {
	while (*string) {
		vfd_write(vfd, *string);
		string++;
	}
}

void vfd_set_cursor (US162SD03CB vfd, uint8_t column, uint8_t row) {
	uint8_t address = row * vfd.columns + column;
	if (address >= vfd.total_chars) address = 0;
	vfd_write_character_direct(vfd, SET_CURSOR_POSITION);
	vfd_write_character_direct(vfd, address + 1);

}

#endif
