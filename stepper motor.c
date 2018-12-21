	#include<reg51.h>
	#include"delay.h"
	sbit m1=P1^0;
	sbit m2=P1^1;
	sbit m3=P1^2;
	sbit m4=P1^3;

	 void main()
	 {

	
	   while(1)
	   {
		 m1=1;m2=1;m3=0;m4=0;
		 delay_ms(2);
		 m1=0;m2=1;m3=1;m4=0;
		 delay_ms(2);
		 m1=0;m2=0;m3=1,m4=1;
		 delay_ms(2);
		 m1=1;m2=0;m3=0;m4=1;
		 delay_ms(2);
		
	   }
	  
	 }