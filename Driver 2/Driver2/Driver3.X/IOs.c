/* 
 * File:   IOs.c
 * Authors: Alexander Sembrat, Matthew Ho, Jonathan Chong
 * ENCM 511 Driver Project 2
 * Created on October 15
 */


#include <xc.h>
#include "TimeDelay.h"
#include "IOs.h"

void IOinit(){
    AD1PCFG = 0xFFFF; // Turn all analog pins as digital
    TRISAbits.TRISA2 = 1; //Make GPIO RA2 a digital input
    TRISAbits.TRISA4 = 1; //Make GPIO RA4 a digital input
    TRISBbits.TRISB4 = 1; //Make GPIO RB4 a digital input
    CNPU1bits.CN0PUE = 1; //Enables pull up resistor on RA4/CN0
    CNPU2bits.CN30PUE = 1; //Enables pull up resistor on RA2/CN30
    CNPU1bits.CN1PUE = 1; //Enables pull up resistor on RB2/CN1
    TRISBbits.TRISB8 = 0; //Make GPIO RB8 a digital output
    
}
void IOcheck(){
    while(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 0){
        LATBbits.LATB8 = 1; //Turn LED connected to RB8 on
    }
    while(PORTAbits.RA2 == 0 && PORTBbits.RB4 == 0){
        LATBbits.LATB8 = 1; //Turn LED connected to RB8 on
    }
    while(PORTAbits.RA4 == 0 && PORTBbits.RB4 == 0){
        LATBbits.LATB8 = 1; //Turn LED connected to RB8 on
    }
    while(PORTAbits.RA4 == 0 && PORTBbits.RB4 == 0 && PORTAbits.RA4 == 0){
        LATBbits.LATB8 = 1; //Turn LED connected to RB8 on
    }
    while(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1  ){
        LATBbits.LATB8 = 1; //Turn LED connected to RB8 on
        Delay_ms(500);     //Delay for 1000 ms until next line of code is run
        LATBbits.LATB8 = 0; //Turn LED connected to RB8 off
        Delay_ms(500);     //Delay for 1000 ms until next line of code is run
    }
    while(PORTAbits.RA4 == 0 && PORTAbits.RA2 == 1 && PORTBbits.RB4 == 1){
        LATBbits.LATB8 = 1; //Turn LED connected to RB8 on
        Delay_ms(2000);     //Delay for 2000 ms until next line of code is run
        LATBbits.LATB8 = 0; //Turn LED connected to RB8 off
        Delay_ms(2000);     //Delay for 2000 ms until next line of code is run
    }
    while(PORTBbits.RB4 == 0 && PORTAbits.RA4 == 1 && PORTAbits.RA2 == 1){
        LATBbits.LATB8 = 1; //Turn LED connected to RB8 on
        Delay_ms(3000);     //Delay for 3000 ms until next line of code is run
        LATBbits.LATB8 = 0; //Turn LED connected to RB8 off
        Delay_ms(3000);     //Delay for 3000 ms until next line of code is run
    }
    LATBbits.LATB8 = 0;     //Turn LED connected to RB8 off
}
