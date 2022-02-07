/*
Copyright 2017 Danny Nguyen <danny@keeb.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// #define USE_I2C
#define EE_HANDS

// sync custom state
#define SPLIT_TRANSACTION_IDS_USER PUT_CUSTOM_STATE
#define FORCED_SYNC_THROTTLE_MS_USER 100

// configure combos
#define COMBO_COUNT 5
#define COMBO_TERM_PER_COMBO

// rgb matrix effects
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_RAINDROPS
#define RGB_MATRIX_KEYPRESSES
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
