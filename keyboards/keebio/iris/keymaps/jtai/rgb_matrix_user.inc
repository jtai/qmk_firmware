RGB_MATRIX_EFFECT(SOLID_COLOR_UNDERGLOW)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool SOLID_COLOR_UNDERGLOW(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        //RGB_MATRIX_TEST_LED_FLAGS();
        if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS



#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#    ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
RGB_MATRIX_EFFECT(SOLID_REACTIVE_SIMPLE_UNDERGLOW)
#        ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool SOLID_REACTIVE_SIMPLE_UNDERGLOW(effect_params_t* params) {
    bool finished = SOLID_REACTIVE_SIMPLE(params);

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    return finished;
}

#        endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#    endif      // ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#endif          // RGB_MATRIX_KEYREACTIVE_ENABLED
