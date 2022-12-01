#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <math.h>
#include "d_led.h"

int main(void){
	d_led_init();
	int number = 20;
	sei();
	while(1){
		roll();
		display_integer_number(number);
		number++;
		_delay_ms(700);
	}
	return 0;
}


