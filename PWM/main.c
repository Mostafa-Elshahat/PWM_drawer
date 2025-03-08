/*
 * PWM.c
 *
 * Created: 2025-02-23 1:04:45 PM
 * Author : MOSTAFA ALI MAHMOUD
 */ 

#include <avr/io.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
/*pwm library*/
#include "PWM_interface.h"
/*lcd library*/
#include "LCD_interface.h"
#include <util/delay.h>
/*include the timer0*/
#include "TMR0_interface.h"
#include "TMR0_register.h"
int main(void)
{
	
	u8 Duaty_cycle_generated = 50;
	u8 Duaty_cycle_reading = 0;


	// LCD Init
	LCD_voidInit();
	
	// Set PD7 as Output (To generate PWM)
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN7, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN6, DIO_PIN_INPUT);

	// Initialize Timer0 for PWM Reading
	
	TCNT0_REG = 0;  // Start from 0
	TCCR0_REG = (1 << CS01) | (1 << CS00);  

	// Generate PWM First (To ensure a signal exists)
	PWM_voidInitChannel2();
	PWM_voidGeneratePWMChannel2(Duaty_cycle_generated);
		
    while (1) 
    {
	
				PWM_Read( &Duaty_cycle_reading);

			if (Duaty_cycle_reading == 0)
			{
				LCD_voidDisplayPWM(Duaty_cycle_generated);
			}
			else
			{
				
				LCD_voidDisplayPWM(Duaty_cycle_reading);
			}

			
		}
	
    
}

