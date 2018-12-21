sbit C0=P2^0;
sbit C1=P2^1;
sbit C2=P2^2;
sbit C3=P2^3;

sbit R0=P2^4;
sbit R1=P2^5;
sbit R2=P2^6;
sbit R3=P2^7;

bit key_test;

char ch[4][4]={1,2,3,4,
			   5,6,7,8,
			   9,10,11,12,
			   13,14,15,16};	



unsigned char keyscan(void)
{
   	int r=0,c=0;
	R0=R1=R2=R3=0;
	C0=C1=C2=C3=1;
	while(C0&C1&C2&C3);
	while(1)
	{
		R0=0;R1=R2=R3=1;
		if(!(C0&C1&C2&C3))
		{
			r=0;
			break;
		}
		R1=0;R0=R2=R3=1;
		if(!(C0&C1&C2&C3))
		{
			r=1;
			break;
		}
		R2=0;R1=R0=R3=1;
		if(!(C0&C1&C2&C3))
		{
			r=2;
			break;
		}
		R3=0;R1=R2=R0=1;
		if(!(C0&C1&C2&C3))
		{
			r=3;
			break;
		}
	}
	if(C0==0)
		c=0;
	else if(C1==0)
		c=1;
	else if(C2==0)
		c=2;
	else if(C3==0)
		c=3;
	while(!(C0&C1&C2&C3));
	return(ch[r][c]);
}