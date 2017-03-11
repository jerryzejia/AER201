/*
 * File:   main.c
 * Author: True Administrator
 *
 * Created on July 18, 2016, 12:11 PM
 */
#include <xc.h>
#include <stdio.h>
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "I2C.h"
#include "pwm.h"



#define __delay_1s() for(char i=0;i<100;i++){__delay_ms(10);}
#define __lcd_newline() lcdInst(0b11000000);
#define __lcd_clear() lcdInst(0x01);
#define __lcd_home() lcdInst(0b10000000);
#define LCD_LINE_1_ADDRESS 0x00
#define LCD_LINE_2_ADDRESS 0x20
#define LCD_LINE_3_ADDRESS lcdInst(11000000)
#define LCD_LINE_4_ADDRESS 0x60





void set_time(void);
void get_time(unsigned char *);
void startMotor(int dir);
void stopMotor(void);
void readADC(char channel);
void motorMove(unsigned char *);
void sort(int tap, int noLabel, int tin);

const char timeSetter[7] = {  0x00, // Seconds
                        0x19, // Minutes
                        0x15, // hour mode, set to 23:00
                        0x04, //Wednesday
                        0x25, //25th
                        0x01, //January
                        0x17  //2017
                      };
unsigned char mode = 0; // Variable that tells what message should be displayed on the lcd
unsigned char start_time[7];
unsigned char end_time[7];
unsigned char passed_time;
unsigned char Count;
const char keys[] = "123A456B789C*0#D";

int tap = 0;
int tin = 0;
int noLabel = 0;

int count = 0;
int tapPop = 0;
int noLabelSoup = 0;
int labelSoup = 0;
int noTapCan = 0;





int en1 = 0;
int en2 = 0;


void set_time(void){ //This program only has to be written once
    I2C_Master_Start(); //Start condition
    I2C_Master_Write(0b11010000); //7 bit RTC address + Write
    I2C_Master_Write(0x00); //Set memory pointer to seconds
    for(char i=0; i<7; i++){
        I2C_Master_Write(timeSetter[i]);
    }
    I2C_Master_Stop(); //Stop condition
    return;
}

void get_time(unsigned char datime[7]){
    I2C_Master_Start();
    I2C_Master_Write(0b11010001); //7 bit RTC address + Read
    for(unsigned char i=0;i<0x06;i++){
        datime[i] = I2C_Master_Read(1);
    }
    datime[6] = I2C_Master_Read(0);       //Final Read without ack
    I2C_Master_Stop();
    //Reset RTC memory pointer
    I2C_Master_Start(); //Start condition
    I2C_Master_Write(0b11010000); //7 bit RTC address + Write
    I2C_Master_Write(0x00); //Set memory pointer to seconds
    I2C_Master_Stop(); //Stop condition
}

void motorMove( unsigned char dir[]){
  if(dir == "right"){
    LATCbits.LATC0 = 1;
    LATCbits.LATC1 = 1;
    LATCbits.LATC3 = 0;
    LATCbits.LATC4 = 0;
  }
  if(dir == "left"){
    LATCbits.LATC0 = 0;
    LATCbits.LATC1 = 0;
    LATCbits.LATC3 = 1;
    LATCbits.LATC4 = 1;
  }
}

void switchControl( unsigned char dir[]){
}

void servo(){
  for (int i = 0; i < 500;i++){
    LATCbits.LATC1 = 1;
    delay(500);
    LATCbits.LATC1 = 0;
    delay(500);
  }
}


void sort (int tap, int noLabel, int tin){
    count++;
    if(tap && noLabel){
      tapPop++;
      motorMove("right");
      switchControl("right");
    }
    else if(!tap && noLabel && !tin){
      noTapCan++;
      motorMove("right");
      switchControl("left");
    }
    else if(!tap && noLabel && tin){
      noLabelSoup++;
      motorMove("left");
      switchControl("left");

    }
    else if(!tap && !noLabel && tin){
      labelSoup++;
      motorMove("left");
      switchControl("right");

    }

    return;
}

