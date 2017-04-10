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
  /* First, check if it is a tin or pop can */

  
  /*
  if (0 == 0){ // This might be wrong - assuming B1 is connected to
                            // a switch that is 1 when it is a tin can
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
*/
  
  if (0 == 0) {
    for (int i = 0; i < 10000; i++) { // Check a bunch of times, see if MAX is FF
      
      readADC(1); // Channel 0 for label detector?
      if (ADRESH > H_max) {
        H_max = ADRESH;
      }
      if (ADRESH > 30){
          return POP_TAB;
      }
    }
    if (H_max >= 0xA0) { // Is this the max?
      return POP_TAB;
    } else {
      return POP_NOTAB;
    }
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