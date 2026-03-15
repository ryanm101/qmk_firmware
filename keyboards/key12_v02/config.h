#pragma once

/* TODO: verify these by probing PCB traces with a multimeter */

/* CRITICAL: EP0 uses 8-byte packets on CH579M (confirmed from lsusb).
 * FIXED_CONTROL_ENDPOINT_SIZE overrides the QMK/LUFA ChibiOS platform default
 * of 64 — without this override the device descriptor advertises 64-byte EP0
 * which causes host enumeration to fail against the 8-byte hardware buffer. */
#define USB_EP0_SIZE                8
#undef  FIXED_CONTROL_ENDPOINT_SIZE
#define FIXED_CONTROL_ENDPOINT_SIZE 8
