sbit clk  = P1^0;
sbit dout  = P1^1;
sbit din = P1^2;
sbit cs   = P1^3;

unsigned int read_adc()
{
	unsigned int temp = 0;	
	signed char i;
	cs = 0;	//chip is enabled for commu
	clk=0; din=1; clk=1; //Start bit
	clk=0; din=1; clk=1; //Single Ended Mode Selected
	clk=0; din=1; clk=1; //D2 is dont care in MCP3204 
	
	//Selecting CH0
	clk=0; din=1 ;clk=1; //D1 bit for ch select
	clk=0; din=0 ;clk=1; //D0 bit for ch select & Start Sampling
	
	clk=0; din=1; clk=1; //Tsample 
	clk=0; din=1; clk=1; //for NULL
	
	//reading 12bits digital val from ADC
	for (i=11; i>=0; i--)
	{
		clk=0;
		if (dout==1)
			temp|=(1<<i);
		
		clk=1;
	}
	cs=1;//Chip is disabled
	return temp;
}
	