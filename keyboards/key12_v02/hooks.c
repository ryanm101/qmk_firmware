/*
 * Phase-marker hook for CH579M port diagnostics.
 *
 * keyboard_post_init_kb() fires at the end of keyboard_init(), which is the
 * last call before protocol_post_init() and the main loop.  Writing 0x22 into
 * ep1_in_buf[6] here lets us see whether keyboard_init() completed normally.
 *
 * Phase map (byte[6] of EP1 HID stream):
 *   0x00  stuck before protocol_pre_init completed
 *   0x11  protocol_pre_init completed
 *   0x22  keyboard_init completed  ← this hook
 *   0x33  main loop started (first protocol_pre_task call)
 *   0x44  matrix_scan_custom running (byte[7] also changes to 0xDD)
 */
#include "quantum.h"
#include "CH579.h"
#include "encoder.h"

void usb_lld_set_phase_marker(uint8_t v);

void keyboard_post_init_kb(void) {
    usb_lld_set_phase_marker(0x22);
    keyboard_post_init_user();
}

/* encoder_quadrature_handle_read declared in encoder_quadrature.c (no public header) */
extern void encoder_quadrature_handle_read(uint8_t index, uint8_t pin_a_state, uint8_t pin_b_state);

/* Override weak encoder_driver_task — read encoder pins directly from hardware
 * registers to bypass any PAL indirection.
 * enc1 (index 0): B10=phase-A, B11=phase-B
 * enc2 (index 1): A0=phase-A,  A5=phase-B */
void encoder_driver_task(void) {
    uint32_t pb = R32_PB_PIN;
    uint32_t pa = R32_PA_PIN;

    static uint8_t prev_b0 = 0xFF, prev_b1 = 0xFF;
    uint8_t b0 = (uint8_t)((pb >> 0) & 1u);
    uint8_t b1 = (uint8_t)((pb >> 1) & 1u);
    if (b0 != prev_b0 || b1 != prev_b1) {
        uprintf("ENC1_RAW B0=%u B1=%u PB_PU=%08lX PB_DIR=%08lX\n",
                b0, b1,
                (unsigned long)R32_PB_PU,
                (unsigned long)R32_PB_DIR);
        prev_b0 = b0;
        prev_b1 = b1;
    }

    encoder_quadrature_handle_read(0, b0, b1);
    encoder_quadrature_handle_read(1, (uint8_t)((pa >> 0) & 1u), (uint8_t)((pa >> 5) & 1u));
}
