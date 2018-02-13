#include "jj40.h"
#include "action_layer.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define _QWERTY 0
#define _L1  1
#define _L2  2
#define _L3  3

// Custom Key Combos
#define KC_CAD LCTL(LALT(KC_DEL)) // CTL+ALT+DEL (windows)
#define KC_CAE LGUI(LALT(KC_ESC)) // CMD+ALT+ESC (Force Close)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  L1,
  L2,
  L3
};

//Tap Dance Declarations
#define COLON TD(CLN)
#define QUOTE TD(QUOT)
#define PARAN TD(PAR)
#define CURLY TD(CUR)
#define SQUAR TD(SQU)
#define ANGUL TD(ANG)
#define TMUX TD(TD_TMUX)
#define CADCAE TD(CAD_CAE)

enum {
  CLN = 0,
  QUOT,
  CAD_CAE,
  PAR,
  CUR,
  SQU,
  ANG,
  TD_TMUX,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:  |  '@  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |  \|  |  L1  |    Space    |  L2  | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
   KC_TAB,    KC_Q, KC_W,               KC_E,       KC_R,  KC_T,    KC_Y,       KC_U,    KC_I,    KC_O,        KC_P,  KC_BSPC, \
   KC_ESC,    KC_A, KC_S,               KC_D,       KC_F,  KC_G,    KC_H,       KC_J,    KC_K,    KC_L,       COLON,  QUOTE, \
  KC_LSFT,    KC_Z, KC_X,               KC_C,       KC_V,  KC_B,    KC_N,       KC_M, KC_COMM,  KC_DOT,     KC_SLSH,   KC_ENT, \
  KC_LCTL, KC_LGUI, KC_LALT, KC_NONUS_BSLASH,    MO(_L1),     KC_SPC    ,    MO(_L2), KC_LEFT, KC_DOWN,       KC_UP,  KC_RGHT \
),

/* L1
 * ,-----------------------------------------------------------------------------------.
 * |  `¬  |INSERT| PGUP | HOME |  <>  |      |  ()  |  7&  |  8*  |  9(  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |DELETE| PGDN | END  |  []  |  {}  |  =+  |  4$  |  5%  |  6^  |  *   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |LSHIFT|PSCRN |      |CADCAE|  L3  |      |  -_  |  1!  |  2"  |  3£  |  /?  |ENTER |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |  #~  |      |    Space    |      |   0) |  .>  |      | MENU |
 * `-----------------------------------------------------------------------------------'
 */
[_L1] = KEYMAP( \
   KC_GRV,  KC_INSERT,   KC_PGUP,  KC_HOME,   ANGUL, XXXXXXX,   PARAN,    KC_7,  KC_8,           KC_9, XXXXXXX, XXXXXXX, \
  XXXXXXX,  KC_DELETE, KC_PGDOWN,   KC_END,   SQUAR,   CURLY,  KC_EQL,    KC_4,  KC_5,           KC_6, S(KC_8), XXXXXXX, \
  KC_LSFT, KC_PSCREEN,   XXXXXXX,   CADCAE, MO(_L3), XXXXXXX, KC_MINS,    KC_1,  KC_2,           KC_3, KC_SLSH,  KC_ENT, \
  KC_LCTL,    KC_LGUI,   KC_LALT,  KC_NUHS, XXXXXXX,      KC_SPC     , XXXXXXX,  KC_0, ALGR_T(KC_DOT), XXXXXXX, KC_MENU \
),

