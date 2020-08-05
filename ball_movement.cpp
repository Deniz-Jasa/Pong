#include "functions.h"

#define ball_delay -400  // ball_delay allows the ball to only go out of bounds and delays the re-start position of the ball.

// Global variables:
extern float y_paddle_RS;
extern float y_paddle_LS;
extern float x_paddle_LS;
extern float x_paddle_RS;
extern char sound_selection;
extern int score_RS;
extern int score_LS;
extern bool done;
extern bool redraw;
extern bool continue_play;
extern int rally_counter;

// Global structs:
extern unsigned char key[ALLEGRO_KEY_MAX];
extern BOUNCER obj[BT_N];

void ball_update() {

    /**************************************************************************************************************************************************************
    *  BALL MOVEMENT LOGIC: Ball movement logic: For each BOUNCER (i.e the ball), their x and y coordinates are changed by adding each dimension's respective     *
    *  velocity (dx, dy) to them. This means the velocities set up earlier between -1 and +1, are the number of pixels it will moves every frame. However, I also *
    *  had to consider what happens if the ball is about to go off screen or hit the paddles. If it bumps into the paddles, dx is inverted so that it immediately *
    *  travelles in the other direction. Vice versa for dy for the top or bottom. Furthermore, this function makes sure that the object isn't out-of-bounds any   *
    *  more by putting it back within-bounds by the amount it came out, so if x = -3, it becomes x = 3.                                                           *
    ***************************************************************************************************************************************************************/

    for(int i = 0; i < BT_N; i++) {

        float volume = sound_toggle();

        BOUNCER* b = &obj[i];
        b->x += b->dx;
        b->y += b->dy;

        if(key[ALLEGRO_KEY_ESCAPE]) {

            done = true; // Break from loop is game is exited.
            continue_play = false; // Close the Allegro game.
        }

        if (b->x > 0 && b->x < 35) { // If the ball hits the left paddle.

            if ((b->y >= y_paddle_LS - 50) && (b->y <= y_paddle_LS + 200)) {

                b->dx += -0.1;
                b->x *= 1;
                b->dx *= -1;
                paddle_hit_sound(volume, 1.0); // Volume: 0.5, Speed: 1.0x.
                rally_counter++; // rally score increased by 1.
            }
        }

        else if (b->x < (0 + ball_delay)) { // If the ball hits the left side wall.

            b->dx *= -1;
            b->x = ball_start_x();
            b->y = ball_start_y();

            // Based on the paddles position, when the ball restarts it will be going in the direction of the paddle.
            if (b->y < y_paddle_RS) {

                b->dx = ball_speed_x();
                b->dy = ball_speed_y();
            }

            else if (b->y > y_paddle_RS) {

                b->dx = ball_speed_x();
                b->dy = ball_speed_y() * -1;
            }

            score_sound((volume + 0.5), 1.0);
            score_RS++;
            rally_counter = 0; // rally score reset to 0 after the ball is lost out of bounds.
        }

        if(b->x > (1210) && b->x < (display_width - GAP)) { // If the ball hits the right paddle.

            if ((b->y >= y_paddle_RS - 50) && (b->y <= y_paddle_RS + 210)) {

                b->dx += 0.1;
                b->x -= (b->x - (1200));
                b->dx *= -1;
                paddle_hit_sound(volume, 1.0);
                rally_counter++;
            }
        }

        else if (b->x > (display_width - (GAP + ball_delay))) { // If the ball hits the right side wall.

            b->x *= -1;
            b->x = ball_start_x(); // Reset the ball in the middle
            b->y = ball_start_y();

            // Based on the paddles position, when the ball restarts it will be going in the direction of the paddle.
            if (b->y < y_paddle_LS) {

                b->dx = ball_speed_x() * -1;
                b->dy = ball_speed_y();
            }
            else if (b->y > y_paddle_LS) {

                b->dx = ball_speed_x() * -1;
                b->dy = ball_speed_y() * -1;
            }

            score_sound((volume + 0.5), 1.0); // Volume: 1.0, Speed: 1.0x.
            score_LS++;
            rally_counter = 0;
        }

        if(b-> y < 0) { // If the ball hits the top wall.

            b->y  *= -1;
            b->dy *= -1;
        }

        else if(b->y > (display_height - GAP)) {  // If the ball hits the bottom wall.

            b->x -= (b->y - (720 - GAP));
            b->dy *= -1;
        }

        redraw = true;
        break;
    }
}
