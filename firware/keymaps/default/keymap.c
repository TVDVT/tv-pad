// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <string.h>
static uint16_t last_keypress = 0;
static const char *oled_message = "(O__O)";
#define MY_UNDO  LCTL(KC_Z)
#define MY_CUT   LCTL(KC_X)
#define MY_COPY  LCTL(KC_C)
enum custom_keycodes {
    MY_PASTE = SAFE_RANGE
};
#define MY_TAB LGUI(KC_TAB)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌─────┬───────┬──────┐  
     * │ SS  │ UNDO  │ENTER │ 
     * ├─────┼───────┼──────┤
     * │ CUT │ COPY  │PASTE │ note taking
     * ├─────┼───────┼──────┤
     * │ VUP │ PAUSE │ VDWN │ music
     * ├─────┼───────┼──────┼
     */
    [0] = LAYOUT(
        KC_PSCR,  MY_UNDO,   MY_TAB,   
        MY_CUT,   MY_COPY,   MY_PASTE,   
        KC_AUDIO_VOL_DOWN,   KC_MEDIA_PLAY_PAUSE, KC_AUDIO_VOL_UP
    ) 
};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == MY_PASTE) {
        if (record->event.pressed) {
            last_keypress = timer_read();
            oled_message = "PASTE";
            return true;
        } else {
            if (timer_elapsed(last_keypress) >= 500) {
                tap_code16(LGUI(KC_V));
            } else {
                tap_code16(LCTL(KC_V));
            }
            return false;
        }
    }

    if (record->event.pressed) {
        last_keypress = timer_read();

        if (keycode == MY_UNDO) {
            oled_message = "UNDO";
        } else if (keycode == KC_PSCR) {
            oled_message = "SWITCH TAB";
        } else if (keycode == MY_TAB) {
            oled_message = "SCREENSHOT";
        } else if (keycode == MY_COPY) {
            oled_message = "COPY";
        } else if (keycode == MY_CUT) {
            oled_message = "CUT";
        } else if (keycode == KC_AUDIO_VOL_DOWN) {
            oled_message = "VOLUME DOWN";
        } else if (keycode == KC_AUDIO_VOL_UP) {
            oled_message = "VOLUME UP";
        } else if (keycode == KC_MEDIA_PLAY_PAUSE) {
            oled_message = "PAUSE/PLAY";
        }
    }

    return true;
}
#ifdef OLED_ENABLE

bool oled_task_user(void) {
    static const char *last_displayed = "";

    if (timer_elapsed(last_keypress) >= 3000) {
        oled_message = "(O__O)";
    }

    if (strcmp(oled_message, last_displayed) != 0) {
        oled_clear();

        uint8_t text_length = strlen(oled_message);
        uint8_t column = (21 - text_length) / 2;

        oled_set_cursor(column, 1);
        oled_write(oled_message, false);

        last_displayed = oled_message;
    }

    return false;
}

#endif