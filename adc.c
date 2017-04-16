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
  int cansize = 0; // 0 is tin, 1 is pop
  int conductOnFall = 0;
  /* First, check if it is a tin or pop can */

<<<<<<< HEAD
<<<<<<< HEAD
  /* But before, we want to see if the can triggers the sensor as it falls
     Do this because sometimes the fall gives conductivity on the no label 
     but sometimes it doesn't work as it's sitting there    */
  for (int i = 0; i < 10000; i++) { 
      readADC(0);
      if (ADRESH > H_max) {
        H_max = ADRESH;
      }
      
      if (ADRESH > 30){
          conductOnFall = 1;
      }
      
       if (H_max >= 0xA0) { 
          conductOnFall = 1;
    }
    }
  
  // Now, check the switch to see the size of the can
  __delay_ms(100);
  if (PORTBbits.RB0 == 1){
      cansize = 0;
  }
  else {
      cansize = 1;
  }
  
  LATDbits.LATD0 = 0;
  main_servo_control(NEUTRAL);
  side_servo_control(NEUTRAL);
  __delay_ms(500);
  main_servo_control(NEUTRAL);
  side_servo_control(NEUTRAL);
  LATDbits.LATD0 = 1;
  
  /* TIN CAN SORTING AREA */
  if (cansize == 0){ 
      
    /*so, here's the sensing that was done before we checked the switch 
      if the can is a tin can, and it did trigger it as it fell, we know
      it has no label*/
      if (conductOnFall){
          return TIN_NOLAB;
      }
      
    for (int i = 0; i < 10000; i++) { // Check a bunch of times, see if MAX is FF
=======
  if (PORTBbits.RB0 == 1){ // This might be wrong - assuming B1 is connected to
=======
  if (PORTBbits.RB0 == 1) { // This might be wrong - assuming B1 is connected to
>>>>>>> parent of 567e986... .
                            // a switch that is 1 when it is a tin can
                            /* TIN CAN */
    for (int i = 0; i < 100; i++) { // Check a bunch of times, see if MAX is FF
      /* Read ADC */
>>>>>>> parent of ff33206... 。
      readADC(0); // Channel 0 for label detector?
      if (ADRESH > H_max) {
        H_max = ADRESH;
      }
<<<<<<< HEAD
      
      if (ADRESH > 30){
          count(TIN_NOLAB);
          return TIN_NOLAB;
      }
    }
     
    if (H_max >= 0xA0) { // Is this the max?
        count(TIN_NOLAB);
      return TIN_NOLAB;
    } else {
      count(TIN_LAB);
=======
    }

    if (H_max == 0xFF) { // Is this the max?
      /* No Label */
      return TIN_NOLAB;
    } else {
      /* Label */
>>>>>>> parent of ff33206... 。
      return TIN_LAB;
    }
  }

<<<<<<< HEAD
  /* POP CAN SORTING AREA */
  else{
    
    /* see if the first time the solenoid pushes works */
    for (int i = 0; i < 10000; i++) {
      
      readADC(1);
      if (ADRESH > H_max) {
        H_max = ADRESH;
      }
      if (ADRESH > 30){
          count(POP_NOTAB);
          return POP_NOTAB;
      }
    }
    if (H_max >= 0xA0) {
      count(POP_NOTAB);
      return POP_NOTAB;
    }
    
    
  /* push solenoid again */  
  LATDbits.LATD0 = 0;
  main_servo_control(NEUTRAL);
  side_servo_control(NEUTRAL);
  __delay_ms(500);
  main_servo_control(NEUTRAL);
  side_servo_control(NEUTRAL);

  LATDbits.LATD0 = 1;
  
  /* second time test */
  for (int i = 0; i < 10000; i++) {
      
      readADC(1);
      if (ADRESH > H_max) {
        H_max = ADRESH;
      }
      if (ADRESH > 30){
          count(POP_NOTAB);
          return POP_NOTAB;
      }
    }
    if (H_max >= 0xA0) { // Is this the max?
          count(POP_NOTAB);
      return POP_NOTAB;
    }
  
    /* if it never conducts, then it has a tab */
    else {
        count(POP_TAB);
      return POP_TAB;
    }
    
  // WARNING: this method is poop if you can get a false positive on conductivity if there is a tab
  // So, hardware must make sure that tab NEVER conducts.
=======
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
>>>>>>> parent of ff33206... 。
  }
}

int canOn(){
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