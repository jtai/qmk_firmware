#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_1x4(
        LT(0, MS_BTN1), LT(0, MS_BTN2), _______, _______
    )
};

typedef struct mouse_key_deferred_data {
  uint16_t keycode;
  uint32_t led;
  uint32_t delay;
} mouse_key_deferred_data;

typedef struct mouse_key_state {
  bool toggled;
  mouse_key_deferred_data data;
  deferred_token token;
} mouse_key_state;

uint32_t mouse_key_deferred_callback(uint32_t trigger_time, void *cb_arg) {
    mouse_key_deferred_data* data = (mouse_key_deferred_data*)cb_arg;
    if (data->led) {
      gpio_write_pin_high(data->led);
    }
    tap_code_delay(data->keycode, 50);
    if (data->led) {
      gpio_write_pin_low(data->led);
    }
    return data->delay;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(0, MS_BTN1):
    case LT(0, MS_BTN2):
      if (record->event.pressed) {
        static mouse_key_state mouse_key_states[2];

        unsigned char index = keycode - LT(0, MS_BTN1); // Assumes keycodes are adjacent
        mouse_key_state* state = &mouse_key_states[index];
        uint16_t tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
        uint32_t led = index == 0 ? LED1 : LED2;

        state->toggled = !state->toggled;
        if (state->toggled) {
          if (record->tap.count) {
            state->data = (mouse_key_deferred_data) {tap_keycode, led, 1000};
            state->token = defer_exec(1, mouse_key_deferred_callback, &state->data);
          } else {
            register_code(tap_keycode);
            gpio_write_pin_high(led);
            state->data = (mouse_key_deferred_data) {KC_LCTL, 0, 60000};
            state->token = defer_exec(60000, mouse_key_deferred_callback, &state->data);
          }
        } else {
          unregister_code(tap_keycode);
          gpio_write_pin_low(led);
          cancel_deferred_exec(state->token);
        }
      }
      return false; // Skip all further processing of this key
      break;

    default:
      return true; // Process all other keycodes normally
  }
}
