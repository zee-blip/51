#include <REGX52.H>
#include "Timer0.h"
#include "key.h"
#include <INTRINS.H>


unsigned char KeyNum,LEDMode;

void main()
{
	P2=0xFE;
	Timer0_Init();
	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)
		{
			LEDMode++;
			if(LEDMode>=2)LEDMode=0;
		}
	}
}


void Timer0_Routine() interrupt 1 //中断函数
{
	static unsigned int T0Count;	//static关键字让变量在结束后依然占据空间，且只可以由本函数使用
	TH0=64535/256;//重装定时器
	TL0=64535%256+1;	
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;
		if(LEDMode==0)
			P2=_crol_(P2,1);	
		//			P2<<=1;	//区别在于他不循环左移
		if(LEDMode==1)
			P2=_cror_(P2,1);
	}

}