#include <REGX52.H>//任何自定义的变量，函数在调用前必须有定义和声明（同一个.c）
#include "Delay.h"

unsigned char Nixie_Buf[9]={0,10,10,10,10,10,10,10,10};

unsigned NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7E,0x6F,0x00,0x40};

void Nixie_SetBuf(unsigned char location,number)
{
	Nixie_Buf[location]=number;
}

void Nixie_Scan(unsigned char location,number)
{
	P0=0x00;	//断码清零
	switch(location)	//位选
	{
		case 1:P2_4=0;P2_3=0;P2_2=0;break;
		case 2:P2_4=0;P2_3=0;P2_2=1;break;
		case 3:P2_4=0;P2_3=1;P2_2=0;break;
		case 4:P2_4=0;P2_3=1;P2_2=1;break;
		case 5:P2_4=1;P2_3=0;P2_2=0;break;
		case 6:P2_4=1;P2_3=0;P2_2=1;break;
		case 7:P2_4=1;P2_3=1;P2_2=0;break;
		case 8:P2_4=1;P2_3=1;P2_2=1;break;
	}	
	P0=NixieTable[number];
}

void Nixie_Loop(void)
{
	static unsigned char i=1;
	Nixie_Scan(i,Nixie_Buf[i]);
	i++;
	if(i>=9){i=1;}
}