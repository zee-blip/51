#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "timer0.H"

unsigned char Sec=55,Min=59,Hour=23;

void main()
{
	LCD_Init();
	Timer0_Init();
	
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,1,"  :  :");
	
	while(1)
	{
		LCD_ShowNum(2,1,Hour,2);
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowNum(2,7,Sec,2);
	}
}

void Timer0_Routine() interrupt 1 //中断函数
{
	static unsigned int T0Count;	//static关键字让变量在结束后依然占据空间，且只可以由本函数使用
	TH0=64535/256;//重装定时器
	TL0=64535%256+1;	
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		Sec++;
		if(Sec>=60)
		{
			Sec=0;
			Min++;
			if(Min>=60)
			{
				Min=0;
				Hour++;
				if(Hour>=24)
				{
					Hour=0;
				}
			}
		}
	}
}