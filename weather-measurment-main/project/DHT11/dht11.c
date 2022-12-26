/*
 * dht11.c
 *
 * Created: 12/25/2022 10:44:27 AM
 *  Author: Mina
 */ 
#include "dht11.h"
char c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

void Requestt()
{
	SET_BiT(DIO_DDRC,1);
	C1_CLEAR;	/* set to low pin */
	_delay_ms(20);			/* wait for 20ms */
	C1_OUTPUT;
}
void Responsee()
{
	CLR_Bit(DIO_DDRC,1);  //make pin input
	while(C1_INPUT);      //wait for dht11 low pulse
	while(C1_INPUT==0);   //wait for dht11 high pulse
	while(C1_INPUT);      //wait for dht11 low pulse
}

TU08 Receive_dataa()			//receive data
{
	for (int q=0; q<8; q++)
	{
		while(C1_INPUT == 0);  // check received bit 0 or 1
		_delay_us(30);
		if(C1_INPUT)           // if high pulse is greater than 30ms
		c = (c<<1)|(0x01);	   // then its logic HIGH
		else			       // otherwise its logic LOW
		c = (c<<1);
		while(C1_INPUT);
	}
	return c;
}
void int_Dhtt (void){
	char data[5];
	lcd_goto_xy(0,0);
	lcd_write_word("Humidity =");
	lcd_goto_xy(1,0);
	lcd_write_word("Temp =");
	Requestt();		           // send start pulse
	Responsee();		       // receive response
	I_RH=Receive_dataa();	   // store first eight bit in I_RH
	D_RH=Receive_dataa();	   // store next eight bit in D_RH
	I_Temp=Receive_dataa();	   // store next eight bit in I_Temp
	D_Temp=Receive_dataa();	   // store next eight bit in D_Temp
	CheckSum=Receive_dataa();  // store next eight bit in CheckSum
	if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
	{
		lcd_goto_xy(0,0);
		lcd_write_word("Error");
	}
	
	else
	{
		itoa(I_RH,data,10);
		lcd_goto_xy(0,11);
		lcd_write_word(data);
		lcd_write_word(".");
		
		itoa(D_RH,data,10);
		lcd_write_word(data);
		lcd_write_word("%");

		itoa(I_Temp,data,10);
		lcd_goto_xy(1,7);
		lcd_write_word(data);
		lcd_write_word(".");
		
		itoa(D_Temp,data,10);
		lcd_write_word(data);
		lcd_write_word("C ");
		lcd_set_courser(1,12);
	}
}