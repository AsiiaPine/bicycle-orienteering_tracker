#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <EEPROM.h>

#define EEPROM_SIZE 512
#define EEPROM_START_ADDRESS 0

struct ParameterBounds {
    uint16_t min;
    uint16_t max;
    uint16_t default_value;
    void in_range(uint16_t *value) {
        if (*value < min) {
            *value = min;
        }
        if (*value > max) {
            *value = max;
        }
    }
};

enum ParametersNames {
    TIME_LIMIT_H,
    DISTANCE_KM,
    WHEEL_DIAMETER_MM,
    SCALE,
    NUM_PARAMETERS
};

struct ParametersInterface {
    inline void init() {
        init_bounds();
        read();
    }

    void set(ParametersNames name, uint16_t value) {
        bounds[name].in_range(&value);
        parameters[name] = value;
    }

    uint16_t get(ParametersNames name) {
        return parameters[name];
    }

    inline void save() {
        EEPROM.put(EEPROM_START_ADDRESS, *this);
    }

 private:
    uint16_t parameters[ParametersNames::NUM_PARAMETERS];
    ParameterBounds bounds[ParametersNames::NUM_PARAMETERS];
    void init_bounds() {
        bounds[ParametersNames::TIME_LIMIT_H] = {0, 99, 8};
        bounds[ParametersNames::DISTANCE_KM] = {0, 999, 80};
        bounds[ParametersNames::WHEEL_DIAMETER_MM] = {0, 5000, 2200};
        bounds[ParametersNames::SCALE] = {1, 25, 999};
    }
    inline void read() {
        EEPROM.get(EEPROM_START_ADDRESS, *parameters);
        for (uint8_t i = 0; i < ParametersNames::NUM_PARAMETERS; i++) {
            bounds[i].in_range(&parameters[i]);
        }
    }
};

#endif  // PARAMETERS_H
