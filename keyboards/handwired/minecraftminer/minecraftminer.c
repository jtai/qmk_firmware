#include "minecraftminer.h"

void keyboard_pre_init_kb() {
    gpio_set_pin_output(LED1);
    gpio_write_pin_low(LED1);

    gpio_set_pin_output(LED2);
    gpio_write_pin_low(LED2);

    keyboard_pre_init_user();
}
