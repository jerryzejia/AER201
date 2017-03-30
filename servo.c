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
    for (i = 0; i < 10; i++) {
        LATAbits.LATA2 = 1;
        __delay_ms(1);

        LATAbits.LATA2 = 0;
        __delay_ms(19);
    }    
  }
  else if(dir == 1){
      for (i = 0; i < 10; i++) {
        LATAbits.LATA2 = 1;
        __delay_ms(2.5);

        LATAbits.LATA2 = 0;
        __delay_ms(17.5);
    }
  }
  else if (dir == 2){
      for (i = 0; i < 10; i++) {
        LATAbits.LATA2 = 1;
        __delay_ms(1);

        LATAbits.LATA2 = 0;
        __delay_ms(19);
    }
  }
}

void side_servo_control(int dir){
  int i;
  if( dir == 0){ 
    for (i = 0; i < 10; i++) {
        LATAbits.LATA3 = 1;
        __delay_ms(1);

        LATAbits.LATA3 = 0;
        __delay_ms(19);
    }    
  }
  else if(dir == 1){
      for (i = 0; i < 10; i++) {
        LATAbits.LATA3 = 1;
        __delay_ms(2);

        LATAbits.LATA3 = 0;
        __delay_ms(18);
    }
  }
  else if (dir == 2){
      for (i = 0; i < 10; i++) {
        LATAbits.LATA3 = 1;
        __delay_ms(0.5);

        LATAbits.LATA3 = 0;
        __delay_ms(19.5);
    }
  }
}

void move_can(int canType){
    if(canType == 1){
        side_servo_control(RIGHT);
        main_servo_control(RIGHT);
        main_servo_control(NEUTRAL);
        side_servo_control(NEUTRAL);
    }
    else if(canType == 2){
        side_servo_control(LEFT);
        main_servo_control(RIGHT);
        main_servo_control(NEUTRAL);
        side_servo_control(NEUTRAL);

    }
    else if (canType == 3){
        main_servo_control(LEFT);
        side_servo_control(LEFT);
        main_servo_control(NEUTRAL);
        side_servo_control(NEUTRAL);
    }
    else{
        side_servo_control(RIGHT);
        main_servo_control(LEFT);
        main_servo_control(NEUTRAL);
        side_servo_control(NEUTRAL);
    }
}

void gate(){
    int i;
    for (i = 0; i < 20; i++) {
        if(PORTBbits.RB3 == 1){
                LATCbits.LATC2 = 1;
                __delay_ms(1.67);
                LATCbits.LATC2 = 0;
                __delay_ms(18.33);
            
        }
        else{
            LATCbits.LATC2 = 1;
            __delay_ms(1.68);

            LATCbits.LATC2 = 0;
            __delay_ms(18.32);
        }
    }
    
        
}

