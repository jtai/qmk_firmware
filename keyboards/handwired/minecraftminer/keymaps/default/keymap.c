#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_1x4(
        LT(0, MS_BTN1), LT(0, MS_BTN2), _______, _______
    )
};

uint16_t mouse_buttons[] = {MS_BTN1, MS_BTN2};
const uint32_t mouse_leds[] = {LED1, LED2};

uint32_t mouse_tap_deferred_callback(uint32_t trigger_time, void *cb_arg) {
    uint16_t keycode = *(uint16_t*)cb_arg;
    unsigned char index = keycode - MS_BTN1;
    gpio_write_pin_high(mouse_leds[index]);
    tap_code(keycode);
    gpio_write_pin_low(mouse_leds[index]);
    return 1000;
}

uint32_t mouse_hold_deferred_callback(uint32_t trigger_time, void *cb_arg) {
    tap_code(KC_LCTL);
    return 60000;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(0, MS_BTN1):
    case LT(0, MS_BTN2):
      static bool mouse_toggle[] = {false, false};
      static deferred_token mouse_token[2];

      if (record->event.pressed) {
        unsigned char index = keycode - LT(0, MS_BTN1);
        mouse_toggle[index] = !mouse_toggle[index];
        if (mouse_toggle[index]) {
          if (record->tap.count) {
            mouse_token[index] = defer_exec(1, mouse_tap_deferred_callback, &mouse_buttons[index]);
          } else {
            register_code(mouse_buttons[index]);
            gpio_write_pin_high(mouse_leds[index]);
            mouse_token[index] = defer_exec(60000, mouse_hold_deferred_callback, NULL);
          }
        } else {
          unregister_code(mouse_buttons[index]);
          gpio_write_pin_low(mouse_leds[index]);
          cancel_deferred_exec(mouse_token[index]);
        }
      }
      return false; // Skip all further processing of this key
      break;

    default:
      return true; // Process all other keycodes normally
  }
}
