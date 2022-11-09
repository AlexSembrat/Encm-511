/* 
 * File:  TimeDelay.h
 * Authors: Alexander Sembrat, Matthew Ho, Jonathan Chong
 * ENCM 511 Driver Project 2
 * Created on October 15
 */

#ifndef TIMEDELAY_H
#define	TIMEDELAY_H
void Delay_ms(int time_ms);
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);
#endif	/* TIMEDELAY_H */

