 #include "reg51.h"
 
sbit SPK  = P1^5;
unsigned char i;
unsigned char onLED[8] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};
unsigned char on2LED[7] = {0xfc, 0xf9, 0xf3, 0xe7, 0xcf, 0x9f, 0x3f};
unsigned char customLED[44] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x3e,0x3d,0x3b,0x37,0x2f,0x1f,0x1e,0x1d,0x1b,0x17,0x0f,0x0e,0x0d,0x0b,0x07,0x06,0x05,0x03,0x02,0x01,0x00,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff};
unsigned char symLED[8] = {0x7e, 0xbd, 0xdb, 0xe7, 0xe7, 0xdb, 0xbd, 0x7e};
	
//Delay 0-65536
void delay(unsigned int time)   
{							    
	while(time--);
}
 
void main(void)
{
	SPK = 0;	// Tat buzzer
	P2 = 0xff;	// Mac dinh LED dang tat
	// Bat/tat ca 8 LED don theo thu tu: tat - bat - tat - bat va lap lai 3 lan
	for(i=0; i<3; i++)
	{
		P2 = 0x00;	// Bat het LED
		delay(50000000);	// Delay 50000000 lan lap vong lap while co ban
		P2 = 0xff;	// Tat het LED
		delay(50000000);
		P2 = 0x00;
		delay(50000000);
		P2 = 0xff;
		delay(50000000);
	}
	// Bat lan luot tung LED don tu trai qua phai va lap lai 3 lan
	for(i=0; i<3; i++)
	{
		unsigned char j;
		for(j=0; j<8; j++)
		{
			P2 = onLED[j];	// Bat LED thu i (i tu 0 den 8 tu trai qua phai)
			delay(50000000);
		}
	}
	// Bat lan luot tung LED don tu phai qua trai va lap lai 3 lan
	for(i=0; i<3; i++)
	{
		unsigned char j;
		for(j=0; j<8; j++)
		{
			P2 = onLED[8-j-1];	// Bat LED nguoc lai mode o tren (i tu 0 den 8 tu trai qua phai)
			delay(50000000);
		}
	}
	// Bat lan luoi tung cap LED don tu trai qua phai va tu phai qua trai (lap lai 3 lan)
	for(i=0; i<3; i++)
	{
		unsigned char j;
		for(j=0; j<7; j++)
		{
			P2 = on2LED[j];
			delay(50000000);
		}
		for(j=0; j<7; j++)
		{
			P2 = on2LED[7-j-1];
			delay(50000000);
		}
	}
	// Bat lan luot LED don tu trai va don qua phai, roi tat lan luot tu phai qua trai
	for(i=0; i<3; i++)
	{
		unsigned char j;
		for(j=0; j<44; j++)
		{
			P2 = customLED[i];
			delay(50000000);
		}
	}
	// Bat lan luot 2 LED don doi xung tu ngoai vao roi tu trong ra
	for(i=0; i<3; i++)
	{
		unsigned char j;
		for(j=0; j<8; j++)
		{
			P2 = symLED[i];
			delay(50000000);
		}
	}
}
