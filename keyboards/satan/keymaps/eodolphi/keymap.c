#include "satan.h"


// Used for SHIFT_ESC
#define SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define BASE_LAYER 0
#define FUN_LAYER 1
#define VIM_LAYER 1

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BASE_LAYER: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space            |Alt |Gui |FN  |Ctrl |
   * `-----------------------------------------------------------'
   */
[BASE_LAYER] = KEYMAP_ANSI(
  F(0),    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS, \
  MO(VIM_LAYER), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,  \
  OSM(MOD_LSFT), MO(VIM_LAYER),        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,         KC_RSFT, \
  KC_LCTL, KC_LGUI,KC_LALT,                KC_SPC,                                 MO(VIM_LAYER),KC_RALT, KC_RCTL, TG(VIM_LAYER)
  ),
  /* Keymap FUN_LAYER: Function Layer
   * ,-----------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   | RST |   |  | PGDN | PGUP    |
   * |-----------------------------------------------------------|
   * |      | RST |   |   |   |   | RGT | DWN   | UP  | LFT  |    |        |
   * |-----------------------------------------------------------|
   * |        |   | DEL  |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */

[VIM_LAYER] = KEYMAP_ANSI(
  KC_GRV,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,_______,  \
  _______,_______,LALT(KC_RGHT),_______,BL_TOGG,RESET,LGUI(KC_C),LGUI(KC_Z),MO(VIM_LAYER),_______,LGUI(KC_V), _______,KC_PGDN, KC_PGUP, \
  _______,MO(VIM_LAYER),_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,_______,_______,_______, \
  _______,_______,_______,KC_DEL,_______,_______,LALT(KC_LEFT),KC_VOLD,KC_VOLU,KC_MUTE,_______,LGUI(KC_F),_______, _______, \
  _______,_______,_______,                 _______,                       _______,_______,_______),
};


enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&SHIFT_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
};

void matrix_scan_user() {
    uint8_t layer = biton32(layer_state);

    if (layer && !get_backlight_level()) {
        backlight_increase();
        backlight_increase();
        backlight_increase();
    }

    if (!layer && get_backlight_level()) {
        backlight_decrease();

    }
};
