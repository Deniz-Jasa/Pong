#include "functions.h"

// Declaration of gloabal variables for "user_functionality.cpp":
extern bool menu_condition;
extern bool continue_play;
extern char user_selection_play;
extern char username_1[256];
extern char username_2[256];
extern char sound_selection;
extern int rally_counter;
extern bool menu_play_condition;

/*************PROCESS*************/

void menu_play_functionality (char user_selection_play) {

    if (user_selection_play == 'a') { // Playver vs. Player gamemode.
        menu_play_condition = false;
        system("cls");
        printf("Player 1 please enter your name: ");
        scanf("%s", username_1);
        system("cls");
        printf("Player 2 please enter your name: ");
        scanf("%s", username_2);
        system("cls");
        printf("%s and %s, enjoy the game!\n", username_1, username_2);
        continue_play = true;
    }

    else if (user_selection_play == 'b') { // Playver vs. Computer gamemode.
        menu_play_condition = false;
        system("cls");
        difficulty_selection();
        computer_paddle_update();
        system("cls");
        printf("Before beginning, please enter your name: ");
        scanf("%s", username_1);
        strcpy(username_2, "Computer");
        system("cls");
        printf("%s, enjoy the game! You will be controlling the left paddle.", username_1);
        Sleep(3000); // Gives the user a chance to read the short instructions.
        continue_play = true;
    }

    else { // Invalid char input from the user.
        menu_play_condition = true;
        system("cls");
        printf("\x1B[31mInvalid Input! Try Again.\033[0m\n\n"); // "Invalid Input" message in red.
        continue_play = false; // Blocks the Allegro game from opening.
    }
}

void menu_play_screen() {

    while (menu_play_condition) { // Main menu bool condition.

        char play_user_input = ' ';
        menu_play_interface();
        play_user_input = menu_play_selection(); // Set the user's choice equal to a local variable.
        menu_play_functionality(play_user_input); // Passes through the function the user's choice via the local variable.
    }
}

void menu_screen_functionality(int main_user_input) {

    if (main_user_input == 1) { // "Play Menu"

        menu_condition = false;
        system("cls");

        menu_play_screen();
    }

    else if (main_user_input == 2) { // "Instruction Menu"

        system("cls");
        menu_condition = false;
        menu_instructions_interface ();
        printf("\n\n\t\t\t\t\t\tPress Enter to Return: "); // Enter any key!
        fflush(stdin);
        getchar();
        system("cls");
        menu_condition = true; // returns to menu screen
    }

    else if (main_user_input == 3) { // "Credits Menu"

        system("cls");
        menu_condition = false;
        menu_settings_interface();
        fflush(stdin);
        scanf("%c", &sound_selection);
        printf("\n\t\t  ______________________________________________________________________________________");
        printf("\n\n\t\t\t\t\t\tPress Enter to Return: ");
        fflush(stdin);
        getchar();
        system("cls");
        menu_condition = true; // returns to menu screen
    }

    else if (main_user_input == 4) { // "Credits Menu"

        system("cls");
        menu_condition = false;
        menu_credits_interface ();
        printf("\n\n\t\t\t\t\t\tPress Enter to Return: ");
        fflush(stdin);
        getchar();
        system("cls");
        menu_condition = true; // returns to menu screen
    }

    else {

        system("cls");
        printf("\x1B[31m \n\t\t\t\t\t\tInvalid Input! Try Again.\033[0m\t\t"); // "Invalid Input" message in red.
        menu_condition = true; // returns to menu screen
    }

}

void menu_screen() {

    while (menu_condition) { // Main menu bool condition.

        int main_user_input = 0;
        menu_main_interface();
        main_user_input =  menu_screen_selection(); // Set the user's choice equal to a local variable.
        menu_screen_functionality(main_user_input); // Passes through the function the user's choice via the local variable.
    }
}


int high_score_input (struct SCOREBOARD scoreboard) {

    // Set file pointer to the "high_scores" text file.
    FILE *high_score_in = fopen("text_files/high_score.txt", "r");

    memset(scoreboard.top_scores, 0, sizeof(scoreboard.top_scores)); // Set array elements to 0.

    if (high_score_in == NULL) {

        // File did not open. Give error and abort.
        printf("Error opening file, program aborted.\n");
        exit(1); //exits program
    }

    // File opens
    else {

        // Scans the entire content of a file until the end of line.
        fscanf(high_score_in, "%s %s %d", scoreboard.name_1,  scoreboard.name_2, & scoreboard.top_scores[0]); // The current high score becomes the first element of the array.
    }

    fclose(high_score_in); // close the input file

    return scoreboard.top_scores[0];

}

// High Score:
void high_score_output (struct SCOREBOARD scoreboard) {

    /*************INPUT*************/
    scoreboard.top_scores[0] = high_score_input(scoreboard);

    /*************PROCESS*************/

    if (rally_counter > scoreboard.top_scores[0]) {

        strcpy(scoreboard.name_1, username_1);
        strcpy(scoreboard.name_2, username_2);

        // Insert the current user's names:
        scoreboard.top_scores[1] = rally_counter; // The new high score becomes the second element (or element [1]) of the array.

        // Re-opening the file in wrtie mode in order to clear the previous data.
        FILE *high_score_ou = fopen("text_files/high_score.txt", "w");

        if (high_score_ou == NULL) {

            // File did not open. Give error and abort.
            printf("Error opening file, program aborted.\n");
            exit(1); //exits program
        }

        // File opens
        else {

            fprintf(high_score_ou, "%s %s %d", scoreboard.name_1, scoreboard.name_2, scoreboard.top_scores[1]);
            // Print the new high score and player names to textfile.
        }

        fclose(high_score_ou); // close the ouput file
    }
}
