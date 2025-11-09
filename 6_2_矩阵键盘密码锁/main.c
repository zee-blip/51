#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"

unsigned char KeyNum;//0~255
unsigned int PassWord;//0 ~ 65535
int Count;
	
void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	while(1)
	{
		KeyNum=MatrixKey();
		if(KeyNum)//KeyNum非0，即按下按键并松手后才显示KeyNum,防止刷新过快
		{
			
			if(KeyNum<=10)//按下S1-S10的按键，输入密码
			{
				if(Count<4)
				{
					PassWord*=10;
					PassWord+=KeyNum%10;
				}
				Count++;
				LCD_ShowNum(2,1,PassWord,4);//Parameter 0~65535
			}	
					
		}
		if(KeyNum==11)
		{
			if(PassWord==321)
			{
				LCD_ShowString(1,11,"KaiMen");
				Count=0;
				PassWord=0;
				LCD_ShowNum(2,1,PassWord,4);
			}
			else
			{
				LCD_ShowString(1,11,"BuKai");
				Count=0;
				PassWord=0;
				LCD_ShowNum(2,1,PassWord,4);
			}	
		}
		if(KeyNum==12)
		{
			Count=0;
			PassWord=0;
			LCD_ShowNum(2,1,PassWord,4);
		}
	}
}