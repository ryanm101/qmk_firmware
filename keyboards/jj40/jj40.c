/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2018 by Kenneth <github.com/krusli>

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

#include "jj40.h"

#include <avr/pgmspace.h>

#include "action_layer.h"
#include "quantum.h"

#include "i2c.h"

// for keyboard subdirectory level init functions
void matrix_init_kb(void) {
  // call user level keymaps
  matrix_init_user();
}

#include "backlight.h"

extern rgblight_config_t rgblight_config;

// custom RGB driver
void rgblight_set(void) {
  if (!rgblight_config.enable) {
    for (uint8_t i=0; i<RGBLED_NUM; i++) {
      led[i].r = 0;
      led[i].g = 0;
      led[i].b = 0;
    }
  }

  i2c_init();
  i2c_send(0xb0, (uint8_t*)led, 3 * RGBLED_NUM);
}

bool rgb_init = false;

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_NUM_LOCK)) {
        DDRD &= ~(1 << 0); PORTD &= ~(1 << 0);
    } else {
        DDRD |= (1 << 0); PORTD |= (1 << 0);
    }

    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        DDRD &= ~(1 << 4); PORTD &= ~(1 << 4); // originally (1 << 1), port/pin D1
    } else {
        DDRD |= (1 << 4); PORTD |= (1 << 4);
    }

    if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
        DDRD &= ~(1 << 6); PORTD &= ~(1 << 6);
    } else {
        DDRD |= (1 << 6); PORTD |= (1 << 6);
    }
}

__attribute__ ((weak))
void matrix_scan_user(void) {
    // if LEDs were previously on before poweroff, turn them back on
    if (rgb_init == false && rgblight_config.enable) {
      i2c_init();
      i2c_send(0xb0, (uint8_t*)led, 3 * RGBLED_NUM);
      rgb_init = true;
    }

    // activate backlighting pin?
    // if (backlight_config.enable == 1) { // turn on
      DDRD &= ~(1 << 4); PORTD &= ~(1 << 4);
    // } else {  // turn off
      // DDRD |= (1 << 4); PORTD |= (1 << 4);
    // }

    rgblight_task();
    /* Nothing else for now. */
}
