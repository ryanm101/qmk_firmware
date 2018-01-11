/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified by krusli <github.com/krusli>

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

// NOTE work in progress
#include "backlight.h"
extern backlight_config_t backlight_config;

#include <avr/io.h>
#include <avr/interrupt.h>
// #include <apr/eeprom.h>

#ifndef PWM10
	// mega128 PWM bits
	#define PWM10	WGM10
	#define PWM11	WGM11
#endif

// for keyboard subdirectory level init functions
void matrix_init_kb(void) {
  matrix_init_user(); // for keymap level matrix init functions
  led_init_ports();
}

// Initialise backlighting ports
void led_init_ports(void) {
  DDRD  |= (1 << 4);
  PORTD &= ~(1 << 4);

  /* timer1PWMInit(8) */
  // cbi(TCCR1A,PWM11);
  // sbi(TCCR1A,PWM10);
	// sbi(TCCR1A,COM1B1);
  // cbi(TCCR1A,COM1B0);
  TCCR1A &= ~(_BV(PWM11));
  TCCR1A |= _BV(PWM10);
  TCCR1A |= _BV(COM1B1);
  TCCR1A &= ~(_BV(COM1B0));

	// clear output compare value A
	// outb(OCR1AH, 0);
	// outb(OCR1AL, 0);
  (OCR1AH) = 0;
  (OCR1AL) = 0;
	// clear output compare value B
	// outb(OCR1BH, 0);
	// outb(OCR1BL, 0);
  (OCR1BH) = 0;
  (OCR1BL) = 0;

  // init underglow already done below.
}

#define TIMER_PRESCALE_MASK		0x07	///< Timer Prescaler Bit-Mask
#define TIMER_CLK_DIV64			  0x03	///< Timer clocked at F_CPU/64
#define TIMER1PRESCALE		    TIMER_CLK_DIV64		///< timer 1 prescaler default

#define PWM_MAX 0xFF
/*
 timer0: USB/PS2 interface
 timer1: PWM
*/

#define _ledBrightnessMax 255   // TODO TEST
#define ledBrightnessLimit 10  // TODO

uint16_t getBrightness(uint16_t xValue){
	uint16_t gBri = xValue * _ledBrightnessMax / PWM_MAX;
	if(gBri > ledBrightnessLimit)
	{
		gBri = ledBrightnessLimit;
	}

	return gBri;
}

void setPWM(int xValue){
    // if(_ledOff) return;  // TODO

    // timer1PWMBSet(xValue);
    OCR1B = xValue;
}

// Set the backlight
void backlight_set(uint8_t level) {
  // from timer1Init()
    // from timer1SetPrescaler()
    // outb(TCCR1B, (inb(TCCR1B) & ~TIMER_PRESCALE_MASK) | prescale);
    (TCCR1B) = ((TCCR1B) & ~TIMER_PRESCALE_MASK) | TIMER1PRESCALE;

  // from timer1PWMBOn
    // turn on channel B (OC1B) PWM output
  	// set OC1B as non-inverted PWM
    // sbi(TCCR1A,COM1B1);
  	// cbi(TCCR1A,COM1B0);
    TCCR1A |= _BV(COM1B1);
    TCCR1A &= ~(_BV(COM1B0));

  // from setFullLEDState
  /* http://www.nongnu.org/avr-libc/user-manual/group__avr__sfr.html
  sbi(A, B) is A |= _BV(B) // BV: byte value
  cbi(sfr, bit) is sfr &= ~(_BV(bit))
  */
  // TODO check mode first from EEPROM
  // TODO only max brightness for now

  // setPWM(getBrightness(PWM_MAX));
  setPWM(getBrightness(PWM_MAX));

}

// TODO HACK
// quantum.c backlight_task overridden
void backlight_task(void) {
  // for now, just send command to PWM registers
  PORTD |= (1 << 4);
}

// END NOTE

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
