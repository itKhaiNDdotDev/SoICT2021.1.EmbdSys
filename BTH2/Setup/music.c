/////////////////////////////////////////////////////////////////////////////////////
//                     Embedded Systems - IT4210 (SoICT-HUST)                      //
//						       Sample codes for Lab #2 							   //
/////////////////////////////////////////////////////////////////////////////////////
#include "reg51.h"

sbit SPK  = P3^7;	

//verify this table according to your CPU clock
code unsigned int note_table[]={
    0xf8,0x8b,        //1 do
    0xf9,0x5b,        //2 re
    0xfa,0x17,        //3 mi
    0xfa,0x6b,        //4 fa
    0xfb,0x07,        //5 sol
    0xfb,0x92,        //6 la
    0xfc,0x0d,        //7 si
};
unsigned char note_index;	

void init();		
void delay(unsigned int time); 

void main(void) 
{
	unsigned char i;
	init();
	while(1){
		note_index=0;
		for(i=0;i<7;i++){		
			TH0=note_table[note_index];
			TL0=note_table[note_index+1];			
			TR0=1;
			delay(50000);
			TR0=0;
			SPK=1;
			delay(30000);
			note_index+=2;			
		}
		delay(50000);
		delay(50000);
	}			
}


void init()
{
	TMOD=0x01;
	EA=1;
	ET0=1;
	TR0=0;
}

void timer0() interrupt 1
{
	TH0=note_table[note_index];
	TL0=note_table[note_index+1];
	SPK=~SPK;
}

void delay(unsigned int time)
{
	while(time--);
}
