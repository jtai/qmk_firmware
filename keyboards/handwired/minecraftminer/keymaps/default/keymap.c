#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_1x4(
        LT(0, MS_BTN1), LT(0, MS_BTN2), QK_BOOT, _______
    )
};

typedef struct mouse_key_state {
  bool toggled;
  bool hold;
  uint16_t keycode;
  uint32_t delay;
  deferred_token token;
  bool indicator;
} mouse_key_state;

static mouse_key_state mouse_key_states[2];

uint32_t mouse_key_indicator_deferred_callback(uint32_t trigger_time, void *cb_arg) {
  mouse_key_state* state = (mouse_key_state*)cb_arg;
  state->indicator = false;
  return 0;
}

uint32_t mouse_key_deferred_callback(uint32_t trigger_time, void *cb_arg) {
  mouse_key_state* state = (mouse_key_state*)cb_arg;
  if (!state->hold) {
    state->indicator = true;
    defer_exec(25, mouse_key_indicator_deferred_callback, state);
  }
  tap_code(state->keycode);
  return state->delay;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(0, MS_BTN1):
    case LT(0, MS_BTN2):
      if (record->event.pressed) {
        unsigned char index = keycode - LT(0, MS_BTN1); // Assumes keycodes are adjacent
        mouse_key_state* state = &mouse_key_states[index];

        uint16_t tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);

        state->toggled = !state->toggled;
        if (state->toggled) {
          if (record->tap.count) {
            state->hold = false;
            state->keycode = tap_keycode;
            state->delay = 1000;
            state->token = defer_exec(1, mouse_key_deferred_callback, state);
          } else {
            state->hold = true;
            state->keycode = KC_LCTL;
            state->delay = 60000;
            state->token = defer_exec(60000, mouse_key_deferred_callback, state);

            register_code(tap_keycode);
            state->indicator = true;
          }
        } else {
          cancel_deferred_exec(state->token);

          if (state->hold) {
            unregister_code(tap_keycode);
            state->indicator = false;
          }
        }
      }
      return false; // Skip all further processing of this key
      break;

    default:
      return true; // Process all other keycodes normally
  }
}

void housekeeping_task_user(void) {
  gpio_write_pin(LED1, mouse_key_states[0].indicator);
  gpio_write_pin(LED2, mouse_key_states[1].indicator);
}