#include <REGX52.H>

/**
  * @brief 定时器0初始化，1ms@12.000MHz
  * @param 无 
  * @retval 无
  */
void Timer0_Init() //1ms@12.000MHz
{
//void Timer0Init(void)		//1ms@12.000MHz
//{
	//	AUXR &= 0x7F;		//Timer clock is 12T mode新版C52，老版不用
//	TMOD &= 0xF0;		//Set timer work mode
//	TMOD |= 0x01;		//Set timer work mode
//	TL0 = 0x18;		//Initial timer value
//	TH0 = 0xFC;		//Initial timer value
//	TF0 = 0;		//Clear TF0 flag
//	TR0 = 1;		//Timer0 start run
//}
	//TMOD=0x01;   //0000 0001 不可位寻址
	TMOD&=0XF0; //把TMOD的低四位清零，高四位保持不变
	TMOD|=0X01; //把TMOD的最低位置1，高四位保持不变
	TF0=0; //定时器T0溢出中断标志
	TR0=1; //开始计数
	TH0=64535/256;
	TL0=64535%256+1;
	ET0=1;	//	T0的溢出中断允许位//IE:中断允许寄存器
	EA=1;	//CPU总中断允许控制位
	PT0=0;	//IP：中断优先级控制寄存器
}

/* 定时器中断函数模板
void Timer0_Routine() interrupt 1 //中断函数
{
	static unsigned int T0Count;	//static关键字让变量在结束后依然占据空间，且只可以由本函数使用
	TH0=64535/256;//重装定时器
	TL0=64535%256+1;	
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;	
	}
}
*/