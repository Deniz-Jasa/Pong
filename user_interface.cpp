#include "functions.h"

// All global variables used in "user_interface.cpp":
extern bool continue_play;
extern bool play_again;
extern bool menu_condition;
extern char username_1[256];
extern char username_2[256];
extern char user_selection_play;
extern int difficulty_level;
extern int rally_counter;

extern float y_paddle_LS;
extern float y_paddle_RS;
extern float x_paddle_LS;
extern float x_paddle_RS;

extern BOUNCER obj[BT_N];


// Main Menu:

/*************INPUT*************/

char menu_play_selection () {

    fflush(stdin);
    scanf("%c", &user_selection_play);

    return user_selection_play;  // returns the user's char selection.
}

int menu_screen_selection () {

    static int user_selection = 0; // stored in the statically allocated memory, for reuse.
    scanf("%d", &user_selection);

    return user_selection; // returns the user's int selection.
}

void difficulty_selection () {

    menu_difficulty_interface();
    fflush(stdin);
    scanf("%d", &difficulty_level);
}

/*************OUTPUT*************/

/** Main Menu Output **/

void menu_main_interface () {

    // Reads in and displays all the text for the main menu using the read file function.
    char file_menu[256] = "text_files/menu_main.txt";
    read_file(file_menu);
}

void menu_instructions_interface () {

    // Reads in and displays all the text for the instructions menu.
    char file_instructions[256] = "text_files/menu_instructions.txt";
    read_file(file_instructions);
}

void menu_settings_interface () {

    // Reads in and displays all the text for the settings menu.
    char file_menu[256] = "text_files/menu_settings.txt";
    read_file(file_menu);
}

void menu_credits_interface () {

    // Reads in and displays all the text for the credits menu.
    char file_menu[256] = "text_files/menu_credits.txt";
    read_file(file_menu);
}

void menu_play_interface () {

     // Reads in and displays all the text for the play menu.
    char file_menu[256] = "text_files/PLAY/menu_play.txt";
    read_file(file_menu);
}

void menu_difficulty_interface () {

     // Reads in and displays all the text for the ifficulty menu.
    char file_menu[256] = "text_files/PLAY/menu_difficulty.txt";
    read_file(file_menu);
}

/** In Game Output **/

// Draws the score board to the screen.
void scoreboard_draw(struct FONT font, int score_LS, int score_RS) {

    // Live Scores:
    al_draw_textf(font.scoreboard, al_map_rgb(255, 255, 255), 550, 50, 0, "%d", score_LS);
    al_draw_textf(font.scoreboard, al_map_rgb(255, 255, 255), 700, 50, 0, "%d", score_RS);

    // Player Names:
    al_draw_textf(font.names, al_map_rgb(255, 255, 255), 490, 660, 0, "%s", username_1);
    al_draw_textf(font.names, al_map_rgb(255, 255, 255), 700, 660, 0, "%s", username_2);
}

void bitmaps_draw(struct SPRITES sprites) {

    // Bitmaps:
    al_draw_bitmap(sprites.paddle_LS, x_paddle_LS, y_paddle_LS, 0);
    al_draw_bitmap(sprites.paddle_RS, x_paddle_RS, y_paddle_RS, 0);
    al_draw_bitmap(sprites.divider, 600, 4, 0);
}

// Draws the ball image to the screen.
void ball_draw(struct SPRITES sprites) {

    for(int i = 0; i < BT_N; i++) {

        BOUNCER* b = &obj[i]; // Struct pointer "b" set to objects (ball)

        switch(b->type) {

        case BT_CIRCLE:
            al_draw_bitmap(sprites.ball, b->x, b->y, 0); // draws the game ball given bouncer type (BT_CIRCLE).
            break;
        }
    }
}

void high_score_draw(int input_rally_score, struct FONT font) { // input_rally_score --> Previous high score from text file.

    if (rally_counter == input_rally_score) {

        al_draw_textf(font.names, al_map_rgb(255, 255, 255), 465, 330, 0, "New High Score!    With %d rallies! ", rally_counter);
    }
}

/** End Game Output **/

void end_screen() {

    char user_selection_again = ' ';
    system("cls"); // clears the console
    printf("Thank you for playing! You were amazing out there!\n");
    printf("\nWould you like to play again? (y/n): ");
    fflush(stdin);
    scanf("%c", &user_selection_again);

    if (user_selection_again == 'Y' || user_selection_again == 'y') {

        reset_globals(); // Before playing again with different settings, reset all global variables.
        continue_play = false;
        menu_condition = true;
        play_again = true; // Return to menu.
        system("cls");
    }

    else {

        // Close the menu and game.
        continue_play = false;
        play_again = false;
    }
}
