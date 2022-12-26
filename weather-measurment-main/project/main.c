/*
 * project.c
 *
 * Created: 11/13/2021 11:15:20 PM
 * Author : Mina
 */ 
#include "main.h"
int state = 0;
void toggle(void);

int main(void)
{	
	init_interrrupt();
	
	_delay_ms(2000);
	DIREC();
	lcd_init();
	adc_init();
	
	lcd_clear();
    while (1) 
    {
		SET_CallBack_INT0(toggle);
		if (state ==1){
		    int_Dhtt();
			_delay_ms(2000);
		}
		lcd_clear();
		_delay_ms(5);
		if (state == 0 ){
        	soil();
			rain();
			_delay_ms(2000);
		}
		lcd_clear();
		_delay_ms(5);
	}

}

void toggle(void){
	if (state == 1){
		state = 0;
	}
	else{
		state = 1;
	}
}