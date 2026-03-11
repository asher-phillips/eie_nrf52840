//Main gameplay file :)

/*-------------------------------------------------------------------LIBRARIES-------------------------------------------------------------------*/
#include <zephyr/kernel.h>  //Core Zephyr OS files
#include <zephyr/smf.h>     
#include <lvgl.h>           //Screen library
#include <game_sm.h>        //Include my sm header file
#include <zephyr/random/random.h>

/*--------------------------------------------------------------------MACROS---------------------------------------------------------------------*/
#define ONE_SECOND 1000        //1 second
typedef enum {
    RUNE1,
    RUNE2,
    RUNE3,
    RUNE4,
    NEXT,
    RUNE_COUNT
} rune_t;

int lives = 3;
int points = 0;
int high_score = 0;
int heart_x = 0;
int heart_y = 0;
int heart_update = 0;
int game_over = 0;
rune_t current_rune = RUNE1;
rune_t displayed_rune = RUNE1;


/*--------------------------------------------------------------------IMAGES---------------------------------------------------------------------*/
//Runes
extern const lv_image_dsc_t BlueRune;
extern const lv_image_dsc_t GreenRune;
extern const lv_image_dsc_t PurpleRune;
extern const lv_image_dsc_t RedRune;

//Hearts
extern const lv_image_dsc_t HeartRune;
extern const lv_image_dsc_t GreyHeartRune;
extern const lv_image_dsc_t ThreeHeartsRune;
extern const lv_image_dsc_t TwoHeartsRune;
extern const lv_image_dsc_t OneHeartRune;
extern const lv_image_dsc_t ZeroHeartRune;

//Title
extern const lv_image_dsc_t RuneTitle;


/*----------------------------------------------------------------STATE FUNCTIONS----------------------------------------------------------------*/
static void mm_entry(void *o);
static enum smf_state_result mm_run(void *o);
static void gp_entry(void *o);
static enum smf_state_result gp_run(void *o);
static void s_entry(void *o);
static enum smf_state_result s_run(void *o);

/*----------------------------------------------------------------BASIC FUNCTIONS-----------------------------------------------------------------*/
static void button(lv_align_t AS, int x, int y, const char *name, lv_event_cb_t callback, uint32_t colour);
static void clear(void);
static void next_rune(void);
static lv_obj_t* label(const char *name, lv_align_t AS, int x, int y, uint32_t colour);
static lv_obj_t* image(lv_align_t AS, const lv_image_dsc_t *src, int x, int y);

/*----------------------------------------------------------------DEFINE STATES-------------------------------------------------------------------*/
//Takes in entry, run, exit, parent and initial
static const struct smf_state states[] = {
    [STATE_MM] = SMF_CREATE_STATE(mm_entry, mm_run, NULL, NULL, NULL),
    [STATE_GP] = SMF_CREATE_STATE(gp_entry, gp_run, NULL, NULL, NULL),
    [STATE_S] = SMF_CREATE_STATE(s_entry, s_run, NULL, NULL, NULL),
};

//Creates a single state
static struct game_sm_ctx ctx;

//Starts the system in sm (Start Menu)
void game_sm_init(void) {
    smf_set_initial(SMF_CTX(&ctx), &states[STATE_MM]);
}

//Tells the system to run the current function from the right state declared above
void game_sm_run(void) {
    smf_run_state(SMF_CTX(&ctx));
}

//Starts the call back
static void start_cb(lv_event_t *e) {
    smf_set_state(SMF_CTX(&ctx), &states[STATE_GP]);
}

static void back_to_menu_cb() {
    smf_set_state(SMF_CTX(&ctx), &states[STATE_MM]);
}

static void retry_cb() {
    smf_set_state(SMF_CTX(&ctx), &states[STATE_GP]);
}

static void rune1_cb(lv_event_t *e) {
    if(displayed_rune == RUNE1) {
        points++;
        next_rune();
    }
    else {
        next_rune();
        lives -= 1;
    }
}
static void rune2_cb(lv_event_t *e) {
    if(displayed_rune == RUNE2) {
        points++;
        next_rune();
    }
    else {
        next_rune();
        lives -= 1;
    }
}
static void rune3_cb(lv_event_t *e) {
    if(displayed_rune == RUNE3) {
        points++;
        next_rune();
    }
    else {
        next_rune();
        lives -= 1;
    }
}
static void rune4_cb(lv_event_t *e) {
    if(displayed_rune == RUNE4) {
        points++;
        next_rune();
    }
    else {
        next_rune();
        lives -= 1;
    }
}

