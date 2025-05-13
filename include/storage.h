/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Anastasiia Stepanova <asiiapine@gmail.com>
 * Copyright (c) 2025
 */

#pragma once

#include <EEPROM.h>

// Save uint16 value to EEPROM. Max value is 65535
uint16_t load_uint16(uint16_t address) {
  uint16_t value;
  EEPROM.get(address, value);
  return value;
}

// Save uint32 value to EEPROM. Max value is 4294967295
uint32_t load_uint32(uint16_t address) {
  uint32_t value;
  EEPROM.get(address, value);
  return value;
}

// Save uint16 value to EEPROM. Max value is 65535
inline void save_uint16(uint16_t value, uint16_t address) {
  while (load_uint16(address) != value) {
    EEPROM.put(address, value);
  }
}

// Save uint32 value to EEPROM. Max value is 4294967295
inline void save_uint32(uint32_t value, uint16_t address) {
  while (load_uint32(address) != value) {
    EEPROM.put(address, value);
  }
}
