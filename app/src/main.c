/*
 * main.c
 */

#include <zephyr/kernel.h>

#include "BTN.h"
#include "LED.h"

#define SLEEP_MS 1
#define VAL_LO 0
#define VAL_HI 16

int main(void)
{
  uint8_t count = VAL_LO;
  if(BTN_init() < 0)
  {
    return 0;
  }
  if(LED_init() < 0)
  {
    return 0;
  }

  while(1)
  {
    if(BTN_check_clear_pressed(BTN0))
    {
      count++;
    }
    if((count & 0x1) == 0x1)
    {
      LED_set(LED0,1);
    }
    else
    {
      LED_set(LED0, 0);
    }
    if((count & 0x2) == 0x2)
    {
      LED_set(LED1,1);
    }
    else
    {
      LED_set(LED1, 0);
    }
    if((count & 0x4) == 0x4)
    {
      LED_set(LED2,1);
    }
    else
    {
      LED_set(LED2, 0);
    }
    if((count & 0x8) == 0x8)
    {
      LED_set(LED3,1);
    }
    else
    {
      LED_set(LED3, 0);
    }
    if(count >= 15)
    {
      count = 0;
    }
  }
  return 0;
}



//Better solution with shifting! Good to remember actually
//If you need to check a bit, shift it to the lsb and and
//it with 1. That way you know if that bit is high or not
//Can also just use a for loop to iterate over the possible
//bits

/*
int main(void)
{
  uint8_t count = VAL_LO;
  if(BTN_init() < 0)
  {
    return 0;
  }
  if(LED_init() < 0)
  {
    return 0;
  }

  while(1)
  {
    if(BTN_check_clear_pressed(BTN0))
    {
      count = count & 0xF;  // Auto-wrap at   15
    }
    
//Here's the juicy part, for every bit check whether it's 
//high or low using a shift. 
//Let's do an example, if count is 12 bits 3 and 2 are high
//In binary 1010. So in this algorithm, we have
//For i=0, count >> 0 results in 1010 & 0x1 = 0
//Meaning LSB is low
//For i=1, count >> 1 results in  0101 & 0x1 = 1
//Meaning bit 1 is high
//For i=2, count >> 2 results in 0010 & 0x1 = 0
//Meaning bit 2 is low
//For i=3, count >> 3 results in 0001 & 0x1 = 1
//Meaning MSB is high!

//Essentiallly all you're doing is moving the bit you want
//to be the lsb and checking if it's high or not!
    for(int i = 0; i < 4; i++)
    {
      LED_set(i, (count >> i) & 0x1);
    }
    
    k_msleep(SLEEP_MS);
  }
  return 0;
}
*/

