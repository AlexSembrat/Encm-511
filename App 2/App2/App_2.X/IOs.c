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
#include "ADC.h"

extern uint8_t PBFlag;

void IOinit(){
    AD1PCFG = 0xFFDF; // Analog: AN5/Pin 8
    TRISAbits.TRISA2 = 1;   //RA2: input
    CNPU2bits.CN30PUE = 1;  //CN30/RA2: enable pull up
    CNEN2bits.CN30IE = 1;   //CN30/RA2: enable CN interrupt
    IPC4bits.CNIP = 0b111;  //set CN interrupt priority
    IFS1bits.CNIF = 0;      // clear CN interrupt flag
    IEC1bits.CNIE = 1;      //enable CN interrupt

}
void IOCheck(void)
{
    IEC1bits.CNIE = 0;  //turn off interrupts
    if (PORTAbits.RA2==0){
        int i = 0;
        while(i<10){
            Disp2Graph(do_ADC());
            i++;
        }
    }
    else{
        Idle();
    }
    return;
}