#include QMK_KEYBOARD_H
#include "features/caps_word.h"

#define _QWERTY 0
#define _COLEMAK 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

enum custom_keycodes {
    KC_SPAM_BSPC = SAFE_RANGE,
};

enum tap_dances {
    TD_LWR,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // generally try to keep keys where they are on a "normal" keyboard (at least relatively, e.g., order of esc/tab/shift)
    // for modifiers, keep shift keys in normal position, but move main modifiers to thumb keys, and use mod tap for LCTL/HYPER modifiers
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
 LCTL_T(KC_TAB), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, HYPR_T(KC_QUOT),
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                            KC_LALT, KC_LGUI, TD(TD_LWR), MO(_RAISE), KC_SPC,  KC_ENT
    ),

    [_COLEMAK] = LAYOUT_split_3x6_3(
        _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______,
        _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                            KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    _______,
        _______, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                            KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, _______,
                                            _______, _______, _______,       _______, _______, _______
    ),

    // number/symbols and media layer, again try to keep symbols in similar positions (or at least relative positions) as a "normal" keyboard
    // position of thumb key used to activate this layer allows holding shift, so dedicated keys for !@#$... are not required
    // media keys should be accessible with left hand only
    [_LOWER] = LAYOUT_split_3x6_3(
        KC_GRV,  _______, _______, _______, _______, _______,                         _______, _______, _______, KC_MINS, KC_EQL,  _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, _______, KC_VOLD, KC_VOLU, KC_MPLY, KC_MNXT,                         _______, _______, _______, KC_LBRC, KC_RBRC, RSFT_T(KC_BSLS),
                                            _______, _______, _______,       _______, _______, _______
    ),

    // nav layer, should be accessible with right hand only
    [_RAISE] = LAYOUT_split_3x6_3(
        _______, _______, _______, _______, _______, _______,                         _______, _______, KC_UP,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                         KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,                         KC_PGDN, KC_HOME, _______, KC_END,  _______, _______,
                                            _______, _______, _______,       _______, _______, _______
    ),

    // function layer for F1..F12 keys and caps lock, as well as keyboard functions like reset and n-key rollover toggle
    [_ADJUST] = LAYOUT_split_3x6_3(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_SPAM_BSPC,
        KC_CAPS, KC_F11,  KC_F12,  _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
        _______, _______, DF(_QWERTY), DF(_COLEMAK), _______, RESET,                  NK_TOGG, _______, _______, _______, _______, _______,
                                            _______, _______, _______,       _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Caps word feature, see https://getreuer.info/posts/keyboards/caps-word/index.html
    if (!process_caps_word(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case MO(_RAISE):
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            return false;

        case KC_SPAM_BSPC:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < 24; i++) {
                    tap_code(KC_BSPC);
                }
            }
            return false;

        // TODO: intercept RESET and turn on both indicator LEDs

        default:
            return true;
    }
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // allow mod tap interrupt for ctrl
        // tab is typically typed on its own, so chances of rolling are low
        case LCTL_T(KC_TAB):
            return false;
        default:
            return true;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_LWR):
            return TAPPING_TERM + 100;
        default:
            return TAPPING_TERM;
    }
}

static bool dance_lower_gui_hold = false;
static bool dance_lower_alt_hold = false;

void dance_lower_each(qk_tap_dance_state_t *state, void *user_data) {
    layer_on(_LOWER);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
}

void dance_lower_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            break;
        case 2:
            dance_lower_gui_hold = true;
            register_code(KC_LGUI);
            caps_word_set(false);
            break;
        case 3:
            dance_lower_alt_hold = true;
            register_code(KC_LALT);
            caps_word_set(false);
            break;
        default:
            dance_lower_gui_hold = true;
            dance_lower_alt_hold = true;
            register_code(KC_LGUI);
            register_code(KC_LALT);
            caps_word_set(false);
            break;
    }
}

void dance_lower_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (dance_lower_alt_hold) {
        dance_lower_alt_hold = false;
        unregister_code(KC_LALT);
    }
    if (dance_lower_gui_hold) {
        dance_lower_gui_hold = false;
        unregister_code(KC_LGUI);
    }
    layer_off(_LOWER);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LWR] = ACTION_TAP_DANCE_FN_ADVANCED(dance_lower_each, dance_lower_finished, dance_lower_reset),
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

bool led_update_user(led_t led_state) {
    // caps lock indicator should only light on the left (non-master) side
    return !is_keyboard_master();
}

void caps_word_set_user(bool active) {
    // caps word indicator should only light on the right (master) side
    // this code will only run on the master because caps word state
    // is not transported to the non-master side
    uint16_t level = active ? LED_PIN_ON_STATE : ~LED_PIN_ON_STATE;
    writePin(LED_CAPS_LOCK_PIN, level);
}
