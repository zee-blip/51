#ifndef __DS1302_H__
#define __ds1302_H__



#endif

//外部可调用时间数组，索引0~6分别为年、月、日、时、分、秒、星期
extern char DS1302_Time[]; //外部调用变量必须加extern,有符号字符范围-128~127

void DS1302_Init(void);
void DS1302_WriteByte(unsigned char Command,Data);
unsigned char DS1302_ReadByte(unsigned char Command);
void DS1302_SetTime(void);
void DS1302_ReadTime(void);