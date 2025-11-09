#include <REGX52.H>
#include "LCD1602.H"
#include "Ds1302.h"
#include "Delay.h"
#include "Key.h"
#include "Timer0.h"

unsigned char KeyNum,MODE,TimeSetSelect,TimeSetFlashFlag;

void TimeShow(void)	//时间显示功能
{
	DS1302_ReadTime();	//读取时间
	LCD_ShowNum(1,1,DS1302_Time[0],2);	//显示年
	LCD_ShowNum(1,4,DS1302_Time[1],2);	//显示月
	LCD_ShowNum(1,7,DS1302_Time[2],2);	//显示日
	LCD_ShowNum(2,1,DS1302_Time[3],2);	//显示时
	LCD_ShowNum(2,4,DS1302_Time[4],2);	//显示分
	LCD_ShowNum(2,7,DS1302_Time[5],2);	//显示秒
}

void TimeSet(void)	//时间设置功能
{
	if(KeyNum==2)
	{
		TimeSetSelect++;
		TimeSetSelect%=6;	//if(TimeSetSelect>5)TimeSetSelect=0;越界设置
	}
	if(KeyNum==3)
	{
		DS1302_Time[TimeSetSelect]++;
		if(DS1302_Time[0]>99){DS1302_Time[0]=0;}	//年越界判断
		if(DS1302_Time[1]>12){DS1302_Time[1]=1;}	//月越界判断
		if(DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || DS1302_Time[1]==7 || DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}	//大月
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}	//小月
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}	//闰年2月
			}
			else
			{
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}	//平年2月
			}
		}
		if(DS1302_Time[3]>23){DS1302_Time[3]=0;}
		if(DS1302_Time[4]>59){DS1302_Time[4]=0;}
		if(DS1302_Time[5]>59){DS1302_Time[5]=0;}
	}
	if(KeyNum==4)
	{
		DS1302_Time[TimeSetSelect]--;
		if(DS1302_Time[0]<0){DS1302_Time[0]=99;}	//年越界判断
		if(DS1302_Time[1]<1){DS1302_Time[1]=12;}	//月越界判断
		if(DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || DS1302_Time[1]==7 || DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=31;}	//大月
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=30;}	//小月
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}	//小月
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=29;}	//闰年2月
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}	
			}
			else
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=28;}	//平年2月
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}	
			}
		}
		if(DS1302_Time[3]<0){DS1302_Time[3]=23;}
		if(DS1302_Time[4]<0){DS1302_Time[4]=59;}
		if(DS1302_Time[5]<0){DS1302_Time[5]=59;}
	}
	if(TimeSetSelect==0&&TimeSetFlashFlag==1){LCD_ShowString(1,1,"  ");}
	else{LCD_ShowNum(1,1,DS1302_Time[0],2);}
	if(TimeSetSelect==1&&TimeSetFlashFlag==1){LCD_ShowString(1,4,"  ");}
	else{LCD_ShowNum(1,4,DS1302_Time[1],2);}
	if(TimeSetSelect==2&&TimeSetFlashFlag==1){LCD_ShowString(1,7,"  ");}
	else{LCD_ShowNum(1,7,DS1302_Time[2],2);}
	if(TimeSetSelect==3&&TimeSetFlashFlag==1){LCD_ShowString(2,1,"  ");}
	else{LCD_ShowNum(2,1,DS1302_Time[3],2);}
	if(TimeSetSelect==4&&TimeSetFlashFlag==1){LCD_ShowString(2,4,"  ");}
	else{LCD_ShowNum(2,4,DS1302_Time[4],2);}
	if(TimeSetSelect==5&&TimeSetFlashFlag==1){LCD_ShowString(2,7,"  ");}
	else{LCD_ShowNum(2,7,DS1302_Time[5],2);}
//	LCD_ShowNum(2,10,TimeSetSelect,2);	
//	LCD_ShowNum(1,1,DS1302_Time[0],2);	//显示年
//	LCD_ShowNum(1,4,DS1302_Time[1],2);	//显示月
//	LCD_ShowNum(1,7,DS1302_Time[2],2);	//显示日
//	LCD_ShowNum(2,1,DS1302_Time[3],2);	//显示时
//	LCD_ShowNum(2,4,DS1302_Time[4],2);	//显示分
//	LCD_ShowNum(2,7,DS1302_Time[5],2);	//显示秒
}

void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0_Init();
	LCD_ShowString(1,1,"  -  -  ");	//静态字符初始化显示
	LCD_ShowString(2,1,"  :  :  ");
	DS1302_SetTime();	//设置时间
	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)
		{
			if(MODE==0){MODE=1;TimeSetSelect=0;}
			else if(MODE==1){MODE=0;DS1302_SetTime();}
		}
		switch(MODE)
		{
			case 0:TimeShow();break;
			case 1:TimeSet();break;
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
		TimeSetFlashFlag=!TimeSetFlashFlag;	//逻辑取反，与~按位取反不同
	}
}