void interrupt keypressed(void){

    if(INT1IF){
        __lcd_newline();
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        putch(keys[keypress]);
        if (mode == 2){ // get operation time
            get_time(end_time);
            passed_time = (end_time[1] - start_time[1])*60 + (end_time[0] - start_time[0]);
            mode = 3;
        }
        else if(keypress == 0x0){ //display time
            if(mode==0){
                mode = 1;
            }
        }
        else if(keypress == 0x3){ //sort
            if(mode==0){
                mode = 2;}
        }

        else if (keypress == 0x1){ //back
                mode = 0;
            }
        }
        INT1IF = 0;     //Clear flag bit
}

void main(void) {

    TRISA = 0XFF; //All input mode
    TRISC = 0x11100110; // RC1 = PWM


    TRISC = 0x11100110;
    TRISD = 0x00;   //All output mode
    TRISB = 0xFF;   //All input mode
    LATB = 0x00;
    LATC = 0b00000000;
    ADCON0 = 0x00;
    ADCON1 = 0x0C;
    ADFM = 0;

    initLCD();
    I2C_Master_Init(10000);
    I2C_Master_Start(); //Start condition
    I2C_Master_Write(0b11010000); //7 bit RTC address + Write
    I2C_Master_Write(0x00); //Set memory pointer to seconds
    I2C_Master_Stop(); //Stop condition
    passed_time = 0;
    unsigned char time[7];

    INT1IE = 1;
    mode = 0;
    ei();           //Enable all interrupts

    OSCCON = OSCCON|0b01110000;
    OSCTUNEbits.PLLEN = 1;

    set_PWM_freq (3100);


    PWM1_Start();
    set_PWM1_duty(256);
    while(1){
        if(mode == 0){
            __lcd_clear();
            __lcd_home();
            __delay_ms(200);
            printf("Welcome!");
            printf("            ");
            printf("2 Back to start menu");
            __lcd_newline();
            printf("1 Time" );
            printf("              ");
            printf("A Sorting");
            while(mode ==0){}
        }
        else if(mode == 1){
            __lcd_clear();
            __delay_ms(300);
            while(mode == 1){
                I2C_Master_Start();
                I2C_Master_Write(0b11010001); //7 bit RTC address + Read
                for(unsigned char i=0;i<0x06;i++){
                    time[i] = I2C_Master_Read(1);
                }
                time[6] = I2C_Master_Read(0);       //Final Read without ack
                I2C_Master_Stop();
                __lcd_home();
                printf("%02x/%02x/%02x", time[6],time[5],time[4]);    //Print date in YY/MM/DD
                __lcd_newline();
                printf("%02x:%02x:%02x", time[2],time[1],time[0]);    //HH:MM:SS
                  //Reset RTC memory pointer
                I2C_Master_Start(); //Start condition
                I2C_Master_Write(0b11010000); //7 bit RTC address + Write
                I2C_Master_Write(0x00); //Set memory pointer to seconds
                I2C_Master_Stop(); //Stop condition
                //write new function!!
                __delay_ms(990);
                __lcd_home();
            }
        }
        else if(mode == 2){
            __lcd_clear();
            __delay_ms(100);
            printf("Sorting Started");
            __lcd_newline();
            printf("Press 1/2/A to stop");
            get_time(start_time);
            __lcd_home();


            int tap = 0;
            int tin = 0;
            int noLabel = 0;
            //1 = yes, 0 = no


            readADC(0); // side
            if(ADRESH ==0XFF){
              noLabel = 1;
            }

            readADC(1);// tap
            if(ADRESH ==0XFF){
              tap = 1;
            }

            if(PORTAbits.RA2 == 1){
              tin = 1;
            }

            if (mode == 3){
              break;
            }
              }

            }
        }

        else if (mode==3){
            __lcd_clear();
            __delay_ms(10);
            LATCbits.LATC1=0;
            int i = passed_time;
            printf("Time used: %d s", i);
            __lcd_newline();
            printf("Count: %02x", Count);
            while(mode==3){
            }
        }
    }
    return;
}
