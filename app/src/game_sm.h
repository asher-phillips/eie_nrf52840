//Header file to set up the state machine
#ifndef GAME_SM_H   //If the header file is not already defined do the following

#define GAME_SM_H
#include <zephyr/smf.h>     //Gives state machine framwork
#include <lvgl.h>           //Sets up the screen libary?

//Define state machine
typedef enum {
    STATE_MM,
    STATE_GP,
    STATE_S,
} gs_t;

//State machine memory
struct game_sm_ctx {
    struct smf_ctx ctx;     //Current state
    uint32_t song_start_ms;    //How long it takes for the game to end
    lv_obj_t *rune_image;
    lv_obj_t *title_image;
    lv_obj_t *hearts;
    lv_obj_t *title_card;
};

//Function declarations
void game_sm_init(void);
void game_sm_run(void);

#endif
