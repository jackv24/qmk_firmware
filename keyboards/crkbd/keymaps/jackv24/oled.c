// From: https://github.com/drcforbin/keyboards/blob/master/crkbd/keymap.c

#include QMK_KEYBOARD_H
#include "manna-harbour_miryoku.h"

#include "oled.h"

// forwards
bool is_keyboard_left(void);
const char *read_logo(void);
extern const unsigned char font[] PROGMEM;

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void render_layer_state(void) {
    oled_write_P(PSTR("Lay:"), false);
    oled_write_char('\n', false);
    oled_write_char('\n', false);
    switch (layer_state) {
        case BASE:
            oled_write_P(PSTR("BASE "), false);
            break;
        case 1 << BUTTON:
            oled_write_P(PSTR("BTN  "), false);
            break;
        case 1 << MEDIA:
            oled_write_P(PSTR("MEDIA"), false);
            break;
        case 1 << NAV:
            oled_write_P(PSTR("NAV  "), false);
            break;
        case 1 << MOUSE:
            oled_write_P(PSTR("MOUSE"), false);
            break;
        case 1 << SYM:
            oled_write_P(PSTR("SYM  "), false);
            break;
        case 1 << NUM:
            oled_write_P(PSTR("NUM  "), false);
            break;
        case 1 << FUN:
            oled_write_P(PSTR("FUN  "), false);
            break;
        case 1 << G_FPS:
            oled_write_P(PSTR("G_FPS"), false);
            break;
        case 1 << G_2D:
            oled_write_P(PSTR("G_2D "), false);
            break;
        default:
            oled_write_P(PSTR("?????"), false);
            break;
    }
}

void render_mod_status(uint8_t modifiers) {
    //oled_write_P(PSTR("Mods: "), false);
    oled_write_char('S', (modifiers & MOD_MASK_SHIFT));
    oled_write_char('C', (modifiers & MOD_MASK_CTRL));
    oled_write_char('A', (modifiers & MOD_MASK_ALT));
    oled_write_char('G', (modifiers & MOD_MASK_GUI));
    //oled_write_char('\n', false);
}

void render_status_master(void) {
    render_layer_state();
    oled_write_char('\n', false);
    oled_write_char('\n', false);
    oled_write_char('\n', false);

    render_mod_status(get_mods() | get_oneshot_mods());
}

void render_status_slave(void) {
    render_layer_state();
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status_master();
    } else {
        render_status_slave();
    }

    return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}
