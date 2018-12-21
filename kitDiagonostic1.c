		#include<reg51.h>
		#include<stdio.h>
		#include"delay.h"
		#include"lcd8bit.h"
		#include"uart.h"
		#include"keypad.h"
		#include"I2C.h"
		#include"I2C_DEVICE.h"
		#include"adc.h"

/************** option selection  ****************/
		unsigned char ch1,ch2;
	    
/*************   dc motor *******************************/

	         	sbit m1=P2^2;              
                sbit m2=P2^3; 		         



/*************   stepper motor pins *********************/

                sbit a1= P2^4;              
                sbit a2= P2^5;
                sbit m3= P2^6;
                sbit m4= P2^7;	

void my_isr1(void) interrupt 0
{
	switch(ch1)
	{
		case 'a':
		      uart_string("\r\n***************LEDs are working properly*****************\r\n");
			  ch1=0;
		      P2=0x0f;
			  break;
		
	    case 'b':
			  uart_string("\r\n*****************ULN2003 is working properly*******************\r\n");
			  ch1=0;
			  a1=0;a2=0;m3=0;m4=0;
		          break;
		
	    case 'c':
		      uart_string("\r\n**********************keypad are working properly**********************\r\n");
			  ch1=0;
			  break;
		
		case 'd':
			  uart_string("\r\n**************************EEPROM is working properly************************\r\n");
			  lcd_cmd(0x01);
			  ch1=0;
			  break;
		  
		case 'e':
			  uart_string("\r\n*************************LCD working properly**********************\r\n");
			  lcd_cmd(0x01);
			  ch1=0;

			  break; 
		
		case 'f':
			  uart_string("\r\n**********************SPI(LDR) is working properly************************\r\n");
			  delay_ms(100);
			  lcd_cmd(0x01);
			  ch1=0;
			  break;
		
		case '1':
			  uart_string("\r\n**************************L293d is working properly***************************\r\n");
			  ch1=0;
			 
			  m1=0;  
              m2=0;
			  break;	
			  
			  
 	}
}
void my_isr2(void) interrupt 2
{
	switch(ch1)
	{
		case 'a':
			  uart_string("\r\n****************LEDs are not working properly******************\r\n");
			  ch1=0;
		      P2=0x0f;
			  break;
			 
	    case 'b':
			  uart_string("\r\n**********************ULN2003 is not working properly****************\r\n");
			  ch1=0;
			  a1=0;a2=0;m3=0;m4=0;
			  break;
		
	    case 'c':
		      uart_string("\r\n*******************keypad is not working properly********************\r\n");
			  ch1=0;
			  break;
		
		case 'd':
			  uart_string("\r\n*************************EEPROM is not working properly*************************\r\n");			  
			  lcd_cmd(0x01);
			  ch1=0;
			  break;
			 
		case 'e':
			  uart_string("\r\n*************************LCD is not working properly**************************\r\n");
			  lcd_cmd(0x01);
			  ch1=0;
			  break; 
			
		case 'f':
			  uart_string("\r\n**********************SPI(LDR) is not working properly*****************************\r\n");
			  delay_ms(100);
			  lcd_cmd(0x01);
			  ch1=0;
			  break;
			
		case '1':
			  uart_string("\r\n*************************L293d is not working properly*******************************\r\n");
			  ch1=0;
			  m1=0;  
              m2=0;
			  break;
		
        }
}


