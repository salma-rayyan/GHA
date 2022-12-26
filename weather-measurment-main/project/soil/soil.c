
/*
 * soil.c
 *
 * Created: 12/25/2022 10:29:53 AM
 *  Author: Mina
 */ 
#include "soil.h"
void soil(void){
	TU16 adc_value;
	float moisture;
	char array[10];
	adc_value = ADC_READ(1);
	moisture = 100-(adc_value*100.00)/1023.00;
	lcd_goto_xy(0,0);
	lcd_write_word("Moisture:");
	dtostrf(moisture,3,2,array);  //turn float to string dtostrf(float_value, min_width, num_digits_after_decimal, where_to_store_string)
	strcat(array,"%   ");  //join to string
	lcd_goto_xy(0,10);
	lcd_write_word(array);
	memset(array,0,10); //fill block of memory
}
