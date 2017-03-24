/*
 * File:   servo.c
 * Author: jerryjia
 *
 * Created on March 24, 2017, 2:53 PM
 */
#include <xc.h>
#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "pwm.h"
#include "function.h"
#include <stdio.h>
#include <xc.h>

void main_servo_control(int dir){
  int i;
  if( dir == 0){ 
    for (i = 0; i < 500; i++) {
        LATAbits.LATA2 = 1;
        __delay_ms(1);

        LATAbits.LATA2 = 0;
        __delay_ms(19);
    }    
  }
  else if(dir == 1){
      for (i = 0; i < 500; i++) {
        LATAbits.LATA2 = 1;
        __delay_ms(2.5);

        LATAbits.LATA2 = 0;
        __delay_ms(17.5);
    }
  }
  else if (dir == 2){
      for (i = 0; i < 500; i++) {
        LATAbits.LATA2 = 1;
        __delay_ms(0.4);

        LATAbits.LATA2 = 0;
        __delay_ms(19.6);
    }
  }
}

void side_servo_control(int dir){
  int i;
  if( dir == 0){ 
    for (i = 0; i < 500; i++) {
        LATAbits.LATA3 = 1;
        __delay_ms(1);

        LATAbits.LATA3 = 0;
        __delay_ms(19);
    }    
  }
  else if(dir == 1){
      for (i = 0; i < 500; i++) {
        LATAbits.LATA3 = 1;
        __delay_ms(2.5);

        LATAbits.LATA3 = 0;
        __delay_ms(17.5);
    }
  }
  else if (dir == 2){
      for (i = 0; i < 500; i++) {
        LATAbits.LATA3 = 1;
        __delay_ms(0.4);

        LATAbits.LATA3 = 0;
        __delay_ms(19.6);
    }
  }
}