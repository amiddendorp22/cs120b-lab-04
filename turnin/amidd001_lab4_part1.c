/*	Author: amidd001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;
void TimerISR()
{
	TimerFlag = 1;
}

enum SM_States {SM_Init, SM_Press1, SM_Wait, SM_Wait2, SM_Press2, SM_Wait3, SM_Wait4} SM_State;

void TickFct_Press()
{

	switch(SM_State) //transitions
	{
		case(SM_Init):
			if(PINA == 0x00)
			{
				SM_State = SM_Init;	
			}
			else if(PINA == 0x01)
			{
				SM_State = SM_Press1;
			}
			break;
		case(SM_Press1):
			SM_State = SM_Wait;
			break;
		case(SM_Wait):
			if(PINA == 0x01)
			{
				SM_State = SM_Wait;
			}
			else if(PINA == 0x00)
			{
				SM_State = SM_Wait2;
			}
			break;
		case(SM_Wait2):
			if(PINA == 0x00)
			{
				SM_State = SM_Wait2;
			}
			else if(PINA == 0x01)
			{
				SM_State = SM_Press2;
			}
			break;
		case(SM_Press2):
			SM_State = SM_Wait3;
			break;
		case(SM_Wait3):
			if(PINA == 0x01)
			{
				SM_State = SM_Wait3;
			}
			else if(PINA == 0x00)
			{
				SM_State = SM_Wait4;
			}
			break;
		case(SM_Wait4):
			if(PINA == 0x00)
			{
				SM_State = SM_Wait4;
			}
			else if(PINA == 0x01)
			{
				SM_State = SM_Press1;
			}
			break;
		default:
			break;
	}


	switch(SM_State) //State actions
	{
		case(SM_Init):
			PORTB = 0x01;
			break;
		case(SM_Press1):
			PORTB = 0x02;
			break;
		case(SM_Wait):
			break;
		case(SM_Wait2):
			break;
		case(SM_Press2):
			PORTB = 0x01;
			break;
		case(SM_Wait3):
			break;
		case(SM_Wait4):
			break;
		default:
			break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //sets PINA as input
    DDRB = 0xFF; PORTB = 0x00; //sets PORTB as output
    /* Insert your solution below */
    SM_State = SM_Init;   
    while (1) {
	TickFct_Press();
	//TimerTick();
    }
    return 1;
}
