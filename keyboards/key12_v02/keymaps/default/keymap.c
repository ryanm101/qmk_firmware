#include QMK_KEYBOARD_H

/*
 * Default keymap — encoders at TOP, encoder 1 on LEFT, encoder 2 on RIGHT.
 *
 * Physical layout (row, col):
 *
 *   [ENC1 press/B2]        [B13?]      <- encoder row
 *   (0,0) R   (0,1) T   [ ?? ]         <- key row 0
 *   (1,0) S   [ ?? ]    [ ?? ]         <- key row 1
 *   (2,0) U   [ ?? ]    (2,2) X        <- key row 2
 *
 * Encoder 1 (left):  B10=phase-A (CW), B11=phase-B (CCW). index=0.
 * Encoder 2 (right): A0=phase-A (CW),  A5=phase-B (CCW).  index=1.
 * B13 and A1: physical position unknown — KC_NO until confirmed.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MUTE, KC_NO,        /* ENC1 press (B2), B13 unknown */
        KC_R,    KC_T,         /* (0,0) R,          (0,1) T    */
        KC_S,                  /* (1,0) S                       */
        KC_U,    KC_NO, KC_X   /* (2,0) U, A1 unknown, (2,2) X */
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
