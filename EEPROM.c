#include <xc.h>
#include <stdio.h>
#include "configBits.h"
#include "constants.h"
#include "countCan.h"
#include "time.h"
#include "lcd.h"
#include "I2C.h"
#include "macros.h"
#include "function.h"
#include "EEPROM.h"


// <editor-fold defaultstate="collapsed" desc="VARIABLE DEFINITIONS">
unsigned char sel;

int log_completion;
int log_count_total;

int log_count_pop_no_tab;
int log_count_pop_w_tab;

int log_count_can_w_lab;
int log_count_can_no_lab;

int log_startTime[7];

int log_total_time;
// </editor-fold>

void initEEPROM(void){
    EEPROM_write(0, 0x01);
}

void EEPROM_write(unsigned short address, unsigned char data){    
    EECON1bits.WREN = 1;    // Enable writing of EEPROM
    
    // Set address registers
    EEADRH = (unsigned char)(address >> 8);
    EEADR = (unsigned char)address;
    
    EEDATA = data;          // Write our data to the SFR
    EECON1bits.EEPGD = 0;   // Select EEPROM data mem. instead of program mem.
    EECON1bits.CFGS = 0;    // Access flash/EEPROM, NOT config. registers
    
    di(); // Disable interrupts for critical write sequence
    // Mandatory write initialization sequence
    EECON2 = 0x55;
    EECON2 = 0x0AA;
    EECON1bits.WR = 1;
    ei(); // Enable interrupts

    // Poll EEIF for write completion (we could use an ISR for it but we'd run
    // into race conditions anyway when we're writing a bunch of data)
    while(PIR2bits.EEIF == 0) {continue;} 
    PIR2bits.EEIF = 0; // Clear interrupt after it occurs
    EECON1bits.WREN = 0; // Disable write for data integrity
    
    // DEBUG
}

unsigned char EEPROM_read(unsigned short address){
    // Set address registers
    EEADRH = (unsigned char)(address >> 8);
    EEADR = (unsigned char)address;

    EECON1bits.EEPGD = 0;       // Select EEPROM Data Memory
    EECON1bits.CFGS = 0;        // Access flash/EEPROM, NOT config. registers
    EECON1bits.RD = 1;          // Start a read cycle

    // A read should only take one cycle, and then the hardware will clear
    // the RD bit
    while(EECON1bits.RD == 1) {continue;}

    return EEDATA;  // Return data
}

void logRun(void){
    // Log the global variables of interest for the most recent sorting run
    //
    // Variables:
    // - # cans (tot) => Ranges from 0?12 => 4 bits
    // - # cans of each type => Ranges from 0?12 => 4 bits
    // - Start date and time => 7 date/time references * 8 bits per reference => 56 bits
    // - Sort duration => up to 179 s => 8 bits
    // - Completion flag => 1 bit
    //
    // Total is 85 bits, which is 11 writes
    
    // Check which log space to go to (log spaces are zero-indexed)
    sel = EEPROM_read(0);
    unsigned short addr = 1 + 11 * sel;
    
    // Increment selection bits for the next write (or clear if max value)
    if (sel < 3){
        unsigned char num = sel+1;
        EEPROM_write(0, num);
    }
    else{
        EEPROM_write(0, 0);
    }
    
    // Log completion flag and total # of cans
    unsigned char byte1 = 0b10000000 | total_count;
    EEPROM_write(addr, byte1);
    addr++;
    
    // Log # of cans of each type
    unsigned char byte2 = (pop_can_no_tap << 4) | pop_can_tap;
    EEPROM_write(addr, byte2);
    addr++;
    
    unsigned char byte3 = (soup_can_label << 4) | soup_can_no_label;
    EEPROM_write(addr, byte3);
    addr++;
    
    // Log start date and time
    for(int i = 0; i < 7; i++){
        unsigned char byte_i = start_time[i];
        EEPROM_write(addr, byte_i);
        addr++;
    }
    
    // Log sort duration
    unsigned char byte11 = passed_time;
    EEPROM_write(addr, byte11);
}

void retrieveLog(int logNum){
    // Retrieve the data of interest and place it in global variables
    // 85 bits therefore 11 reads
    // Logs are zero-indexed
    
    // Calculate address to begin reading from
    unsigned short addr = 1 + logNum * 11;
    
    // Get completion flag and total # of cans
    unsigned char byte1 = EEPROM_read(addr);
    log_completion = (int)(byte1 & 0b10000000);
    log_count_total = (int)(byte1 & 0b00001111);
    addr++;
    
    // Get # of cans of each type
    unsigned char byte2 = EEPROM_read(addr);
    log_count_pop_no_tab = (int)((byte2 & 0b11110000)>> 4);
    log_count_pop_w_tab = (int)(byte2 & 0b00001111);
    addr++;
    unsigned char byte3 = EEPROM_read(addr);
    log_count_can_w_lab = (int)((byte3 & 0b11110000)>> 4);
    log_count_can_no_lab = (int)(byte3 & 0b00001111);
    addr++;
    
    // Get start date and time
    for(int i = 0; i < 7; i++){
        log_startTime[i] = (int)EEPROM_read(addr);
        addr++;
    }
    
    // Get sort duration
    log_total_time = (int)EEPROM_read(addr);    
}