#include QMK_KEYBOARD_H

#include "keymap_us_international.h"
#include "sendstring_us_international.h"

#include "oneshot.h"

#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)
#define LA_FUN MO(FUN)

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
    FUN,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_LSFT = SAFE_RANGE,
    OS_LCTL,
    OS_LALT,
    OS_LGUI,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MENU,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                            LA_FUN,  LA_NAV,  KC_BSPC,          KC_SPC,  LA_SYM,  XXXXXXX
    ),
    [SYM] = LAYOUT_split_3x6_3(
        _______, KC_TAB,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,                            KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,  _______,
        _______, KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,                             KC_HASH, OS_LCTL, OS_LSFT, OS_LALT, OS_LGUI, _______,
        _______, KC_PLUS, KC_PIPE, KC_AT,   KC_BSLS, KC_PERC,                            XXXXXXX, KC_AMPR, KC_SCLN, KC_COLN, KC_EXLM, _______,
                                            XXXXXXX, _______, KC_DEL,           _______, _______, XXXXXXX
    ),
    [NAV] = LAYOUT_split_3x6_3(
        _______, KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,                            KC_PSCR, US_ARNG, US_ADIA, US_ODIA, XXXXXXX, _______,
        _______, OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, KC_VOLD,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, CW_TOGG, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY,                            KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, _______,
                                            XXXXXXX, _______, _______,          KC_ENT,  _______, XXXXXXX
    ),
    [NUM] = LAYOUT_split_3x6_3(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, KC_F11,                             KC_F12,  OS_LCTL, OS_LSFT, OS_LALT, OS_LGUI, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
                                            XXXXXXX, _______, KC_DEL,           KC_ENT,  _______, XXXXXXX
    ),
    [FUN] = LAYOUT_split_3x6_3(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, KC_BTN4, KC_MS_U, KC_BTN5, XXXXXXX, _______,
        _______, OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, XXXXXXX,                            XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, _______,
                                            XXXXXXX, _______, _______,          KC_BTN1, KC_BTN2, KC_BTN3
    )
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
        case LA_FUN:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
        case LA_FUN:
        case KC_LSFT:
        case OS_LSFT:
        case OS_LCTL:
        case OS_LALT:
        case OS_LGUI:
            return true;
        default:
            return false;
    }
}

oneshot_state os_shift_state = os_up_unqueued;
oneshot_state os_control_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_super_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shift_state, KC_LSFT, OS_LSFT,
        keycode, record
    );
    update_oneshot(
        &os_control_state, KC_LCTL, OS_LCTL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_LALT,
        keycode, record
    );
    update_oneshot(
        &os_super_state, KC_LGUI, OS_LGUI,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
