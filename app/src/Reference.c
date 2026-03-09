/*-----------------HOW TO USE STUFF----------------------*/

/*---------If you want to make a button :)
    lv_obj_t *ui_btn = lv_button_create(screen);                                                        //Creates the button
    lv_obj_align(object you're setting(ui_bt), Anchor point(LV_ALIGN_CENTER), x_offset, y_offset));     //Determines where it is
    lv_obj_t *button_label = lv_label_create(ui_btn);                                                   //Creates a text label that is a child of the button
    char label_text[10];                                                                                //Create the name of the button
    snprintf(label_text, 10, "MESSAGE");                                                                //Print the label, number is max size of buffer
    lv_label_set_text(button_label, label_text);                                                        //Label the button
    lv_obj_align(button_label, LV_ALIGN_CENTER, 0,0);                                                   //Align the text on the button (what are the parameters)

    led_id led = (led_id)i;                                                                             //Data you want to pass into the callback
    lv_obj_t *data_obj = lv_data_obj_create_alloc_assign(ui_btn, &led, sizeof(led_id));                 //Safely attach that data to the button object
    lv_obj_add_event_cb(ui_btn, lv_button_callback, LV_EVENT_CLICKED, data_obj);                        //When this button is clicked call lv_button_callback and pass it data_obj

  display_blanking_off(display_dev);                                                                    //Display blank off so you can see stuff

/*---------If you want just text to appear :)
    lv_obj_t *label = lv_label_create(screen);                                                          //Create a label
    lv_label_set_text(label, "YOUR MESSAGE");                                                           //Set the text of the label
    display_blanking_off(display_dev);                                                                  //Display the message                                                                               
*/

/*---------If you want to move something :)
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);                                                         // dead center
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);                                                       // top center, 20px down
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -20);                                                   // bottom center, 20px up
*/


/*----------Update the screen :)
while(1) {
    lv_timer_handler();                                                                                 //lls LVGL to process any pending events and redraw anything that changed                                                              
    k_msleep(SLEEP_MS);                                                                                 // wait 100ms before doing it again - this is your tick rate
  }
  return 0;
*/

/*---------If you want to clear the screen
    lv_obj_clean(lv_screen_active()); //Clear the screen
*/

