#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_1x4(
        MS_BTN1, MS_BTN2, _______, _______
    )
};

uint32_t mouse_deferred_callback(uint32_t trigger_time, void *cb_arg) {
    tap_code(KC_LCTL);
    return 60000;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MS_BTN1:
    case MS_BTN2:
      static bool mouse_toggle[] = {false, false};
      static deferred_token mouse_token[2];

      if (record->event.pressed) {
        unsigned char index = keycode - MS_BTN1;
        mouse_toggle[index] = !mouse_toggle[index];
        if (mouse_toggle[index]) {
          register_code(keycode);
          mouse_token[index] = defer_exec(60000, mouse_deferred_callback, NULL);
        } else {
          unregister_code(keycode);
          cancel_deferred_exec(mouse_token[index]);
        }
      }
      return false; // Skip all further processing of this key
      break;

    default:
      return true; // Process all other keycodes normally
  }
}

