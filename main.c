/*  flush led left to right and right to left
 * fengmingqi.c
 *
 * Created: 2022/5/18 11:23:26
 * Author : tende
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include<util/delay.h>
#define BIT(x)  (1 << (x))


int main(void)
{
    unsigned int i,j;
	DDRC=0xff;
	PORTC=0xff;
	
    while (1) 
    {
	    j=0x01;
		for(i=0;i<8;i++){
			PORTC=~j;
			_delay_ms(500);
			j=j<<1;
		}
	j=0x80;
	for(i=0;i<8;i++){
		PORTC=~j;
		_delay_ms(500);
		j=j>>1;
	}

    }
}

