/*
 *  IOXhop_I2CKeypad.cpp v0.1 - keypad/I2C expander interface for Arduino
 *
 *  Copyright (c) 2017 IOXhop : www.ioxhop.com
 *  All rights reserved.
 *
 *  Original source from i2ckeypad v0.1 of Angel Sancho <angelitodeb@gmail.com>
 *  Original source from keypad v0.3 of Mark Stanley <mstanley@technologist.com>
 *  (http://www.arduino.cc/playground/Main/KeypadTutorial)
 *
 *
 *  LICENSE
 *  -------
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *  EXPLANATION
 *  -----------
 *  This library is designed for use with PCF8574, but can possibly be
 *  adapted to other I2C port expanders
 *
 *  Wiring diagrams for PCF8574 and 4x3 keypad can be found under
 *  examples directory. Library runs correctly without cols pull-up
 *  resistors but it's better to use it
 *
 *  You can change pin connections between PCF8574 and keypad under
 *  PIN MAPPING section below
 *
 *  IMPORTANT! You have to call Wire.begin() before init() in your code
 *
 *  ... and sorry for my poor english!
 */

#include "IOXhop_I2CKeypad.h"

/*
 *  CONSTRUCTORS
 */

IOXhop_I2CKeypad::IOXhop_I2CKeypad(int addr) {
	IOXhop_I2CKeypad(addr, 4, 4);
}

IOXhop_I2CKeypad::IOXhop_I2CKeypad(int addr, int r, int c) {
	pcf8574_i2c_addr = addr;
	num_rows = r;
	num_cols = c;
}


/*
 *  PUBLIC METHODS
 */
 
void IOXhop_I2CKeypad::begin(bool startWire) {
	// I2C begin
	if (startWire) Wire.begin();

	// All PCF8574 ports high
	pcf8574_write(pcf8574_i2c_addr, 0xff);

	// Start with the first row
	row_select = 0;
}

char IOXhop_I2CKeypad::get_key() {
	static int temp_key;
	int tmp_data;
	int key = '\0';

	// Search row low
	pcf8574_write(pcf8574_i2c_addr, pcf8574_row_data[row_select]);

	for(int r=0;r<num_cols;r++) {
		// Read pcf8574 port data
		tmp_data = pcf8574_byte_read(pcf8574_i2c_addr);

		// XOR to compare obtained data and current data and know
		// if some column are low
		tmp_data ^= current_data;

		// Key pressed!
		if(col[r] == tmp_data) {
			temp_key = keymap[row_select][r];
			return '\0';
		}
	}

	// Key was pressed and then released
	if((key == '\0') && (temp_key != '\0')) {
		key = temp_key;
		temp_key = '\0';
		return key;
	}

	// All PCF8574 ports high again
	pcf8574_write(pcf8574_i2c_addr, 0xff);

	// Next row
	row_select = ++row_select == num_rows ? 0 : row_select;

	return key;
}

/*
 *  PRIVATE METHODS
 */

void IOXhop_I2CKeypad::pcf8574_write(int addr, int data) {
	current_data = data;

	Wire.beginTransmission(addr);
	Wire.write(data);
	Wire.endTransmission();
}

int IOXhop_I2CKeypad::pcf8574_byte_read(int addr) {
	Wire.requestFrom(addr, 1);

	return Wire.read();
}

