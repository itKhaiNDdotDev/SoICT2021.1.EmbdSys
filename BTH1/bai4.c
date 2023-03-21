#include "reg51.h"


code unsigned char LEDfont[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char LEDp=0;	


sbit LED7SEG_0 = P1^0;	 
sbit LED7SEG_1 = P1^1;	
sbit LED7SEG_2 = P1^2;	
sbit LED7SEG_3 = P1^3;	


sbit JDQ  = P1^4;	
 
sbit SPK  = P1^5;	


sbit k1 = P3^2;	
sbit k2 = P3^3;	


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
	da=da%10000;	 	
	switch(LEDp){
	case 0:		
		LED7SEG_0=0;
		LED7SEG_1=1;
		LED7SEG_2=1;
		LED7SEG_3=1;
		P0=LEDfont[da/1000];	
		break;
	case 1:		
		LED7SEG_0=1;
		LED7SEG_1=0;
		LED7SEG_2=1;
		LED7SEG_3=1;
		P0=LEDfont[da%1000/100]; 
		break;
	case 2:		
		LED7SEG_0=1;
		LED7SEG_1=1;
		LED7SEG_2=0;
		LED7SEG_3=1;
		P0=LEDfont[da%100/10];  
		break;
	case 3:		
		LED7SEG_0=1;
		LED7SEG_1=1;
		LED7SEG_2=1;
		LED7SEG_3=0;
		P0=LEDfont[da%10];	 
		break;
	}
	LEDp++;		
	if(LEDp>3)
		LEDp=0;	
}

void main(){
    unsigned int count=0;
    unsigned char a1=0,a2=0,b1=0,b2=0;
		SPK = 0;	  
		JDQ = 0; 

    while(1){
        display(count);
        delay_1ms(10);
        count++;
        if(count==6000) count=0;
			
        //start
        if(k1==0){
            while(!k1){
                count=0;
                display(count);
            }
            count=0;
        }

        //stop
        if(k2==0){
            while(k1){
                display(count);
                delay_1ms(10);
            }
        }
    }
}