#include QMK_KEYBOARD_H

/*
 * Physical layout:
 *
 *         Col 0        Col 1        Col 2
 *  Enc  KC_A / B2     —        KC_B / A6
 *  r0   KC_C / B19  KC_D / B21  KC_E / A15
 *  r1   KC_F / B20  KC_G / A12  KC_H / A3
 *  r2   KC_I / B22  KC_J / A13  KC_K / A2
 *  r3   KC_L / B15  KC_M / A14  KC_N / A1
 *
 * Encoder 1 (left):  B0=phase-A, B1=phase-B, B2=button
 * Encoder 2 (right): A0=phase-A, A5=phase-B, A6=button
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A,          /* idx  0  B2  ENC1 btn */
        KC_C,  KC_D,   /* idx 1,3  B19 r0c0, B21 r0c1 */
        KC_F,          /* idx  2  B20 r1c0 */
        KC_I,          /* idx  4  B22 r2c0 */
        KC_N,          /* idx  5  A1  r3c2 */
        KC_K,          /* idx  6  A2  r2c2 */
        KC_L,          /* idx  7  B15 r3c0 */
        KC_J,  KC_M,   /* idx 8,9  A13 r2c1, A14 r3c1 */
        KC_B,          /* idx 10  A6  ENC2 btn */
        KC_G,          /* idx 11  A12 r1c1 */
        KC_E,  KC_H    /* idx 12,13  A15 r0c2, A3 r1c2 */
    )
};

bool encoder_update_kb(uint8_t index, bool clockwise) {
    uprintf("ENC idx=%u cw=%u\n", index, clockwise);
    if (!encoder_update_user(index, clockwise)) return false;
    if (index == 0) { /* encoder 1: B10(CW) / B11(CCW) */
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
    } else if (index == 1) { /* encoder 2: A0(CW) / A5(CCW) */
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
    }
    return true;
}
