/*flash an LED every 50 ms (you can surely see the LED flashing this time ;)). We have an XTAL of 16 MHz.
Methodology – Using Interrupts
So now, we have to flash the LED every 50 ms. With CPU frequency 16 MHz, even a maximum delay of 16.384 ms can be achieved using a 1024 prescaler. So what do we do now? Well, we use interrupts.

The concept here is that the hardware generates an interrupt every time the timer overflows. Since the required delay is greater than the maximum possible delay, obviously the timer will overflow. And whenever the timer overflows, an interrupt is fired. Now the question is how many times should the interrupt be fired?

For this, let’s do some calculation. Let’s choose a prescaler, say 256. Thus, as per the calculations, it should take 4.096 ms for the timer to overflow. Now as soon as the timer overflows, an interrupt is fired and an Interrupt Service Routine (ISR) is executed. Now,

50 ms ÷ 4.096 ms = 12.207

Thus, in simple terms, by the time the timer has overflown 12 times, 49.152 ms would have passed. After that, when the timer undergoes 13th iteration, it would achieve a delay of 50 ms. Thus, in the 13th iteration, we need a delay of 50 – 49.152 = 0.848 ms. At a frequency of 62.5 kHz (prescaler = 256), each tick takes 0.016 ms. Thus to achieve a delay of 0.848 ms, it would require 53 ticks. Thus, in the 13th iteration, we only allow the timer to count up to 53, and then reset it. All this can be achieved in the ISR as follows:
 * timer0.c
 *
 * Created: 2022/6/14 13:28:25
 * Author : tende
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
//#include <util/delay.h>
#include <avr/interrupt.h>

// global variable to count the number of overflows
volatile uint8_t tot_overflow;

void timer0_init()
{
	// set up timer with prescaler = 256
	TCCR0 |= (1 << CS02);
	
	// initialize counter
	TCNT0 = 0;
	
	// enable overflow interrupt
	TIMSK |= (1 << TOIE0);
	
	// enable global interrupts
	sei();
	
	// initialize overflow counter variable
	tot_overflow = 0;
}

// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER0_OVF_vect)
{
	// keep a track of number of overflows
	tot_overflow++;
}

int main(void)
{
	// connect led to pin PC0
	DDRC |= (1 << 0);
	
	// initialize timer
	timer0_init();
	
	// loop forever
	while(1)
	{
		// check if no. of overflows = 12
		if (tot_overflow >= 12)  // NOTE: '>=' is used
		{
			// check if the timer count reaches 53
			if (TCNT0 >= 53)
			{
				PORTC ^= (1 << 0);    // toggles the led
				TCNT0 = 0;            // reset counter
				tot_overflow = 0;     // reset overflow counter
			}
		}
	}
}
