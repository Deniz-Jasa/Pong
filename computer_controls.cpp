#include "functions.h"

extern BOUNCER obj[BT_N];
extern float y_paddle_RS;
extern int difficulty_level;
extern bool continue_play;
extern char user_selection_play;

/*************PROCESS*************/

 /***************************************************************************************************************************
 *  COMPUTER ALGORITHM LOGIC: Based on the y-position of the ball, the computer controlled paddle will move. If the ball's  *
 *  y-position is below the center of paddle, it will move up given a ball speed value. If the ball is above the paddle,    *
 *  it will move down given a ball speed value. The paddle will keep adjust as the ball moves around the screen.            *
 ****************************************************************************************************************************/

void paddle_computer_algorithm (float ball_speed) {

    for(int i = 0; i < BT_N; i++) {

        BOUNCER* b = &obj[i];

        if (b->y > y_paddle_RS + 100) {  // If the ball is below the center of the paddle.

            y_paddle_RS += ball_speed;
        }

        else if (b->y < y_paddle_RS + 100) { // If the ball is above the center of the paddle.

            y_paddle_RS -= ball_speed;
        }
    }
}



void computer_paddle_update() {

    if (user_selection_play == 'b') {

        if (difficulty_level == 1) { // Easy:

            paddle_computer_algorithm(1.2); // Slow paddle movement speed and reaction time.
        }

        else if (difficulty_level == 2) { // Medium:

            paddle_computer_algorithm(1.5); // Medium paddle movement speed and reaction time.
        }

        else if (difficulty_level == 3) { // Hard:

            paddle_computer_algorithm(1.65); // Super quick paddle movement speed and reaction time.
        }

        else {

            system("cls");
            // Invalid char input from the user.
            printf("\x1B[31mInvalid Input! Try Again.\033[0m\n\n"); // "Invalid Input" message in red.
            continue_play = false; // Blocks the Allegro game from opening.
            difficulty_selection();
            return computer_paddle_update(); // Return to the beginning of the function
        }
    }
}
