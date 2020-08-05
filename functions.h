#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define GAP 35
#define display_width 1280
#define display_height 720
#define KEY_SEEN     1
#define KEY_RELEASED 2

/*** Structures and enumeration ***/

enum BOUNCER_TYPE {

    BT_CIRCLE,
    BT_N

};

typedef struct BOUNCER {

    float x, y; // Position on screen
    float dx, dy; // Speeds of ball
    int type;

} BOUNCER;

typedef struct SPRITES {

    ALLEGRO_BITMAP* paddle_LS;
    ALLEGRO_BITMAP* paddle_RS;

    ALLEGRO_BITMAP* divider;
    ALLEGRO_BITMAP* ball;

} SPRITES;

typedef struct FONT {

    ALLEGRO_FONT* names;
    ALLEGRO_FONT* scoreboard;

} FONT;

typedef struct AUDIO {

    ALLEGRO_SAMPLE* sample_paddle_hit;
    ALLEGRO_SAMPLE* sample_ball_out;

} AUDIO;

typedef struct SCOREBOARD {

    char name_1[256];
    char name_2[256];
    int top_scores[2];

} SCOREBOARD;


/*** All Files ***/

/*** User Interface ***/
// Main Menu:
int menu_screen_selection();
char menu_play_selection();
void difficulty_selection();

void menu_screen();
void menu_play_screen();
void menu_main_interface();
void menu_instructions_interface();
void menu_settings_interface();
void menu_credits_interface();
void menu_play_interface();
void menu_difficulty_interface();

// In-Game Interfaces:
void scoreboard_draw(struct FONT font, int score_LS, int score_RS);
void bitmaps_draw(struct SPRITES sprites);
void ball_draw(struct SPRITES sprites);
void high_score_draw(int score, struct FONT font);

// End Screen:
void end_screen();

/*** User Functionality ***/
void read_file(char filename[256]);
int high_score_input(struct SCOREBOARD scoreboard);
void high_score_output(struct SCOREBOARD scoreboard);
void menu_play_functionality(char user_selection_play);
void menu_screen_functionality(int x);

/*** Addons Setup ***/
// Initialization
void must_init(bool test, const char *description);

// Addons:
void keyboard_init();
void sprites_init();
void sprites_deinit();
void display_init();
void display_deinit();
void font_init();
void font_deinit();
void audio_init();
void audio_deinit();

// Audio Functions:
void paddle_hit_sound(float volume, float speed);
void score_sound(float volume, float speed);

/*** Game Setup ***/
// Ball Movement:
int ball_start_x ();
int ball_start_y ();
float ball_speed_x ();
float ball_speed_y ();
float sound_toggle();
void ball_start();
void ball_update ();
void reset_globals();

/*** User Controls ***/
// Paddle Movement:
void keyboard_update(ALLEGRO_EVENT* event);

/*** Computer Controls ***/
// Computer paddle movement
void paddle_computer_algorithm(float ball_speed);
void computer_paddle_update();
