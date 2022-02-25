#include QMK_KEYBOARD_H
#include "transactions.h"
#include "features/caps_word.h"

#define _QWERTY 0
#define _FN 1
#define _NAV 2
#define _RGB 3
#define _GAME 4

enum tap_dances {
    TD_LH,
    TD_TG,
    TD_CAPS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    TD(TD_LH),       TD(TD_TG),KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, KC_LALT, MO(_FN),                   MO(_FN), KC_SPC,  TD(TD_CAPS)
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_FN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_MINS, KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_VOLU, _______, _______,                            _______, KC_PGUP, KC_UP,   KC_HOME, KC_UNDS, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_VOLD, KC_MPLY, KC_MNXT,                            _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_LBRC, KC_RBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,          _______, _______, KC_PGDN, _______, KC_END,  _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, KC_PGUP, KC_UP,   KC_HOME, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, KC_PGDN, _______, KC_END,  _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_RGB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, RGB_RMOD,RGB_MOD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, RGB_SAI, _______, _______,                            _______, _______, RGB_VAI, _______, _______, RGB_TOG,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, RGB_HUD, RGB_SAD, RGB_HUI, _______,                            _______, RGB_SPD, RGB_VAD, RGB_SPI, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,  _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_GAME] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_SPC,  _______, _______,                   _______, KC_LGUI, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

enum combos {
    DF_ESC,
    MAGIC_BSPC_RGB_MOD,
    MAGIC_ENT_RGB_TOG,
    MAGIC_R_RESET,
    MAGIC_E_EEP_RST,
    MAGIC_D_DEBUG,
    MAGIC_N_NK_TOGG,
};

const uint16_t PROGMEM df_combo[]         = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM magic_bspc_combo[] = {KC_LGUI, TD(TD_CAPS), KC_BSPC, COMBO_END};
const uint16_t PROGMEM magic_ent_combo[]  = {KC_LGUI, TD(TD_CAPS), KC_ENT, COMBO_END};
const uint16_t PROGMEM magic_r_combo[]    = {KC_LGUI, TD(TD_CAPS), KC_R, COMBO_END};
const uint16_t PROGMEM magic_e_combo[]    = {KC_LGUI, TD(TD_CAPS), KC_E, COMBO_END};
const uint16_t PROGMEM magic_d_combo[]    = {KC_LGUI, TD(TD_CAPS), KC_D, COMBO_END};
const uint16_t PROGMEM magic_n_combo[]    = {KC_LGUI, TD(TD_CAPS), KC_N, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [DF_ESC]             = COMBO(df_combo,         KC_ESC),
    [MAGIC_BSPC_RGB_MOD] = COMBO(magic_bspc_combo, RGB_MOD),
    [MAGIC_ENT_RGB_TOG]  = COMBO(magic_ent_combo,  RGB_TOG),
    [MAGIC_R_RESET]      = COMBO(magic_r_combo,    RESET),
    [MAGIC_E_EEP_RST]    = COMBO(magic_e_combo,    EEP_RST),
    [MAGIC_D_DEBUG]      = COMBO(magic_d_combo,    DEBUG),
    [MAGIC_N_NK_TOGG]    = COMBO(magic_n_combo,    NK_TOGG),
};

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        // Home row combo keys are typically pressed within 10ms of each other.
        // Default 50ms COMBO_TERM risks accidental triggering (e.g., vim sequences).
        case DF_ESC:
            return 25;
        default:
            return COMBO_TERM;
    }
}

void dance_left_hand(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code(KC_SPC);
            break;
        case 2:
            tap_code(KC_DEL);
            break;
    }
}

static bool dance_toggle_layer_hold = false;

