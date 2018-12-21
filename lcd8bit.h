
sfr LCD_PORT= 0X80;
sbit RS = P3^4;
sbit RW = P3^5;
sbit EN = P3^6;



			  
void lcd_cmd(unsigned char c)
{
 LCD_PORT = c;
 RS = 0;
 RW = 0;
 EN = 1;
 delay_ms(2);
 EN = 0;	  
 }

   	  void lcd_init()
 {
  lcd_cmd(0x2);
  lcd_cmd(0x38);
  lcd_cmd(0x6);
  lcd_cmd(0xE);
  lcd_cmd(0x1);
 }	 


 void lcd_data(unsigned char d)
 {
 	LCD_PORT = d;
	RS = 1;
	RW = 0;
	EN = 1;
	delay_ms(2);
	EN= 0;
 }
 


 void lcd_string(char * s)
 {
 while(*s)
 lcd_data(*s++);
 }
 


	   void mylcd_integer(int n)
{
   char buf[10],i=0;
   if(n==0)
   {
    lcd_data('0');
	return;
   }


   if(n<0)
   {
   lcd_data('-');
   n=-n;
   }

	while(n)
	{
	  buf[i++]=n%10 +48	;
	  n=n/10;
	}
 
    for(i=--i;i>=0;i--)
	lcd_data(buf[i]);
   
}

   void lcd_integer (int n)
{
	char buf[10];
	sprintf (buf,"%d",n);
	lcd_string (buf); 	
}

void lcd_float(float f)
{
	char buf[7];
	sprintf(buf,"%.2f",f);
	lcd_string (buf); 
}

