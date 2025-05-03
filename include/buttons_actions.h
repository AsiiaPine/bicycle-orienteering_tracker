#ifndef BUTTONS_ACTIONS_H
#define BUTTONS_ACTIONS_H


#include <parameters.h>
#include <run_frame.h>
#include <parameters_frame.h>
#include <buttons.h>
#include <reed_switch.h>

enum FrameNum {
    PARAM_FRAME,
    RUN_FRAME
};

struct ButtonsActions {
    void setup(RunData* run_data, ParametersInterface* param_int,
                RunFrameData* run_frame, ParametersFrameData* parameters_frame) {
        this->run_data = run_data;
        this->param_int = param_int;
        this->run_frame = run_frame;
        this->parameters_frame = parameters_frame;
        frame_num = RUN_FRAME;
    }

    void update() {
        left_top_pressed = (check_bottom_falling_edge(LEFT_TOP_PIN, &LEFT_TOP_STATE));
        left_bot_pressed = (check_bottom_falling_edge(LEFT_BOT_PIN, &LEFT_BOT_STATE));
        right_top_pressed = (check_bottom_falling_edge(RIGHT_TOP_PIN, &RIGHT_TOP_STATE));
        right_bot_pressed = (check_bottom_falling_edge(RIGHT_BOT_PIN, &RIGHT_BOT_STATE));
        if (left_top_pressed && left_bot_pressed) {
            change_frame();
            return;
        }
        if (right_top_pressed && right_bot_pressed) {
            reed_switch_callback_counter = 0;
            return;
        }
        if (frame_num == PARAM_FRAME) {
            parameters_frame_callback();
            parameters_frame->draw();
            return;
        }
        run_frame_callback();
        run_frame->draw();
    }

 private:
    FrameNum frame_num;
    RunData* run_data;
    ParametersInterface* param_int;
    RunFrameData* run_frame;
    ParametersFrameData* parameters_frame;

    void change_frame() {
        if (frame_num == PARAM_FRAME) {
            parameters_frame->save_parameters(param_int);
            frame_num = RUN_FRAME;
            return;
        }
        frame_num = PARAM_FRAME;
        parameters_frame->load_parameters(param_int);
    }

    void parameters_frame_callback() {
        if (left_top_pressed) {
            parameters_frame->prev_row();
            return;
        }
        if (left_bot_pressed) {
            parameters_frame->next_row();
            return;
        }
        if (right_top_pressed) {
            parameters_frame->increase_value();
            return;
        }
        if (right_bot_pressed) {
            parameters_frame->decrease_value();
        }
    }

    void run_frame_callback() {
        run_frame->update(*run_data);
    }
    bool left_top_pressed = false;
    bool left_bot_pressed = false;
    bool right_top_pressed = false;
    bool right_bot_pressed = false;
};

#endif  // BUTTONS_ACTIONS_H
