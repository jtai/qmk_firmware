#include QMK_KEYBOARD_H
#include "features/caps_word.h"

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // generally try to keep keys where they are (at least relatively, e.g., order of esc/tab/shift) on a "normal" keyboard
    // shift keys in normal position, main modifiers on thumb keys, mod tap for LCTL/HYPER modifiers
    // enter gets a dedicated key
    // reserve two keys for layers
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
 LCTL_T(KC_TAB), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, HYPR_T(KC_QUOT),
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                            KC_LALT, KC_LGUI, MO(_LOWER), MO(_RAISE), KC_SPC,  KC_ENT
    ),

    // number/symbols and media layer, again try to keep symbols in similar positions (or at least relative positions) as a "normal" keyboard
    // position of thumb key should allow holding shift, so dedicated keys for !@#$... are not required
    // media keys should be accessible with left hand only
    [_LOWER] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        _______, _______, KC_VOLD, KC_VOLU, KC_MPLY, KC_MNXT,                         _______, _______, _______, _______, KC_MINS, KC_EQL,
        _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, KC_LBRC, KC_RBRC,
                                            _______, _______, _______,       _______, _______, _______
    ),

    // nav layer, should be accessible with right hand only
    // left hand number keys is to allow common cmd+number key combos without requiring left thumb to press two adjacent thumb keys
    // for cmd+n where n is 6..0, left thumb and index finger can be used to press cmd and layer key
    [_RAISE] = LAYOUT_split_3x6_3(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                            _______, KC_PGUP, KC_UP,   KC_HOME, _______, _______,
        _______, _______, _______, _______, _______, _______,                         _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,                         _______, KC_PGDN, _______, KC_END,  _______, _______,
                                            _______, _______, _______,       _______, _______, _______
    ),

    // function layer for F1..F12 keys and caps lock, as well as keyboard functions like reset and n-key rollover toggle
    [_ADJUST] = LAYOUT_split_3x6_3(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        KC_CAPS, KC_F11,  KC_F12,  _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, RESET,                           NK_TOGG, _______, _______, _______, _______, _______,
                                            _______, _______, _______,       _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Caps word feature, see https://getreuer.info/posts/keyboards/caps-word/index.html
    if (!process_caps_word(keycode, record)) {
        return false;
    }

    if (keycode == MO(_LOWER)) {
        if (record->event.pressed) {
            layer_on(_LOWER);
        } else {
            layer_off(_LOWER);
        }
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        return false;
    }

    if (keycode == MO(_RAISE)) {
        if (record->event.pressed) {
            layer_on(_RAISE);
        } else {
            layer_off(_RAISE);
        }
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        return false;
    }

    return true;
}

// TODO: set P13 LEDs
// left on = caps lock
// right on = caps word
// both on = firmware flashing mode
