/*
 * KEY12-V02 / CH579M custom matrix — direct-to-GND pins.
 *
 * All pins configured INPUT_PULLUP. Press = pin pulled low = bit set in row.
 *
 * Pin map (col idx → pin → role):
 *   0=B2   encoder 1 press (confirmed)
 *   1=B13  unknown
 *   2=B19  R  — key (row=0, col=0)
 *   3=B20  S  — key (row=1, col=0)
 *   4=B21  T  — key (row=0, col=1)
 *   5=B22  U  — key (row=2, col=0)
 *   6=A1   unknown
 *   7=A2   X  — key (row=2, col=2)
 *
 * Encoder phase pins (NOT in this list — handled by QMK encoder driver):
 *   enc1: B0  (phase-A/left), B1  (phase-B/right)
 *   enc2: A0  (phase-A/CW),   A5  (phase-B/CCW)
 *
 * Physical layout (encoders at top, enc1 left, enc2 right):
 *   col:  0    1    2
 *   enc: [ENC1]    [ENC2]
 *   r=0: [R]  [T]  [??]
 *   r=1: [S]  [??] [??]
 *   r=2: [U]  [??] [X]
 */

#include "quantum.h"

static const pin_t KEY_PINS[] = {
    B2, B13, B19, B20, B21, B22, A1, A2,
};
#define N_KEYS ((uint8_t)(sizeof(KEY_PINS) / sizeof(KEY_PINS[0])))

_Static_assert(N_KEYS == MATRIX_COLS, "MATRIX_COLS must equal N_KEYS (8)");

/* Direct bit positions for fast PIN register reads */
static const uint8_t pb_bit[N_KEYS] = {2, 13, 19, 20, 21, 22, 0xFF, 0xFF};
static const uint8_t pa_bit[N_KEYS] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 1, 2};

void matrix_init_custom(void) {
    for (uint8_t i = 0; i < N_KEYS; i++) {
        palSetPadMode(PAL_PORT(KEY_PINS[i]), PAL_PAD(KEY_PINS[i]),
                      PAL_MODE_INPUT_PULLUP);
    }
    /* Enc1 phase pins — B0 (left/A) and B1 (right/B). Configure pull-ups
     * here so the state is stable before encoder_init reads the initial
     * quadrature position. */
    palSetPadMode(GPIOB, 0, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOB, 1, PAL_MODE_INPUT_PULLUP);
}

/*
 * Eager debounce: register the first edge immediately, then lock out for
 * LOCKOUT_MS so that contact bounce cannot generate spurious events.
 */
#define LOCKOUT_MS 150u

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    /* Diagnostic: watch B0/B1 (enc1 phases) and A0/A5 (enc2 phases) directly */
    {
        static uint32_t prev_enc = 0xFFFFFFFFU;
        uint32_t pb = R32_PB_PIN;
        uint32_t pa = R32_PA_PIN;
        uint32_t enc = ((pb >> 0) & 1U)         /* B0  */
                     | (((pb >> 1) & 1U) << 1)  /* B1  */
                     | (((pa >> 0) & 1U) << 2)  /* A0  */
                     | (((pa >> 5) & 1U) << 3);  /* A5  */
        if (enc != prev_enc) {
            uprintf("ENC_PIN B0=%u B1=%u A0=%u A5=%u\n",
                    (unsigned)(enc & 1), (unsigned)((enc >> 1) & 1),
                    (unsigned)((enc >> 2) & 1), (unsigned)((enc >> 3) & 1));
            prev_enc = enc;
        }
    }
    uint32_t pb_pin = R32_PB_PIN;
    uint32_t pa_pin = R32_PA_PIN;

    matrix_row_t row0 = 0;
    for (uint8_t i = 0; i < N_KEYS; i++) {
        uint32_t bit = (pb_bit[i] != 0xFF)
            ? ((pb_pin >> pb_bit[i]) & 1U)
            : ((pa_pin >> pa_bit[i]) & 1U);
        if (!bit) row0 |= (matrix_row_t)(1u << i);
    }

    static uint32_t      lockout_since  = 0;
    static bool          in_lockout     = false;
    static matrix_row_t  last_committed = 0;
    static uint32_t      scan_count     = 0;

    scan_count++;
    uint32_t now = timer_read32();

    if (current_matrix[0] != last_committed) {
        uprintf("EXT sc=%lu cm=%04X was=%04X row=%04X t=%lu\n",
                (unsigned long)scan_count,
                (unsigned)current_matrix[0],
                (unsigned)last_committed,
                (unsigned)row0,
                (unsigned long)now);
        last_committed = current_matrix[0];
    }

    if (in_lockout) {
        if (now - lockout_since < LOCKOUT_MS) {
            return false;
        }
        in_lockout = false;
        if (row0 != current_matrix[0]) {
            uprintf("LKEXP cm=%04X->%04X t=%lu sc=%lu\n",
                    (unsigned)current_matrix[0], (unsigned)row0,
                    (unsigned long)now, (unsigned long)scan_count);
            current_matrix[0] = row0;
            last_committed     = row0;
            lockout_since      = now;
            in_lockout         = true;
            return true;
        }
        return false;
    }

    if (row0 != current_matrix[0]) {
        uprintf("EDGE cm=%04X->%04X t=%lu sc=%lu\n",
                (unsigned)current_matrix[0], (unsigned)row0,
                (unsigned long)now, (unsigned long)scan_count);
        current_matrix[0] = row0;
        last_committed     = row0;
        lockout_since      = now;
        in_lockout         = true;
        return true;
    }
    return false;
}
