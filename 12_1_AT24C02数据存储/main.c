#include <REGX52.H>
#include "LCD1602.h"
#include "Key.h"
#include "AT24C02.h"
#include "Delay.h"

//unsigned char Data;
unsigned char KeyNum;
unsigned int Num;

void main()
{
	LCD_Init();
	LCD_ShowNum(1,1,Num,5);
//	AT24C02_WriteByte(1,155);
//	Delay(5);	//因为24C02写周期最大5ms
//	Data=AT24C02_ReadByte(1);
//	LCD_ShowNum(2,1,Data,3);
	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)
		{
			Num++;
			LCD_ShowNum(1,1,Num,5);
		}
		if(KeyNum==2)
		{
			Num--;
			LCD_ShowNum(1,1,Num,5);
		}
		if(KeyNum==3)
		{
			AT24C02_WriteByte(0,Num%256);
			Delay(5);	//因为24C02写周期最大5ms
			AT24C02_WriteByte(1,Num/256);
			Delay(5);	//因为24C02写周期最大5ms
			LCD_ShowString(2,1,"Write OK");
			Delay(1000);
			LCD_ShowString(2,1,"        ");
		}
		if(KeyNum==4)
		{
			Num=AT24C02_ReadByte(0);
			Num|=AT24C02_ReadByte(1)<<8;	//char与int运算时,char会内部转化为int型参与运算,所以读出值左移八位不会溢出
			LCD_ShowNum(1,1,Num,5);
			LCD_ShowString(2,1,"Read OK ");
			Delay(1000);
			LCD_ShowString(2,1,"        ");
		}
	}
}
