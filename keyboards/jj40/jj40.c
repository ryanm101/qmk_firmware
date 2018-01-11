#include "jj40.h"

#include <avr/pgmspace.h>

#include "action_layer.h"
#include "quantum.h"

#include "i2c.h"

// custom RGB driver
extern rgblight_config_t rgblight_config;
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

__attribute__ ((weak))
void matrix_scan_user(void) {
    // if LEDs were previously on before poweroff, turn them back on
    if (rgb_init == false && rgblight_config.enable) {
      i2c_init();
      i2c_send(0xb0, (uint8_t*)led, 3 * RGBLED_NUM);
      rgb_init = true;
    }

    rgblight_task();
    /* Nothing else for now. */
}
