#ifndef IOXhop_I2CKeypad_h
#define IOXhop_I2CKeypad_h

#include <Arduino.h>
#include <Wire.h>

/*
 *  PIN MAPPING
 *
 *  Here you can change your wire mapping between your keypad and PCF8574
 *  Default mapping is for 4x4 keypad
 */

#define ROW0  0
#define ROW1  1
#define ROW2  2
#define ROW3  3
#define COL0  4
#define COL1  5
#define COL2  6
#define COL3  7

class IOXhop_I2CKeypad {
	public:
		IOXhop_I2CKeypad(int) ;
		IOXhop_I2CKeypad(int, int, int) ;
		void begin(bool startWire = true) ;
		char get_key() ;

	private:
	
		/*
		 *  KEYPAD KEY MAPPING
		 *
		 *  Default key mapping for 4x4 keypads, you can change it here if you have or
		 *  like different keys
		 */

		const char keymap[4][5] = {
		  "123A",
		  "456B",
		  "789C",
		  "*0#D"
		};

		/*
		 *  VAR AND CONSTANTS DEFINITION. Don't change nothing here
		 *
		 */

		// Default row and col pin counts
		int num_rows, num_cols;

		// PCF8574 i2c address
		int pcf8574_i2c_addr;

		// Current search row
		int row_select;

		// Current data set in PCF8574
		int current_data;

		// Hex byte statement for each port of PCF8574
		const byte hex_data[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

		// Hex data for each row of keypad in PCF8574
		const byte pcf8574_row_data[4] = {
			hex_data[ROW1] | hex_data[ROW2] | hex_data[ROW3] |
			hex_data[COL0] | hex_data[COL1] | hex_data[COL2] | hex_data[COL3],
			hex_data[ROW0] | hex_data[ROW2] | hex_data[ROW3] |
			hex_data[COL0] | hex_data[COL1] | hex_data[COL2] | hex_data[COL3],
			hex_data[ROW0] | hex_data[ROW1] | hex_data[ROW3] |
			hex_data[COL0] | hex_data[COL1] | hex_data[COL2] | hex_data[COL3],
			hex_data[ROW0] | hex_data[ROW1] | hex_data[ROW2] |
			hex_data[COL0] | hex_data[COL1] | hex_data[COL2] | hex_data[COL3],
		};

		// Hex data for each col of keypad in PCF8574
		byte col[4] = {hex_data[COL0], hex_data[COL1], hex_data[COL2], hex_data[COL3]};
		
		void pcf8574_write(int, int);
		int pcf8574_byte_read(int);

}
;

#endif

