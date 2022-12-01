/*
 * d_led.c
 *
 *  Created on: 1 gru 2022
 *      Author: mherc
 */

#include<stdbool.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include<avr/pgmspace.h>
#include <avr/delay.h>
#include"d_led.h"

volatile uint8_t d_led_no1;
volatile uint8_t d_led_no2;
volatile uint8_t d_led_no3;
volatile uint8_t d_led_no4;

uint8_t symbol[26] PROGMEM = {
	~(S_A|S_B|S_C|S_D|S_E|S_F), 			//0
	~(S_B|S_C),								//1
	~(S_A|S_B|S_D|S_E|S_G),					//2
	~(S_A|S_B|S_C|S_D|S_G),					//3
	~(S_B|S_C|S_F|S_G),						//4
	~(S_A|S_C|S_D|S_F|S_G),  				//5
	~(S_A|S_C|S_D|S_E|S_F|S_G),				//6
	~(S_A|S_B|S_C|S_F),						//7
	~(S_A|S_B|S_C|S_D|S_E|S_F|S_G),			//8
	~(S_A|S_B|S_C|S_D|S_F|S_G),				//9

	~(S_A|S_B|S_C|S_D|S_E|S_F|S_DT),		//0.
	~(S_B|S_C|S_DT),						//1.
	~(S_A|S_B|S_D|S_E|S_G|S_DT),			//2.
	~(S_A|S_B|S_C|S_D|S_G|S_DT),			//3.
	~(S_B|S_C|S_F|S_G|S_DT),				//4.
	~(S_A|S_C|S_D|S_F|S_G|S_DT),			//5.
	~(S_A|S_C|S_D|S_E|S_F|S_G|S_DT),		//5.
	~(S_A|S_B|S_C|S_F|S_DT),				//6.
	~(S_A|S_B|S_C|S_D|S_E|S_F|S_G|S_DT),	//7.
	~(S_A|S_B|S_C|S_D|S_F|S_G|S_DT),		//8.

	~(S_A),									//Roll1
	~(S_B),									//Roll2
	~(S_C),									//Roll3
	~(S_D),									//Roll4
	~(S_E),									//Roll5
	~(S_F),									//Roll6
};

void d_led_init(void){
	LED_DATA_DIR = 0xFF;
	LED_DATA = 0xFF;

	ANODES_DIR |= CA1 | CA2 | CA3 | CA4;
	ANODES_PORT |= CA1 | CA2 | CA3 | CA4;

	TCCR0 |= ( 1<<WGM01 );
	TCCR0 |= ( 1<<CS02 ) | ( 1<<CS00 );
	OCR0 = 38;
	TIMSK |= ( 1<<OCIE0 );
}

void roll( void ){
	int number = 20;
	do {
		d_led_no1 = number;
		d_led_no2 = number;
		d_led_no3 = number;
		d_led_no4 = number;
		_delay_ms(50);
		number++;
	} while ( number < 26 );
}

void display_number( int number ){
	d_led_no4 = number%10;
	number = number/10;
	d_led_no3 = number%10;
	number = number/10;
	d_led_no2 = number%10;
	number = number/10;
	d_led_no1 = number%10;
}

ISR(TIMER0_COMP_vect){
	static uint8_t counter = 1;
	ANODES_PORT = ~counter;
	if 		(counter==1) LED_DATA = pgm_read_byte( &symbol[d_led_no1] );
	else if (counter==2) LED_DATA = pgm_read_byte( &symbol[d_led_no2] );
	else if (counter==4) LED_DATA = pgm_read_byte( &symbol[d_led_no3] );
	else if (counter==8) LED_DATA = pgm_read_byte( &symbol[d_led_no4] );
	counter <<= 1;
	if ( counter>8 ) counter =1;
}
