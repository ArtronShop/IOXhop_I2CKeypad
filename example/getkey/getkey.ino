/*
 *  getkey.ino - keypad/I2C expander interface example for Arduino
 *
 *  Copyright (c) 2017 IOXhop : www.ioxhop.com
 *  All rights reserved.
 *
 *  Original source from i2ckeypad v0.1 of Angel Sancho <angelitodeb@gmail.com>
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
 */

#include <Wire.h>
#include <IOXhop_I2CKeypad.h>

#define ROWS 4
#define COLS 4

// With A0, A1 and A2 of PCF8574 to ground I2C address is 0x20
#define PCF8574_ADDR 0x20


IOXhop_I2CKeypad kpd(PCF8574_ADDR, ROWS, COLS);

void setup() {
  Serial.begin(9600);

  kpd.begin();

  Serial.println("Testing keypad/PCF8574 I2C port expander arduino lib");
  Serial.println("---------------------");
}

void loop() {
  char key = kpd.get_key();
  if(key != '\0') {
    Serial.print(key);
    delay(300);
  }
}