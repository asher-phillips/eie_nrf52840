//Main gameplay file :)
#include <zephyr/kernel.h>  //Core Zephyr OS files
#include <zephyr/smf.h>     
#include <lvgl.h>           //Screen library
#include <game_sm.h>        //Include my sm header file

//Defines
#define ONE_SECOND 1000        //1 second

//State Functions :)
static void mm_entry(void *o);
static void mm_run(void *o);
static void gp_entry(void *o);
static void gp_run(void *o);
static void s_entry(void *o);
static void s_run(void *o);

//Make life easier functions :)
static void button(lv_align_t AS, int x, int y, const char *name, lv_event_cb_t callback, uint32_t colour);
static void clear(void);
static void label(const char *name, lv_align_t AS, int x, int y, uint32_t colour);

//Define the states, takes in entry, run, exit, parent and initial
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

/*-------------------------------------RUNNING STATES----------------------------------------------*/
static void mm_entry(void *o) {
    //Clear the screen
    //Add a button in for starting the game

    //Clear
    clear();
    
    //Create the button
    button(LV_ALIGN_CENTER, 0, 0, "START", start_cb, 0x00FF00);
}

static void mm_run(void *o) {
    //This gets called every tick while you're in this state
    //Empty for now
}

static void gp_entry(void *o) {
    //Clear the screen
    //Add Gameplay label
    //Start the timer of the song

    //Clear the screen
    clear();

    //Create gameplay label
    label("GAMEPLAY", LV_ALIGN_TOP_MID, 0, 0, 0x000000);

    //Start the clock
    ctx.song_start_ms = k_uptime_get_32();  
}

static void gp_run(void *o) {
    //This gets called every tick while you're in this state
    //Check how long it's been
    uint32_t elapsed = k_uptime_get_32() - ctx.song_start_ms;
    if(elapsed >= 5 * ONE_SECOND) {
        smf_set_state(SMF_CTX(&ctx), &states[STATE_S]);
    }
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
}

static void s_run(void *o) {
    //This gets called every tick while you're in this state
    //Emtpy for now
}




/*-----------------------------------------------EASY FUNCTIONS :)---------------------------------------------------------*/


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
static void label(const char *name, lv_align_t AS, int x, int y, uint32_t colour) {
    lv_obj_t *label = lv_label_create(lv_screen_active());                                                          //Create a label
    lv_label_set_text(label, name);                                                                           //Set the text of the label                                 
    lv_obj_align(label, AS, x, y); 
    lv_obj_set_style_text_color(label, lv_color_hex(colour), LV_STATE_DEFAULT);  // white text
}

//Clear Screen :)
static void clear(void) {
    lv_obj_clean(lv_screen_active()); 
}