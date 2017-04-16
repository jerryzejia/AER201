#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "macros.h"
#include "pwm.h"
#include <stdio.h>
#include <xc.h>

void set_time(void);
void get_time(unsigned char *);
void startMotor(int dir);
void stopMotor(void);
void readADC(char channel);
void motorMove(unsigned char *);
void move_can(int can_type);
int sense_can();
void delay_ms(unsigned int milliseconds);
void servo_control();
