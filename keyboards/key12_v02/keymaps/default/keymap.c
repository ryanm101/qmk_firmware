#include QMK_KEYBOARD_H

/*
 * idx→pin→key:
 *  0=B0→A   1=B1→B   2=B2→C   3=B3→D   4=B4→E   5=B5→F   6=B6→G
 *  7=B7→H   8=B8→I   9=B9→J  10=B12→K 11=B13→L 12=B14→M 13=B15→N
 * 14=B16→O 15=B17→P 16=B18→Q 17=B19→R 18=B20→S 19=B21→T
 * 20=B22→U 21=B23→V
 * 22=A0→W  23=A1→X  24=A2→Y  25=A3→Z  26=A4→1  27=A5→2
 *
 * PB22 (idx 20) is the BOOT key → should type 'u' when pressed.
 * Also check qmk console for PASSIVE/ACTIVE pin messages.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G,
        KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N,
        KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T,
        KC_U, KC_V,
        KC_W, KC_X, KC_Y, KC_Z, KC_1, KC_2
    )
};
