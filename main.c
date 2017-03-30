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

extern char mode;
extern unsigned char start_time[7];
extern unsigned char end_time[7];
extern unsigned char passed_time; 

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

    else if (mode == 99) {
      debug();
    }
  }
  return;
}