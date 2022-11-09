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
    IPC4bits.CNIP = 0b111;  //set CN interrupt priority
    IFS1bits.CNIF = 0;      // clear CN interrupt flag
    IEC1bits.CNIE = 1;      //enable CN interrupt
    TRISAbits.TRISA2 = 1; //Make GPIO RA2 a digital input
    TRISAbits.TRISA4 = 1; //Make GPIO RA4 a digital input
    TRISBbits.TRISB4 = 1; //Make GPIO RB4 a digital input
    CNPU1bits.CN0PUE = 1; //Enables pull up resistor on RA4/CN0
    CNPU2bits.CN30PUE = 1; //Enables pull up resistor on RA2/CN30
    CNPU1bits.CN1PUE = 1; //Enables pull up resistor on RB2/CN1
}
void IOCheck(void)
{
    float ADC, result, frequency, time;
    time = 31.0 * 2.0 / 31250.0;
    IEC1bits.CNIE = 0;  //turn off interrupts
    char out[10];
    //voltage

    if (PORTAbits.RA2==0){
        ADC = (float)do_ADC(0) / 1023.0;
        result = ADC * 3.25; // voltage = (ADC / 1023) * VDD
           sprintf(out, "%1.3f", (double)result);
        Disp2String("VOLTMETER Voltage = ");    
        Disp2String(out);                       
        Disp2String(" V  ");                   
    }
    //resistance
    else if(PORTAbits.RA4==0){
        ADC = (float)do_ADC(1) /1023.0;
        result = 1000.0 * ADC / (1-ADC); // resistance = resistor * (ADC/1023) / (1 - (ADC / 1023))
        Disp2String("OHMMETER Resistance = ");
        sprintf(out, "%1.3f", (double)result);
        Disp2String(out); 
        XmitUART2(234, 1); //print ohms symbol
        Disp2String("  ");
    }
    //capacitance
    else if(PORTBbits.RB4 == 0){
        ADC = (float)do_ADC(2)/1023.0;
        result = time / (1000.0 * ADC / (1-ADC)); // capacitance = time / resistance 
        Disp2String("Capacitance = ");    
        sprintf(out, "%1.3f", (double)result);
        Disp2String(out);               
        Disp2String(" uF  ");  
    }
    //frequency
    if(PORTBbits.RB4 == 1 || PORTAbits.RA4 == 1 || PORTAbits.RA2 == 1 ){
    frequency = 1.44 / (time / (1000.0 * ADC / (1-ADC)));
    Disp2String("Frequency = ");    
    sprintf(out, "%1.3f", (double)frequency);
    Disp2String(out);                        
    Disp2String(" Hz   \r");
}
    return;
}