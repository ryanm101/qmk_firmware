#include "jj40.h"
#include "action_layer.h"

#define _QWERTY 0
#define _LOWER  1
#define _RAISE  2
#define _NINJA  3

// Custom Key Combos
#define KC_CAD LALT(LCTL(KC_DEL))

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  NINJA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:  |  '"  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |  \|  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
   KC_TAB,    KC_Q, KC_W,               KC_E,       KC_R,      KC_T,    KC_Y,          KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC, \
   KC_ESC,    KC_A, KC_S,               KC_D,       KC_F,      KC_G,    KC_H,          KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
  KC_LSFT,    KC_Z, KC_X,               KC_C,       KC_V,      KC_B,    KC_N,          KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_ENT , \
  KC_LCTL, KC_LGUI, KC_LALT, KC_NONUS_BSLASH, MO(_LOWER),         KC_SPC    ,    TT(_RAISE), KC_LEFT, KC_DOWN,   KC_UP,  KC_RGHT \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  `¬  |INSERT| PGUP | HOME |  ]}  |      |  (   |  7&  |  8*  |  9(  |  )   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |DELETE| PGDN | END  |  [{  |      |  =+  |  4$  |  5%  |  6^  |  *   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |LSHIFT|PSCRN |      |C+A+De| NINJA|      |  -_  |  1!  |  2"  |  3£  |  /?  |ENTER |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |  #~  |      |    Space    |      |   0) |  .>  |      | MENU |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
   KC_GRV,  KC_INSERT,   KC_PGUP,           KC_HOME,    KC_RBRC, _______,  KC_LPRN,    KC_7,    KC_8,              KC_9,   KC_RPRN, _______, \
  _______,  KC_DELETE, KC_PGDOWN,            KC_END,    KC_LBRC, _______,   KC_EQL,    KC_4,    KC_5,              KC_6,   S(KC_8), _______, \
  KC_LSFT, KC_PSCREEN,   _______,            KC_CAD, TT(_NINJA), _______,  KC_MINS,    KC_1,    KC_2,              KC_3,   KC_SLSH,  KC_ENT, \
  KC_LCTL,    KC_LGUI,   KC_LALT,           KC_NUHS,    _______,      KC_SPC      , _______,    KC_0,    ALGR_T(KC_DOT), _______, KC_MENU \
),

/* NINJA
 * ,-----------------------------------------------------------------------------------.
 * |RGBTOG|RGBHUI|RGBHUD|RGBSAI|RGBSAD|      |      | PGDN | PGUP |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |BLTOG |BLSTEP|RGBVAI|RGBVAD|RGBMOD|RGBRMD| Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Space    |(qwrt)|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
 [_NINJA] = KEYMAP( \
    RGB_TOG, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  _______, _______,   KC_PGDOWN, KC_PGUP,  _______, _______, _______, \
    BL_TOGG, BL_STEP, RGB_VAI, RGB_VAD, RGB_MOD, RGB_RMOD, KC_LEFT,     KC_DOWN,   KC_UP, KC_RIGHT, _______, _______, \
    _______, _______, _______, _______, _______,  _______, _______,     _______, _______,  _______, _______,  KC_ENT, \
    _______, _______, _______, _______, _______,       KC_SPC     , TO(_QWERTY), _______,  _______, _______, _______ \
 ),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |Sysreq|  F9  |  F10 |  F11 |  F12 |      |NUMLK |   7  |   8  |   9  |   *  |Bksp  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      |   4  |   5  |   6  |  /   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |   1  |   2  |   3  |  +   |KP_ENT|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |      |(qwrt)|    Space    |      |   0  |   .  |  -   |      |
 * `-----------------------------------------------------------------------------------'
 */
 [_RAISE] = KEYMAP( \
      KC_SYSREQ,   KC_F9,  KC_F10,  KC_F11,      KC_F12, _______, KC_NUMLOCK, KC_KP_7, KC_KP_8,   KC_KP_9, KC_KP_ASTERISK,     KC_BSPC, \
        _______,   KC_F5,   KC_F6,   KC_F7,       KC_F8, _______,    _______, KC_KP_4, KC_KP_5,   KC_KP_6,    KC_KP_SLASH,     _______, \
        _______,   KC_F1,   KC_F2,   KC_F3,       KC_F4, _______,    _______, KC_KP_1, KC_KP_2,   KC_KP_3,     KC_KP_PLUS, KC_KP_ENTER, \
        KC_LCTL, KC_LGUI, KC_LALT, _______, TO(_QWERTY),        KC_SPC      , _______, KC_KP_0, KC_KP_DOT,    KC_KP_MINUS,      _______ \
 )
 };
