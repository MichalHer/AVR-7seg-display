/*
 * d_led.h
 *
 *  Created on: 1 gru 2022
 *      Author: mherc
 */

#ifndef D_LED_H_
#define D_LED_H_

#define LED_DATA PORTA
#define LED_DATA_DIR DDRA

#define ANODES_PORT PORTD
#define ANODES_DIR DDRD

#define CA1 ( 1<<PA0 )
#define CA2 ( 1<<PA1 )
#define CA3 ( 1<<PA2 )
#define CA4 ( 1<<PA3 )

#define S_A ( 1<<0 )
#define S_B ( 1<<2 )
#define S_C ( 1<<6 )
#define S_D ( 1<<4 )
#define S_E ( 1<<3 )
#define S_F ( 1<<1 )
#define S_G ( 1<<7 )
#define S_DT ( 1<<5 )

extern volatile uint8_t d_led_no1;
extern volatile uint8_t d_led_no2;
extern volatile uint8_t d_led_no3;
extern volatile uint8_t d_led_no4;

void d_led_init(void);
void display_number( int number );
void display_roll( void ); //Takes 300ms

#endif /* D_LED_H_ */
