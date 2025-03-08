/*
 * TMR0_config.h
 *
 * Created: 16/12/2024 09:35:24 م
 *  Author: Kareem Hussein
 */ 


#ifndef TMR0_CONFIG_H_
#define TMR0_CONFIG_H_


/* Options FOR TMR0 Mode:
1- TMR0_NORMAL_MODE
2- TMR0_CTC_MODE
*/
#define TMR0_MODE				            TMR0_CTC_MODE

#define TMR0_PRELOAD_VALUE			        154
#define TMR0_OVER_FLOW_COUNTER              2442

#define TMR0_OUTPUT_COMPARE_VALUE			249
#define TMR0_CTC_COUNTER                    1500


#endif /* TMR0_CONFIG_H_ */