/********************             main program             ***********************/

		main()
		{

/***************         declarations              *******************/

		         unsigned int temp;
			     unsigned char temp1;            /***************    i2c  ******************/
	                 float t;

/***************  uart and external interrupt initialization        ****************/
		         uart_init(9600);    
                 EA=EX0=EX1=1;
		         IT0=IT1=1;


		while(1)
		{ 
		 uart_string("\r\nenter the device which you want to test \r\n");
		 uart_string("a) LED\r\n");
		 uart_string("b) ULN2003 \r\n");
		 uart_string("c) keypad \r\n");
		 uart_string("d) I2C(EEPROM) \r\n");
		 uart_string("e) LCD \r\n");
	         uart_string("f) SPI(LDR)\r\n");
		 uart_string("1) L293D \r\n");

		 ch1=uart_rx();
		 
	 	 switch(ch1)
		 {

/**********************       led testing   *************************/

case 'a':

			uart_string("\r\nLEDs Testing\r\n");
			P2=0x0F;
			
			uart_string("Connect AL LEDs to P2.0 to P2.3 and AH LEDs to P2.4 to P2.7 and then press enter\r\n");
     		  uart_rx();			
			P2=0xF0;
			uart_string("All LEDs Will be glowing\r\n");
		        while(ch1);
		
		 	   break; 
 	  	


/*********************      ULN2003  testing    *****************************/    
		 
case 'b':
	            uart_string("\r\nULN2003 Testing\r\n");
		        uart_string("CONNECT ULN2003 pin to P2.4 to P2.7 \r\n");
		        uart_string("PRESS ENTER TO CONTINUE\r\n");
		        uart_rx();
				 
		       
			  
	                while(ch1)
	                {
		         a1=1;a2=1;m3=0;m4=0;
		         delay_ms(2);
		         a1=0;a2=1;m3=1;m4=0;
		         delay_ms(2);
		         a1=0;a2=0;m3=1,m4=1;
		         delay_ms(2);
		         a1=1;a2=0;m3=0;m4=1;
		         delay_ms(2);
	                }    
					 
		       while(ch1);


		 	     break;
		
/**************************    KEYPAD TESTING   ********************************/  	
case 'c':

			uart_string("\r\nKEYPAD TESTING\r\n");
			uart_string("CONNECT KEYPAD C0 to R3 pins from  P0.0 to P0.7 and Ensure all DS2 switches off\r\n");
			uart_string("ENTER TO CONTINUE\r\n");
			uart_rx();
    		        uart_string("Enter key on keypad\r\n");

			ch2=keyscan();
			uart_string("Have you pressed   sw ");
			if(ch2<10)
			   uart_tx(ch2%10+48);
			else
			{
				uart_tx(ch2/10+48);
				uart_tx(ch2%10+48);
			}

		    uart_string("\r\nIf yes Y/y or no N/n\r\n");
		    while(ch1);

		    break;

/**********************   I2C   testing  *****************************/
case 'd':     

			uart_string("\r\nI2C(EEPROM) Testing\r\n");
			uart_string("Ensure no connectors are connected to P2.0(SDA) and P2.1(SCL)\r\n");
			//uart_string(" EEPROM\r\n");
			//ch1=uart_rx();
				
			 
				  
		          i2c_device_write(0xA0,0x2,'A');
		          temp1 = i2c_device_read(0xA0,0x2);
		          
				  lcd_data(temp1);

				  uart_string("\r\nIf A then yes Y/y or no N/n\r\n");
	              while(ch1);
		
				 
				 
				 break;

/*************************    lcd TESTING     *****************************************/
case 'e': 
   
			        	uart_string("\r\nLCD Testing........... \r\n");
                        uart_string("Make sure no connectors are connected to P0 and P2\r\n");
                        uart_string("Ensure DS0 are on for DATA LINES connected from P0.4 TO P0.7 AND DS3 switches on for CONTROL SIGNALS P3.4 TO P3.6)\n");
                        uart_string("Then enter any key to continue\r\n");
                        uart_rx();
                        lcd_init();
                        lcd_cmd(0x80);
                        lcd_string("shubham");
                        lcd_cmd(0xC0);
                        lcd_string("baghel");
                        uart_string("If Viewing display on LCD \r\n");
                        uart_string("Then Y/y for Yes or N/n for No from keyboard\r\n");
	                while(ch1);
              
             		   break;

/***********************  SPI testing   *******************/
case 'f':
				 uart_string("\r\nSPI(LDR) Testing\r\n");
				 uart_string("CONNECT SPI pin to P1.0 to P1.3 \r\n");
				 uart_string("PRESS ENTER TO CONTINUE\R\N");
				 uart_rx();
				 
				 uart_string("LDR will start giving  values\r\n");
		     uart_string("If yes y/Y or no n/N\r\n");
         //ch2=uart_rx();
			        
	                lcd_init ();
	                while(ch1)
                  	{
	                	temp = read_adc();
	                	lcd_cmd(0x01);
	                 	lcd_integer(temp);
	                	t=((temp*5.0)/4095);	 
		                lcd_cmd(0xC0);
		                lcd_float(t);
	                   	delay_ms (100);
                   	}	


				
		 	               break;
		
		
/***************************   L293D  testing   **********************/                     
case '1':                

                        uart_string("\r\n L293D Testing using dc motor \r\n");
                        uart_string("Connect motor to P2.2 and P2.3 then enter any key to continue\r\n");
                        uart_rx();
                        uart_string("Enter 1 for rotating the motor in forward direction\r\n");
                        uart_string("Enter 2 for rotating the motor in reverse direction\r\n");
                        
                        ch1=uart_rx();
                        uart_tx(ch1);

                        if(ch1=='1')
                        {
						 uart_string("clockwise\r\n");
                                m1=0;  
                                m2=1;
                        }
												
                        if(ch1=='2')
                        {
						 uart_string("anti-clockwise\r\n");
                                m1=1;
                                m2=0;
                        }
                                   
					    uart_string("motor will be rotating\r\n");
			            uart_string("If yes y/Y or no n/N\r\n");
				    while(ch1);
		
		 	   break;
 	  	    			         
		 }
		 }							   
	  
		 }
/*****************************   END   ************************************/
