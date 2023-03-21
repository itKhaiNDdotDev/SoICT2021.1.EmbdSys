			  #include "at89x51.h"
 
code unsigned char LEDfont[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char LEDpos=0;	//Choose 7-seg display position	

unsigned int cntDwnTime = 9999; // So thoi gian muon dem nguoc
unsigned int time1Sec = 0;

unsigned char oldkey=0xff;	//Push button data (release status)

//Define 7-seg anode display control (on/off):	
sbit LED7SEG_0 = P1^0;	//7-seg 1 anode display 
sbit LED7SEG_1 = P1^1;	//7-seg 2 anode display
sbit LED7SEG_2 = P1^2;	//7-seg 3 anode	display
sbit LED7SEG_3 = P1^3;	//7-seg 4 anode display

sbit SPK  = P1^5; 

//Delay 0-65536
void delay(unsigned int time)   
{							    
	while(time--);
}

void display(unsigned int da)
{
	P0=0xFF;			//Port 0 data off
	da=da%10000;	 	//Output data for 4 7-seg displays (4-digits)
	switch(LEDpos){
	case 0:		//Choose 7-seg display #1
		LED7SEG_0=0;
		LED7SEG_1=1;	
		LED7SEG_2=1;		
		LED7SEG_3=1;
		P0=LEDfont[da/1000];	//The Digit-4 (Thousands)
		break;
	case 1:		//Choose 7-seg display #2
		LED7SEG_0=1;
		LED7SEG_1=0;	
		LED7SEG_2=1;		
		LED7SEG_3=1;
		P0=LEDfont[da%1000/100]; //The Digit-3 (Hundreds)
		break;
	case 2:		//Choose 7-seg display #3
		LED7SEG_0=1;
		LED7SEG_1=1;	
		LED7SEG_2=0;		
		LED7SEG_3=1;
		P0=LEDfont[da%100/10];  //The Digit-2 (Tens)
		break;
	case 3:		//Choose 7-seg display #4
		LED7SEG_0=1;
		LED7SEG_1=1;	
		LED7SEG_2=1;		
		LED7SEG_3=0;
		P0=LEDfont[da%10];	 //The Digit-1 (Units)
		break;
	}
	LEDpos++;		//Turn around
	if(LEDpos>3)
		LEDpos=0;	
}


void timerProcess() interrupt TF0_VECTOR
{
	TF0  = 0;           
	time1Sec += 50;
	if(time1Sec == 1000)
	{
		cntDwnTime--;	// Giam thoi gian dem nguoc theo thoi gian thuc
		time1Sec = 0;
	}
}


//====================MAIN==
void main(void)
{
	SPK = 0;	// Tat buzzer
	
	// init timer 0
	TMOD = TMOD & 0xF0;
	TMOD = TMOD | 0x01;
	TH0  = 0x3C;
	TL0  = 0xB0;	
	TF0  = 0; 		
	ET0  = 1;		
	EA   = 1;		
	TR0  = 1;
	
	while(1)
	{
		display(cntDwnTime);		//Display 4 digits on 4 7-seg displays
		delay(100);
	}
}