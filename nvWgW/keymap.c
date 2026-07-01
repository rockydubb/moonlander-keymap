#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  HSV_0_245_245,
  HSV_74_255_206,
  HSV_152_255_255,
};



enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_2,
  DANCE_3,
  DANCE_4,
  DANCE_5,
  DANCE_6,
  DANCE_7,
  DANCE_8,
  DANCE_9,
  DANCE_10,
  DANCE_11,
  DANCE_12,
  DANCE_13,
  DANCE_14,
  DANCE_15,
  DANCE_16,
  DANCE_17,
  DANCE_18,
  DANCE_19,
  DANCE_20,
};

#define DUAL_FUNC_0 LT(13, KC_F5)
#define DUAL_FUNC_1 LT(5, KC_5)
#define DUAL_FUNC_2 LT(3, KC_F)
#define DUAL_FUNC_3 LT(12, KC_F18)
#define DUAL_FUNC_4 LT(15, KC_F)
#define DUAL_FUNC_5 LT(11, KC_F7)
#define DUAL_FUNC_6 LT(6, KC_4)
#define DUAL_FUNC_7 LT(14, KC_F22)
#define DUAL_FUNC_8 LT(15, KC_P)
#define DUAL_FUNC_9 LT(13, KC_F24)
#define DUAL_FUNC_10 LT(6, KC_E)
#define DUAL_FUNC_11 LT(4, KC_8)
#define DUAL_FUNC_12 LT(13, KC_H)
#define DUAL_FUNC_13 LT(13, KC_P)
#define DUAL_FUNC_14 LT(6, KC_L)
#define DUAL_FUNC_15 LT(4, KC_N)
#define DUAL_FUNC_16 LT(6, KC_Q)
#define DUAL_FUNC_17 LT(7, KC_H)
#define DUAL_FUNC_18 LT(4, KC_D)
#define DUAL_FUNC_19 LT(7, KC_F10)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    MT(MOD_LALT | MOD_LCTL, KC_ESCAPE),KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_AUDIO_VOL_DOWN,                                KC_AUDIO_VOL_UP,KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           TD(DANCE_2),    
    TD(DANCE_0),    KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           RGB_MODE_FORWARD,                                TG(1),          KC_Y,           KC_U,           KC_I,           KC_O,           DUAL_FUNC_7,    KC_BSPC,        
    ALL_T(KC_CAPS), KC_A,           KC_S,           KC_D,           DUAL_FUNC_0,    KC_G,           LT(3, KC_EQUAL),                                                                DUAL_FUNC_8,    KC_H,           KC_J,           KC_K,           KC_L,           LT(2, KC_SCLN), MT(MOD_RSFT, KC_ENTER),
    KC_LEFT_SHIFT,  DUAL_FUNC_1,    DUAL_FUNC_2,    DUAL_FUNC_3,    DUAL_FUNC_4,    KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         LT(3, KC_SLASH),KC_RIGHT_SHIFT, 
    TD(DANCE_1),    OSL(4),         OSL(3),         KC_LEFT,        KC_RIGHT,       DUAL_FUNC_5,                                                                                                    DUAL_FUNC_9,    KC_UP,          KC_DOWN,        KC_LBRC,        KC_RBRC,        KC_RIGHT_CTRL,  
    KC_LEFT_GUI,    KC_LEFT_ALT,    DUAL_FUNC_6,                    KC_HYPR,        KC_TAB,         MT(MOD_LALT, KC_SPACE)
  ),
  [1] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         
    KC_TAB,         KC_EXLM,        KC_AT,          KC_LCBR,        KC_RCBR,        KC_PIPE,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_UP,          KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_MINUS,    KC_F12,         
    KC_TRANSPARENT, KC_HASH,        KC_DLR,         KC_LPRN,        KC_RPRN,        KC_GRAVE,       KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_DOWN,        KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_PLUS,     KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_CIRC,        KC_LBRC,        KC_RBRC,        KC_TILD,                                        KC_MEH,         KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_SLASH,    KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_COMMA,       HSV_0_245_245,  HSV_74_255_206, HSV_152_255_255,RGB_MODE_FORWARD,                                                                                                RGB_TOG,        KC_KP_DOT,      KC_KP_0,        KC_EQUAL,       KC_KP_ASTERISK, KC_KP_ENTER,    
    RGB_VAD,        RGB_VAI,        KC_TRANSPARENT,                 KC_TRANSPARENT, RGB_HUD,        RGB_HUI
  ),
  [2] = LAYOUT_moonlander(
    AU_TOGG,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,        
    KC_TRANSPARENT, LGUI(LCTL(KC_LEFT_SHIFT)),KC_MS_BTN1,     KC_MS_UP,       KC_MS_BTN2,     KC_TRANSPARENT, KC_TRANSPARENT,                                 TO(1),          KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_UP,       KC_MS_BTN2,     KC_TRANSPARENT, KC_TRANSPARENT, 
    MU_NEXT,        KC_MEH,         KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, TD(DANCE_3),    TD(DANCE_4),    TD(DANCE_5),    TD(DANCE_6),    KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE,
    KC_TRANSPARENT, KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_MS_WH_UP,    KC_MS_WH_RIGHT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_MS_WH_LEFT,  KC_MS_WH_UP,    KC_MS_WH_DOWN,  KC_MS_WH_RIGHT, KC_MEDIA_PREV_TRACK,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_BTN2,     KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, TD(DANCE_7),    TD(DANCE_8),    KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_MEDIA_NEXT_TRACK,
    DUAL_FUNC_10,   DUAL_FUNC_11,   KC_TRANSPARENT,                 KC_TRANSPARENT, KC_WWW_BACK,    KC_WWW_FORWARD
  ),
  [3] = LAYOUT_moonlander(
    KC_NO,          RALT(RCTL(RSFT(KC_KP_1))),RALT(RCTL(RSFT(KC_KP_2))),DUAL_FUNC_12,   RALT(RCTL(RSFT(KC_KP_4))),KC_NO,          KC_NO,                                          RALT(RCTL(RSFT(KC_KP_6))),RALT(RCTL(RSFT(KC_KP_6))),RALT(RCTL(RSFT(KC_KP_7))),KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_TRANSPARENT, TD(DANCE_9),    KC_NO,          LGUI(KC_E),     LGUI(LSFT(KC_R)),TD(DANCE_10),   KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          LCTL(KC_I),     KC_NO,          KC_NO,          KC_NO,          
    KC_NO,          DUAL_FUNC_13,   KC_NO,          KC_NO,          LGUI(LSFT(KC_F)),KC_NO,          KC_TRANSPARENT,                                                                 KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT, KC_NO,          
    KC_NO,          KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                                                          LGUI(LSFT(KC_R)),KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    LGUI(LSFT(KC_LBRC)),KC_NO,          RGUI(RSFT(KC_RBRC)),                KC_NO,          LGUI(KC_LBRC),  RGUI(KC_RBRC)
  ),
  [4] = LAYOUT_moonlander(
    KC_TRANSPARENT, TD(DANCE_11),   TD(DANCE_12),   TD(DANCE_13),   TD(DANCE_14),   TD(DANCE_15),   KC_TRANSPARENT,                                 KC_TRANSPARENT, TD(DANCE_16),   TD(DANCE_17),   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LGUI(LSFT(KC_B)),
    LALT(KC_GRAVE), KC_TRANSPARENT, LGUI(LCTL(KC_W)),KC_F,           LALT(LSFT(KC_R)),LALT(LSFT(KC_T)),KC_TRANSPARENT,                                 TD(DANCE_18),   LALT(LSFT(KC_H)),LALT(LSFT(KC_J)),LALT(LSFT(KC_K)),LALT(LSFT(KC_L)),KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, LGUI(LCTL(KC_A)),LGUI(LCTL(KC_S)),LGUI(LCTL(KC_D)),LGUI(LSFT(KC_F)),KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, LALT(KC_H),     DUAL_FUNC_17,   DUAL_FUNC_18,   LALT(KC_L),     KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, LGUI(LCTL(KC_Z)),DUAL_FUNC_14,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 LALT(LGUI(KC_H)),DUAL_FUNC_19,   LALT(LGUI(KC_K)),LALT(LGUI(KC_L)),LALT(LSFT(KC_M)),KC_LEFT_GUI,    
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, DUAL_FUNC_15,   DUAL_FUNC_16,   LGUI(KC_9),                                                                                                     LGUI(LSFT(KC_R)),TD(DANCE_19),   TD(DANCE_20),   LALT(KC_COMMA), LALT(KC_DOT),   LALT(KC_SLASH), 
    LGUI(LSFT(KC_LBRC)),LGUI(LSFT(KC_RBRC)),KC_TRANSPARENT,                 KC_TRANSPARENT, LGUI(KC_LBRC),  LGUI(KC_RBRC)
  ),
};





