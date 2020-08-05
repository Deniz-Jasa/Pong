#include "functions.h"

extern char user_selection_play;
extern unsigned char key[ALLEGRO_KEY_MAX];
extern float y_paddle_LS;
extern float y_paddle_RS;

/*************PROCESS*************/

void keyboard_update(ALLEGRO_EVENT* event) {

    switch(event->type) {

    case ALLEGRO_EVENT_TIMER:

        // Ensures that after every run of the game logic, another one of the bits is set to 0. Look for explation below
        // about the key array and events.
        for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= KEY_SEEN;

        // Only if staments (an not else if) are used to allow both players to press down different keys at the same time.

        if (user_selection_play == 'a') { // Player vs. Player gamemode:

            if(key[ALLEGRO_KEY_UP]) { // UP arrow key logic:

                // Movement limits so that the paddles doesn't leave the screen. The paddle can move up until y = 0.
                if (y_paddle_RS > 0) {
                    y_paddle_RS-= 3.0;
                }
                else {
                    y_paddle_RS-= 0;
                }

            }

            if(key[ALLEGRO_KEY_DOWN]) { // DOWN arrow key logic:

                // The paddle can move down until y = 495.
                if (y_paddle_RS < 495) {
                    y_paddle_RS += 3.0;
                }
                else {
                    y_paddle_RS += 0;
                }
            }


            if(key[ALLEGRO_KEY_W]) { //  W key logic:

                // The paddle can move up until y = 0.
                if (y_paddle_LS > 0) {
                    y_paddle_LS -= 3.0;
                }
                else {
                    y_paddle_LS -= 0;
                }

            }
            if(key[ALLEGRO_KEY_S]) { // S key logic:

                // The paddle can move down until y = 495.
                if (y_paddle_LS < 495) {
                    y_paddle_LS += 3.0;
                }
                else {
                    y_paddle_LS += 0;
                }
            }
        }

        else if (user_selection_play == 'b') { // Player vs. Computer gamemode:

            // Only requires left paddle input:
            if(key[ALLEGRO_KEY_W]) {
                if (y_paddle_LS > 0) {
                    y_paddle_LS -= 3;
                }
                else {
                    y_paddle_LS -= 0;
                }

            }
            if(key[ALLEGRO_KEY_S]) {
                if (y_paddle_LS < 495) {
                    y_paddle_LS += 3;
                }
                else {
                    y_paddle_LS += 0;
                }
            }
        }

    // When a key is pressed down, two of the bits are set to 1 in the key's corresponding entry in the key array.
    // When the key is unpressed (in the array it is stored as 00000000). When the key is pressed down it will
    // becomes 00000011. *Note: the binary examples of keys are dependant on the endianness of those keys in the system.

    case ALLEGRO_EVENT_KEY_DOWN:
        key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
        break;

    // When the key is released, the case event below is fired. One of the bits is then set to 0. Now it becomes (00000001).

    case ALLEGRO_EVENT_KEY_UP:
        key[event->keyboard.keycode] &= KEY_RELEASED;
        break;

    // In short, all these conditions ensure that a keypress can't be missed between game logic runs because any given
    // member of the key array has a truthy value so long as the game logic hasn't seen it yet or if the key is still
    // held down.

    }

}
