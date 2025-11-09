#ifndef __NIXIE_H__
#define __NIXIE_H__

void Nixie_SetBuf(unsigned char location,number);
void Nixie_Scan(unsigned char location,number);//分号很重要
void Nixie_Loop(void);

#endif