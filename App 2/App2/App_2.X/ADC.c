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


uint16_t do_ADC(){
    
    NewClk(500); //set clock to 500MHz
    
    uint16_t ADCValue; //used to store final value
    unsigned long long int value = 0;  //used to store all the mesasurments

    AD1CON1bits.ADON = 1;       //turn ADC on
    AD1CON1bits.FORM = 0b00;    //make output an unsigned integer
    AD1CON1bits.SSRC = 0b111;   //after sampling auto convert
    AD1CON2bits.VCFG = 0b000;   //use microcontroller reference voltage
    AD1CON2bits.BUFM = 0;       //make output a 16 bit word
    AD1CON3bits.ADRC = 0;       //use system clock
    AD1CON3bits.SAMC = 0b11111; //change the sample rate
    AD1CHSbits.CH0NA = 0;       //use VRef-
    AD1CHSbits.CH0SA = 0b0101;  //use VRef+
    
    int i = 0;
    while(i<3000){
        /* Sampling and Converting */
        AD1CON1bits.SAMP = 1;       //begin sampling
        while(AD1CON1bits.DONE == 0)//wait until sampling and converting is done
        {}
       if(i%3==0){
           value += ADC1BUF0;
       }
        
        AD1CON1bits.SAMP = 0;       //stop sampling
        i++;
    } 
    AD1CON1bits.ADON = 0;       //turn ADC off
    ADCValue = value/1000;     //get the average
    NewClk(32);                 //set clock back to 32MHz
    return ADCValue;
}