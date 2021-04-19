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

enum SM_States {SM_Init, SM_Start, SM_Wait1, SM_Next, SM_Lock} SM_State;

void TickFct_Press()
{

	switch(SM_State) //transitions
	{
		case(SM_Init):
			if(PINA == 0x00)
			{
				SM_State = SM_Init;	
			}
			else if(PINA == 0x04)
			{
				SM_State = SM_Start;
			}
			else if(PINA == 0x80)
			{
				SM_State = SM_Lock;
			}
			else
			{
				SM_State = SM_Init;
			}
			break;
		case(SM_Start):
			if(PINA != 0x00)
			{
				SM_State = SM_Start;
			}
			else
			{
				SM_State = SM_Wait1;
			}
			break;
		case(SM_Wait1):
			if(PINA == 0x02)
			{
				SM_State = SM_Next;
			}
			else if(PINA == 0x00)
			{
				SM_State = SM_Wait1;
			}
			else if(PINA != 0x00 && PINA != 0x02)
			{
				SM_State = SM_Init;
			}
			break;
		case(SM_Next):
			if(PINA == 0x80)
			{
				SM_State = SM_Lock;
			}
			else
			{
				SM_State = SM_Next;
			}
			break;
		case(SM_Lock):
			SM_State = SM_Init;
			break;
		default:
			break;
	}


	switch(SM_State) //State actions
	{
		case(SM_Init):
			PORTC = 0x00;
			PORTB = 0x00;
			break;
		case(SM_Start):
			PORTC = 0x01;
			break;
		case(SM_Wait1):
			PORTC = 0x02;
			break;
		case(SM_Next):
			PORTB = 0x01;
			PORTC = 0x03;
			break;
		case(SM_Lock):
			PORTC = 0x04;
			PORTB = 0x00;
			break;
		default:
			break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //sets PINA as input
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00; //sets PORTC as output
    /* Insert your solution below */
    SM_State = SM_Init;
    PORTC = 0x00;
    PORTB = 0x00;   
    while (1) {
	TickFct_Press();
	//TimerTick();
    }
    return 1;
}
