#include "string.h"
#include "reg51.h"

sbit SPK  = P3^7;
unsigned char note_index;	
string uart_data;
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
		0xfe,0x47,        // C6
		 0xfe,0x60,       // C#6
    0xfe,0x78,        // D6
    0xfe,0x8e,        // D#6
    0xfe,0xa3,        // E6
    0xfe,0xb6,        // F6
    0xfe,0xc9,        // F#6
		 0xfe,0xda,       // G6
    0xfe,0xeb,        // G#6
    0xfe,0xfa,        // A6
    0xff,0x08,        // A#6
    0xff,0x16,        // B6
};
unsigned char song[]={ //Danh sách các note của đoạn nhạc
	10, 10, 0, 0, 4, 4, 0,
	10, 10, 0, 0, 4, 4, 0,
	 0,  0, 4, 8, 10, 10,
	 0,  0, 4, 8, 10, 10
};
void init(); //Hàm thiết lập chế độ hoạt động 1 của timer0
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
		for(i=0;i<96;i++){ //Chơi một đoạn nhạc theo danh sách các note ở mảng song[]
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

	while(1){ //vòng lặp vô hạn xử lý sự kiện nhấn phím
	note_index=0;
		switch(uart_data){

			case "w0": //sẽ hiển thị "C3" trên màn hình LCD và phát ra note tương ứng là note đô

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
			
			case "b0" : // hiển thị "C#3" trên màn hình LCD và phát ra note tương ứng là note rê
		
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

			case "w1": // hiển thị "D3" trên màn hình LCD và phát ra note tương ứng là note mi
			
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

			case "b1": //hiển thị "D#3" trên màn hình LCD và phát ra note tương ứng là note fa

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

			case "w2": // hiển thị "E3" trên màn hình LCD và phát ra note tương ứng là note sol

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

			case "w3": //hiển thị "F3" trên màn hình LCD và phát ra note tương ứng là note la

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

			case "b2": //hiển thị "F#3" trên màn hình LCD và phát ra note tương ứng là note si

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
 
			case "w4": //hiển thị "G3" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "b3": // hiển thị "G#3" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "w5": // hiển thị "A3" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "b4": // hiển thị "A#3" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "w6": // hiển thị "B3" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "w7": //hiển thị "C4" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "b5": //hiển thị "C#4" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "w8": //hiển thị "D4" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "b6": //hiển thị "D#4" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "w9": //hiển thị "E4" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "w10": //hiển thị "F4" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "b7": // hiển thị "F#4" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "w11": // hiển thị "G4" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "b8": //hiển thị "G#4" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "w12": //hiển thị "A4" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "b9": //hiển thị "A#4" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "w13": //hiển thị "B4" trên màn hình LCD và phát ra note tương ứng là note si

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
			
			case "w14": //hiển thị "C5" trên màn hình LCD và phát ra note tương ứng là note si

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
			case "b10": //hiển thị "C#5" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=50;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("C#5");	uart_data='o';
				break;
			case "w15": //hiển thị "D5" trên màn hình LCD và phát ra note tương ứng là note si

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
			case "b11": //hiển thị "D#5" trên màn hình LCD và phát ra note tương ứng là note si

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
			case "w15": //hiển thị "E5" trên màn hình LCD và phát ra note tương ứng là note si

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
			case "b11": //hiển thị "F5" trên màn hình LCD và phát ra note tương ứng là note si

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
			case "w16": //hiển thị "F#5" trên màn hình LCD và phát ra note tương ứng là note si

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
			case "w17": //hiển thị "G5" trên màn hình LCD và phát ra note tương ứng là note si

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
			case "b12": //hiển thị "G#5" trên màn hình LCD và phát ra note tương ứng là note si

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
			case "w18": // hiển thị "A5" trên màn hình LCD và phát ra note tương ứng là note si

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
			case "b13": //sẽ hiển thị "A#5" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=68;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("A#5");	uart_data='o';
				break;
			case "w19": //hiển thị "B5" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=70;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("B5");	uart_data='o';
				break;
			
		case "w21": //hiển thị "C6" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=72;
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
			case "b15": //hiển thị "C#6" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=74;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("C#5");	uart_data='o';
				break;
			case "w22": //hiển thị "D6" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=76;
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
			case "b16": // hiển thị "D#6" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=78;
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
			case "w23": // hiển thị "E6" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=80;
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
			case "w24": // hiển thị "F6" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=82;
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
			case "b17": // hiển thị "F#6" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=84;
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
			case "w25": //hiển thị "G6" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=86;
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
			case "b18": // sẽ hiển thị "G#6" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=88;
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
			case "w26": //hiển thị "A6" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=90;
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
			case "b19": //hiển thị "A#6" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=92;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("A#5");	uart_data='o';
				break;
			case "w27": //hiển thị "B6" trên màn hình LCD và phát ra note tương ứng là note si

				note_index=94;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				delay(50000);
				TR0=0;
				SPK=1;
				//delay(30000);
				LCD_init();
				LCD_Write_String("B5");	uart_data='o';
				break;
			
			default:
				LCD_init(); 
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

void serial_IT(void) interrupt 4 //hàm xử lý ngắt serial port khi truyền/ nhận xong một ký tự
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

void timer0() interrupt 1 //hàm xử lý ngắt tràn timer0
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

