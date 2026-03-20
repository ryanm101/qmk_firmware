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

void usb_lld_set_phase_marker(uint8_t v);

void keyboard_post_init_kb(void) {
    usb_lld_set_phase_marker(0x22);
    keyboard_post_init_user();
}
