/*
 * rain.c
 *
 * Created: 12/25/2022 10:40:20 AM
 *  Author: Mina
 */ 
#include "rain.h"

void rain(void){
	lcd_goto_xy(1,0);
	lcd_write_word("Rain:");
	if (GET_Bit(DIO_PINC,0)==1){
		lcd_goto_xy(1,6);
		lcd_write_word("Raining");
		}else{
		lcd_goto_xy(1,6);
		lcd_write_word("No Rain");
	}
}