extern rgb_config_t rgb_matrix_config;

RGB hsv_to_rgb_with_value(HSV hsv) {
  RGB rgb = hsv_to_rgb( hsv );
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  return (RGB){ f * rgb.r, f * rgb.g, f * rgb.b };
}

void keyboard_post_init_user(void) {
  // Force RGB animation on layer 0, bypassing the Oryx ledmap[] static
  // colors. The Oryx keymap sets up a static color override for each
  // layer, which clobbers any QMK animation effect on every matrix scan.
  // By disabling layer-LED overrides and forcing a specific animation
  // mode at boot, the user can use the "Switch ANI" / "Animation" key
  // (RGB_MODE_FORWARD) to cycle through QMK animation effects.
  // This snippet is re-applied by patches/apply_patches.py after Oryx syncs.
  keyboard_config.disable_layer_led = true;
  eeconfig_update_kb(keyboard_config.raw);
  rgb_matrix_enable_noeeprom();
  rgb_matrix_mode_noeeprom(6);  // CYCLE_LEFT_RIGHT (rainbow sweep)
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {41,255,255}, {41,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {0,245,245}, {41,255,255}, {41,255,255}, {152,255,255}, {41,255,255}, {0,245,245}, {41,255,255}, {41,255,255}, {152,255,255}, {41,255,255}, {0,245,245}, {41,255,255}, {41,255,255}, {152,255,255}, {41,255,255}, {0,245,245}, {41,255,255}, {41,255,255}, {152,255,255}, {41,255,255}, {0,245,245}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {188,255,255}, {74,255,206}, {74,255,206}, {0,245,245}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {0,245,245}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,245,245}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,245,245}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,245,245}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,245,245}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {188,255,255}, {188,255,255} },

    [1] = { {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {188,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,245,245}, {188,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {188,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,245,245}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255} },

    [2] = { {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {41,255,255}, {188,255,255}, {41,255,255}, {0,245,245}, {0,245,245}, {188,255,255}, {188,255,255}, {0,245,245}, {0,245,245}, {0,245,245}, {41,255,255}, {188,255,255}, {41,255,255}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb_with_value(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (!keyboard_config.disable_layer_led) { 
    switch (biton32(layer_state)) {
      case 0:
        set_layer_color(0);
        break;
      case 1:
        set_layer_color(1);
        break;
      case 2:
        set_layer_color(2);
        break;
     default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
          rgb_matrix_set_color_all(0, 0, 0);
        }
    }
  } else {
    if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
      rgb_matrix_set_color_all(0, 0, 0);
    }
  }

  return true;
}


typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,      
    SINGLE_HOLD,         
    DOUBLE_TAP,          
    DOUBLE_HOLD,         
    DOUBLE_SINGLE_TAP,   
    MORE_TAPS            
};

