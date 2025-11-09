#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"

unsigned char KeyNum;
void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Bowen");
	while(1)
	{
		KeyNum=MatrixKey();
		if(KeyNum)//KeyNum非0，即按下按键并松手后才显示KeyNum,防止刷新过快
		{
			LCD_ShowNum(2,1,KeyNum,2);
		}
	}
}