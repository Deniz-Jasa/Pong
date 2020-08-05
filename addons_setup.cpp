#include "functions.h"

// All global variables used in "addon_setup.cpp":
extern unsigned char key[ALLEGRO_KEY_MAX];

extern SPRITES sprites;
extern FONT font;
extern AUDIO audio;
extern ALLEGRO_DISPLAY* disp;


/*************INPUT*************/

// Tests and initializes all Allegro and files (images, text files, sounds, etc).
void must_init(bool test, const char *description) {

    if(test)
        return;

    printf("\nERROR! Couldn't initialize %s.\n", description);
    exit(1);
}

// Installs Allegro keyboard.
void keyboard_init() {

    must_init(al_install_keyboard(), "keyboard");

    // C standard library's memset function efficiently makes sure the contents of the key array are zeroed.
    memset(key, 0, sizeof(key));
}

// Intialization of sprites.
void sprites_init() {

    sprites.paddle_LS = al_load_bitmap("primitives/paddle.png");
    must_init(sprites.paddle_LS, "paddle_LS");

    sprites.paddle_RS = al_load_bitmap("primitives/paddle.png");
    must_init(sprites.paddle_RS, "paddle_RS");

    sprites.ball = al_load_bitmap("primitives/ball.png");
    must_init(sprites.ball, "ball");

    sprites.divider = al_load_bitmap("primitives/background.png");
    must_init(sprites.divider, "divider");

}

// Deintialization of sprites.
void sprites_deinit() {

    al_destroy_bitmap(sprites.paddle_RS);
    al_destroy_bitmap(sprites.paddle_LS);
    al_destroy_bitmap(sprites.ball);
    al_destroy_bitmap(sprites.divider);
}

// Intialization of the display.
void display_init() {

    // Anti-aliasing
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    disp = al_create_display(display_width, display_height);
    must_init(disp, "display");
}

// Deintialization of the display.
void display_deinit() {

    al_destroy_display(disp);
}

// Intialization of the fonts.
void font_init() {

    al_init_font_addon();
    al_init_ttf_addon();

    font.scoreboard = al_load_font("fonts/8_bit_font.ttf", 50, 0);
    must_init(font.scoreboard, "scoreboard font");

    font.names = al_load_font("fonts/8_bit_font.ttf", 20, 0);
    must_init(font.names, "name font");

}

// Deintialization of the fonts.
void font_deinit() {

    al_destroy_font(font.scoreboard);
    al_destroy_font(font.names);
}

// Intialization of audio.
void audio_init() {

    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);

    audio.sample_paddle_hit = al_load_sample("sounds/paddle_hit.wav");
    must_init(audio.sample_paddle_hit, "paddle hit sound");

    audio.sample_ball_out = al_load_sample("sounds/ball_out.wav");
    must_init(audio.sample_ball_out, "ball out sound");
}

// Deintialization of audio.
void audio_deinit() {

    al_destroy_sample(audio.sample_paddle_hit);
    al_destroy_sample(audio.sample_ball_out);
}

// Audio functions:

// Paddle hit sound effect:
void paddle_hit_sound(float volume, float speed) {

    al_play_sample(
        audio.sample_paddle_hit,    // the sample to play
        volume,                     // gain ('volume')
        0.0,                        // pan ('balance')
        speed,                      // speed
        ALLEGRO_PLAYMODE_ONCE,      // play mode
        NULL                        // sample id
    );
}

// Goal hit sound effect:
void score_sound(float volume, float speed) {

    al_play_sample(
        audio.sample_ball_out,   // the sample to play
        volume,                  // gain ('volume')
        0.0,                     // pan ('balance')
        speed,                   // speed
        ALLEGRO_PLAYMODE_ONCE,   // play mode
        NULL                     // sample id
    );
}
