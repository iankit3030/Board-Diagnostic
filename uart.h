	
	
	void uart_init(int baud)
	{
		SCON = 0X50;
		TMOD = 0X20;
			
		switch(baud)
		{
			case 7200  : TH1 = 252;break;
			case 9600  : TH1 = 253;break;
			case 28800 : TH1 = 255;break;
			case 57600 : TH1 = 252;PCON = 0x80;break;
			default : TH1 = 253;
		}

		TR1 = 1;
	}

	void uart_tx(unsigned char ch)
	{
		SBUF = ch;
		while(TI==0);
		TI=0;
	}  

	unsigned  uart_rx()
	{
		while(RI==0);
		RI=0;
		return SBUF;
	} 

	void uart_string(char *s)
	{
	 while(*s)
	 uart_tx(*s++);
	} 

	/*void uart_integer(int n)
	{
	 
	 char buf[10];
	 sprintf(buf,"%d",n);	
	 uart_string(buf);
	}

	void uart_float(float n)
	{
	  char buf[10];
	  sprintf(buf,"%d",n);
	  uart_string(buf);
	}*/
	