void dance_toggle_layer_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            if (state->pressed) {
                dance_toggle_layer_hold = true;
                register_code(KC_LCTL);
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                register_code(KC_LALT);
            } else {
                if (!layer_state_is(_NAV)) {
                    layer_on(_NAV);
                } else {
                    layer_off(_NAV);
                }
            }
            break;
        case 2:
            if (!layer_state_is(_RGB)) {
                layer_on(_RGB);
            } else {
                layer_off(_RGB);
            }
            break;
        case 3:
            if (!layer_state_is(_GAME)) {
                layer_on(_GAME);
                combo_disable();
            } else {
                layer_off(_GAME);
                combo_enable();
            }
            break;
    }
}

void dance_toggle_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (dance_toggle_layer_hold) {
        dance_toggle_layer_hold = false;
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LCTL);
    }
}

void dance_caps(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            caps_word_set(!caps_word_get());
            break;
        case 2:
            tap_code(KC_CAPS);
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LH]   = ACTION_TAP_DANCE_FN(dance_left_hand),
    [TD_TG]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_toggle_layer_finished, dance_toggle_layer_reset),
    [TD_CAPS] = ACTION_TAP_DANCE_FN(dance_caps),
};

// true if the last press of GRAVE_ESC was shifted (i.e. ALT or SHIFT were pressed), false otherwise.
// Used to ensure that the correct keycode is released if the key is released.
static bool grave_esc_was_shifted = false;

static bool rgb_matrix_disabled = false;
static uint8_t rgb_matrix_config_mode = RGB_MATRIX_SOLID_COLOR;
static HSV rgb_matrix_config_hsv = { .h = 0, .s = 0, .v = 0 };

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

    // RGB should always be enabled, otherwise indicators won't work
    // See https://docs.qmk.fm/#/feature_rgb_matrix?id=indicators-without-rgb-matrix-effect
    if (keycode == RGB_TOG) {
        if (!record->event.pressed) {
            if (!rgb_matrix_disabled) {
                // Save current values
                rgb_matrix_config_mode = rgb_matrix_get_mode();
                rgb_matrix_config_hsv = rgb_matrix_get_hsv();

                // Pretend off
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_OFF);

                rgb_matrix_disabled = true;
            } else {
                // Restore original values
                rgb_matrix_mode_noeeprom(rgb_matrix_config_mode);
                rgb_matrix_sethsv_noeeprom(rgb_matrix_config_hsv.h, rgb_matrix_config_hsv.s, rgb_matrix_config_hsv.v);

                rgb_matrix_disabled = false;
            }
        }
        return false;
    }

    // Activate LEDs to indicate we're in bootloader mode
    if (keycode == RESET) {
        if (record->event.pressed) {
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_SOLID_COLOR_UNDERGLOW);
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
        bool nav_layer  : 1;
        bool rgb_layer  : 1;
        bool game_layer : 1;
        bool caps_lock  : 1;
        bool caps_word  : 1;
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

    custom_state.nav_layer = layer_state_is(_NAV);
    custom_state.rgb_layer = layer_state_is(_RGB);
    custom_state.game_layer = layer_state_is(_GAME);
    custom_state.caps_lock = host_keyboard_led_state().caps_lock;
    custom_state.caps_word = caps_word_get();

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

// RGB indicators for nav layer, caps lock, and caps word
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (custom_state.nav_layer) {
        RGB_MATRIX_INDICATOR_SET_COLOR(61, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS); // layer toggle key
    }
    if (custom_state.rgb_layer) {
        RGB_MATRIX_INDICATOR_SET_COLOR(45, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS); // enter key
    }
    if (custom_state.game_layer) {
        RGB_MATRIX_INDICATOR_SET_COLOR(59, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS); // old space key
    }
    if (custom_state.caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(58, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS); // caps key
    }
    if (custom_state.caps_word) {
        RGB_MATRIX_INDICATOR_SET_COLOR(23, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS); // left shift
        RGB_MATRIX_INDICATOR_SET_COLOR(57, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS); // right shift
    }
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(PUT_CUSTOM_STATE, custom_state_handler_slave);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        custom_state_handler_master();
    }
}