static tap dance_state[21];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_GRAVE);
        tap_code16(KC_GRAVE);
        tap_code16(KC_GRAVE);
    }
    if(state->count > 3) {
        tap_code16(KC_GRAVE);
    }
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_GRAVE); break;
        case DOUBLE_TAP: register_code16(KC_TILD); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_GRAVE); register_code16(KC_GRAVE);
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_GRAVE); break;
        case DOUBLE_TAP: unregister_code16(KC_TILD); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_GRAVE); break;
    }
    dance_state[0].step = 0;
}
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_HOLD: register_code16(KC_LEFT_CTRL); break;
        case DOUBLE_HOLD: register_code16(KC_LEFT_GUI); break;
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_HOLD: unregister_code16(KC_LEFT_CTRL); break;
        case DOUBLE_HOLD: unregister_code16(KC_LEFT_GUI); break;
    }
    dance_state[1].step = 0;
}
void on_dance_2(tap_dance_state_t *state, void *user_data);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_MINUS);
        tap_code16(KC_MINUS);
        tap_code16(KC_MINUS);
    }
    if(state->count > 3) {
        tap_code16(KC_MINUS);
    }
}

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_TAP: register_code16(KC_MINUS); break;
        case SINGLE_HOLD: register_code16(KC_PLUS); break;
        case DOUBLE_TAP: register_code16(KC_EQUAL); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_MINUS); register_code16(KC_MINUS);
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_TAP: unregister_code16(KC_MINUS); break;
        case SINGLE_HOLD: unregister_code16(KC_PLUS); break;
        case DOUBLE_TAP: unregister_code16(KC_EQUAL); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_MINUS); break;
    }
    dance_state[2].step = 0;
}
void on_dance_3(tap_dance_state_t *state, void *user_data);
void dance_3_finished(tap_dance_state_t *state, void *user_data);
void dance_3_reset(tap_dance_state_t *state, void *user_data);

void on_dance_3(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(RALT(KC_H));
        tap_code16(RALT(KC_H));
        tap_code16(RALT(KC_H));
    }
    if(state->count > 3) {
        tap_code16(RALT(KC_H));
    }
}

void dance_3_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case SINGLE_TAP: register_code16(RALT(KC_H)); break;
        case DOUBLE_TAP: register_code16(RALT(RSFT(KC_H))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(RALT(KC_H)); register_code16(RALT(KC_H));
    }
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
        case SINGLE_TAP: unregister_code16(RALT(KC_H)); break;
        case DOUBLE_TAP: unregister_code16(RALT(RSFT(KC_H))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(RALT(KC_H)); break;
    }
    dance_state[3].step = 0;
}
void on_dance_4(tap_dance_state_t *state, void *user_data);
void dance_4_finished(tap_dance_state_t *state, void *user_data);
void dance_4_reset(tap_dance_state_t *state, void *user_data);

void on_dance_4(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(RALT(KC_J));
        tap_code16(RALT(KC_J));
        tap_code16(RALT(KC_J));
    }
    if(state->count > 3) {
        tap_code16(RALT(KC_J));
    }
}

