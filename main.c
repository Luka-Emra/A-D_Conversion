/*
 * GccApplication1.c
 *
 * Created: 12/11/2020 3:17:58 AM
 * Author : Luka Emrashvili
 * Red ID: 823355800
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL   
#define BAUD 9600         
#define BAUDRATE ((F_CPU)/(16UL*BAUD))-1


int main(void)
{
	DDRC &=~(1<<PINC1);
	DDRB |=(1<<DDB5);
	cli();
	init_ADC();
	PWM_timer0();
	LED_timer2();
	sei();
	while (1)
	{
		
	}
}

ISR (ADC_vect)
{
	uint16_t ADC_Potentiometer = ADC;
	OCR2B = ((ADC_Potentiometer)/1024.0)*88; 
	
}

ISR (TIMER2_COMPA_vect)
{
	if (OCR2B > 0 )
	PORTB |= (1<<5);
}

ISR (TIMER2_COMPB_vect)
{
	PORTB &= ~(1<<5);
}

void init_ADC(void)
{
	ADMUX |= (1<< REFS0);
	ADCSRA |= (1<< ADEN) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADPS2);
	ADCSRB |= (1<< ADTS1) | (1<<ADTS0);
}

void LED_timer2()
{
	TCCR2A |= (1<<WGM21);
	OCR2A = 88;
	TIMSK2 |= (1<<OCIE2A) | (1<<OCIE2B);
	TCCR2B |= (1<<CS22);
}

void PWM_timer0()
{
	TCCR0A |= (1<<WGM01);
	OCR0A = 62;
	TIMSK0 |= (1<<OCIE0A);
	TCCR0B |= (1<<CS02);
}

