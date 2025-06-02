/* Copyright 2019 Yiancar
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
#include "drivers/led/issi/is31fl3733.h"
#include "keyboards/wilba_tech/wt_rgb_backlight.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_65_ansi( /* Base */
    QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,\
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,\
    KC_HYPR, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,\
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,\
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[1] = LAYOUT_65_ansi( /* Missing keys, media keys, LED controls, board functions */
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  H1_INC, \
    EF_INC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LT(0, MS_BTN1), LT(0, MS_BTN2), _______, H1_DEC, \
    KC_CAPS, _______, KC_VOLD, KC_VOLU, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______,          _______, S1_INC, \
    MO(3),   _______, _______, _______, _______, _______, NK_TOGG, TG(2),   _______, _______, _______, MO(3),            BR_INC,  S1_DEC, \
    _______, _______, _______,                   _______,                            _______, _______, _______, ES_DEC,  BR_DEC,  ES_INC),

[2] = LAYOUT_65_ansi( /* Restore caps lock/disable hyper */
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
    KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,\
    _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______),

[3] = LAYOUT_65_ansi( /* More LED controls */
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, H2_INC, \
    EF_DEC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, H2_DEC, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, S2_INC, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, S2_DEC, \
    _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______),

[4] = LAYOUT_65_ansi( /* Dummy layer to signal layer state LED */
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,\
    _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______),

[5] = LAYOUT_65_ansi( /* Dummy layer to signal layer state LED */
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,\
    _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______),
};

typedef struct mouse_key_state {
    bool toggled;
    bool hold;
    uint16_t keycode;
    uint32_t delay;
    deferred_token token;
    uint8_t layer;
} mouse_key_state;

static mouse_key_state mouse_key_states[2];

uint32_t mouse_key_indicator_deferred_callback(uint32_t trigger_time, void *cb_arg) {
    mouse_key_state* state = (mouse_key_state*)cb_arg;
    layer_off(state->layer);
    return 0;
}

uint32_t mouse_key_deferred_callback(uint32_t trigger_time, void *cb_arg) {
    mouse_key_state* state = (mouse_key_state*)cb_arg;
    if (!state->hold) {
        layer_on(state->layer);
        defer_exec(25, mouse_key_indicator_deferred_callback, state);
    }
    tap_code(state->keycode);
    return state->delay;
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

        // When toggled, hold down mouse button and tap CTRL every minute to prevent idle
        case LT(0, MS_BTN1):
        case LT(0, MS_BTN2):
             if (record->event.pressed) {
                unsigned char index = keycode - LT(0, MS_BTN1); // Assumes keycodes are adjacent
                mouse_key_state* state = &mouse_key_states[index];

                uint16_t tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
                uint8_t layer = 4 + index;

                state->toggled = !state->toggled;
                if (state->toggled) {
                    if (record->tap.count) {
                        state->hold = false;
                        state->keycode = tap_keycode;
                        state->layer = layer;
                        state->delay = 1000;
                        state->token = defer_exec(1, mouse_key_deferred_callback, state);
                    } else {
                        state->hold = true;
                        state->keycode = KC_LCTL;
                        state->layer = layer; // Not actually used
                        state->delay = 60000;
                        state->token = defer_exec(60000, mouse_key_deferred_callback, state);

                        register_code(tap_keycode);
                        layer_on(layer);
                    }
                } else {
                    cancel_deferred_exec(state->token);

                    if (state->hold) {
                        unregister_code(tap_keycode);
                        layer_off(layer);
                    }
                }
            }
            return false; // Skip all further processing of this key
            break;

        default:
            return true; // Process all other keycodes normally
    }
}

// Activate caps lock indicator LED when caps word is active
void caps_word_set_user(bool active) {
    if (active) {
        is31fl3733_set_color( 7+64-1, 0, 255, 0 );
    } else {
        led_update_ports(host_keyboard_led_state());
    }
}

// Ensure host LED update is aware of caps word
bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        is31fl3733_set_color( 7+64-1, 0, 255, 0 );
    } else {
        if (is_caps_word_on()) {
            is31fl3733_set_color( 7+64-1, 0, 255, 0 );
        } else {
            is31fl3733_set_color( 7+64-1, 0, 0, 0 );
        }
    }

    // prevent kb version from running
    return false;
}

// Activate red LED when a layer >= layer 2 are toggled
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t R = 0;
    uint8_t G = 0;
    uint8_t B = 0;
    if (state & (1UL << 1)) {
        R = 255;
        B = 255;
    }
    if (state >> 2) {
        G = 255;
    }

    is31fl3733_set_color( 6+64-1, R, G, B );
    return state;
}
