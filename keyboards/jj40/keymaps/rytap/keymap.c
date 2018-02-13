#include "jj40.h"
#include "action_layer.h"

#define _______ KC_TRNS
#define _QWERTY 0
#define _L1  1
#define _L2  2
#define _L3  3

// Custom Key Combos
#define KC_CAD LALT(LCTL(KC_DEL))

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  L1,
  L2,
  L3
};



//Tap Dance Declarations
#define COLON TD(CLN)
#define PARAN TD(PAR)
#define CURLY TD(CUR)
#define SQUAR TD(SQU)
#define ANGUL TD(ANG)

enum {
  CLN = 0,
  PAR,
  CUR,
  SQU,
  ANG,
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
   KC_ESC,    KC_A, KC_S,               KC_D,       KC_F,  KC_G,    KC_H,       KC_J,    KC_K,    KC_L,       COLON,  KC_QUOT, \
  KC_LSFT,    KC_Z, KC_X,               KC_C,       KC_V,  KC_B,    KC_N,       KC_M, KC_COMM,  KC_DOT,     KC_SLSH,   KC_ENT, \
  KC_LCTL, KC_LGUI, KC_LALT, KC_NONUS_BSLASH,    MO(_L1),     KC_SPC    ,    MO(_L2), KC_LEFT, KC_DOWN,       KC_UP,  KC_RGHT \
),

/* L1
 * ,-----------------------------------------------------------------------------------.
 * |  `¬  |INSERT| PGUP | HOME |  <>  |      |  ()  |  7&  |  8*  |  9(  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |DELETE| PGDN | END  |  []  |  {}  |  =+  |  4$  |  5%  |  6^  |  *   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |LSHIFT|PSCRN |      |C+A+De|  L3  |      |  -_  |  1!  |  2"  |  3£  |  /?  |ENTER |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |  #~  |      |    Space    |      |   0) |  .>  |      | MENU |
 * `-----------------------------------------------------------------------------------'
 */
[_L1] = KEYMAP( \
   KC_GRV,  KC_INSERT,   KC_PGUP,  KC_HOME,   ANGUL, _______,   PARAN,    KC_7,    KC_8,              KC_9, _______, _______, \
  _______,  KC_DELETE, KC_PGDOWN,   KC_END,   SQUAR,   CURLY,  KC_EQL,    KC_4,    KC_5,              KC_6, S(KC_8), _______, \
  KC_LSFT, KC_PSCREEN,   _______,   KC_CAD, MO(_L3), _______, KC_MINS,    KC_1,    KC_2,              KC_3, KC_SLSH,  KC_ENT, \
  KC_LCTL,    KC_LGUI,   KC_LALT,  KC_NUHS, _______,      KC_SPC     , _______,    KC_0,    ALGR_T(KC_DOT), _______, KC_MENU \
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
      KC_SYSREQ,   KC_F9,  KC_F10,  KC_F11,      KC_F12, _______, KC_NUMLOCK, KC_KP_7, KC_KP_8,   KC_KP_9, KC_KP_ASTERISK,     KC_BSPC, \
        _______,   KC_F5,   KC_F6,   KC_F7,       KC_F8, _______,    _______, KC_KP_4, KC_KP_5,   KC_KP_6,    KC_KP_SLASH,     _______, \
        _______,   KC_F1,   KC_F2,   KC_F3,       KC_F4, _______,    _______, KC_KP_1, KC_KP_2,   KC_KP_3,     KC_KP_PLUS, KC_KP_ENTER, \
        KC_LCTL, KC_LGUI, KC_LALT, _______,     _______,        KC_SPC      , _______, KC_KP_0, KC_KP_DOT,    KC_KP_MINUS,      _______ \
 ),
 

/* L3
 * ,-----------------------------------------------------------------------------------.
 * |RGBTOG|RGBHUI|RGBHUD|RGBSAI|RGBSAD|      |      | PGDN | PGUP |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |BLTOG |BLSTEP|RGBVAI|RGBVAD|RGBMOD|RGBRMD| Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Space    |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
 [_L3] = KEYMAP( \
    RGB_TOG, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  _______, _______,   KC_PGDOWN, KC_PGUP,  _______, _______, _______, \
    BL_TOGG, BL_STEP, RGB_VAI, RGB_VAD, RGB_MOD, RGB_RMOD, KC_LEFT,     KC_DOWN,   KC_UP, KC_RIGHT, _______, _______, \
    _______, _______, _______, _______, _______,  _______, _______,     _______, _______,  _______, _______,  KC_ENT, \
    _______, _______, _______, _______, _______,       KC_SPC     ,     _______, _______,  _______, _______, _______ \
 )
};
/*
 void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
   if (state->count == 1) {
     register_code (KC_RSFT);
     register_code (KC_SCLN);
   } else {
     register_code (KC_SCLN);
   }
 }

 void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
   if (state->count == 1) {
     unregister_code (KC_RSFT);
     unregister_code (KC_SCLN);
   } else {
     unregister_code (KC_SCLN);
   }
 }

 void send_gitcheckout (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING ("git checkout");
    reset_tap_dance (state);
  }
 }
 void send_gitcheckout (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING ("tmux");
    reset_tap_dance (state);
  }
 }
*/

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

 //All tap dance functions would go here. Only showing this one.
 qk_tap_dance_action_t tap_dance_actions[] = {
   [CLN] = ACTION_TAP_DANCE_DOUBLE (KC_SCLN, S(KC_SCLN ))
   ,[PAR] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, paranthesis_dance )
   ,[CUR] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, curly_dance )
   ,[SQU] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, square_dance )
   ,[ANG] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, angular_dance )
  //,[TD_GCO] = ACTION_TAP_DANCE_FN (send_gitcheckout)
  //[CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset)
 };
