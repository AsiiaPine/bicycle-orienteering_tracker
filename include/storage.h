#pragma once

#include <EEPROM.h>

inline void save_uint16(uint16_t value, uint16_t address) {
  EEPROM.put(address, value);
}

inline void save_uint32(uint32_t value, uint16_t address) {
  EEPROM.put(address, value);
}

uint16_t load_uint16(uint16_t address) {
  uint16_t value;
  EEPROM.get(address, value);
  return value;
}

uint32_t load_uint32(uint16_t address) {
  uint32_t value;
  EEPROM.get(address, value);
  return value;
}