/*---------------------------------------------------------------RUNNING STATES----------------------------------------------------------------*/
static void mm_entry(void *o) {
    //Clear the screen
    //Add a button in for starting the game

    //Clear
    clear();

    //Title Card
    ctx.title_card = image(LV_ALIGN_CENTER, &RuneTitle, 0, -20);

    //Name
    label("By Asher :)", LV_ALIGN_CENTER, 0, 10, 0x000000);
    
    //Create the button
    button(LV_ALIGN_CENTER, 0, 40, "START", start_cb, 0x00FF00);
}

static enum smf_state_result mm_run(void *o) {
    //This gets called every tick while you're in this state
    //Empty for now
    return SMF_EVENT_HANDLED;
}

static void gp_entry(void *o) {
    //Clear the screen
    //Add Gameplay label
    //Start the timer of the game (bomb maybe?)
    //Pick random rune to start

    //Clear the screen
    clear();

    //Create title image
    ctx.title_image = image(LV_ALIGN_TOP_MID, &RuneTitle, 0, 0);

    //Start the clock
    ctx.song_start_ms = k_uptime_get_32();  

    current_rune = sys_rand32_get() % 4;

    button(LV_ALIGN_TOP_LEFT, 5, 5, "             ", rune1_cb, 0x2596BE);
    button(LV_ALIGN_TOP_RIGHT, -5, 5, "             ", rune2_cb, 0x634E77);
    button(LV_ALIGN_BOTTOM_LEFT, 5, -5, "             ", rune3_cb, 0xA74D56);
    button(LV_ALIGN_BOTTOM_RIGHT, -5, -5, "             ", rune4_cb, 0x076438);

    points = 0;
    heart_update = 0;
    lives = 3;

    //Starting Points
    ctx.hearts = image(LV_ALIGN_BOTTOM_MID, &ThreeHeartsRune, heart_x, heart_y);
}

static enum smf_state_result gp_run(void *o) {
    //This gets called every tick while you're in this state
    //Check how long it's been
    //Eventually check whether the person got it right

    uint32_t elapsed = k_uptime_get_32() - ctx.song_start_ms;
    /*
    if(elapsed >= 5 * ONE_SECOND) {
        smf_set_state(SMF_CTX(&ctx), &states[STATE_S]);
    }*/
    if(current_rune == RUNE1) {
        displayed_rune = RUNE1;
        ctx.rune_image = image(LV_ALIGN_CENTER, &BlueRune, 0, 0);
        current_rune = NEXT;
    }
    if(current_rune == RUNE2) {
        displayed_rune = RUNE2;
        ctx.rune_image = image(LV_ALIGN_CENTER, &PurpleRune, 0, 0);
        current_rune = NEXT;
    }
    if(current_rune == RUNE3) {
        displayed_rune = RUNE3;
        ctx.rune_image = image(LV_ALIGN_CENTER, &RedRune, 0, 0);
        current_rune = NEXT;
    }
    if(current_rune == RUNE4) {
        displayed_rune = RUNE4;
        ctx.rune_image = image(LV_ALIGN_CENTER, &GreenRune, 0, 0);
        current_rune = NEXT;
    }
    if(lives == 2 && heart_update != 1) {
        lv_obj_del(ctx.hearts);
        ctx.hearts = image(LV_ALIGN_BOTTOM_MID, &TwoHeartsRune, heart_x, heart_y);
        heart_update = 1;
    }
    else if(lives == 1 && heart_update != 2) {
        lv_obj_del(ctx.hearts);
        ctx.hearts = image(LV_ALIGN_BOTTOM_MID, &OneHeartRune, heart_x, heart_y);
        heart_update = 2;
    }
    else if(lives == 0 && game_over == 0)
    {
        lv_obj_del(ctx.hearts);
        lv_obj_del(ctx.rune_image);
        ctx.hearts = image(LV_ALIGN_BOTTOM_MID, &ZeroHeartRune, heart_x, heart_y);
        if(points > high_score) {
            high_score = points;
        }
        game_over = 1;
    }
    else if(game_over == 1) {
        k_msleep(1000);
        smf_set_state(SMF_CTX(&ctx), &states[STATE_S]);
        game_over = 0;
    }
    return SMF_EVENT_HANDLED;
}

