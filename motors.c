/*
 * File:   motord.c
 * Author: jerry
 *
 * Created on March 1, 2017, 3:58 PM
 */


#include <xc.h>
#include "motors.h"
#include "pwm.h"
void setMotor(int motorID, int direction, int speed){

    switch(motorID){
            case ARML:
                if (direction == RIGHT){
                    LATAbits.LA4 = 1;
                    set_PWM1_duty(speed);
                    LATAbits.LA3 = 0;
                }
                if (direction == LEFT){
                    LATAbits.LA4 = 1;
                    set_PWM1_duty(1024 - speed);
                    LATAbits.LA3 = 1;
                }
                if (direction == STOP){
                    set_PWM1_duty(0);
                    LATAbits.LA4 = 0;
                }
                break;

            case ARMR:
                if (direction == RIGHT){
                    LATCbits.LC0 = 1;
                    set_PWM1_duty(speed);
                    LATCbits.LC1 = 0;
                }
                if (direction == LEFT){
                    LATCbits.LC0 = 1;
                    set_PWM1_duty(1024 - speed);
                    LATCbits.LC1 = 1;
                }
                if (direction == STOP){
                    set_PWM1_duty(0);
                    LATCbits.LC0 = 0;
                }
                break;

            case LOAD:

                break;

            case GATE:
                if (direction == RIGHT){

                }
                if (direction == LEFT){

                }
                break;

            case OUT:
                if (direction == RIGHT){

                }
                if (direction == LEFT){

                }
                break;
    }

}
