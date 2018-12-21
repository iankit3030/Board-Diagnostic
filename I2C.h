
	 sbit SDA = P2^0;
	 sbit SCL = P2^1;
		
	 void i2c_start()
		{
				SCL = 1;
				SDA = 1;
				SDA=0;
		}
			
		void i2c_stop()
		 {
				SCL = 0;
				SDA = 0;
				SCL = 1;
			  SDA = 1;
		 }
			
		void i2c_write(unsigned char d)
		 {
			signed char i;
			for(i=7;i>=0;i--)
			{
				SCL = 0;
			  SDA = (d&(1<<i))?1:0;
				SCL = 1 ;
			}
		 }
		 
		unsigned char i2c_read()
		 {
				signed char i;
				unsigned char temp=0;
				for(i=7;i>=0;i--)
			  {
					SCL = 1;
					if(SDA==1)
					temp = temp|(1<<i);
					SCL = 0;
				}
				return temp;
		 }
		 
		 
		void i2c_ack()
		 {
			SCL = 0;
			SDA = 1;
			SCL = 1;
			while(SDA==1);
			SCL = 0;
		 }
		 
		void i2c_noack()
		 {
			 SCL = 0;
			 SDA = 1;
			 SCL = 1;
		 }
		 
		 
		 
		 
		 
		 
		 
		 
		 