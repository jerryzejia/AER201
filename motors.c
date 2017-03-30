/*
 * File:   motord.c
 * Author: jerry
 *
 * Created on March 1, 2017, 3:58 PM
 */


#include <xc.h>
#include "motors.h"

void setMotor(int motorID, int direction, int speed){
    
    switch(motorID)
            case ARML:
                if (direction == RIGHT){
                    set_PWM1_duty(speed);
                    
                }
                if (direction == LEFT){
                    
                }
                break;
                
            case ARMR:
                if (direction == RIGHT){
                    
                }
                if (direction == LEFT){
                    
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