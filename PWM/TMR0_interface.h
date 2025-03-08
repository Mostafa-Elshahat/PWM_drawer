/*
 * TMR0_interface.h
 *
 * Created: 16/12/2024 09:35:06 م
 * Author : MOSTAFA ALI MAHMOUD

 */ 


#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_

/* MACROS FOR TIMER0 MODE CONFIGURATION */
#define TMR0_NORMAL_MODE			1
#define TMR0_CTC_MODE               2

                      /*************** APIS PROTOTYPES ***************/

void TMR0_voidInit                       (void);
void TMR0_voidStart                      (void);
void TMR0_voidStop                       (void);
void TMR0_voidSetCallBackOVF             (void(*copy_pFunAction)(void));
void TMR0_voidSetCallBackCTC             (void(*copy_pFunAction)(void));
void TMR0_voidSetDelay_msCompareMatchMode(u16 copy_u16Delay_ms);


#endif /* TMR0_INTERFACE_H_ */