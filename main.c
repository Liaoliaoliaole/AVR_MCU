/*given that the duty cycle is 45%, which means OCR0 = 45% of 255 = 114.75 = 115
 * PWMMode.c
 *
 * Created: 2022/6/17 12:42:36
 * Author : tende
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>


void pwm_init()
{
	// initialize TCCR0 as per requirement, say as follows
	TCCR0 |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<CS00);
	
	// make sure to make OC0 pin (pin PB0 for atmega8515) as output pin
	DDRB |= (1<<PB0);
}
int main()
{
	unsigned char brightness;
	//duty = 255;       // duty cycle = 45% of 255 = 114.75 = 115
	
	// initialize timer in PWM mode
	pwm_init();
	
	// run forever
	while(1)
	{
		// increasing brightness
		for (brightness = 0; brightness < 255; ++brightness)
		{
			// set the brightness as duty cycle
			OCR0 = brightness;
			
			// delay so as to make the user "see" the change in brightness
			_delay_ms(10);
		}
		
		// decreasing brightness
		for (brightness = 255; brightness > 0; --brightness)
		{
			// set the brightness as duty cycle
			OCR0 = brightness;
			
			// delay so as to make the user "see" the change in brightness
			_delay_ms(10);
		}
		
		// repeat this forever
	}
}
