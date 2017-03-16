#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "macros.h"
#include "pwm.h"
#include <stdio.h>
#include <xc.h>

void delay_ms(float milliseconds) {
  _delay((unsigned long)((x) * (_XTAL_FREQ / 4000.0)));
}

void main_servo_control(int uptime, int downtime) {
  int i;
  for (i = 0; i < 500; i++) {
    LATAbits.LATA2 = 1;
    delay_ms(uptime);

    LATAbits.LATA2 = 0;
    delay_ms(downtime);
  }
}

void side_servo_control(int uptime, int downtime) {
  int i;
  for (i = 0; i < 500; i++) {
    LATAbits.LATA3 = 1;
    delay_ms(uptime);

    LATAbits.LATA3 = 0;
    delay_ms(downtime);
  }
}
