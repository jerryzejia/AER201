/*
 * File:   interrupt.c
 * Author: jerryjia
 *
 * Created on March 27, 2017, 8:22 PM
 */


#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "pwm.h"
#include "function.h"
#include "macros.h"
#include <stdio.h>
#include <xc.h>
extern char mode;
const char keys[] = "123A456B789C*0#D";
extern unsigned char start_time[7];
extern unsigned char end_time[7];
extern unsigned int passed_time; 
extern int displayFlag;
void interrupt interrupt_handler(void) {
   /* 1 = display current time (0x0)
    * 2 = go back to main menu (0x01)
    * 3 = debugging mode (0x02)
    * A = start to sort (0x03) 
    * Once in sorting mode press 1/2/A to quit.
    */
  if (INT1IF) {
    __lcd_newline();
    unsigned char keypress = (PORTB & 0xF0) >> 4;
    putch(keys[keypress]);
    /* mode = 0 : Welcome Screen
     * mode = 1 : Display Time
     * mode = 2 : Sort Mode
     * mode = 3 : Display_Sorting_Time
     * mode = 4 : Debugging Mode
     */
    if (mode == 2) { // get operation time
        mode = 3;
    } else if (keypress == 0x0) { // display time
      if (mode == 0) {
        mode = 1;
      }
    } else if (keypress == 0x3) { // sort
<<<<<<< HEAD
        get_time(start_time);
=======
      if (mode == 0) {
>>>>>>> parent of ff33206... 。
        mode = 2;
    }
    else if (keypress == 0x1) { // back
      mode = 0;
    }else if (keypress == 0x2) {
      mode = 4;
    }
    

  }
  INT1IF = 0; // Clear flag bit
  
  
  
  
  /*if(TMR0IF){
        TMR0IF = 0;
        if(mode == 2){
            getSortTime();
            // Initialize timer again!
            TMR0H = 0b10000101;
            TMR0L = 0b11101110;
            TMR0ON = 1;
        }
    }

   */ 
  
  
  
}

