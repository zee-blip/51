#include <REGX52.H>
void Delay(unsigned int xms);//delare the function first

unsigned char LEDNum;

void main()
{
	P2=~0X01;
	while(1)
	{	
		if(P3_1==0)
		{
			Delay(20);
			while(P3_1==0);
			Delay(20);
			LEDNum++;
			if(LEDNum>=8)
				LEDNum=0;//If there is only one code in the logic roll,don't need{}
			P2=~(0X01<<LEDNum);
		}
		if(P3_0==0)//!
		{
			Delay(20);
			while(P3_0==0);
			Delay(20);
			if(LEDNum==0)
				LEDNum=7;
    		else
				LEDNum--;//If there is only one code in the logic roll,don't need{}
			P2=~(0X01<<LEDNum);
		}
	}
}

void Delay(unsigned int xms)//the whole part of the code of the function
{
	unsigned char i, j;

	while(xms--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		//xms--;
	}
}