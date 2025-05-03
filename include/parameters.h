#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <EEPROM.h>

// #define EEPROM_SIZE 512
#define EEPROM_START_ADDRESS 0

struct ParameterBounds {
    uint16_t min;
    uint16_t max;
    uint16_t default_value;
    uint16_t in_range(uint16_t value) {
        if (value < min) {
            value = default_value;
        }
        if (value > max) {
            value = default_value;
        }
        return value;
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
        uint16_t new_value = bounds[name].in_range(value);
        parameters[name] = new_value;
    }

    uint16_t get(ParametersNames name) {
        return parameters[name];
    }

    inline void save() {
        // for (uint8_t i = 0; i < ParametersNames::NUM_PARAMETERS; i++) {
        //     EEPROM.put(EEPROM_START_ADDRESS + i*sizeof(uint16_t), parameters[i]);
        // }

    }

 private:
    uint16_t parameters[ParametersNames::NUM_PARAMETERS];
    ParameterBounds bounds[ParametersNames::NUM_PARAMETERS];
    void init_bounds() {
        bounds[ParametersNames::TIME_LIMIT_H] = {1, 99, 8};
        bounds[ParametersNames::DISTANCE_KM] = {1, 999, 80};
        bounds[ParametersNames::WHEEL_DIAMETER_MM] = {10, 5000, 2200};
        bounds[ParametersNames::SCALE] = {1, 999, 25};
    }
    inline void read() {
        for (uint8_t i = 0; i < ParametersNames::NUM_PARAMETERS; i++) {
            uint16_t value = 0;
            // EEPROM.get(EEPROM_START_ADDRESS + i * sizeof(uint16_t), value);
            parameters[i] = bounds[i].in_range(value);
        }
    }
};

#endif  // PARAMETERS_H