void dance_4_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[4].step = dance_step(state);
    switch (dance_state[4].step) {
        case SINGLE_TAP: register_code16(RALT(KC_J)); break;
        case DOUBLE_TAP: register_code16(RALT(RSFT(KC_J))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(RALT(KC_J)); register_code16(RALT(KC_J));
    }
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[4].step) {
        case SINGLE_TAP: unregister_code16(RALT(KC_J)); break;
        case DOUBLE_TAP: unregister_code16(RALT(RSFT(KC_J))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(RALT(KC_J)); break;
    }
    dance_state[4].step = 0;
}
void on_dance_5(tap_dance_state_t *state, void *user_data);
void dance_5_finished(tap_dance_state_t *state, void *user_data);
void dance_5_reset(tap_dance_state_t *state, void *user_data);

void on_dance_5(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(RALT(KC_K));
        tap_code16(RALT(KC_K));
        tap_code16(RALT(KC_K));
    }
    if(state->count > 3) {
        tap_code16(RALT(KC_K));
    }
}

void dance_5_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[5].step = dance_step(state);
    switch (dance_state[5].step) {
        case SINGLE_TAP: register_code16(RALT(KC_K)); break;
        case DOUBLE_TAP: register_code16(RALT(RSFT(KC_K))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(RALT(KC_K)); register_code16(RALT(KC_K));
    }
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[5].step) {
        case SINGLE_TAP: unregister_code16(RALT(KC_K)); break;
        case DOUBLE_TAP: unregister_code16(RALT(RSFT(KC_K))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(RALT(KC_K)); break;
    }
    dance_state[5].step = 0;
}
void on_dance_6(tap_dance_state_t *state, void *user_data);
void dance_6_finished(tap_dance_state_t *state, void *user_data);
void dance_6_reset(tap_dance_state_t *state, void *user_data);

void on_dance_6(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(RALT(KC_L));
        tap_code16(RALT(KC_L));
        tap_code16(RALT(KC_L));
    }
    if(state->count > 3) {
        tap_code16(RALT(KC_L));
    }
}

void dance_6_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[6].step = dance_step(state);
    switch (dance_state[6].step) {
        case SINGLE_TAP: register_code16(RALT(KC_L)); break;
        case DOUBLE_TAP: register_code16(RALT(RSFT(KC_L))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(RALT(KC_L)); register_code16(RALT(KC_L));
    }
}

void dance_6_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[6].step) {
        case SINGLE_TAP: unregister_code16(RALT(KC_L)); break;
        case DOUBLE_TAP: unregister_code16(RALT(RSFT(KC_L))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(RALT(KC_L)); break;
    }
    dance_state[6].step = 0;
}
void on_dance_7(tap_dance_state_t *state, void *user_data);
void dance_7_finished(tap_dance_state_t *state, void *user_data);
void dance_7_reset(tap_dance_state_t *state, void *user_data);

void on_dance_7(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_HOME);
        tap_code16(KC_HOME);
        tap_code16(KC_HOME);
    }
    if(state->count > 3) {
        tap_code16(KC_HOME);
    }
}

void dance_7_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[7].step = dance_step(state);
    switch (dance_state[7].step) {
        case SINGLE_TAP: register_code16(KC_HOME); break;
        case DOUBLE_TAP: register_code16(RALT(KC_HOME)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_HOME); register_code16(KC_HOME);
    }
}

void dance_7_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[7].step) {
        case SINGLE_TAP: unregister_code16(KC_HOME); break;
        case DOUBLE_TAP: unregister_code16(RALT(KC_HOME)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_HOME); break;
    }
    dance_state[7].step = 0;
}
void on_dance_8(tap_dance_state_t *state, void *user_data);
void dance_8_finished(tap_dance_state_t *state, void *user_data);
void dance_8_reset(tap_dance_state_t *state, void *user_data);

void on_dance_8(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_END);
        tap_code16(KC_END);
        tap_code16(KC_END);
    }
    if(state->count > 3) {
        tap_code16(KC_END);
    }
}

void dance_8_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[8].step = dance_step(state);
    switch (dance_state[8].step) {
        case SINGLE_TAP: register_code16(KC_END); break;
        case DOUBLE_TAP: register_code16(RALT(KC_END)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_END); register_code16(KC_END);
    }
}

void dance_8_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[8].step) {
        case SINGLE_TAP: unregister_code16(KC_END); break;
        case DOUBLE_TAP: unregister_code16(RALT(KC_END)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_END); break;
    }
    dance_state[8].step = 0;
}
void on_dance_9(tap_dance_state_t *state, void *user_data);
void dance_9_finished(tap_dance_state_t *state, void *user_data);
void dance_9_reset(tap_dance_state_t *state, void *user_data);

void on_dance_9(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LGUI(KC_T));
        tap_code16(LGUI(KC_T));
        tap_code16(LGUI(KC_T));
    }
    if(state->count > 3) {
        tap_code16(LGUI(KC_T));
    }
}

void dance_9_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[9].step = dance_step(state);
    switch (dance_state[9].step) {
        case SINGLE_TAP: register_code16(LGUI(KC_T)); break;
        case DOUBLE_TAP: register_code16(LALT(LGUI(KC_T))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LGUI(KC_T)); register_code16(LGUI(KC_T));
    }
}

