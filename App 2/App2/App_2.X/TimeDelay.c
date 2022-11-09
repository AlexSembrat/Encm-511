/* 
 * File:   TimeDelay.c
 * Authors: Alexander Sembrat, Matthew Ho, Jonathan Chong
 * ENCM 511 Driver Project 2
 * Created on October 15
 */

#include <xc.h>
#include "TimeDelay.h"
#include "IOs.h"

void Delay_ms(int time_ms)
{
    CLKDIVbits.RCDIV = 111; //set clock frequency to 31.25kHz
    
    T2CONbits.TON = 0;  // internal timer 2 stop
    T2CONbits.TCS = 0;  //use internal not external clock
    T2CONbits.TSIDL = 0; // continue module operation in idle mode
    T2CONbits.TCKPS = 0; //use default 00 prescale bits.
    T2CONbits.T32 = 0; // timer 2 and 3 are 2 16 bit timers not 1 32 bit timer
    
    IPC1bits.T2IP2 = 1; //set interrupt priority
    IEC0bits.T2IE = 1; //enable timer interrupt
    IFS0bits.T2IF = 0; //in the event of an interrupt the bit is set
   
    PR2 = time_ms * 31.25 / 2; // PR2 = time*fclk/2, solve for PR2
    T2CONbits.TON = 1; //internal timer 2 start
    Idle(); //wait in idle mode
    T2CONbits.TON = 0; //internal timer 2 stop
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0; //Clear timer 2 flag
    T2CONbits.TON = 0; //internal timer 2 stop
}

