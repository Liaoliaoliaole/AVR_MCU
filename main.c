/*  flush led left to right and right to left (two method, so two int main function)
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



unsigned char display_led1[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
int main (){
		//char i;
		DDRC=0xff;
		PORTC=0xff;
		while (1)
		{
			PORTC ^= (1<<PC5);
			_delay_ms(500);
			for(int i=0;i<8;i++){
				PORTC=~display_led1[i];
				_delay_ms(500);
			}
			for(int8_t i=7;i>=0 ;i--){
				PORTC=~display_led1[i];
				_delay_ms(100);
			}
		}
	}

