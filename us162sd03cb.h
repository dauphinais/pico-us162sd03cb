#ifndef _US162SD03CB_H_
#define _US162SD03CB_H_

#include "pico/stdlib.h"

// Control Characters

#define CLEAR_DISPLAY 1
#define SET_CURSOR_POSITION 2
#define SET_CURSOR_MODE 3
#define SET_BRIGHTNESS 4
#define SET_IO_MODE 5
#define SET_FLASH_POSITION 6
#define SET_FLASH_MODE 7
#define SET_FLASH_RATE 8
#define SELECT_FONT 9
#define LOAD_USER_CHAR 10
#define SET_BUFFERED_MODE 11
#define PRINT_MESSAGE_BUFFER 12

// Timings
#define PROCESS_TIME 20
#define PERIOD_TIME 40
#define DATA_SET_TIME 3
#define RESET_SET_TIME 30
#define RESET_HOLD_TIME 2000

///////////////////////////////////////

typedef struct {
	const uint8_t clk;
	const uint8_t dat;
	const uint8_t rst;

	uint8_t columns;
	uint8_t rows;

	int total_chars;

	uint8_t period;
} US162SD03CB;

/*
	Creates a new VFD
	uint8_t : clock
	uint8_t : data
	uint8_t : reset
*/
US162SD03CB vfd_init (const uint8_t, const uint8_t, const uint8_t);

/*
	Starts the VFD
	US162SD03CB : The VFD
	uint8_t : number of columns
	uint8_t : number of rows
*/
void vfd_begin (US162SD03CB, uint8_t, uint8_t);

/*
	Resets the VFD
	US162SD03CB : The VFD
*/
void vfd_reset (US162SD03CB);

/*
	clears display
*/
void vfd_clear (US162SD03CB);

/*
	Directly writes a character to the display
	US162SD03CB : The VFD
	uint8_t : The character to write
*/
void vfd_write_character_direct (US162SD03CB, uint8_t);

/*
	Writes a character to the display
	US162SD03CB : The VFD
	uint8_t : The character to write
*/
void vfd_write (US162SD03CB, char);

/*
	Writes a string to the display
	US162SD03CB : The VFD
	*char : The string to write
*/
void vfd_write_string (US162SD03CB, char*);

/*
	Sets cursor on VFD
	US162SD03CB : The VFD
	uint8_t : The column
	uint8_t : The row
*/
void vfd_set_cursor (US162SD03CB, uint8_t, uint8_t);

#endif
