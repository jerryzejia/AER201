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
    ADCON0 = 0x00;
    ADCON0 = (ADCON0 & 0X3C)|((channel & 0x0F)<<2);
    ADON = 1;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO_NOT_DONE){
    }

}

int sense_can() {

  int H_max = 0;
  int cansize = 0; // 0 is tin, 1 is pop
  int conductOnFall = 0;
  /* First, check if it is a tin or pop can */

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
      readADC(0); // Channel 0 for label detector?
      if (ADRESH > H_max) {
        H_max = ADRESH;
      }
      
      if (ADRESH > 30){
          return TIN_NOLAB;
      }
    }
     
    if (H_max >= 0xA0) { // Is this the max?
      return TIN_NOLAB;
    } else {
      return TIN_LAB;
    }
  }

  /* POP CAN SORTING AREA */
  else{
    
    /* see if the first time the solenoid pushes works */
    for (int i = 0; i < 10000; i++) {
      
      readADC(1);
      if (ADRESH > H_max) {
        H_max = ADRESH;
      }
      if (ADRESH > 30){
          return POP_NOTAB;
      }
    }
    if (H_max >= 0xA0) {
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
          return POP_NOTAB;
      }
    }
    if (H_max >= 0xA0) { // Is this the max?
      return POP_NOTAB;
    }
  
    /* if it never conducts, then it has a tab */
    else {
      return POP_TAB;
    }
    
  // WARNING: this method is poop if you can get a false positive on conductivity if there is a tab
  // So, hardware must make sure that tab NEVER conducts.
  }
}

int readLightSensor(){
   int H_max = 0;
    int i = 0;
    while(i < 50){
        __lcd_home();
        //int i = readLightSensor();
        readADC(2);
        if (ADRESH > H_max) {
            H_max = ADRESH;
        }
        if (ADRESH < 0x20){
            return 1;
        }
        printf("%x", ADRESH);
        __delay_ms(5);
        i++;
    }
    
    if(H_max >= 0x20){
        return 0;
    }
    else{
        return 1;
 
    }
}