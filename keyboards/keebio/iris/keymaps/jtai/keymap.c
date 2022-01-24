#include QMK_KEYBOARD_H
#include "transactions.h"
#include "features/caps_word.h"

#define _QWERTY 0
#define _NAV 1
#define _FN 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    TG(_NAV),         KC_RALT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, KC_LALT, MO(_FN),                   KC_RGUI, KC_SPC, KC_CAPS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            KC_PGUP, _______, KC_UP,   _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, KC_HOME, _______,          _______, KC_END,  _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_FN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_MINS, KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_VOLU, KC_LCBR, _______,                            KC_PGUP, KC_RCBR, KC_UP,   _______, KC_UNDS, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_VOLD, KC_MPLY, KC_MNXT,                            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_F10,  KC_F11,  KC_F12,  KC_LBRC, KC_HOME, _______,          _______, KC_END,  KC_RBRC, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

enum combos {
    DF_ESC,
    MAGIC_R_RESET,
    MAGIC_E_EEP_RST,
    MAGIC_D_DEBUG,
    MAGIC_N_NK_TOGG,
};

const uint16_t PROGMEM df_combo[]      = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM magic_r_combo[] = {KC_LGUI, KC_CAPS, KC_R, COMBO_END};
const uint16_t PROGMEM magic_e_combo[] = {KC_LGUI, KC_CAPS, KC_E, COMBO_END};
const uint16_t PROGMEM magic_d_combo[] = {KC_LGUI, KC_CAPS, KC_D, COMBO_END};
const uint16_t PROGMEM magic_n_combo[] = {KC_LGUI, KC_CAPS, KC_N, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [DF_ESC]          = COMBO(df_combo,      KC_ESC),
    [MAGIC_R_RESET]   = COMBO(magic_r_combo, RESET),
    [MAGIC_E_EEP_RST] = COMBO(magic_e_combo, EEP_RST),
    [MAGIC_D_DEBUG]   = COMBO(magic_d_combo, DEBUG),
    [MAGIC_N_NK_TOGG] = COMBO(magic_n_combo, NK_TOGG),
};

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        // Home row combo keys are typically pressed within 10ms of each other.
        // Default 50ms COMBO_TERM risks accidental triggering (e.g., vim sequences).
        case DF_ESC:
            return 15;
        default:
            return COMBO_TERM;
    }
}

// true if the last press of GRAVE_ESC was shifted (i.e. ALT or SHIFT were pressed), false otherwise.
// Used to ensure that the correct keycode is released if the key is released.
static bool grave_esc_was_shifted = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Caps word feature, see https://getreuer.info/posts/keyboards/caps-word/index.html
    if (!process_caps_word(keycode, record)) { return false; }

    // Adapted from quantum/process_keycode/process_grave_esc.c, except consider GRAVE_ESC shifted if
    // ALT is pressed (instead of GUI) to accommodate a physical Windows-style keyboard layout (CTRL, GUI, ALT)
    // with GUI and ALT swapped in macOS.
    if (keycode == GRAVE_ESC) {
        const uint8_t mods = get_mods();
        uint8_t shifted = mods & MOD_MASK_SA;

        if (record->event.pressed) {
            grave_esc_was_shifted = shifted;
            add_key(shifted ? KC_GRAVE : KC_ESCAPE);
        } else {
            del_key(grave_esc_was_shifted ? KC_GRAVE : KC_ESCAPE);
        }
        send_keyboard_report();
        return false;
    }

    // Activate LEDs to indicate we're in bootloader mode
    if (keycode == RESET) {
        if (record->event.pressed) {
            rgb_matrix_sethsv_noeeprom(HSV_RED);
        } else {
            // Wait until key is released before entering bootloader mode so that the LEDs have time to update
            // (and sync to the other half)
            reset_keyboard();
        }
        return false;
    }

    return true;
}

typedef union {
    uint8_t raw;
    struct {
        bool caps_word_active : 1;
    };
} custom_state_t;

custom_state_t custom_state;

void custom_state_handler_slave(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    if (in_buflen == sizeof(custom_state)) {
        memcpy(&custom_state, in_data, in_buflen);
    }
}

void custom_state_handler_master(void) {
    static uint8_t last_state = 0;
    static uint32_t last_sync = 0;
    bool needs_sync = false;

    custom_state.caps_word_active = caps_word_get();

    if (memcmp(&custom_state, &last_state, sizeof(custom_state))) {
        needs_sync = true;
        memcpy(&last_state, &custom_state, sizeof(custom_state));
    }

    if (timer_elapsed32(last_sync) > FORCED_SYNC_THROTTLE_MS_USER) {
        needs_sync = true;
    }

    if (needs_sync) {
        if (transaction_rpc_send(PUT_CUSTOM_STATE, sizeof(custom_state), &custom_state)) {
            last_sync = timer_read32();
        }
    }
}

// RGB indicators for caps lock, toggled layers, and caps word
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (layer_state_is(_NAV)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(27, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    }
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(58, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    }
    if (custom_state.caps_word_active) {
        RGB_MATRIX_INDICATOR_SET_COLOR(23, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
        RGB_MATRIX_INDICATOR_SET_COLOR(57, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    }
}

// Must enable RGB matrix for indicators to work
// See https://docs.qmk.fm/#/feature_rgb_matrix?id=indicators-without-rgb-matrix-effect
void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_SOLID_COLOR_UNDERGLOW);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);

    transaction_register_rpc(PUT_CUSTOM_STATE, custom_state_handler_slave);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        custom_state_handler_master();
    }
}
