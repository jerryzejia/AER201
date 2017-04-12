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
<<<<<<< HEAD
        LATEbits.LATE0 = 1;
        __delay_ms(3.5);

        LATEbits.LATE0 = 0;
        __delay_ms(16.5);
=======
        LATAbits.LATA2 = 1;
        __delay_ms(2.5);

        LATAbits.LATA2 = 0;
        __delay_ms(17.5);
>>>>>>> parent of ff33206... 。
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
<<<<<<< HEAD
        __delay_ms(2000);
        
        for (int i = 0; i<5; i++){        //do the loop to keep main servo angled
            side_servo_control(RIGHT);
            main_servo_control(RIGHT);
            __delay_ms(10);
        }
        
=======
        main_servo_control(RIGHT);
>>>>>>> parent of ff33206... 。
        main_servo_control(NEUTRAL);
        side_servo_control(NEUTRAL);
    }
    else if(canType == 2){
        side_servo_control(LEFT);
<<<<<<< HEAD
        __delay_ms(2000);

        for (int i = 0; i<5; i++){        //do the loop to keep main servo angled
            side_servo_control(LEFT);
            main_servo_control(RIGHT);
            __delay_ms(10);
        }
        
        
=======
        main_servo_control(RIGHT);
>>>>>>> parent of ff33206... 。
        main_servo_control(NEUTRAL);
        side_servo_control(NEUTRAL);

    }
<<<<<<< HEAD
    else if (canType == POP_TAB){
       
        side_servo_control(LEFT);
         __delay_ms(2000);
         for (int i = 0; i<5; i++){        //do the loop to keep main servo angled
            side_servo_control(LEFT);
             main_servo_control(LEFT);
            __delay_ms(10);
        }
=======
    else if (canType == 3){
        main_servo_control(LEFT);
        side_servo_control(LEFT);
>>>>>>> parent of ff33206... 。
        main_servo_control(NEUTRAL);
        side_servo_control(NEUTRAL);
    }
    else{
        side_servo_control(RIGHT);
<<<<<<< HEAD
        __delay_ms(2000);
         for (int i = 0; i<5; i++){        //do the loop to keep main servo angled
            side_servo_control(RIGHT);
             main_servo_control(LEFT);
            __delay_ms(10);
        }
=======
        main_servo_control(LEFT);
>>>>>>> parent of ff33206... 。
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

