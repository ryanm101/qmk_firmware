/*
 * Debug matrix scanner for KEY12-V02 / CH579M.
 *
 * STRATEGY:
 *   1. Passive read: all candidate pins held INPUT_PULLUP.  Any pin that reads
 *      LOW without driving is an encoder button or direct-to-GND switch.
 *      e.g. the BOOT key (PB22) pulls its pin to GND when pressed.
 *   2. Active scan: drive each candidate LOW one at a time, read all others.
 *      Any that reads LOW while driven = matrix key connection.
 *
 * In both cases the detected pin index is printed via uprintf so you can see
 * which GPIO corresponds to which physical key (run `qmk console` on host).
 *
 * CANDIDATES (B0-B9, B12-B23, A0-A5 = 28 pins):
 *   idx  0=B0   1=B1   2=B2   3=B3   4=B4   5=B5   6=B6   7=B7
 *   idx  8=B8   9=B9  10=B12 11=B13 12=B14 13=B15 14=B16 15=B17
 *   idx 16=B18 17=B19 18=B20 19=B21 20=B22 21=B23
 *   idx 22=A0  23=A1  24=A2  25=A3  26=A4  27=A5
 *
 * B10/B11 excluded (USB D-/D+).
 *
 * keyboard.json must have MATRIX_ROWS=1, MATRIX_COLS=28.
 */

#include "quantum.h"

static const pin_t CANDIDATES[] = {
    B0,  B1,  B2,  B3,  B4,  B5,  B6,  B7,
    B8,  B9,  B12, B13, B14, B15, B16, B17,
    B18, B19, B20, B21, B22, B23,
    A0,  A1,  A2,  A3,  A4,  A5,
};
#define N_CAND ((uint8_t)(sizeof(CANDIDATES) / sizeof(CANDIDATES[0])))

_Static_assert(N_CAND == MATRIX_COLS, "MATRIX_COLS must equal N_CAND");

static matrix_row_t raw_matrix[MATRIX_ROWS];

/* Pin name helpers for uprintf */
static inline char port_char(pin_t pin) {
    return (PAL_PORT(pin) == GPIOA) ? 'A' : 'B';
}

void matrix_init(void) {
    for (uint8_t i = 0; i < N_CAND; i++) {
        setPinInputHigh(CANDIDATES[i]);
    }
    memset(raw_matrix, 0, sizeof(raw_matrix));
}

uint8_t matrix_scan(void) {
    matrix_row_t row0 = 0;

    /* ── Phase 1: passive read (encoder buttons, direct-to-GND) ─── */
    for (uint8_t c = 0; c < N_CAND; c++) {
        if (!readPin(CANDIDATES[c])) {
            row0 |= (matrix_row_t)(1u << c);
            uprintf("PASSIVE LOW: P%c%u (idx %u)\n",
                    port_char(CANDIDATES[c]),
                    (unsigned)PAL_PAD(CANDIDATES[c]),
                    (unsigned)c);
        }
    }

    /* ── Phase 2: active scan (matrix keys via row drive) ───────── */
    for (uint8_t r = 0; r < N_CAND; r++) {
        setPinOutput(CANDIDATES[r]);
        writePinLow(CANDIDATES[r]);
        wait_us(10);

        for (uint8_t c = 0; c < N_CAND; c++) {
            if (c == r) continue;
            if (!readPin(CANDIDATES[c])) {
                uprintf("ACTIVE P%c%u->P%c%u (r=%u c=%u)\n",
                        port_char(CANDIDATES[r]),
                        (unsigned)PAL_PAD(CANDIDATES[r]),
                        port_char(CANDIDATES[c]),
                        (unsigned)PAL_PAD(CANDIDATES[c]),
                        (unsigned)r, (unsigned)c);
                /* Fire the drive-pin's column so each drive pin = unique key */
                row0 |= (matrix_row_t)(1u << r);
            }
        }

        setPinInputHigh(CANDIDATES[r]);
    }

    uint8_t changed = (row0 != raw_matrix[0]);
    raw_matrix[0]   = row0;
    return changed;
}

matrix_row_t matrix_get_row(uint8_t row) {
    return raw_matrix[row];
}

void matrix_print(void) {}
