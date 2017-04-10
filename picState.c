#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "macros.h"
#include "pwm.h"
#include "function.h"
#include <stdio.h>
#include <xc.h>

char mode;
extern int flag;
extern unsigned char start_time[7];
extern unsigned char end_time[7];
extern unsigned char passed_time; 
extern unsigned char time[7];



void welcome() {
  __lcd_clear();
  __lcd_home();
  __delay_ms(200);
  
  printf("Welcome!");
  printf("            ");
  printf("2 Back to start menu");
  __lcd_newline();
  printf("1 Time");
  printf("              ");
  printf("A Sorting");
  LATDbits.LATD0 = 0;
  LATCbits.LATC1 = 0;

  //main_servo_control(NEUTRAL);
  //side_servo_control(NEUTRAL);

  while (mode == 0) {
  }
}

void debug() {

    
    
    //LATDbits.LATD0 = 1;
    //int i = sense_can();
    //printf("%d", i);
    int i = 0; 
    while(1){
        __lcd_home();
        readADC(2);
        printf("%x %x", ADRESH,ADRESL);
        __delay_ms(50);
        i++;
    }
     
    //__delay_ms(500);
    //gate();
        /*if (ADRESH > H_max) {
            H_max = ADRESH;
        }
        printf("%x", ADRESH);
        __delay_ms(5);
        i++;
    }
    
    if(H_max >= 0x50){
       __lcd_home();
       printf("HI HI %x", H_max);
       __delay_ms(500);
    }
    else{
       __lcd_home();
       printf("LO LO %x",H_max);
       __delay_ms(500);

  */
    }
    
    
    //gate();



void sort() {

  int tap = 0;
  int tin = 0;
  int noLabel = 0;
  
  __lcd_clear();
  __delay_ms(100);
  printf("Sorting Started");
  __lcd_newline();
  printf("Press 1/2/A to stop");
  get_time(start_time);
  __lcd_home();
  // 1 = yes, 0 = no
  while (mode == 2){
    main_servo_control(NEUTRAL);
    side_servo_control(NEUTRAL);

    if (readLightSensor() == 1) {
      // Everything here should be activated by a switch
      LATDbits.LATD0 = 1;
      
     
        __lcd_home();
        __lcd_newline();
        int can = sense_can();
       

        LATDbits.LATD0 = 0;
       // move_can(can);
        
        for (int x = 0; x< 10; x++){
        main_servo_control(NEUTRAL);
        side_servo_control(NEUTRAL);
        __delay_ms(100);
        }

        printf("%d", can);
        flag++;
    } else {
      // move_can(sense_can());
      shaker();
      LATDbits.LATD0 = 0;
      __delay_ms(500);      
      gate();
      flag = 0;
    }
  }
}

void display_time() {
    
  __lcd_clear();
  __delay_ms(300);
  while (mode == 1) {
    I2C_Master_Start();
    I2C_Master_Write(0b11010001); // 7 bit RTC address + Read
    for (unsigned char i = 0; i < 0x06; i++) {
      time[i] = I2C_Master_Read(1);
    }
    time[6] = I2C_Master_Read(0); // Final Read without ack
    I2C_Master_Stop();
    __lcd_home();
    printf("%02x/%02x/%02x", time[6], time[5],
           time[4]); // Print date in YY/MM/DD
    __lcd_newline();
    printf("%02x:%02x:%02x", time[2], time[1],
           time[0]);              // HH:MM:SS
                                  // Reset RTC memory pointer
    I2C_Master_Start();           // Start condition
    I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
    I2C_Master_Write(0x00);       // Set memory pointer to seconds
    I2C_Master_Stop();            // Stop condition
    // write new function!!
    __delay_ms(990);
    __lcd_home();
  }
}


void display_sorting_time() {
  __lcd_clear();
  __delay_ms(10);
  LATCbits.LATC1 = 0;
  int i = passed_time;
  printf("Time used: %d s", i);
  __lcd_newline();
  __delay_ms(500);
  flag = 0;
  LATDbits.LATD0 = 0;
}