/* L2
 * ,-----------------------------------------------------------------------------------.
 * |Sysreq|  F9  |  F10 |  F11 |  F12 |      |NUMLK |   7  |   8  |   9  |   *  |Bksp  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      |   4  |   5  |   6  |  /   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |   1  |   2  |   3  |  +   |KP_ENT|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |      |      |    Space    |      |   0  |   .  |  -   |      |
 * `-----------------------------------------------------------------------------------'
 */
 [_L2] = KEYMAP( \
      KC_SYSREQ,   KC_F9,  KC_F10,  KC_F11,      KC_F12, XXXXXXX, KC_NUMLOCK, KC_KP_7, KC_KP_8,   KC_KP_9, KC_KP_ASTERISK,     KC_BSPC, \
        XXXXXXX,   KC_F5,   KC_F6,   KC_F7,       KC_F8, XXXXXXX,    XXXXXXX, KC_KP_4, KC_KP_5,   KC_KP_6,    KC_KP_SLASH,     _______, \
        XXXXXXX,   KC_F1,   KC_F2,   KC_F3,       KC_F4, XXXXXXX,    XXXXXXX, KC_KP_1, KC_KP_2,   KC_KP_3,     KC_KP_PLUS, KC_KP_ENTER, \
        KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX,     XXXXXXX,        KC_SPC      , XXXXXXX, KC_KP_0, KC_KP_DOT,    KC_KP_MINUS,      _______ \
 ),

/* L3
 * ,-----------------------------------------------------------------------------------.
 * |RGBTOG|RGBHUI|RGBHUD|RGBSAI|RGBSAD|      |      | PGDN | PGUP |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |BLTOG |BLSTEP|RGBVAI|RGBVAD|RGBMOD|RGBRMD| Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | TMUX |      |      |      |      |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Space    |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
 [_L3] = KEYMAP( \
    RGB_TOG, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  XXXXXXX, XXXXXXX,   KC_PGDOWN, KC_PGUP,  XXXXXXX, XXXXXXX, XXXXXXX, \
    BL_TOGG, BL_STEP, RGB_VAI, RGB_VAD, RGB_MOD, RGB_RMOD, KC_LEFT,     KC_DOWN,   KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX, \
       TMUX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  KC_ENT, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       KC_SPC     ,     XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX \
 )
};

// Parantheses
void paranthesis_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("()"); register_code(KC_LEFT); unregister_code(KC_LEFT);
  } else if (state->count == 2) {
    SEND_STRING("(");
  } else if (state->count == 3) {
    SEND_STRING(")");
  }
}

void curly_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("{}"); register_code(KC_LEFT); unregister_code(KC_LEFT);
  } else if (state->count == 2) {
    SEND_STRING("{");
  } else if (state->count == 3) {
    SEND_STRING("}");
  }
}

void square_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("[]"); register_code(KC_LEFT); unregister_code(KC_LEFT);
  } else if (state->count == 2) {
    SEND_STRING("[");
  } else if (state->count == 3) {
    SEND_STRING("]");
  }
}

void angular_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("<>"); register_code(KC_LEFT); unregister_code(KC_LEFT);
  } else if (state->count == 2) {
    SEND_STRING("<");
  } else if (state->count == 3) {
    SEND_STRING(">");
  }
}

void tmux_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("tmux"); register_code(KC_ENT); unregister_code(KC_ENT);
  } else if (state->count == 2) {
    register_mods(MOD_BIT(KC_LCTRL));
    register_code(KC_B); unregister_code(KC_B);
    unregister_mods(MOD_BIT(KC_LCTRL));
    register_mods(MOD_BIT(KC_LSHIFT));
    register_code(KC_5); unregister_code(KC_5);
    unregister_mods(MOD_BIT(KC_LSHIFT));
  }
}

 //All tap dance functions would go here. Only showing this one.
 qk_tap_dance_action_t tap_dance_actions[] = {
   [CLN] = ACTION_TAP_DANCE_DOUBLE (KC_SCLN, S(KC_SCLN ))
   ,[QUOT] = ACTION_TAP_DANCE_DOUBLE (KC_QUOT, S(KC_2))
   ,[CAD_CAE] = ACTION_TAP_DANCE_DOUBLE (KC_CAD, KC_CAE)
   ,[PAR] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, paranthesis_dance )
   ,[CUR] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, curly_dance )
   ,[SQU] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, square_dance )
   ,[ANG] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, angular_dance )
   ,[TD_TMUX] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, tmux_dance )
 };
