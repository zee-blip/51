#include <REGX52.H>
#include "LCD1602.H"
#include <stdio.h>
#include "Delay.h"

int Result;
	
void main()
{
	
	LCD_Init();
	//LCD_ShowChar(1,1,'Z');
	//LCD_ShowString(1,1,"Thea was sleeping");
	//LCD_ShowNum(1,1,2,3);
	//LCD_ShowSignedNum(1,1,-10,1);
	//LCD_ShowHexNum(2,1,0XAA,3);
	//LCD_ShowBinNum(2,1,0XAA,7);
	while(1)
	{
	Result++;
	Delay(1000);
	LCD_ShowNum(2,1,Result,2);	
	}
}