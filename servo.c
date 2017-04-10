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
  if( dir == NEUTRAL){ 
    for (i = 0; i < 10; i++) {
        LATEbits.LATE0 = 1;
        __delay_ms(1.5);

        LATEbits.LATE0 = 0;
        __delay_ms(18.5);
    }    
  }
  else if(dir == RIGHT){
      for (i = 0; i < 10; i++) {
        LATEbits.LATE0 = 1;
        __delay_ms(3.5);

        LATEbits.LATE0 = 0;
        __delay_ms(16.5);
    }
  }
  else if (dir == LEFT){
      for (i = 0; i < 10; i++) {
        LATEbits.LATE0 = 1;
        __delay_ms(0.15);

        LATEbits.LATE0 = 0;
        __delay_ms(19.85);
    }
  }
}

void side_servo_control(int dir){
  int i;
  if( dir == NEUTRAL){ 
    for (i = 0; i < 10; i++) {
        LATAbits.LATA3 = 1;
        __delay_ms(1.5);

        LATAbits.LATA3 = 0;
        __delay_ms(18.5);
    }    
  }
  else if(dir == RIGHT){
      for (i = 0; i < 10; i++) {
        LATAbits.LATA3 = 1;
        __delay_ms(2);

        LATAbits.LATA3 = 0;
        __delay_ms(118);
    }
  }
  else if (dir == LEFT){
      for (i = 0; i < 10; i++) {
        LATAbits.LATA3 = 1;
        __delay_ms(1.3);

        LATAbits.LATA3 = 0;
        __delay_ms(18.7);
    }
  }
}

void move_can(int canType){
    if(canType == TIN_NOLAB){
        side_servo_control(RIGHT);
        __delay_ms(2000);
        
        for (int i = 0; i<5; i++){        //do the loop to keep main servo angled
            side_servo_control(RIGHT);
            main_servo_control(RIGHT);
            __delay_ms(10);
        }
        
        main_servo_control(NEUTRAL);
        side_servo_control(NEUTRAL);
    }
    else if(canType == TIN_LAB){
        side_servo_control(LEFT);
        __delay_ms(2000);

        for (int i = 0; i<5; i++){        //do the loop to keep main servo angled
            side_servo_control(LEFT);
            main_servo_control(RIGHT);
            __delay_ms(10);
        }
        
        
        main_servo_control(NEUTRAL);
        side_servo_control(NEUTRAL);

    }
    else if (canType == POP_TAB){
       
        side_servo_control(LEFT);
         __delay_ms(2000);
         for (int i = 0; i<5; i++){        //do the loop to keep main servo angled
            side_servo_control(LEFT);
             main_servo_control(LEFT);
            __delay_ms(10);
        }
        main_servo_control(NEUTRAL);
        side_servo_control(NEUTRAL);
    }
    else if(canType == POP_NOTAB){
        side_servo_control(RIGHT);
        __delay_ms(2000);
         for (int i = 0; i<5; i++){        //do the loop to keep main servo angled
            side_servo_control(RIGHT);
             main_servo_control(LEFT);
            __delay_ms(10);
        }
        main_servo_control(NEUTRAL);
        side_servo_control(NEUTRAL);
    }
}

void gate(){
    int i;
    while(PORTBbits.RB3 == 1) {
        LATCbits.LATC2 = 1;
        __delay_ms(1.68);
        LATCbits.LATC2 = 0;
        __delay_ms(18.32);
            
    }
    while(PORTBbits.RB3 != 1){
            LATCbits.LATC2 = 1;
            __delay_ms(1.68);

            LATCbits.LATC2 = 0;
            __delay_ms(18.32);
        }
    
    
        
}

