/* 
 * File: IOs.c
 * Author: Jonathan Chong
 * 
*/ 

#include "IOs.h"
#include "TimeDelay.h"
#include "UART2.h"
#include "ChangeClk.h"
#include "string.h"

extern uint8_t PBFlag;

void IOinit(){
    AD1PCFG = 0xFFFF; // All analog pins digital
    TRISBbits.TRISB8 = 0; //RB8: output
    TRISBbits.TRISB4 = 1;   //RB4: input
    TRISAbits.TRISA4 = 1;   //RA4: input
    TRISAbits.TRISA2 = 1;   //RA2: input
    CNPU1bits.CN0PUE = 1;   //CN0/RA4: enables pull up
    CNPU1bits.CN1PUE = 1;   //CN1/RB4: enable pull up
    CNPU2bits.CN30PUE = 1;  //CN30/RA2: enable pull up
    CNEN1bits.CN0IE = 1;    //CN0/RA4: enable CN interrupt
    CNEN1bits.CN1IE = 1;    //CN1/RB4: enable CN interrupt
    CNEN2bits.CN30IE = 1;   //CN30/RA2: enable CN interrupt
    IPC4bits.CNIP = 0b111;  //set CN interrupt priority
    IFS1bits.CNIF = 0;      // clear CN interrupt flag
    IEC1bits.CNIE = 1;      //enable CN interrupt

}
void IOCheck(void)
{
    IEC1bits.CNIE = 0;  //turn off interrupts
    while(PORTBbits.RB4 == 0 && PORTAbits.RA4 && PORTAbits.RA2){
        Disp2String("\rPB1 is pressed"); 
        LATBbits.LATB8 = 1;
        Delay_ms(500);
        LATBbits.LATB8 = 0;
        Delay_ms(500);
    }
    while(PORTBbits.RB4 && PORTAbits.RA4 == 0 && PORTAbits.RA2){
        Disp2String("\rPB2 is pressed"); 
        LATBbits.LATB8 = 1;
        Delay_ms(2000);
        LATBbits.LATB8 = 0;
        Delay_ms(2000);
    }
    while(PORTBbits.RB4 && PORTAbits.RA4 && PORTAbits.RA2 == 0){
        Disp2String("\rPB3 is pressed"); 
        LATBbits.LATB8 = 1;
        Delay_ms(3000);
        LATBbits.LATB8 = 0;
        Delay_ms(3000);
    }
    while(PORTBbits.RB4 == 0 && PORTAbits.RA4 == 0 && PORTAbits.RA2){
        Disp2String("\rPB1 is pressed and PB2 is pressed"); 
        LATBbits.LATB8 = 1;
    }
    while(PORTBbits.RB4 == 0 && PORTAbits.RA4 && PORTAbits.RA2 == 0){
        Disp2String("\rPB1 is pressed and PB3 is pressed"); 
        LATBbits.LATB8 = 1;
    }
    while(PORTBbits.RB4 && PORTAbits.RA4 == 0 && PORTAbits.RA2 == 0){
        Disp2String("\rPB2 is pressed and PB3 is pressed"); 
        LATBbits.LATB8 = 1;
    }
    while(PORTBbits.RB4 == 0 && PORTAbits.RA4 == 0 && PORTAbits.RA2 == 0){
        Disp2String("\rAll PBs are pressed"); 
        LATBbits.LATB8 = 1;
    }
    while(PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1 && PORTAbits.RA2 == 1){
        Disp2String("\rNothing pressed"); 
        LATBbits.LATB8 = 0;
    }      
    return;
}