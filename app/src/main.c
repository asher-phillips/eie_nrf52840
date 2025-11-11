/*
    main.c
*/

#include <zephyr/kernel.h>          //Provides general functions (I think the equivalent of stdio.h)
#include <zephyr/drivers/gpio.h>    //Includes GPIO functions

#define LED0_NODE DT_ALIAS(led0)    //Creates a macro that gets the device tree node for LED0. DT_ALIAS(led0) looks up teh "led0" alias in the device tree config
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)    
#define LED3_NODE DT_ALIAS(led3)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios); //Creates a GPIO specification struct for LED0. Contains the port, pin number and flags needed to control this LED. GPIO_DT_SPEC_GET extracs the info from the device tree node
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

int main(void)                      //Main function
{
    int ret0;                        //Define a variable
    int ret1;
    int ret2;
    int ret3;

    if(!gpio_is_ready_dt(&led0) || !gpio_is_ready_dt(&led1)|| !gpio_is_ready_dt(&led2)|| !gpio_is_ready_dt(&led3))    //Check if the gpio port is ready to use for led0, returns a 0 if not ready (i.e. checking for if it's ready or not, if not return -1)
    {
        return -1;
    }

    ret0 = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);     //Configures the led0 to be high (active low led) so it sets it off to begin with
    ret1 = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    ret2 = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
    ret3 = gpio_pin_configure_dt(&led3, GPIO_OUTPUT_ACTIVE);

    if (ret0 < 0)                    //If the value is negative return the issue
    {
        return ret0;
    }

    else if(ret1 < 0)
    {
        return ret1;
    }

    else if(ret2 < 0)
    {
        return ret2;
    }

    else if(ret3 < 0)
    {
        return ret3;
    }

    while(1)                        //While in main toggle the led off and on(too fast for human perception, so get the led to sleep for 1s between)
    {   
        //gpio_pin_toggle_dt(&led0);

        gpio_pin_set_dt(&led0, 1);
        gpio_pin_set_dt(&led1, 0);
        gpio_pin_set_dt(&led2, 0);
        gpio_pin_set_dt(&led3, 0);
        k_msleep(500);
        
        gpio_pin_set_dt(&led0, 0);
        gpio_pin_set_dt(&led1, 1);
        gpio_pin_set_dt(&led2, 0);
        gpio_pin_set_dt(&led3, 0);
        k_msleep(500);

        gpio_pin_set_dt(&led0, 0);
        gpio_pin_set_dt(&led1, 0);
        gpio_pin_set_dt(&led2, 1);
        gpio_pin_set_dt(&led3, 0);
        k_msleep(500);

        gpio_pin_set_dt(&led0, 0);
        gpio_pin_set_dt(&led1, 0);
        gpio_pin_set_dt(&led2, 0);
        gpio_pin_set_dt(&led3, 1);
        k_msleep(500);
    }

    return 0;
}


