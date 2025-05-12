/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _MASK,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ansi_67(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,   KC_BSPC,          LT(0, KC_MPLY),
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,            KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,            KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN),  KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT),

    [_MASK] = LAYOUT_ansi_67(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,          _______,
        KC_HYPR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______,
        _______, _______, _______,                            _______,                            _______, _______,  _______,  _______, _______, _______),

    [_FN] = LAYOUT_ansi_67(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,   KC_DEL,           KC_MUTE,
        RM_TOGG, RM_NEXT, RM_VALU, RM_HUEU, RM_SATU, RM_SPDU, _______, _______, _______, _______, _______, MS_BTN1,  MS_BTN2,  _______,          KC_HOME,
        KC_CAPS, RM_PREV, RM_VALD, RM_HUED, RM_SATD, RM_SPDD, _______, _______, _______, _______, _______, _______,            _______,          KC_END,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,            _______, _______,
        _______, _______, _______,                            _______,                            _______, _______,  _______,  _______, _______, _______)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_MASK] = { ENCODER_CCW_CW(_______, _______) },
    [_FN]   = { ENCODER_CCW_CW(_______, _______) },
};
#endif

// Override default win/mac switch behavior, caps lock ("win") becomes hyper ("mac")
bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        if (active) {
            layer_off(_MASK);
        } else {
            layer_on(_MASK);
        }
        return false;
    }
    return true;
}

uint32_t mouse_deferred_callback(uint32_t trigger_time, void *cb_arg) {
    tap_code(KC_LCTL);
    return 60000;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Adapted from quantum/process_keycode/process_grave_esc.c, except consider QK_GRAVE_ESCAPE shifted if
        // ALT is pressed (instead of GUI) to accommodate a physical Windows-style keyboard layout (CTRL, GUI, ALT)
        // with GUI and ALT swapped in macOS.
        case QK_GRAVE_ESCAPE:
            const uint8_t mods = get_mods();
            uint8_t shifted = mods & MOD_MASK_SA;

            // true if the last press of QK_GRAVE_ESCAPE was shifted (i.e. ALT or SHIFT were pressed), false otherwise.
            // Used to ensure that the correct keycode is released if the key is released.
            static bool grave_esc_was_shifted = false;

            if (record->event.pressed) {
                grave_esc_was_shifted = shifted;
                add_key(shifted ? KC_GRAVE : KC_ESCAPE);
            } else {
                del_key(grave_esc_was_shifted ? KC_GRAVE : KC_ESCAPE);
            }

            send_keyboard_report();
            caps_word_off();
            return false; // Skip all further processing of this key
            break;

        // Send media next when encoder is held
        case LT(0, KC_MPLY):
            if (!record->tap.count && record->event.pressed) {
                tap_code(KC_MNXT);
                return false;
            }
            return true; // Return true for normal processing of tap keycode
            break;

        // When toggled, hold down mouse button and tap CTRL every minute to prevent idle
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

// Activate caps lock indicator LED when caps word is active
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (is_caps_word_on()) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_WORD_LED_INDEX_1, 255, 255, 255);
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_WORD_LED_INDEX_2, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_WORD_LED_INDEX_1, 0, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_WORD_LED_INDEX_2, 0, 0, 0);
        }
    }
    return true;
}