void dance_9_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[9].step) {
        case SINGLE_TAP: unregister_code16(LGUI(KC_T)); break;
        case DOUBLE_TAP: unregister_code16(LALT(LGUI(KC_T))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LGUI(KC_T)); break;
    }
    dance_state[9].step = 0;
}
void on_dance_10(tap_dance_state_t *state, void *user_data);
void dance_10_finished(tap_dance_state_t *state, void *user_data);
void dance_10_reset(tap_dance_state_t *state, void *user_data);

void on_dance_10(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LGUI(KC_T));
        tap_code16(LGUI(KC_T));
        tap_code16(LGUI(KC_T));
    }
    if(state->count > 3) {
        tap_code16(LGUI(KC_T));
    }
}

void dance_10_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[10].step = dance_step(state);
    switch (dance_state[10].step) {
        case SINGLE_TAP: register_code16(LGUI(KC_T)); break;
        case DOUBLE_TAP: register_code16(LALT(LGUI(KC_T))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LGUI(KC_T)); register_code16(LGUI(KC_T));
    }
}

void dance_10_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[10].step) {
        case SINGLE_TAP: unregister_code16(LGUI(KC_T)); break;
        case DOUBLE_TAP: unregister_code16(LALT(LGUI(KC_T))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LGUI(KC_T)); break;
    }
    dance_state[10].step = 0;
}
void on_dance_11(tap_dance_state_t *state, void *user_data);
void dance_11_finished(tap_dance_state_t *state, void *user_data);
void dance_11_reset(tap_dance_state_t *state, void *user_data);

void on_dance_11(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LALT(KC_1));
        tap_code16(LALT(KC_1));
        tap_code16(LALT(KC_1));
    }
    if(state->count > 3) {
        tap_code16(LALT(KC_1));
    }
}

void dance_11_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[11].step = dance_step(state);
    switch (dance_state[11].step) {
        case SINGLE_TAP: register_code16(LALT(KC_1)); break;
        case DOUBLE_TAP: register_code16(LALT(LSFT(KC_1))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LALT(KC_1)); register_code16(LALT(KC_1));
    }
}

void dance_11_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[11].step) {
        case SINGLE_TAP: unregister_code16(LALT(KC_1)); break;
        case DOUBLE_TAP: unregister_code16(LALT(LSFT(KC_1))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LALT(KC_1)); break;
    }
    dance_state[11].step = 0;
}
void on_dance_12(tap_dance_state_t *state, void *user_data);
void dance_12_finished(tap_dance_state_t *state, void *user_data);
void dance_12_reset(tap_dance_state_t *state, void *user_data);

void on_dance_12(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LALT(KC_2));
        tap_code16(LALT(KC_2));
        tap_code16(LALT(KC_2));
    }
    if(state->count > 3) {
        tap_code16(LALT(KC_2));
    }
}

void dance_12_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[12].step = dance_step(state);
    switch (dance_state[12].step) {
        case SINGLE_TAP: register_code16(LALT(KC_2)); break;
        case DOUBLE_TAP: register_code16(LALT(LSFT(KC_2))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LALT(KC_2)); register_code16(LALT(KC_2));
    }
}

void dance_12_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[12].step) {
        case SINGLE_TAP: unregister_code16(LALT(KC_2)); break;
        case DOUBLE_TAP: unregister_code16(LALT(LSFT(KC_2))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LALT(KC_2)); break;
    }
    dance_state[12].step = 0;
}
void on_dance_13(tap_dance_state_t *state, void *user_data);
void dance_13_finished(tap_dance_state_t *state, void *user_data);
void dance_13_reset(tap_dance_state_t *state, void *user_data);

void on_dance_13(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LALT(LSFT(KC_3)));
        tap_code16(LALT(LSFT(KC_3)));
        tap_code16(LALT(LSFT(KC_3)));
    }
    if(state->count > 3) {
        tap_code16(LALT(LSFT(KC_3)));
    }
}

void dance_13_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[13].step = dance_step(state);
    switch (dance_state[13].step) {
        case SINGLE_TAP: register_code16(LALT(LSFT(KC_3))); break;
        case DOUBLE_TAP: register_code16(LALT(LSFT(KC_3))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LALT(LSFT(KC_3))); register_code16(LALT(LSFT(KC_3)));
    }
}

void dance_13_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[13].step) {
        case SINGLE_TAP: unregister_code16(LALT(LSFT(KC_3))); break;
        case DOUBLE_TAP: unregister_code16(LALT(LSFT(KC_3))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LALT(LSFT(KC_3))); break;
    }
    dance_state[13].step = 0;
}
void on_dance_14(tap_dance_state_t *state, void *user_data);
void dance_14_finished(tap_dance_state_t *state, void *user_data);
void dance_14_reset(tap_dance_state_t *state, void *user_data);

void on_dance_14(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LALT(KC_4));
        tap_code16(LALT(KC_4));
        tap_code16(LALT(KC_4));
    }
    if(state->count > 3) {
        tap_code16(LALT(KC_4));
    }
}

