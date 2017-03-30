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
#include <stdio.h>
#include <xc.h>
extern char mode;
const char keys[] = "123A456B789C*0#D";
extern unsigned char start_time[7];
extern unsigned char end_time[7];
extern unsigned char passed_time; 

void interrupt interrupt_handler(void) {
  if (INT1IF) {
    __lcd_newline();
    unsigned char keypress = (PORTB & 0xF0) >> 4;
    putch(keys[keypress]);
    if (mode == 2) { // get operation time
      get_time(end_time);
      passed_time = 
             (end_time[1] - start_time[1]) * 60 + (end_time[0] - start_time[0]);
      mode = 3;
       
        
        
    } else if (keypress == 0x0) { // display time
      if (mode == 0) {
        mode = 1;
      }

    } else if (keypress == 0x3) { // sort
      if (mode == 0) {
        mode = 2;
      }
    }

    else if (keypress == 0x1) { // back
      mode = 0;
    
    }else if (keypress == 0x2) {
      mode = 99;
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

