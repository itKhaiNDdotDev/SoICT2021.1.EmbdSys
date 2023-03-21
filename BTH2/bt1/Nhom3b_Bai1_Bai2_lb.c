//////////////////////////////////////////////////////////////////////////////////////
//                     Embedded Systems - IT4210 (SoICT-HUST)                      //
//				Bai thuc hanh 2: Lap trinh ghep noi PC, ngoai vi voi 8051 		   //
/////////////////////////////////////////////////////////////////////////////////////
/* Code bai 1 va bai 2: tuong tac voi terminal va ket noi voi PC
Nhom 3b
- Nguyen Duy Khai - 20183771
- Dang Quang Thang - 20183829
*/

#include "reg51.h"
char uart_data;	// Khai bao bien dung de luu du lieu truyen va nhan cho thanh ghi SBUF

void main (void)
{
  SCON = 0x50; 			/* uart in mode 1 (8 bit), REN=1 */	//Thiet lap che do lam viec noi tiep 1 de dong khung 8 bit data cho thanh ghi SCON
  TMOD = TMOD | 0x20 ; 	/* Timer 1 in mode 2 */	//	// Nap thanh ghi TMOD voi Timer1 o mode 2 de thiet lap mode baud
  TH1 = 0xFD; 			/* 9600 Bds at 11.0592MHz */
  TL1 = 0xFD; 			/* 9600 Bds at 11.0592MHz */
  ES = 1; 				/* Enable serial interrupt*/
  EA = 1; 				/* Enable global interrupt */
  TR1 = 1; 				/* Timer 1 run */
  while(1); 			/* endless */	// Vong lap vo han de giu chuong trinh khong bi ngat sau khi thuc hien xong 1 thao tac
}

// Ham truyen va nhan du lieu (ky tu) tu 8051 voi PC qua cong COM hay voi Virtual Terminal
void serial_IT(void) interrupt 4
{
  if (RI == 1)	// Neu RI == 1 (co nhan du lieu bat) danh dau da nhan du lieu
  { 
    RI = 0; 			/* prepare for next reception */	// Thiet lap trang thai bai dau cho co nhan RI sau khi danh dau viec nhan du lieu
    /* Virtual Terminal o bai 1 va thiet bi COMPIM (dung de thiet lap cong COM ket noi voi PC) o bai 2
    duoc ket noi voi 8051 qua cac chan TxD va RxD (mach nhu hinh ve trong file pdf). Nen de trao doi
    duoc du lieu (gui va nhan du lieu qua bien uart_data) phai thong qua thanh ghi SBUF. Do do:(doan code duoi day) */
    uart_data = SBUF; 	/* Read receive data */		// Doc du lieu nhan duoc o SBUF ra bien uart_data
    SBUF = uart_data; 	/* Send back same data on uart*/	// Gui lai du lieu vua gan cho uart_data vao SBUF
    /* Vi thuc hien lan luot doc du lieu roi gui lai nay nen treen virtual terminal hay tren hercules_3-2-8 cua PC da
    	den 8051 qua cong COM thi sau khi nhap ky tu, 8051 nhan va gui lai nen cac ky tu do lai tu dong xuat hien leen
    	man hinh 1 lan nua */
  }
  else 
    TI = 0; 			/* if emission occur */	// Thiet lap trang thai bai dau cho co tuyen TI sau khi danh dau viec truyen du lieu
}
