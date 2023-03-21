#include "string.h"
#include "reg51.h"

sbit SPK  = P3^7;
unsigned char note_index;	
unsigned char uart_data;
code unsigned int note_table[]={
    0xf2,0x3d,        // C3
    0xf3,0x03,        // C#3
    0xf3,0xbe,        // D3
    0xf4,0x63,        // D#3
    0xf5,0x14,        // E3
    0xf5,0xb1,        // F3
    0xf6,0x45,        // F#3
	 0xf6,0xd1,         // G3
    0xf7,0x54,        // G#3
    0xf7,0xd1,        // A3
    0xf8,0x47,        // A#3
    0xf8,0xb6,        // B3
    0xf9,0x1f,        // C4
	 0xf9,0x82,         // C#4
    0xf9,0xdf,        // D4
    0xfa,0x37,        // D#4
    0xfa,0x8A,        // E4
    0xfa,0xd9,        // F4
    0xfb,0x23,        // F#4
	 0xfb,0x69,         // G4
    0xfb,0xaa,        // G#4
    0xfb,0xe8,        // A4
    0xfb,0x24,        // A#4
    0xf5,0x5a,        // B4
    0xf5,0x8f,        // C5
		 0xf2,0xc1,       // C#5
    0xf3,0xef,        // D5
    0xf3,0x1b,        // D#5
    0xf4,0x45,        // E5
    0xf5,0x6c,        // F5
    0xf5,0x91,        // F#5
		 0xf2,0xb4,       // G5
    0xf3,0xd5,        // G#5
    0xf3,0xf4,        // A5
    0xf4,0x11,        // A#5
    0xf5,0x2e,        // B5
};
unsigned char song[]={ //Danh sÃ¡ch cÃ¡c note cá»§a Ä‘oáº¡n nháº¡c
	10,10,0,0,4,4,0,
	10,10,0,0,4,4,0,
	0,0,4,8,10,10,
	0,0,4,8,10,10
};
void init(); //HÃ m thiáº¿t láº­p cháº¿ Ä‘á»™ hoáº¡t Ä‘á»™ng 1 cá»§a timer0
void delay(unsigned int time);

