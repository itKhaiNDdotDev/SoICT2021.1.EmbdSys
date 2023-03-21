//////////////////////////////////////////////////////////////////////////////////////
//                     Embedded Systems - IT4210 (SoICT-HUST)                      //
//				Bai thuc hanh 2: Lap trinh ghep noi PC, ngoai vi voi 8051 		   //
/////////////////////////////////////////////////////////////////////////////////////
/* Code bai 3: lam viec voi man hinh LCD
Nhom 3b
- Nguyen Duy Khai - 20183771
- Dang Quang Thang - 20183829
*/

#include <at89x51.h>
#include "string.h"
//Dinh nghia mot so chan de dieu khien den LCD
#define LCD_DATA P2		// Dat hang so thay the Port2 xuat du lieu tu 8051 ra LCD (cong ket noi)
// Khai bao cac chan ket noi voi LCD tuong ung cho viec nhan lenh, nhan du lieu va thao tac voi ky tu tren man hinh LCD
sbit EN=P0^2;
sbit RS=P0^0;
sbit RW=P0^1;	   
//Khai bao prototype cho cac ham
void Init_System();	
void Delay_ms(int interval);  
void LCD_init();
void Wait_For_LCD();
void LCD_Send_Command(unsigned char x);
void LCD_Write_One_Char(unsigned char c);
void LCD_Write_String(unsigned char *s);
// Chi tiet cac ham duoc trien khai va comment o duoi (sau ham main)

void main()
{
	Init_System();	// Thiet lap he thong bat dau voi LCD o che do doc
	LCD_init();		// Thiet lap LCD san sang ghi va hien thi ra man hinh voi 2 dong cho cac xau ky tu bat dau tu con tro o dau dong 1
	LCD_Write_String("Hello");	// In ra "Hello" o dong dau tien cua man hinh LCD
	LCD_Send_Command(0xC0); //Chuyen con tro xuong dong thu 2
	LCD_Write_String("World....");	// In ra "World...." o dong thu 2 man hinh LCD
	while(1){		// Lap vo han de giu chuong trinh dang thuc thi khong bi ngat
	}
}
void Init_System()
{
	//Thiet lap LCD o che do doc
	RW=1;	
}

// Dat 1000 lan lap cho delay tren moi ms
void Delay_ms(int interval)
{
	int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<interval;j++);	// Dung 1000 don vi thuc hien cua vong lap de xay dung thao tac delay
	}
}

//Ham thuc hien gui mot lenh xuong LCD
void LCD_Send_Command(unsigned char x)
{
	LCD_DATA=x;		// Gui ky tu qua chan ket noi tu 8051 den LCD
	RS=0; //Chon thanh ghi lenh	
	RW=0; //De ghi du lieu			// Keo RW xuong muc thap de chon che do ghi
	EN=1;	// Tao xung chan E bang cach tu 1 roi xong 0 o dong EN = 0 de cho phep lenh duoc ghi vao LCD
	Delay_ms(1);	// Delay de giu trang thai
	EN=0;		// EN tu 1 xuong 0
	Wait_For_LCD(); //Doi cho LCD san sang	//Delay doi LCD thuc hien xong lenh tren
	EN=1;		  // EN tu 0 len 1 (van la tao xung) EN = 0 la mo cho phep truyen command vao LCD, EN = 1 la dong
}

//Ham kiem tra va cho den khi LCD san sang
void Wait_For_LCD()
{
	Delay_ms(10);
}

// Thiet lap khoi tao LCD san sang ghi xau ky tu ra man hinh theo 2 hang bat dau tu con tro dau dong 1
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
	LCD_DATA=c; //Dua du lieu vao thanh ghi  (ghi nhan ky tu)
	RS=1; //Chon thanh ghi du lieu
	RW=0;	// Keo RW xuong muc thap de chon che do ghi
	EN=1;
	Delay_ms(1);	
	EN=0;
	Wait_For_LCD();	
	EN=1;
	// Phan tao xung voi EN nhay 0-1 va 1-0 va delay cho viec ghi du lieu duoc giai thich tuong tu o ham LCD_Send_Command()
}
//Ham de LCD hien thi mot xau
void LCD_Write_String(unsigned char *s)
{
	unsigned char length;
	length=strlen(s); //Lay do dai xau
	while(length!=0)
	{	// Lap lai den khi ghi ket ky tu trong chuoi bang viec duyet lan luot con tro de ghi lan luot tung ky tu cua chuoi
		LCD_Write_One_Char(*s); //Ghi ra LCD gia tri duoc tro boi con tro
		s++; //Tang con tro
		length--;	  		 
	}
}

