/*
 * 4_digit_7_seg.c
 * connecting with 74hc595n
 * Created: 2022/5/27 13:12:31
 * Author : tende
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include<util/delay.h>

enum DIGIT {D1,D2,D3,D4};
const uint8_t seg[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x4f};//7segment0-9,common cathode
//const uint8_t seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};//7segment0-9,common anode
	
#define DS PD0 //595 pin 14 connected to PD0,data input
#define SHCP PD1 //595 pin 12 connected to PD1, storage register clock input
#define STCP PD2 //595 pin 11 connected to PD2, shift register clock input,latch

void selectDigit(int d){ //PC0-PC3,4 digit
	PORTC = 0x01<<d;
}

void displayDigit(uint8_t val){
	int i;
	for(i=0;i<10;i++){				
		PORTD = (PORTD & 0xfe) + (((val<<i) & 0x80) == 0x80);//DS 
		//PORTD = (PORTD & 0xfe) | ((val>>i) & 0x01);
		
	//storage clock high and low once, enable a byte DS input		
	PORTD |= 0x04;//storage register clock input (PD2 high),clockpin
	_delay_us(500);
	PORTD = PORTD & 0xfb;//(xxxxx0xx, PD2 low)
	//_delay_us(500);
		
	}
	PORTD = (PORTD & 0xfd) | 0x02;//shift register clock input (xxxxxx0x | 00000010 == xxxxxx1x, only control PD1 high),latch pin
	_delay_us(500);
	PORTD = PORTD & 0xfd; //(xxxxxx0x, PD1 low)
	//_delay_us(500);
}

int main(void)
{
    DDRC = 0x0f;//output PORTC bit0-3
	DDRD = 0x0f;
	
    while (1) 
    {
		//selectDigit(D1);
		//displayDigit(seg[2]);
		//_delay_ms(1000);
		for(unsigned char i=0;i<10;i++){
			selectDigit(D1+i%4);//0-3
			displayDigit(seg[i]);
			_delay_ms(1000);
		}
	}
}

