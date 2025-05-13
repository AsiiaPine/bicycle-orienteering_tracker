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