void dance_14_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[14].step = dance_step(state);
    switch (dance_state[14].step) {
        case SINGLE_TAP: register_code16(LALT(KC_4)); break;
        case DOUBLE_TAP: register_code16(LALT(LSFT(KC_4))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LALT(KC_4)); register_code16(LALT(KC_4));
    }
}

void dance_14_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[14].step) {
        case SINGLE_TAP: unregister_code16(LALT(KC_4)); break;
        case DOUBLE_TAP: unregister_code16(LALT(LSFT(KC_4))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LALT(KC_4)); break;
    }
    dance_state[14].step = 0;
}
void on_dance_15(tap_dance_state_t *state, void *user_data);
void dance_15_finished(tap_dance_state_t *state, void *user_data);
void dance_15_reset(tap_dance_state_t *state, void *user_data);

void on_dance_15(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LALT(KC_5));
        tap_code16(LALT(KC_5));
        tap_code16(LALT(KC_5));
    }
    if(state->count > 3) {
        tap_code16(LALT(KC_5));
    }
}

void dance_15_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[15].step = dance_step(state);
    switch (dance_state[15].step) {
        case SINGLE_TAP: register_code16(LALT(KC_5)); break;
        case DOUBLE_TAP: register_code16(LALT(LSFT(KC_5))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LALT(KC_5)); register_code16(LALT(KC_5));
    }
}

void dance_15_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[15].step) {
        case SINGLE_TAP: unregister_code16(LALT(KC_5)); break;
        case DOUBLE_TAP: unregister_code16(LALT(LSFT(KC_5))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LALT(KC_5)); break;
    }
    dance_state[15].step = 0;
}
void on_dance_16(tap_dance_state_t *state, void *user_data);
void dance_16_finished(tap_dance_state_t *state, void *user_data);
void dance_16_reset(tap_dance_state_t *state, void *user_data);

void on_dance_16(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LALT(KC_6));
        tap_code16(LALT(KC_6));
        tap_code16(LALT(KC_6));
    }
    if(state->count > 3) {
        tap_code16(LALT(KC_6));
    }
}

void dance_16_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[16].step = dance_step(state);
    switch (dance_state[16].step) {
        case SINGLE_TAP: register_code16(LALT(KC_6)); break;
        case DOUBLE_TAP: register_code16(LALT(LSFT(KC_6))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LALT(KC_6)); register_code16(LALT(KC_6));
    }
}

void dance_16_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[16].step) {
        case SINGLE_TAP: unregister_code16(LALT(KC_6)); break;
        case DOUBLE_TAP: unregister_code16(LALT(LSFT(KC_6))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LALT(KC_6)); break;
    }
    dance_state[16].step = 0;
}
void on_dance_17(tap_dance_state_t *state, void *user_data);
void dance_17_finished(tap_dance_state_t *state, void *user_data);
void dance_17_reset(tap_dance_state_t *state, void *user_data);

void on_dance_17(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LALT(KC_7));
        tap_code16(LALT(KC_7));
        tap_code16(LALT(KC_7));
    }
    if(state->count > 3) {
        tap_code16(LALT(KC_7));
    }
}

void dance_17_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[17].step = dance_step(state);
    switch (dance_state[17].step) {
        case SINGLE_TAP: register_code16(LALT(KC_7)); break;
        case DOUBLE_TAP: register_code16(LALT(LSFT(KC_7))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LALT(KC_7)); register_code16(LALT(KC_7));
    }
}

void dance_17_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[17].step) {
        case SINGLE_TAP: unregister_code16(LALT(KC_7)); break;
        case DOUBLE_TAP: unregister_code16(LALT(LSFT(KC_7))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LALT(KC_7)); break;
    }
    dance_state[17].step = 0;
}
void on_dance_18(tap_dance_state_t *state, void *user_data);
void dance_18_finished(tap_dance_state_t *state, void *user_data);
void dance_18_reset(tap_dance_state_t *state, void *user_data);

void on_dance_18(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LALT(KC_S));
        tap_code16(LALT(KC_S));
        tap_code16(LALT(KC_S));
    }
    if(state->count > 3) {
        tap_code16(LALT(KC_S));
    }
}

void dance_18_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[18].step = dance_step(state);
    switch (dance_state[18].step) {
        case SINGLE_TAP: register_code16(LALT(KC_S)); break;
        case DOUBLE_TAP: register_code16(LALT(KC_E)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LALT(KC_S)); register_code16(LALT(KC_S));
    }
}

void dance_18_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[18].step) {
        case SINGLE_TAP: unregister_code16(LALT(KC_S)); break;
        case DOUBLE_TAP: unregister_code16(LALT(KC_E)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LALT(KC_S)); break;
    }
    dance_state[18].step = 0;
}
void on_dance_19(tap_dance_state_t *state, void *user_data);
void dance_19_finished(tap_dance_state_t *state, void *user_data);
void dance_19_reset(tap_dance_state_t *state, void *user_data);

void on_dance_19(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LALT(KC_UP));
        tap_code16(LALT(KC_UP));
        tap_code16(LALT(KC_UP));
    }
    if(state->count > 3) {
        tap_code16(LALT(KC_UP));
    }
}

