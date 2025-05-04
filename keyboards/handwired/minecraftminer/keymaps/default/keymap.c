#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_1x4(
        KC_A, KC_B, KC_C, KC_D
    )
};

// tap CTRL once a minute to prevent idle
uint32_t deferred_callback(uint32_t trigger_time, void *cb_arg) {
    tap_code(KC_LCTL);
    return 60000;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool enable[] = {false, false};
  static deferred_token token[2];
  static uint16_t buttons[] = {QK_MOUSE_BUTTON_1, QK_MOUSE_BUTTON_2};

  switch (keycode) {
    case KC_A:
    case KC_B:
      uint16_t index = keycode - KC_A;
      if (record->event.pressed) {
        enable[index] = !enable[index];
        if (enable[index]) {
          register_code(buttons[index]);
          token[index] = defer_exec(60000, deferred_callback, NULL);
        } else {
          unregister_code(buttons[index]);
          cancel_deferred_exec(token[index]);
        }
      }
      return false; // Skip all further processing of this key
      break;

    default:
      return true; // Process all other keycodes normally
  }
}

