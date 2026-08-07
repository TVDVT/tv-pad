// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌─────┬───────┬──────┐
     * │ SS  │  DEL  │ENTER │ 
     * ├─────┼───────┼──────┤
     * │ CUT │ COPY  │PASTE │ note taking
     * ├─────┼───────┼──────┤
     * │ VUP │ PAUSE │ VDWN │ music
     * ├─────┼───────┼──────┼
     */
    [0] = LAYOUT(
        KC_PSCR,   KC_DELETE,   KC_ENTER,   
        KC_CUT,   KC_COPY,   KC_PASTE,   
        KC_KB_VOLUME_UP,   KC_MEDIA_PLAY_PAUSE, KC_KB_VOLUME_DOWN
    ) 
};
