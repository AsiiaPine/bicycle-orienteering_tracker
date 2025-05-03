#ifndef BUTTONS_ACTIONS_H
#define BUTTONS_ACTIONS_H

#include <run_frame.h>
#include <parameters_frame.h>
#include <buttons.h>
#include <reed_switch.h>
#include <state.h>

enum FrameNum {
    PARAM_FRAME,
    RUN_FRAME
};

struct ButtonsActions {
    void setup() {
        frame_num = RUN_FRAME;
    }

    void update_state() {
        left_top_pressed = (check_bottom_falling_edge(LEFT_TOP_PIN, &LEFT_TOP_STATE));
        left_bot_pressed = (check_bottom_falling_edge(LEFT_BOT_PIN, &LEFT_BOT_STATE));
        right_top_pressed = (check_bottom_falling_edge(RIGHT_TOP_PIN, &RIGHT_TOP_STATE));
        right_bot_pressed = (check_bottom_falling_edge(RIGHT_BOT_PIN, &RIGHT_BOT_STATE));
        if (left_top_pressed && left_bot_pressed) {
            change_frame();
            return;
        }

        if (state.parameters_frame.ToStart) {
            state.parameters_frame.ToStart = false;
            frame_num = RUN_FRAME;
            state.start_run();
            return;
        }
        if (state.parameters_frame.ToContinue) {
            frame_num = PARAM_FRAME;
            state.parameters_frame.ToContinue = false;
            return;
        }
        if (right_top_pressed && right_bot_pressed) {
            state.run_data.make_reset();
            return;
        }
        if (frame_num == PARAM_FRAME) {
            parameters_frame_callback();
            state.parameters_frame.draw();
            return;
        }
        state.update_run_frame();
    }

 private:
    FrameNum frame_num = RUN_FRAME;

    void parameters_frame_callback() {
        if (left_top_pressed) {
            state.parameters_frame.prev_row();
            return;
        }
        if (left_bot_pressed) {
            state.parameters_frame.next_row();
            return;
        }
        if (right_top_pressed) {
            state.parameters_frame.increase_value();
            return;
        }
        if (right_bot_pressed) {
            state.parameters_frame.decrease_value();
        }
    }

    void change_frame() {
        if (frame_num == PARAM_FRAME) {
            state.save_parameters();
            frame_num = RUN_FRAME;
            return;
        }
        frame_num = PARAM_FRAME;
        state.load_parameters();
    }
    void run_frame_callback() {
    }
    bool left_top_pressed = false;
    bool left_bot_pressed = false;
    bool right_top_pressed = false;
    bool right_bot_pressed = false;
};

#endif  // BUTTONS_ACTIONS_H
