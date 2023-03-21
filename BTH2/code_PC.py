import serial
import msvcrt

#Tạo cổng kết nối với 8051 qua cổng COM2
ser = serial()
ser.baudrate = 9600
ser.port = 'COM2'
ser.close()
ser.open()

while(True):
    char = msvcrt.getch() #Đọc sự kiện nhấn phím và trả về ký tự được ấn dưới dạng byte string
    char = char.decode('ASCII') #Chuyển byte char nhận được về dạng ký tự ASCII 
    ser.write(bytes(char, 'utf-8')) #Gửi ký tự char qua cổng com2 đến 8051
    
    print(ser.read()) #in ra ký tự trả về từ 8051
    if(char == '\x03'): break #kết thúc khi nhập ^C
ser.close()
