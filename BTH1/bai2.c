#include "reg51.h"
 
sbit SPK  = P1^5;
sbit P1_0 = P1^0;
unsigned char i;
unsigned char onLED[8] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};
unsigned char on2LED[7] = {0xfc, 0xf9, 0xf3, 0xe7, 0xcf, 0x9f, 0x3f};
unsigned char customLED[44] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x3e,0x3d,0x3b,0x37,0x2f,0x1f,0x1e,0x1d,0x1b,0x17,0x0f,0x0e,0x0d,0x0b,0x07,0x06,0x05,0x03,0x02,0x01,0x00,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff};
unsigned char symLED[8] = {0x7e, 0xbd, 0xdb, 0xe7, 0xe7, 0xdb, 0xbd, 0x7e};
// Ma hexa hien thi so tu 0-9 trong LED 7 thanh	
char numLED[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
int c = 1;

//Delay 0-65536
void delay(unsigned int time)   
{							    
	while(time--);
}

// Bat/tat ca 8 LED don theo thu tu: tat - bat - tat - bat va lap lai 3 lan
void mode1()
{
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
}

// Bat lan luot tung LED don tu trai qua phai va lap lai 3 lan
void mode2()
{
	for(i=0; i<3; i++)
	{
		unsigned char j;
		for(j=0; j<8; j++)
		{
			P2 = onLED[j];	// Bat LED thu i (i tu 0 den 8 tu trai qua phai)
			delay(50000000);
		}
	}
}	

// Bat lan luot tung LED don tu phai qua trai va lap lai 3 lan
void mode3()
{
	for(i=0; i<3; i++)
	{
		unsigned char j;
		for(j=0; j<8; j++)
		{
			P2 = onLED[8-j-1];	// Bat LED nguoc lai mode o tren (i tu 0 den 8 tu trai qua phai)
			delay(50000000);
		}
	}
}

// Bat lan luoi tung cap LED don tu trai qua phai va tu phai qua trai (lap lai 3 lan)
void mode4()
{
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
}

// Bat lan luot LED don tu trai va don qua phai, roi tat lan luot tu phai qua trai
void mode5()
{
	for(i=0; i<3; i++)
	{
		unsigned char j;
		for(j=0; j<44; j++)
		{
			P2 = customLED[i];
			delay(50000000);
		}
	}
}
	
// Bat lan luot 2 LED don doi xung tu ngoai vao roi tu trong ra
void mode6()
{
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

// Ngat ngoai INT0
void evenMode() interrupt 0
{
  if(c <= 6)
	{
		if (c%2 == 0)
		{
			if (c <= 4)
				c += 2;
			else
				c = 2;
		}			
		else
			c = 2;
	}
}

// Ngat ngoai INT1
void oddMode() interrupt 2
{  
  if(c <= 6)
	{
		if (c%2 == 1)
		{
			if (c <= 3)
				c += 2;
			else
			c = 1;
		} 
		else
			c = 1;
	}
}

void numOn()
{
	P1_0 = 0;
	P0 = numLED[c];
}


//====================MAIN==
void main(void)
{
	SPK = 0;	// Tat buzzer
	P2 = 0xff;	// Mac dinh LED dang tat
	
	while(1)
	{
		EX0 = 1;   // Ngat ngoai INT0
		EX1 = 1;   // Ngat ngoai INT1
		EA = 1;    // Ngat tat ca
		IT0 = 1;   // Ngat ngoai theo suon
		IT1 = 1;   // Ngat ngoai theo muc
		numOn();
		switch(c)
		{
			case 1:
				mode1();
				break;
			case 2:
				mode2();
				break;
			case 3:
				mode3();
				break;
			case 4:
				mode4();
				break;
			case 5:
				mode5();
				break;
			case 6:
				mode6();
				break;
		}
	}
}