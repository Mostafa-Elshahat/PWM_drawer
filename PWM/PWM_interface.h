/*
 * PWM_interface.h
 *
 * Created: 2025-02-23 1:05:22 PM
 *  Author: MOSTAFA ALI MAHMOUD
 */ 


#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

void PWM_voidInitChannel0(void);
void PWM_voidGeneratePWMChannel0(u8 copy_u8DutyCycle);
void PWM_voidStopChannel0(void);
//channel two
void PWM_voidInitChannel2(void);
void PWM_voidGeneratePWMChannel2(u8 copy_u8DutyCycle);
void PWM_voidStopChannel2(void);
void PWM_Read(u8* dutyCycle);
void PWM_Initpwmread(void);
#endif /* PWM_INTERFACE_H_ */