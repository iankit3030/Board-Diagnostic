#include <REG51.H>
#include <stdio.h>
#include "delay.h"
#include "adc.h"
#include "lcd8bit.h"
main ()
{
	unsigned int temp;
	float t;
	lcd_init ();
	while (1)
	{
		temp = read_adc();//read ch0
		lcd_cmd(0x01);
		lcd_integer(temp);//displaying ADC val in decimal
		t=((temp*5.0)/4095);
		lcd_cmd(0xC0);
		lcd_float(t);//displaying ADC val in float
		delay_ms (100);
	}	
}
