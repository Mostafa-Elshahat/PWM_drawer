/*
 * LCD_interface.h
 *
 * Created: 19/11/2024 09:46:05 م
 *  Author: Kareem Hussein
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


#define LCD_LINE_ONE			0
#define LCD_LINE_TWO			1
#define prescaler				64
                          /*************** APIS PROTO TYPES ***************/
						  
				

void LCD_voidInit                (void);
void LCD_voidSendCommand         (u8 copy_u8cmnd);
void LCD_voidDisplayChar         (u8 copy_u8Data);
void LCD_voidDisplayString       (u8* copy_Pu8String);
void LCD_voidClear               (void); 
void LCD_voidGoToSpecificPosition(u8 copy_u8LineNumber, u8 copy_u8Position);
void LCD_voidDisplayNumber       (u32 copy_u32Number); 
void LCD_voidDisplayFloat		 (float copy_fNumber);
void LCD_voidShift               (u8 copy_u8ShifttingDirection); //command data sheet
void LCD_voidDisplayPWM(u8 dutyCycle);


#endif /* LCD_INTERFACE_H_ */