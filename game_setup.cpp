#include "functions.h"

// All global variables used in "game_setup.cpp":
extern char username_1[256];
extern char username_2[256];
extern char sound_selection;
extern float y_paddle_RS;
extern float y_paddle_LS;
extern float x_paddle_LS;
extern float x_paddle_RS;
extern int score_RS;
extern int score_LS;
extern int rally_counter;
extern int difficulty_level;
extern bool done;
extern bool redraw;
extern bool continue_play;
extern bool menu_condition;
extern bool menu_play_condition;
extern bool play_again;

// Global stucts:
extern BOUNCER obj[BT_N];

/*************PROCESS*************/

// Resets all global variables.
void reset_globals() {

    score_RS = 0;
    score_LS = 0;
    rally_counter = 0;
    difficulty_level = 0;
    sound_selection = 'y';
    strcpy(username_1, "");
    strcpy(username_2, "");
    y_paddle_LS = 100.00;
    y_paddle_RS = 100.00;
    x_paddle_LS = -25;
    x_paddle_RS = 1205;
    done = true;
    redraw = true;
    continue_play = false;
    menu_condition = true;
    play_again = true;
    menu_play_condition = true;
}

// Prints any text files to the console screen given a text file directory.
void read_file(char filename[256]) {

    FILE *fp_in = fopen(filename, "r");
    char c;

    if (fp_in == NULL) {

        // File did not open. Give error and abort.
        printf("Error opening file, program aborted.\n");
        exit(1); //exits program
    }

    // File opens
    else {

        // Prints the entire content of a file until the end of line.
        while((c = fgetc(fp_in))!= EOF) {
            printf("%c", c);
        }
        fclose(fp_in); // Closes the file
    }
}

int ball_start_x () {
    srand(time(0));
    return rand() % 200 + 400; // Choose from a 100x500 pixel window inside the display where the y-cordinate of the ball will start.
}

int ball_start_y () {
    srand(time(0));
    return rand() % 300 + 200;
}

float ball_speed_x () {
    srand(time(0));
    return ((float)rand()/(float)(RAND_MAX)) * 3.2; // Choose from a random x float speed between 0.0 and 1.8.
}

float ball_speed_y () {
    srand(time(0));
    return ((float)rand()/(float)(RAND_MAX)) * 3.2;
}

float sound_toggle() {

    float volume = 0.0;

    if (sound_selection == 'y' || sound_selection == 'Y') {
        volume = 0.5;
    }

    else {
        volume = 0.0;
    }

    return volume;
}

void ball_start() {

    // Looping thought bouncer types (ball):
    for(int i = 0; i < BT_N; i++) {

        // Bouncer pointer set to object type (the ball).
        BOUNCER *b = &obj[i];

        // X and Y coordinates of the ball.
        b->x = ball_start_x();
        b->y = ball_start_y();

        // Speeds of ball:
        b->dx = ball_speed_x();
        b->dy = ball_speed_y();

        // Object type is set incrementally, so we get one of every BOUNCER_TYPE (ex: the ball):
        b->type = i;
    }
}
