/* generate a 50 Hz PWM signal having 45% duty cycle, ctc mode
Frequency = 50 Hz
In other words, the time period, T
T = T(on) + T(off) = 1/50 = 0.02 s = 20 ms
Also, given that
Duty Cycle = 45%
Thus, solving according to equation given above, we get
T(on)  = 9 ms
T(off) = 11 ms
 * timerctcmode.c
 *
 * Created: 2022/6/15 13:09:04
 * Author : tende
 */ 

#include <avr/io.h>
//#define F_CPU 8000000UL
#include <avr/interrupt.h>

uint8_t count = 0;               // global counter

// initialize timer, interrupt and variable
void timer1_init()
{
	// set up timerX with 8x prescaler and CTC mode
	TCCR1B |= (1 << WGM12)|(1 << CS11);
	// initialize counter
	TCNT1 = 0;
	// initialize compare value
	OCR1A = 19999;//8M/8*20*0.001-1
	// enable compare interrupt
	TIMSK |= (1 << OCIE1A);
	// enable global interrupts
	sei();
}

// process the ISR that is fired
ISR (TIMER1_COMPA_vect)
{
	// do whatever you want to do here
	// say, increment the global counter
	count++;
	
	// check for the global counter
	// if count == odd, delay required = 11 ms
	// if count == even, delay required = 9 ms
	// thus, the value of the OCRx should be constantly updated
	if (count % 2 == 0)
	{
		OCR1A = 8999;      // calculate and substitute appropriate value
		PORTC |= (1<<PC0);
	}
	else{
	OCR1A = 10999;     // calculate and substitute appropriate value
	PORTC &= ~(1<<PC0);
	}
}

int main(void)
{
	// initialize the output pin, say PC0
	DDRC |= (1 << 0);
	
	// initialize timerX
	timer1_init();
	
	// loop forever
	while(1)
	{
		// do nothing
		
	}
}