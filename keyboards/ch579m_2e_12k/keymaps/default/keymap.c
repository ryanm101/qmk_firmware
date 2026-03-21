#include QMK_KEYBOARD_H

/*
 * Physical layout:
 *
 *         Col 0        Col 1        Col 2
 *  Enc  KC_A / B2     —         KC_B / A6
 *  r0   KC_C / B19  KC_D / B21  KC_E / A15
 *  r1   KC_F / B20  KC_G / A12  KC_H / A3
 *  r2   KC_I / B22  KC_J / A13  KC_K / A2
 *  r3   KC_L / B15  KC_M / A14  KC_N / A1
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A,
        KC_C,  KC_D,
        KC_F,
        KC_I,
        KC_N,
        KC_K,
        KC_L,
        KC_J,  KC_M,
        KC_B,
        KC_G,
        KC_E,  KC_H
    )
};

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
    tap_code(clockwise ? KC_VOLU : KC_VOLD);
    return true;
}