void dance_19_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[19].step = dance_step(state);
    switch (dance_state[19].step) {
        case SINGLE_TAP: register_code16(LALT(KC_UP)); break;
        case DOUBLE_TAP: register_code16(LALT(LSFT(KC_UP))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LALT(KC_UP)); register_code16(LALT(KC_UP));
    }
}

void dance_19_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[19].step) {
        case SINGLE_TAP: unregister_code16(LALT(KC_UP)); break;
        case DOUBLE_TAP: unregister_code16(LALT(LSFT(KC_UP))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LALT(KC_UP)); break;
    }
    dance_state[19].step = 0;
}
void on_dance_20(tap_dance_state_t *state, void *user_data);
void dance_20_finished(tap_dance_state_t *state, void *user_data);
void dance_20_reset(tap_dance_state_t *state, void *user_data);

void on_dance_20(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LALT(KC_DOWN));
        tap_code16(LALT(KC_DOWN));
        tap_code16(LALT(KC_DOWN));
    }
    if(state->count > 3) {
        tap_code16(LALT(KC_DOWN));
    }
}

void dance_20_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[20].step = dance_step(state);
    switch (dance_state[20].step) {
        case SINGLE_TAP: register_code16(LALT(KC_DOWN)); break;
        case DOUBLE_TAP: register_code16(LALT(LSFT(KC_DOWN))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LALT(KC_DOWN)); register_code16(LALT(KC_DOWN));
    }
}

