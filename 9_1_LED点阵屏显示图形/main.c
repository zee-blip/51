#include <REGX52.H>
#include "DELAY.H"

sbit RCK=P3^5;	//RCLK,特殊位声明：P3口的第五位
sbit SCK=P3^6;	//SRCLK
sbit SER=P3^4;	//SER

#define MATRIX_LED_PORT	P0

/**
  * @brief 74HC595写入一个字节
  * @param  要写入的字节
  * @retval 无
  */
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		//SER=Byte&0x80=>if(Byte^8)SER=1;else SER=0;//没有进行位对齐，将8位赋给1位：如果8位非0即赋的值为1
		SER=Byte&(0x80>>i);	
		SCK=1;
		SCK=0;		
	}
	RCK=1;
	RCK=0;
}

/**
* @brief LED点阵屏显示一列数据
  * @param  Column 要选择的列，范围：0~7，0在最左边
  * @param  Data 要选择列显示的数据，范围：0~0xFF，高位在上，1为亮，0为灭
  * @retval 无
  */
void MatrixLED_ShowColumn(unsigned char Column,Data)
{
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT=~(0x80>>Column);
//	if(column==0)P0=~0x80;
//	if(column==1)P0=~0x40;
//	if(column==0)P0=~0x20;
	Delay(1);
	MATRIX_LED_PORT=0xFF;
}

void main()
{
	SCK=0;
	RCK=0;

	while(1)
	{
		MatrixLED_ShowColumn(0,0x78);
		MatrixLED_ShowColumn(1,0x84);
		MatrixLED_ShowColumn(2,0x82);
		MatrixLED_ShowColumn(3,0x41);
		MatrixLED_ShowColumn(4,0x41);
		MatrixLED_ShowColumn(5,0x82);
		MatrixLED_ShowColumn(6,0x84);
		MatrixLED_ShowColumn(7,0x78);
	}
}