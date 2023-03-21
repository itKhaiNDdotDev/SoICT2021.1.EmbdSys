/////////////////////////////////////////////////////////////////////////////////////
//                     Embedded Systems - IT4210 (SoICT-HUST)                      //
//						       Sample codes for Lab #2 							   //
/////////////////////////////////////////////////////////////////////////////////////
#include "reg51.h"

sbit SPK  = P3^7;	// thiet lap chan ket noi speaker

//verify this table according to your CPU clock
code unsigned int note_table[]={
    0xf9,0xlf,        // C4
    0xf9,0xdf,        // D4
    0xfa,0x8a,        // E4
    0xfa,0xd9,        // F4
    0xfb,0x68,        // G4
    0xfb,0xe9,        // A4
    0xfc,0x5b,        // B4
		0xfc,0x8f,        // C5
    0xfc,0xef,        // D5
    0xfd,0x45,        // E5
    0xfd,0x6c,        // F5
};
unsigned char note_index;	

void init();	 	
void delay(unsigned int time); 

void main(void) 
{
	unsigned char i;
	init();   // khoi tao
	while(1){
		note_index=0;
		for(i=0;i<11;i++){		
			TH0=note_table[note_index]; // Lay nua dau cua gia tri du lieu tuong ung not nhac
			TL0=note_table[note_index+1];	// Nap nua sau gia tri du lieu tuong ung not nhac
			TR0=1; // khoi dong bo dinh thoi timer 0, mode 2
			delay(50000);  // delay giu trang thai
			TR0=0;  // dung bo dinh thoi
			SPK=1;  // phát tín hieu ra loa
			delay(30000);  // delay giu trang thai
			note_index+=2;	// chuyen sang node ke tiep		
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
