#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include <parameters.h>
#include <run_frame.h>
#include <parameters_frame.h>
#include <run.h>

struct State {
    ParametersInterface param_int;
    RunData run_data;
    RunFrameData run_frame;
    ParametersFrameData parameters_frame;

    void init() {
        param_int.init();
        run_data.set_wheel_diameter(param_int.get(ParametersNames::WHEEL_DIAMETER_MM));
        setup_reed_switch();
        run_frame.draw();
        load_parameters();
    }

    void save_parameters() {
        parameters_frame.save_parameters(&param_int);
    }
    void load_parameters() {
        parameters_frame.load_parameters(&param_int);
    }
    void update_run_frame() {
        run_data.update();
        run_frame.update(run_data);
    }

    void start_run() {
        run_data.start_run(&param_int);
        reed_switch_callback_counter = 0;
    }
};

State state;

#endif  // STATE_H
