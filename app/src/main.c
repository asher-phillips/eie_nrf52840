/**
 * @file main.c
 */


//Get libraries
#include <inttypes.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "BTN.h"
#include "LED.h"

//Define macro
#define SLEEP_MS 1

int main(void) {
  //If initializing leds and buttons doesn't work return 0
  if(0 > LED_init()) {
    return 0;
  }
  if(0 > BTN_init()) {
    return 0;
  }

  //Create a variable for the duty cycle and start LED0 with the varrying duty cycle
  uint8_t duty_cycle = 0;
  LED_pwm(LED0, duty_cycle);

  //Infinite loop
  while(1) {
    //If the button is clicked
    if(BTN_check_clear_pressed(BTN0)) {
      //If the duty cycle is 100 don't do anything, if not add 10 to the duty cycle
      duty_cycle = (duty_cycle >= 100) ? 0 : (duty_cycle + 10);
      //Update with the new brightness level
      printk("Setting LED0 to %d%% brightness.\n", duty_cycle);
      //Reset the LED level
      LED_pwm(LED0, duty_cycle);
    }
    //Wait for 1 MS
    k_msleep(SLEEP_MS);
  }
  return 0;
}

