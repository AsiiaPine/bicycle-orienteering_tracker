#pragma once

#include <EEPROM.h>

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

inline void save_uint16(uint16_t value, uint16_t address) {
  while (load_uint16(address) != value) {
    EEPROM.put(address, value);
  }
}

inline void save_uint32(uint32_t value, uint16_t address) {
  while (load_uint32(address) != value) {
    EEPROM.put(address, value);
  }
}