void dance_20_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[20].step) {
        case SINGLE_TAP: unregister_code16(LALT(KC_DOWN)); break;
        case DOUBLE_TAP: unregister_code16(LALT(LSFT(KC_DOWN))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LALT(KC_DOWN)); break;
    }
    dance_state[20].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
        [DANCE_5] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_5, dance_5_finished, dance_5_reset),
        [DANCE_6] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_6, dance_6_finished, dance_6_reset),
        [DANCE_7] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_7, dance_7_finished, dance_7_reset),
        [DANCE_8] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_8, dance_8_finished, dance_8_reset),
        [DANCE_9] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_9, dance_9_finished, dance_9_reset),
        [DANCE_10] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_10, dance_10_finished, dance_10_reset),
        [DANCE_11] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_11, dance_11_finished, dance_11_reset),
        [DANCE_12] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_12, dance_12_finished, dance_12_reset),
        [DANCE_13] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_13, dance_13_finished, dance_13_reset),
        [DANCE_14] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_14, dance_14_finished, dance_14_reset),
        [DANCE_15] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_15, dance_15_finished, dance_15_reset),
        [DANCE_16] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_16, dance_16_finished, dance_16_reset),
        [DANCE_17] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_17, dance_17_finished, dance_17_reset),
        [DANCE_18] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_18, dance_18_finished, dance_18_reset),
        [DANCE_19] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_19, dance_19_finished, dance_19_reset),
        [DANCE_20] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_20, dance_20_finished, dance_20_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case QK_MODS ... QK_MODS_MAX:
    // Mouse and consumer keys (volume, media) with modifiers work inconsistently across operating systems,
    // this makes sure that modifiers are always applied to the key that was pressed.
    if (IS_MOUSE_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode)) || IS_CONSUMER_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode))) {
      if (record->event.pressed) {
        add_mods(QK_MODS_GET_MODS(keycode));
        send_keyboard_report();
        wait_ms(2);
        register_code(QK_MODS_GET_BASIC_KEYCODE(keycode));
        return false;
      } else {
        wait_ms(2);
        del_mods(QK_MODS_GET_MODS(keycode));
      }
    }
    break;

    case DUAL_FUNC_0:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_F);
        } else {
          unregister_code16(KC_F);
        }
      } else {
        if (record->event.pressed) {
          register_code16(LGUI(KC_F));
        } else {
          unregister_code16(LGUI(KC_F));
        }  
      }  
      return false;
    case DUAL_FUNC_1:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_Z);
        } else {
          unregister_code16(KC_Z);
        }
      } else {
        if (record->event.pressed) {
          register_code16(LGUI(KC_Z));
        } else {
          unregister_code16(LGUI(KC_Z));
        }  
      }  
      return false;
    case DUAL_FUNC_2:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_X);
        } else {
          unregister_code16(KC_X);
        }
      } else {
        if (record->event.pressed) {
          register_code16(LGUI(KC_X));
        } else {
          unregister_code16(LGUI(KC_X));
        }  
      }  
      return false;
    case DUAL_FUNC_3:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_C);
        } else {
          unregister_code16(KC_C);
        }
      } else {
        if (record->event.pressed) {
          register_code16(LGUI(KC_C));
        } else {
          unregister_code16(LGUI(KC_C));
        }  
      }  
      return false;
    case DUAL_FUNC_4:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_V);
        } else {
          unregister_code16(KC_V);
        }
      } else {
        if (record->event.pressed) {
          register_code16(LGUI(KC_V));
        } else {
          unregister_code16(LGUI(KC_V));
        }  
      }  
      return false;
    case DUAL_FUNC_5:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(LGUI(LSFT(KC_G)));
        } else {
          unregister_code16(LGUI(LSFT(KC_G)));
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_CTRL);
        } else {
          unregister_code16(KC_LEFT_CTRL);
        }  
      }  
      return false;
    case DUAL_FUNC_6:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(LGUI(LCTL(KC_0)));
        } else {
          unregister_code16(LGUI(LCTL(KC_0)));
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_CTRL);
        } else {
          unregister_code16(KC_LEFT_CTRL);
        }  
      }  
      return false;
    case DUAL_FUNC_7:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_P);
        } else {
          unregister_code16(KC_P);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_DQUO);
        } else {
          unregister_code16(KC_DQUO);
        }  
      }  
      return false;
    case DUAL_FUNC_8:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          layer_move(2);
        } else {
          layer_move(2);
        }
      } else {
        if (record->event.pressed) {
          layer_on(1);
        } else {
          layer_off(1);
        }  
      }  
      return false;
    case DUAL_FUNC_9:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(LGUI(LCTL(KC_SPACE)));
        } else {
          unregister_code16(LGUI(LCTL(KC_SPACE)));
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_SHIFT);
        } else {
          unregister_code16(KC_LEFT_SHIFT);
        }  
      }  
      return false;
    case DUAL_FUNC_10:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_MS_BTN1);
        } else {
          unregister_code16(KC_MS_BTN1);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_MS_BTN2);
        } else {
          unregister_code16(KC_MS_BTN2);
        }  
      }  
      return false;
    case DUAL_FUNC_11:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_MS_WH_DOWN);
        } else {
          unregister_code16(KC_MS_WH_DOWN);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_MS_WH_UP);
        } else {
          unregister_code16(KC_MS_WH_UP);
        }  
      }  
      return false;
    case DUAL_FUNC_12:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(RALT(RCTL(RSFT(KC_KP_3))));
        } else {
          unregister_code16(RALT(RCTL(RSFT(KC_KP_3))));
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_SHIFT);
        } else {
          unregister_code16(KC_LEFT_SHIFT);
        }  
      }  
      return false;
    case DUAL_FUNC_13:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(LCTL(LSFT(KC_A)));
        } else {
          unregister_code16(LCTL(LSFT(KC_A)));
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_CTRL);
        } else {
          unregister_code16(KC_LEFT_CTRL);
        }  
      }  
      return false;
    case DUAL_FUNC_14:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(LGUI(LCTL(KC_X)));
        } else {
          unregister_code16(LGUI(LCTL(KC_X)));
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_SHIFT);
        } else {
          unregister_code16(KC_LEFT_SHIFT);
        }  
      }  
      return false;
    case DUAL_FUNC_15:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(LALT(KC_PAGE_UP));
        } else {
          unregister_code16(LALT(KC_PAGE_UP));
        }
      } else {
        if (record->event.pressed) {
          register_code16(LALT(LCTL(KC_PAGE_UP)));
        } else {
          unregister_code16(LALT(LCTL(KC_PAGE_UP)));
        }  
      }  
      return false;
    case DUAL_FUNC_16:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(LALT(KC_PGDN));
        } else {
          unregister_code16(LALT(KC_PGDN));
        }
      } else {
        if (record->event.pressed) {
          register_code16(LALT(LCTL(KC_PGDN)));
        } else {
          unregister_code16(LALT(LCTL(KC_PGDN)));
        }  
      }  
      return false;
    case DUAL_FUNC_17:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(LALT(KC_J));
        } else {
          unregister_code16(LALT(KC_J));
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_CTRL);
        } else {
          unregister_code16(KC_LEFT_CTRL);
        }  
      }  
      return false;
    case DUAL_FUNC_18:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(LALT(KC_K));
        } else {
          unregister_code16(LALT(KC_K));
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_CTRL);
        } else {
          unregister_code16(KC_LEFT_CTRL);
        }  
      }  
      return false;
    case DUAL_FUNC_19:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(LALT(LGUI(KC_J)));
        } else {
          unregister_code16(LALT(LGUI(KC_J)));
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_CTRL);
        } else {
          unregister_code16(KC_LEFT_CTRL);
        }  
      }  
      return false;
    case RGB_SLD:
        if (rawhid_state.rgb_control) {
            return false;
        }
        if (record->event.pressed) {
            rgblight_mode(1);
        }
        return false;
    case HSV_0_245_245:
        if (rawhid_state.rgb_control) {
            return false;
        }
        if (record->event.pressed) {
            rgblight_mode(1);
            rgblight_sethsv(0,245,245);
        }
        return false;
    case HSV_74_255_206:
        if (rawhid_state.rgb_control) {
            return false;
        }
        if (record->event.pressed) {
            rgblight_mode(1);
            rgblight_sethsv(74,255,206);
        }
        return false;
    case HSV_152_255_255:
        if (rawhid_state.rgb_control) {
            return false;
        }
        if (record->event.pressed) {
            rgblight_mode(1);
            rgblight_sethsv(152,255,255);
        }
        return false;
  }
  return true;
}

