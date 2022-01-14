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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_65_ansi( /* Base */
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,   KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,            KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,\
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,            KC_LBRC, KC_RBRC, KC_BSLS, KC_END,\
    MO(1),   KC_A,    KC_S,    KC_D,    KC_F,   KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    RALT_T(KC_SCLN), RGUI_T(KC_QUOT),  KC_ENT,  KC_PGUP,\
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,         KC_RSFT,          KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                KC_SPC,                                KC_RALT, MO(2),           KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[1] = LAYOUT_65_ansi( /* Missing keys, Media keys, Extra arrow keys */
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,\
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR,\
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_MNXT, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,          KC_TRNS, KC_SLCK,\
    KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_PAUS,\
    KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

[2] = LAYOUT_65_ansi( /* LED control, RESET, Caps lock */
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EF_DEC,  EF_INC,  KC_TRNS, KC_TRNS,\
    KC_TRNS, H2_DEC,  H2_INC,  S2_DEC,  S2_INC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   KC_TRNS,\
    KC_CAPS, H1_DEC,  H1_INC,  S1_DEC,  S1_INC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,\
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          BR_INC,  KC_TRNS,\
    KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS, ES_DEC,  BR_DEC,  ES_INC),
};

void matrix_init_user(void) {
  //user initialization
}

void matrix_scan_user(void) {
  //user matrix
}

/* true if the last press of GRAVE_ESC was shifted (i.e. GUI or SHIFT were pressed), false otherwise.
 * Used to ensure that the correct keycode is released if the key is released.
 *
 * See quantum/process_keycode/process_grave_esc.c
 */
static bool grave_esc_was_shifted = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // See quantum/process_keycode/process_grave_esc.c
    if (keycode == GRAVE_ESC) {
        const uint8_t mods    = get_mods();
        // add Alt to accommodate physical Windows-style keyboard layout (Ctrl, GUI, Alt)
        // with GUI and Alt swapped in macOS
        uint8_t       shifted = mods & MOD_MASK_SAG;

#ifdef GRAVE_ESC_ALT_OVERRIDE
        // if ALT is pressed, ESC is always sent
        // this is handy for the cmd+opt+esc shortcut on macOS, among other things.
        if (mods & MOD_MASK_ALT) {
            shifted = 0;
        }
#endif

#ifdef GRAVE_ESC_CTRL_OVERRIDE
        // if CTRL is pressed, ESC is always sent
        // this is handy for the ctrl+shift+esc shortcut on windows, among other things.
        if (mods & MOD_MASK_CTRL) {
            shifted = 0;
        }
#endif

#ifdef GRAVE_ESC_GUI_OVERRIDE
        // if GUI is pressed, ESC is always sent
        if (mods & MOD_MASK_GUI) {
            shifted = 0;
        }
#endif

#ifdef GRAVE_ESC_SHIFT_OVERRIDE
        // if SHIFT is pressed, ESC is always sent
        if (mods & MOD_MASK_SHIFT) {
            shifted = 0;
        }
#endif

        if (record->event.pressed) {
            grave_esc_was_shifted = shifted;
            add_key(shifted ? KC_GRAVE : KC_ESCAPE);
        } else {
            del_key(grave_esc_was_shifted ? KC_GRAVE : KC_ESCAPE);
        }

        send_keyboard_report();
        return false;
    }

    // Not a grave keycode so continue processing
    return true;
}