//Dinh nghia mot so chan de dieu khien den LCD
#define LCD_DATA P2
sbit EN=P0^2;
sbit RS=P0^0;
sbit RW=P0^1;	   
//Khai bao prototype cho cac ham dieu khien den LCD
void Init_System();	
void Delay_ms(int interval);  
void LCD_init();
void Wait_For_LCD();
void LCD_Send_Command(unsigned char x);
void LCD_Write_One_Char(unsigned char c);
void LCD_Write_String(unsigned char *s);
void main()
{
	unsigned char i;  
	init();
	SCON = 0x50; 			/* uart in mode 1 (8 bit), REN=1 */
  	TMOD = TMOD | 0x20 ; 	/* Timer 1 in mode 2 */
  	TH1 = 0xFD; 			/* 9600 Bds at 11.0592MHz */
 	TL1 = 0xFD; 			/* 9600 Bds at 11.0592MHz */
  	ES = 1; 				/* Enable serial interrupt*/
  	EA = 1; 				/* Enable global interrupt */
  	TR1 = 1;
	
	Init_System();
	LCD_init();
	
	note_index=0;
		for(i=0;i<26;i++){ //ChÆ¡i má»™t Ä‘oáº¡n nháº¡c theo danh sÃ¡ch cÃ¡c note á»Ÿ máº£ng song[]
			note_index = song[i];		
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

	while(1){ //vÃ²ng láº·p vÃ´ háº¡n xá»­ lÃ½ sá»± kiá»‡n nháº¥n phÃ­m
	note_index=0;
		switch(uart_data){

		case 'Z': //sáº½ hiá»ƒn thá»‹ "C3" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note Ä‘Ã´

				note_index=0;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("C3");
				uart_data='o';
				break;
			
			case 'X' : // hiá»ƒn thá»‹ "C#3" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note rÃª
		
				note_index=2;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("C#3");uart_data='o';
				break;

			case 'C': // hiá»ƒn thá»‹ "D3" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note mi
			
				note_index=4;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("D3");uart_data='o';
				break;

			case 'V': //hiá»ƒn thá»‹ "D#3" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note fa

				note_index=6;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				delay(30000);
				LCD_init();
				LCD_Write_String("D#3");	uart_data='o';
				break;

			case 'B': // hiá»ƒn thá»‹ "E3" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note sol

				note_index=8;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("E3");  uart_data='o';
				break;

			case 'N': //hiá»ƒn thá»‹ "F3" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note la

				note_index=10;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("F3");	uart_data='o';
				break;

			case 'M': //hiá»ƒn thá»‹ "F#3" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=12;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("F#3");	uart_data='o';
				break;
 
			case 'A': //hiá»ƒn thá»‹ "G3" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=14;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("G3");	uart_data='o';
				break;
			
			case 'S': // hiá»ƒn thá»‹ "G#3" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=16;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("G#3");	uart_data='o';
				break;
			
			case 'D': // hiá»ƒn thá»‹ "A3" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=18;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("A3");	uart_data='o';
				break;
			
			case 'F': // hiá»ƒn thá»‹ "A#3" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=20;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("A#3");	uart_data='o';
				break;
			
			case 'G': // hiá»ƒn thá»‹ "B3" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=22;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("B3");	uart_data='o';
				break;
			
			case 'H': //hiá»ƒn thá»‹ "C4" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=24;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("C4");	uart_data='o';
				break;
			
			case 'J': //hiá»ƒn thá»‹ "C#4" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=26;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("C#4");	uart_data='o';
				break;
			
			case 'K': //hiá»ƒn thá»‹ "D4" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=28;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("D4");	uart_data='o';
				break;
			
			case 'L': //hiá»ƒn thá»‹ "D#4" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=30;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("D#4");	uart_data='o';
				break;
			
			case 'Q': //hiá»ƒn thá»‹ "E4" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=32;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("E4");	uart_data='o';
				break;
			
			case 'W': //hiá»ƒn thá»‹ "F4" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=34;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("F4");	uart_data='o';
				break;
			
			case 'E': // hiá»ƒn thá»‹ "F#4" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=36;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("F#4");	uart_data='o';
				break;
			
			case 'R': // hiá»ƒn thá»‹ "G4" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=38;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("G4");	uart_data='o';
				break;
			
			case 'T': //hiá»ƒn thá»‹ "G#4" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=40;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("G#4");	uart_data='o';
				break;
			
			case 'Y': //hiá»ƒn thá»‹ "A4" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=42;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("A4");	uart_data='o';
				break;
			
			case 'U': //hiá»ƒn thá»‹ "A#4" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=44;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("A#4");	uart_data='o';
				break;
			
			case 'I': //hiá»ƒn thá»‹ "B4" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=46;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("B4");	uart_data='o';
				break;
			
			case 'O': //hiá»ƒn thá»‹ "C5" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=48;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("C5");	uart_data='o';
				break;
			case 'P': //hiá»ƒn thá»‹ "C#5" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=50;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(500000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("C#5");	uart_data='o';
				break;
			case '1': //hiá»ƒn thá»‹ "D5" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=52;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("D5");	uart_data='o';
				break;
			case '2': //hiá»ƒn thá»‹ "D#5" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=54;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("D#5");	uart_data='o';
				break;
			case '3': //hiá»ƒn thá»‹ "E5" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=56;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("E5");	uart_data='o';
				break;
			case '4': //hiá»ƒn thá»‹ "F5" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=58;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("F5");	uart_data='o';
				break;
			case '5': //hiá»ƒn thá»‹ "F#5" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=60;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("F#5");	uart_data='o';
				break;
			case '6': //hiá»ƒn thá»‹ "G5" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=62;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("G5");	uart_data='o';
				break;
			case '7': //hiá»ƒn thá»‹ "G#5" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=64;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("G#5");	uart_data='o';
				break;
			case '8': // hiá»ƒn thá»‹ "A5" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=66;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("A5");	uart_data='o';
				break;
			case '9': //sáº½ hiá»ƒn thá»‹ "A#5" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=68;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(500000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("A#5");	uart_data='o';
				break;
			case '0': //hiá»ƒn thá»‹ "B5" trÃªn mÃ n hÃ¬nh LCD vÃ  phÃ¡t ra note tÆ°Æ¡ng á»©ng lÃ  note si

				note_index=70;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(5000000000);
				int k = 500000000000;
				while(k)
				{
					k--;
					TR0=1;
				}
				TR0=0;
				SPK=1;
				//delay(300000000);
				LCD_init();
				LCD_Write_String("B5");	uart_data='o';
				break;
			default:
				LCD_init();
				LCD_Write_One_Char(uart_data);
				break;		
		}		
	} 
}
void Init_System()
{
	//Thiet lap LCD o che do doc
	RW=1;	
}
void Delay_ms(int interval)
{
	int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<interval;j++);
	}
}
//Ham thuc hien gui mot lenh xuong LCD
void LCD_Send_Command(unsigned char x)
{
	LCD_DATA=x;
	RS=0; //Chon thanh ghi lenh
	RW=0; //De ghi du lieu
	EN=1;
	Delay_ms(1);
	EN=0;		
	Wait_For_LCD(); //Doi cho LCD san sang
	EN=1;		  
}
//Ham kiem tra va cho den khi LCD san sang
void Wait_For_LCD()
{
	Delay_ms(10);
}
void LCD_init()
{
	LCD_Send_Command(0x38); //Chon che do 8 bit, 2 hang cho LCD
	LCD_Send_Command(0x0E); //Bat hien thi, nhap nhay con tro	
	LCD_Send_Command(0x01); //Xoa man hinh	
	LCD_Send_Command(0x80); //Ve dau dong
	
}
//Ham de LCD hien thi mot ky tu
void LCD_Write_One_Char(unsigned char c)
{
	LCD_DATA=c; //Dua du lieu vao thanh ghi 
	RS=1; //Chon thanh ghi du lieu
	RW=0;
	EN=1;
	Delay_ms(1);	
	EN=0;
	Wait_For_LCD();	
	EN=1;
}
//Ham de LCD hien thi mot xau
void LCD_Write_String(unsigned char *s)
{
	unsigned char length;
	length=strlen(s); //Lay do dai xau
	while(length!=0)
	{
		LCD_Write_One_Char(*s); //Ghi ra LCD gia tri duoc tro boi con tro
		s++; //Tang con tro
		length--;	  		 
	}
}

void serial_IT(void) interrupt 4 //hÃ m xá»­ lÃ½ ngáº¯t serial port khi truyá»n/ nháº­n xong má»™t kÃ½ tá»±
{
  if (RI == 1)
  { 
    RI = 0; 		
    uart_data = SBUF;
    SBUF = uart_data;
  }
  else 
    TI = 0; 		
}

void timer0() interrupt 1 //hÃ m xá»­ lÃ½ ngáº¯t trÃ n timer0
{
	TH0=note_table[note_index];
	TL0=note_table[note_index+1];
	SPK=~SPK;
}

void init()
{
	TMOD=0x01;
	EA=1;
	ET0=1;
	TR0=0;
}

void delay(unsigned int time)
{
	while(time--);
}	
