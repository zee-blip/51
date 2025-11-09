#include <REGX52.H>

//void UartInit(void)		//4800bps@11.0592MHz
//{
//	PCON |= 0x80;		//Enable SMOD bit
//	SCON = 0x50;		//8bit and variable baudrate
//	AUXR &= 0xBF;		//Timer1's clock is Fosc/12 (12T)
//	AUXR &= 0xFE;		//Use Timer1 as baudrate generator
//	TMOD &= 0x0F;		//Mask Timer1 mode bit
//	TMOD |= 0x20;		//Set Timer1 as 8-bit auto reload mode
//	TL1 = 0xF4;		//Initial timer value
//	TH1 = 0xF4;		//Set reload value
//	ET1 = 0;		//Disable Timer1 interrupt
//	TR1 = 1;		//Timer1 running
//}

/**
  * @brief 串口初始化，//4800bps@11.0592MHz
  * @param  无
  * @retval 无
  */
void UART_Init()	
{
	PCON |= 0x80;		//Enable SMOD bit
	SCON=0X40;
	TMOD&=0XF0; //把TMOD的低四位清零，高四位保持不变
	TMOD|=0X20;
	TL1 = 0xF4;		//Initial timer value
	TH1 = 0xF4;		//Set reload value
	ET1 = 0;		//Disable Timer1 interrupt
	TR1 = 1;		//Timer1 running
}

/**
  * @brief 串口发送一个字节数据
  * @param  Byte 要发送的一个字节数据
  * @retval 无
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}