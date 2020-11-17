/*
 * shift_7segment.c
 *
 * Created: 17.11.2020 13:04:50
 *  Author: dklim
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define CLK 0x02;
#define RST 0x04;
#define INT 0x01;

int main(void)
{
	DDRA = 0x80;
	DDRB = 0x00;
	DDRC = 0x06;
	int tab[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
	
	while(1){
		if(PINC & 0x01){
			int liczba = PINB;
			int sekw[3] = {tab[liczba/100], tab[(liczba%100) / 10], tab[liczba %10]};
			PORTC = RST;
			for (int i = 2; i > -1; i--){
				for (int j = 0; j < 8; j++){
					PORTA = sekw[i] >> (7 - j);
					PORTC = CLK;
					_delay_ms(20);
					PORTC = 0x00;
					_delay_ms(20);
				}
			} 
		}
	}
	
	
	PORTA = 0x00;
	PORTC = 0x00;
	while(1);
	
}