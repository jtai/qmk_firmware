// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

uint32_t deferred_callback(uint32_t trigger_time, void *cb_arg) {
    tap_code(KC_LCTL);
    return 1000;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool enable = false;
  static deferred_token token;

  switch (keycode) {
    case KC_A:
      if (record->event.pressed) {
        enable = !enable;
        if (enable) {
          register_code(QK_MOUSE_BUTTON_1);
          token = defer_exec(1000, deferred_callback, NULL);
        } else {
          unregister_code(QK_MOUSE_BUTTON_1);
          cancel_deferred_exec(token);
        }
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

