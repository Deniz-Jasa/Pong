/**********************************************************************************************************
 *  Name: Deniz Jasarbasic                  Summative - PONG                                  2020/06/10  *
 *                                                                                                        *
 *  DESCRIPTION: Pong is a solo or two-player game that features a paddle for each player and one ball.   *
 *  The goal of the game is for a player to earn more points than the opponent. Points are earned when    *
 *  the opponent fails to return the ball to the other player. In mt version of Pong, you can play        *
 *  against a computer or another player.                                                                 *
 **********************************************************************************************************/

#include "functions.h"

// Makes sure that all Allegro addons are set and initialized.
void must_init(bool test, const char *description);

// Global variables:
int score_LS = 0, score_RS = 0;
int rally_counter = 0;
int difficulty_level = 0;
char username_1[256] = "";
char username_2[256] = "";
char user_selection_play = ' ';
char sound_selection = 'y';
float y_paddle_LS = 100.00;
float y_paddle_RS = 100.00;
float x_paddle_LS = -25;
float x_paddle_RS = 1205;
bool done = true;
bool redraw = true;
bool continue_play = false;
bool menu_condition = true;
bool menu_play_condition = true;
bool play_again = true;

// An array of all of all possible keys to press. ALLEGRO_KEY_MAX constant tells us how big the array is.
unsigned char key[ALLEGRO_KEY_MAX];

// Global structs:
BOUNCER obj[BT_N];
SPRITES sprites;
SCOREBOARD scoreboard;
FONT font;
AUDIO audio;
ALLEGRO_DISPLAY* disp;

int main() {

    while (play_again && menu_condition) {

        /*************INPUT*************/

        // Menu screen:

        menu_screen();

        while ((continue_play) && (user_selection_play == 'a' || user_selection_play == 'b')) {

            // Declartion of all Allegro addons in the main.

            must_init(al_init(), "allegro");
            keyboard_init();

            ALLEGRO_TIMER* timer = al_create_timer(0.2 / 60.0); // Creating a timer that updates 60 frames per second.
            must_init(timer, "timer");

            ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); // Creating an event queue.
            must_init(queue, "queue");

            display_init();

            font_init();

            must_init(al_init_image_addon(), "image addon");
            sprites_init();

            audio_init();

            must_init(al_init_primitives_addon(), "primitives");

            // Registering keyboard, timer, and the display.
            al_register_event_source(queue, al_get_keyboard_event_source());
            al_register_event_source(queue, al_get_timer_event_source(timer));
            al_register_event_source(queue, al_get_display_event_source(disp));

            keyboard_init();

            done = false; // Game logic condition is set to false allowing the game to start.
            redraw = true;

            ALLEGRO_EVENT event;

            ball_start();

            al_start_timer(timer);

            /*************PROCESS*************/

            while(1) {

                al_wait_for_event(queue, &event);

                switch(event.type) {

                    case ALLEGRO_EVENT_DISPLAY_CLOSE:

                        // If the program is closed, end the loop, break, and close the program.
                        done = true;
                        continue_play = false;
                        break;

                    case ALLEGRO_EVENT_TIMER:

                        // Game Logic:

                        // Ball movement.
                        ball_update();

                        // Computer paddle movement.
                        computer_paddle_update();

                        high_score_output(scoreboard);

                  }

                if(done) {
                    break;
                }

                // In game keyboard input and paddle movement.
                keyboard_update(&event);

                /*************OUTPUT*************/

                if(redraw && al_is_event_queue_empty(queue)) {

                    al_clear_to_color(al_map_rgb(0, 0, 0)); // Set backgrond to black

                    bitmaps_draw(sprites); // Draw all BITMAPS to screen.

                    scoreboard_draw(font, score_LS, score_RS); // Draws the scoreboard to the screen.

                    ball_draw(sprites); // Draws the ball to the screen.

                    int input_rally_score = high_score_input(scoreboard); // Sets "input_rally_score" equal to the previous high score.

                    // "input_rally_score" is passed through and used to draws high score message
                    high_score_draw(input_rally_score, font);

                    al_flip_display(); // Flips the display (updates the front and back buffer to display the drawings).
                    redraw = false;
                }
            }

            // Deinitialization of all Allegro addons, events, and timer:

            display_deinit();
            font_deinit();
            sprites_deinit();
            audio_deinit();

            al_destroy_timer(timer);
            al_destroy_event_queue(queue);
        }

        end_screen(); // Exit screen
    }

    return 0;
}
