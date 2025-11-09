#ifndef __Matrix_LED_H__
#define __MATRIX_LED_H__

void MatrixLED_Init();
void _74HC595_WriteByte(unsigned char Byte);
void MatrixLED_ShowColumn(unsigned char Column,Data);

#endif