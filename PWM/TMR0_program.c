/*
 * TMR0_program.c
 *
 * Created: 2025-03-06 11:07:37 AM
 *  Author: mostafa ali mahmoud
 */ 

/* UTILES LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TMR0_interface.h"
#include "TMR0_config.h"
#include "TMR0_register.h"


static void(*PRV_pFunCallBackOVF)(void) = NULL;
static void(*PRV_pFunCallBackCTC)(void) = NULL;
static u16 PRV_u16CTC_counter;
	extern volatile u8 PWM_DoneFlagnew;


void TMR0_voidInit(void)
{
#if TMR0_MODE == TMR0_NORMAL_MODE
	//Select Mode = Normal Mode
	CLR_BIT(TCCR0_REG, WGM00);
	CLR_BIT(TCCR0_REG, WGM01);
	
	//Init Timer With Preload Value
	TCNT0_REG = TMR0_PRELOAD_VALUE;
	
	//Enable OVF Interrupt
	SET_BIT(TIMSK_REG, TOIE0);
	
#elif TMR0_MODE == TMR0_CTC_MODE	
	//Select Mode = CTC Mode
	CLR_BIT(TCCR0_REG, WGM00);
	SET_BIT(TCCR0_REG, WGM01);
	
	// Init Timer With output compare Value
	OCR0_REG = TMR0_OUTPUT_COMPARE_VALUE;
	
	//Enable OC Interrupt
	SET_BIT(TIMSK_REG, OCIE0);
#endif
}


void TMR0_voidStart(void)
{
	//Select Prescaler Value = 64
	SET_BIT(TCCR0_REG, CS00);
	SET_BIT(TCCR0_REG, CS01);
	CLR_BIT(TCCR0_REG, CS02);
}


void TMR0_voidStop(void)
{
	CLR_BIT(TCCR0_REG, CS00);
	CLR_BIT(TCCR0_REG, CS01);
	CLR_BIT(TCCR0_REG, CS02);
}


void TMR0_voidSetCallBackOVF(void(*copy_pFunAction)(void))
{
	if(copy_pFunAction != NULL)
	{
		PRV_pFunCallBackOVF = copy_pFunAction;
	} 
	else
	{
		//return Error State
	}
}


void TMR0_voidSetCallBackCTC(void(*copy_pFunAction)(void))
{
	if(copy_pFunAction != NULL)
	{
		PRV_pFunCallBackCTC = copy_pFunAction;
	}
	else
	{
		//return Error State
	}
}


void TMR0_voidSetDelay_msCompareMatchMode(u16 copy_u16Delay_ms)
{
	//Under Condition Tick Time = 4Ms, OCR0 = 249
	OCR0_REG = 249;
	PRV_u16CTC_counter = copy_u16Delay_ms;
}


//ISR Timer0 OverFlow (normal mode)
void __vector_11(void) __attribute__ ((signal));
void __vector_11(void)
{
	static u16 local_u16Counter = 0;
	local_u16Counter++;
	
	if(TMR0_OVER_FLOW_COUNTER == local_u16Counter)
	{
		//Re-Init Timer With Preload Value
		TCNT0_REG = TMR0_PRELOAD_VALUE;
		
		//Clear Counter
		local_u16Counter = 0;
		
		//Call Action
		if(PRV_pFunCallBackOVF != NULL)
		{
			PRV_pFunCallBackOVF();
		}
	}
		
}


//ISR Timer0 OutputCompare (CTC mode)
void __vector_10(void) __attribute__ ((signal));
void __vector_10(void)
{
	static u16 local_u16Counter = 0;
	local_u16Counter++;
	
	if(PRV_u16CTC_counter == local_u16Counter)
	{
		//Clear Counter
		local_u16Counter = 0;
		
		//Call Action
		if(PRV_pFunCallBackCTC != NULL)
		{
			PRV_pFunCallBackCTC();
		}
	}
}
