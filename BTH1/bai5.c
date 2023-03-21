#include "reg51.h"

code unsigned char LEDfont[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char LEDp=0;		

unsigned char oldkey=0xff;	

	
sbit LED7SEG_0 = P1^0;	
sbit LED7SEG_1 = P1^1;	
sbit LED7SEG_2 = P1^2;	
sbit LED7SEG_3 = P1^3;	


sbit JDQ  = P1^4;	


sbit SPK  = P1^5;	


sbit k1 = P3^2;	
sbit k2 = P3^3;	
sbit k3 = P3^4;	
sbit k4 = P3^5;	

void delay_1ms(int time) {   // tre 1ms
	while(--time) {
		TMOD = 0x01;   // timer0 che do 1
		//65536 - 1000 xung = 64536 -> fc18
		TH0 = 0xfc;
		TL0 = 0x18;
		TR0 = 1;	// timer0 bat dau dem
		while(!TF0);
		TR0 = 0;	// timer0 ngung dem
		TF0 = 0;	// xoa co tran
	}
}

void display(unsigned int da)
{
	P0=0xFF;			
	da=da%100;	 	
	switch(LEDp){
	case 0:		
		LED7SEG_0=0;
		LED7SEG_1=1;
		LED7SEG_2=1;
		LED7SEG_3=1;
		P0=LEDfont[da/10];	
		break;
	case 1:		
		LED7SEG_0=1;
		LED7SEG_1=0;
		LED7SEG_2=1;
		LED7SEG_3=1;
		P0=LEDfont[da%10]; 
		break;
	}
	LEDp++;		
	if(LEDp>1)
		LEDp=0;	
}


unsigned char ReadK(void)	
{
	unsigned char lkey=0;
	if((P3&0xfc)!=0xfc){	
		
		if(oldkey!=(P3&0xfc)){	
			oldkey=P3&0xfc;			
			if(k1==0)
				lkey=1;			
			else if(k2==0)
				lkey=2;			
			else if(k3==0)
				lkey=3;		
			else if(k4==0)
				lkey=4;			
		}
	}
	else{
		oldkey=0xfc;		
	}
	return lkey;
}

int i;
void run(unsigned int LEDdata) {
	for(; LEDdata >0 ; LEDdata--) {
		for(i = 0; i < 50; i++) {
			LED7SEG_0 = 0; P0 = LEDfont[LEDdata/10]; delay_1ms(10); LED7SEG_0 = 1;
			LED7SEG_1 = 0; P0 = LEDfont[LEDdata%10]; delay_1ms(10); LED7SEG_1 = 1;
			
      if(k2==0){
				while(k1){
					display(LEDdata);
					delay_1ms(10);
				}
			}
		}
	}
	SPK=1;
	delay_1ms(3000);
	SPK=0;
}


				
void main(void) 
{
	unsigned int LEDdata=0;		
	SPK = 0;	  
	JDQ = 0; 
	
	while(1){			
		switch(ReadK()){
		case 1: run(LEDdata);
			break;
		case 3:LEDdata++;		
			break;
		case 4:
			if(LEDdata>0)
			{
				LEDdata--;
			}				
			break;
		}		
		display(LEDdata);
		delay_1ms(50);
	}
}