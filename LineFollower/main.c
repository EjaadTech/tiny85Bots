#include "../template.h"

int main(void){
	// PB3 - ADC 3 - pin 2 - Left LDR
	// PB4 - ADC 2 - pin 3 - Right LDR
	
	// PB0 - OC0A - pin 5 - Left Motor
	// PB1 - OC0B - pin 6 - Right Motor
	
	OUT(B,0);
	OUT(B,1);
	
	TCCR0A = BIT(WGM00) | BIT(COM0A1)| BIT(COM0B1);
	TCCR0B = BIT(CS02);

	ADCSRA = BIT(ADEN);
	
	unsigned int rightMotor=0;
	unsigned int leftMotor=0;
	
	while(1){
		ADMUX = BIT(MUX0) | BIT(MUX1);	// Left LDR
		ADCSRA = BIT(ADEN) | BIT(ADSC) | BIT(ADPS0) | BIT(ADPS1) | BIT(ADPS2);
		while(ADCSRA&BIT(ADSC));
		rightMotor = ADC/4;

		ADMUX = BIT(MUX1);	// Right LDR
		ADCSRA = BIT(ADEN) | BIT(ADSC) | BIT(ADPS0) | BIT(ADPS1) | BIT(ADPS2);
		while(ADCSRA&BIT(ADSC));
		leftMotor = ADC/4;
		
		OCR0B = rightMotor;
		OCR0A = leftMotor;
	}
return(0);
}

/*
		OCR0B = OCR0B + change;
		if(OCR0B>250)
			change=-1;.
		else if(OCR0B<5)
			change=1;
	
		delay(10);

	
	ADCSRA = BIT(ADEN) | BIT(ADSC) | BIT(ADPS0) | BIT(ADPS1) | BIT(ADPS2);
		while(ADCSRA&BIT(ADSC));
		OCR0B = ADC;	
		

*/