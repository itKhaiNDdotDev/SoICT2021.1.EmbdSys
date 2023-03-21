/////////////////////////////////////////////////////////////////////////////////////
//                     Embedded Systems - IT4210 (SoICT-HUST)                      //
//						       Sample codes for Lab #1 							   //
/////////////////////////////////////////////////////////////////////////////////////
#include "reg51.h"

//Hex codes to display numbers (0-9) on a 7-segment anode display
code unsigned char LEDfont[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char LEDpos=0;	//Choose 7-seg display position	

unsigned char oldkey=0xff;	//Push button data (release status)

//Define 7-seg anode display control (on/off):	
sbit LED7SEG_0 = P1^0;	//7-seg 1 anode display 
sbit LED7SEG_1 = P1^1;	//7-seg 2 anode display
sbit LED7SEG_2 = P1^2;	//7-seg 3 anode	display
sbit LED7SEG_3 = P1^3;	//7-seg 4 anode display

//Relay connects on P1^4
sbit JDQ  = P1^4;	//Relay on/off

//Buzzer (speaker) connects on P1^5 
sbit SPK  = P1^5;	//Buzzer on/off

//Define 6 push buttons on Port P3
sbit key1 = P3^7;	//Push button 1
sbit key2 = P3^6;	//Push button 2
sbit key3 = P3^5;	//Push button 3
sbit key4 = P3^4;	//Push button 4
sbit key5 = P3^3;	//Push button 5
sbit key6 = P3^2;	//Push button 6
			
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
//Read buttons 1-> 6 on P3
unsigned char ReadKey(void)	
{
	unsigned char lkey=0;
	if((P3&0xfc)!=0xfc){	//If any buttons pressed

		SPK=1;				//Turn on buzzer
		JDQ=1; 				//Turn on motor

		delay(10);			//Delay for buzzer pulse
		if(oldkey!=(P3&0xfc)){	//if any buttons pressed
			oldkey=P3&0xfc;		//Update button's values		
			if(key1==0)
				lkey=1;			//Button 1 pressed
			else if(key2==0)
				lkey=2;			//Button 2 pressed
			else if(key3==0)
				lkey=3;			//Button 3 pressed
			else if(key4==0)
				lkey=4;			//Button 4 pressed
			else if(key5==0)
				lkey=5;			//Button 5 pressed
			else if(key6==0)
				lkey=6;			//Button 6 pressed
		}
	}
	else{
		oldkey=0xfc;		//Default data of buttons port

		SPK=0;				//Turn off buzzer
		JDQ=0; 				//Turn off motor
	}
	return lkey;
}

//Main program				
void main(void) 
{
	unsigned int LEDdata=1234;		//7-seg 4-digit data 
	unsigned char i;
	SPK = 0;	  
	JDQ = 0; 

	for(i=0;i<8;i++){
		P2<<=1;		//Shift left all LEDs		
		delay(5000);
	}

	P1 = 0x0f;
	P2 = 0xff;			//All LED off
	
	P0 = 0;				//Port 0 connects to LCD
	LED7SEG_3=0;		//Turn on 7-seg display #4
	delay(50000);
	LED7SEG_3=1;		//Turn off 7-seg display #4

	LED7SEG_2=0;		//Turn on 7-seg display #3
	delay(50000);
	LED7SEG_2=1;		//Turn off 7-seg display #3

	LED7SEG_1=0;		//Turn on 7-seg display #2
	delay(50000);
	LED7SEG_1=1;		//Turn off 7-seg display #2

	LED7SEG_0=0;		//Turn on 7-seg display #1
	delay(50000);
	LED7SEG_0=1;		//Turn off 7-seg display #1
	
	while(1){			//Forever loop
		P2 = 0x55;		//8 LEDs on Port 2
		switch(ReadKey()){		//Polling push buttons
		case 1:LEDdata++;		//Button 1 pressed
			break;
		case 2:LEDdata--;		//Button 2 pressed
			break;
		case 3:LEDdata+=10;		//Button 3 pressed
			break;
		case 4:LEDdata-=10;		//Button 4 pressed
			break;
		case 5:LEDdata+=100;	//Button 5 pressed
			break;
		case 6:LEDdata-=100;	//Button 6 pressed
			break;
		}		
		display(LEDdata);		//Display 4 digits on 4 7-seg displays
		delay(100);
	}
}
