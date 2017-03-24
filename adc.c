/*
 * File:   adc.c
 * Author: jerry
 *
 * Created on February 28, 2017, 10:05 PM
 */

#include<xc.h>
#include <stdio.h>
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "I2C.h"
#include "macros.h"
#include "function.h"



//Channel 0 = RA0
//Channel 1 = RA1
//Channel 2 = RA2
void readADC(char channel){
    ADCON0 = (ADCON0 & 0X3C)|((channel & 0x0F)<<2);
    ADON = 1;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO_NOT_DONE){
    }

}

void move_can(int can_type) {
 /*
  count++;
  int i = 0;
  if (can_type == POP_TAB) {
    tapPop++;
    main_servo_control(2,18);
    side_servo_control(1,19); 
  } else if (can_type == POP_NOTAB) {
    noTapCan++;
    main_servo_control(2,18);
    side_servo_control(2,18); 

  } else if (can_type == TIN_NOLAB) {
    noLabelSoup++;
    main_servo_control(1,19);
    side_servo_control(1,19); 

  } else if (can_type == TIN_LAB) {
    labelSoup++;
    main_servo_control(1,19);
    side_servo_control(2,18); 

  }
  * */
  return;
}

int sense_can() {

  int H_max = 0;
  /* First, check if it is a tin or pop can */

  if (PORTBbits.RB0 == 1) { // This might be wrong - assuming B1 is connected to
                            // a switch that is 1 when it is a tin can
                            /* TIN CAN */
    for (int i = 0; i < 100; i++) { // Check a bunch of times, see if MAX is FF
      /* Read ADC */
      readADC(0); // Channel 0 for label detector?
      if (ADRESH > H_max) {
        H_max = ADRESH;
      }
    }

    if (H_max == 0xFF) { // Is this the max?
      /* No Label */
      return TIN_NOLAB;
    } else {
      /* Label */
      return TIN_LAB;
    }
  }

  else {
    for (int i = 0; i < 100; i++) { // Check a bunch of times, see if MAX is FF
      /* Read ADC */
      readADC(1); // Channel 0 for label detector?
      if (ADRESH > H_max) {
        H_max = ADRESH;
      }
    }
    if (H_max == 0xFF) { // Is this the max?
      /* Tab */
      return POP_TAB;
    } else {
      /* No Tab */
      return POP_NOTAB;
    }
  }
}

int canON(){
    int H_max = 0; 
    for (int i = 0; i < 100; i++) { // Check a bunch of times, see if MAX is FF
        if (ADRESH > H_max) {
            H_max = ADRESH;
      }
    }
    if(H_max > 0xC00){
        return 1; 
    }
    else{
        return 0;
    }
}