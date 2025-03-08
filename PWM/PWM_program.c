/*
 * PWM_program.c
 *
 * Created: 2025-02-23 1:06:48 PM
 *  Author: MOSTAFA ALI MAHMOUD
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
/*pwm library*/
#include "PWM_config.h"
#include "PWM_interface.h"
#include "PWM_register.h"

/* function implementation*/

void PWM_voidInitChannel0(void)
{
	//Select Mode = fast PWM Mode
	SET_BIT(TCCR0_REG, WGM00);
	SET_BIT(TCCR0_REG, WGM01);
	
	// Select Non Inverting Output
	CLR_BIT(TCCR0_REG, COM00);
	SET_BIT(TCCR0_REG, COM01);
	
	
}
void PWM_voidGeneratePWMChannel0(u8 copy_u8DutyCycle)
{
	if (copy_u8DutyCycle <= 100)
	{
		//under non inverting output
		OCR0_REG=((copy_u8DutyCycle*256)/100)-1;
		//select pre_scaler =64
		SET_BIT(TCCR0_REG,CS00);
		SET_BIT(TCCR0_REG,CS01);
		CLR_BIT(TCCR0_REG,CS00);
			
	} 
	else
	{
		//return error state 
	}

}
void PWM_voidStopChannel0(void)
{
		CLR_BIT(TCCR0_REG,CS00);
		CLR_BIT(TCCR0_REG,CS01);
		CLR_BIT(TCCR0_REG,CS00);
}
/* Function Implementation */
void PWM_voidInitChannel2(void)
{
	// Set PD7 (OC2) as output
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN7, DIO_PIN_OUTPUT);

	// Select Fast PWM Mode (Mode 3)
	SET_BIT(TCCR2_REG, WGM20);
	SET_BIT(TCCR2_REG, WGM21);

	// Select Non-Inverting Output Mode
	CLR_BIT(TCCR2_REG, COM20);
	SET_BIT(TCCR2_REG, COM21);
}

void PWM_voidGeneratePWMChannel2(u8 copy_u8DutyCycle)
{
	if (copy_u8DutyCycle <= 100)
	{
		// Calculate OCR2 value for duty cycle
		OCR2_REG = ((copy_u8DutyCycle * 256) / 100) - 1;

		// Select Prescaler = 64
		SET_BIT(TCCR2_REG, CS20);
		SET_BIT(TCCR2_REG, CS21);
		CLR_BIT(TCCR2_REG, CS22);
	}
	else
	{
		// Return error state (Invalid duty cycle)
	}
}

void PWM_voidStopChannel2(void)
{
	// Stop PWM by clearing prescaler bits
	CLR_BIT(TCCR2_REG, CS20);
	CLR_BIT(TCCR2_REG, CS21);
	CLR_BIT(TCCR2_REG, CS22);
}
/* Function to Read PWM and Return  Duty Cycle */

/****/
void PWM_Read(u8* dutyCycle)
{
	u16 RisingEdge = 0, FallingEdge = 0, Ton = 0, Ttotal = 0;
	u16 timeout = 50000;  // Timeout counter to prevent hanging

	// Set PD6 (ICP1) as input
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN6, DIO_PIN_INPUT);

	// Enable Noise Canceler, Capture on Rising Edge, Prescaler = 64
	TCCR1B_REG = (1 << ICES1) | (1 << CS11) | (1 << CS10);

	// Wait for First Rising Edge with Timeout
	timeout = 50000;
	while ((GET_BIT(TIFR_REG, ICF1) == 0) && (timeout > 0)) {
		timeout--;
	}
	if (timeout == 0) {
		*dutyCycle = 0;   // No signal detected, set duty cycle to 0%
		return;
	}

	RisingEdge = ICR1_REG;
	SET_BIT(TIFR_REG, ICF1);  // Clear flag for next capture

	//  Capture Falling Edge with Timeout
	timeout = 50000;
	CLR_BIT(TCCR1B_REG, ICES1);  // Switch to falling edge
	while ((GET_BIT(TIFR_REG, ICF1) == 0) && (timeout > 0)) {
		timeout--;
	}
	if (timeout == 0) {
		*dutyCycle = 0;
		return;
	}

	FallingEdge = ICR1_REG;
	SET_BIT(TIFR_REG, ICF1);  // Clear flag

	//  Capture Next Rising Edge with Timeout
	timeout = 50000;
	SET_BIT(TCCR1B_REG, ICES1);  // Switch back to rising edge
	while ((GET_BIT(TIFR_REG, ICF1) == 0) && (timeout > 0)) {
		timeout--;
	}
	if (timeout == 0) {
		*dutyCycle = 0;
		return;
	}

	Ttotal = ICR1_REG - RisingEdge;
	SET_BIT(TIFR_REG, ICF1);  // Clear flag

	// Calculate Ton
	Ton = FallingEdge - RisingEdge;

	// Prevent division by zero
	if (Ttotal == 0) {
		*dutyCycle = 0;  // No valid PWM detected
		return;
	}

	// Calculate Duty Cycle
	*dutyCycle = ((Ton * 100) / Ttotal);
}