static void s_entry(void *o) {
    //Clear the screen
    //Add a label for game over
    //Add a button that says restart

    //Clear
    clear(); 

    //Game over label
    label("GAME OVER", LV_ALIGN_TOP_MID, 0, 0, 0x000000);

    //Create main menu button
    button(LV_ALIGN_CENTER, -50, -20, "Main Menu", back_to_menu_cb, 0x00FF00);

    //Create retry button
    button(LV_ALIGN_CENTER, 50, -20, "Retry", retry_cb, 0x00FF00);

    //Score
    char points_str[10];
    snprintf(points_str, 10, "%d", points);
    label(points_str, LV_ALIGN_BOTTOM_MID, 0, 0, 0x000000);
}

static enum smf_state_result s_run(void *o) {
    //This gets called every tick while you're in this state
    //Emtpy for now
    return SMF_EVENT_HANDLED;
}

/*-------------------------------------------------------------EASY FUNCTIONS :)-------------------------------------------------------------------*/

//Button :)
static void button(lv_align_t AS,int x,int y,const char *name, lv_event_cb_t callback, uint32_t colour) {                                                                                              //AS = Anchor Spot, x = x_offset, y = y_offset, 
    lv_obj_t *ui_btn = lv_button_create(lv_screen_active());                                                            //Creates the button
    lv_obj_align(ui_btn, AS, x, y);                                                               //Determines where it is
    lv_obj_t *button_label_2 = lv_label_create(ui_btn);                                                           //Creates a text label that is a child of the button                                                                              //Create the name of the button                                                                //Print the label, number is max size of buffer
    lv_label_set_text(button_label_2, name);                                                                         //Label the button
    lv_obj_align(button_label_2, LV_ALIGN_CENTER, 0,0);
    lv_obj_add_event_cb(ui_btn, callback, LV_EVENT_CLICKED, NULL);  
    lv_obj_set_style_bg_color(ui_btn, lv_color_hex(colour), LV_STATE_DEFAULT);
}

//Create a label
static lv_obj_t* label(const char *name, lv_align_t AS, int x, int y, uint32_t colour) {
    lv_obj_t *label = lv_label_create(lv_screen_active());                                                          //Create a label
    lv_label_set_text(label, name);                                                                           //Set the text of the label                                 
    lv_obj_align(label, AS, x, y); 
    lv_obj_set_style_text_color(label, lv_color_hex(colour), LV_STATE_DEFAULT); 
    return label;
}

//Create an image
static lv_obj_t* image(lv_align_t AS, const lv_image_dsc_t *src, int x, int y) {
    lv_obj_t *img = lv_image_create(lv_screen_active());
    lv_image_set_src(img, src);
    lv_obj_align(img, AS, x, y);
    return img;
}

//Clear Screen :)
static void clear(void) {
    lv_obj_clean(lv_screen_active()); 
}

static void next_rune(void) {
    lv_obj_del(ctx.rune_image);
    current_rune = sys_rand32_get() % 4;
}


/*--------------------------GAME LOGIC--------------------------
What do I need to figure out
1. What are the symbols, and how does the ui work? Just buttons in the corners and the game speeds up?
2. How do I implement lives?
3. How do I clear only part of the screen
4. What is the point system?
5. How do I make it clear which button is which for the symbols?
6. Do I implement the bomb to make it harder? 
7. How do I explain the rules to everyone playing the game?


--------------------------MY THOUGHTS--------------------------
1. I'll draw out runes, probably in different colours and just have buttons in all four corners with colours associated. 
It will randomly draw out a symbol every x many seconds and you have to click the buttons to get the points, if you miss or click the wrong one
you lose a life. (Points are one per corrrect until it's all done then I can add points for speed if I want).
2. Lives are just a counter, I'm thinking 3 and I could display them as three circles at the bottom of the screen, red if you have it grey if you've
lost one. 
3. I dunno yet. I need to be able to clear the symbols as you play and your lives if you lose one to update it.
4. I think for now one per correct you can expand if you need more.
5. Colours I think, just colour each rune a different colour and associate it with the button colours.
6. Not sure, The timer is simple enough but a loading bar to see it going down I don't know how to implement it
7. I think I just have a rules menu, explain the colour association and explain the bomb if I add it.

---------------------------------PLAN---------------------------------
Base Functionality
1. Draw out symbols and lives and add them + 
2. Figure out how to randomly pick a symbol +
3. Detect whether they picked the right one or not +
4. If they get it right give them a point, if not lose a life +
5. If lives go to zero go to end screen +
6. Display final score and keep the retry and main menu buttons + 

Additional
1. Figure out bomb timer
2. Figure out how to get the timer to go back up
3. Figure out how to display bomb
4. Lose remaining if you run out of bomb time
*/