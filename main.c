/*
 * File:   main.c
 * Author: True Administrator
 *
 * Created on July 18, 2016, 12:11 PM
 */
#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "pwm.h"
#include "function.h"
#include <stdio.h>
#include <xc.h>
unsigned char mode = 0;
extern unsigned char start_time[7];
extern unsigned char end_time[7];
extern unsigned char passed_time; 
const char keys[] = "123A456B789C*0#D";


void interrupt keypressed(void) {
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
}


void main(void) {
  
    
  initPIC();
  while (1) {
    if (mode == 0) {
      welcome();

    } else if (mode == 1) {
      display_time();
    }

    else if (mode == 2) {
      sort();
    }

    else if (mode == 3) {
      display_sorting_time();
    }

    else if (mode == 4) {
      debug();
    }
  }
  return;
}