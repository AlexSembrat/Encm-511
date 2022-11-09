/*
 * File:   ADC.c
 * Author: Jonat
 *
 * Created on November 24, 2021, 12:55 PM
 */

#include "ADC.h"
#include "xc.h"
#include "IOs.h"
#include "UART2.h"
#include "ChangeClk.h"


uint16_t do_ADC(uint8_t type){
    uint16_t ADCValue; //used to store final value
    unsigned long long int value = 0;  //used to store all the mesasurments
    
   AD1CON1bits.ADON = 1;       //turn on ADC
    AD1CON1bits.FORM = 0b00;    //output unsigned integer
    AD1CON1bits.SSRC = 0b111;   //auto-convert after sampling
    AD1CON1bits.ASAM = 0;       //start sampling when SAMP bit is set
    
    AD1CON2bits.VCFG = 0b000;   //use pic reference voltage
    AD1CON2bits.CSCNA = 0;      //Don't scan inputs
    AD1CON2bits.BUFM = 0;       //output one 16 bit word
    AD1CON2bits.ALTS = 0;       //use MUXA settings
    
    AD1CON3bits.ADRC = 0;       //use system clock
    AD1CON3bits.SAMC = 0b11111; //slow signal so slowest sampling time is okay and uses least amount of power
    
    AD1CHSbits.CH0NA = 0;       //use VRef-
    
    int i = 0;
    //voltage
    if(type == 0){
       AD1CHSbits.CH0SA = 0b0101;  //use pin 8 for voltage
    }
    else if(type == 1){
        AD1CHSbits.CH0SA = 0b1011;  //use pin 16 for resistance
    }
    //capacitance
    else if(type == 2){
        AD1CHSbits.CH0SA = 0b1010; //use pin 17 for capacitance
    }
    
    AD1CON1bits.SAMP = 1;       //begin sampling
    while(AD1CON1bits.DONE == 0)//wait until sampling and converting is done
    {}
    value = ADC1BUF0;
    AD1CON1bits.SAMP = 0;       //stop sampling
    AD1CON1bits.ADON = 0;       //turn ADC off
    
    
    return ADCValue;
}