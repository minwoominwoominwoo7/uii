#define uss_num 6 
int count = 0 ;
float uss[uss_num]={0.106 , 0.116 , 0.126, 0.136, 0.146, 0.156};
void setup() {
    Serial.begin (115200);
    Serial.print ("Ready...\n");  
}

void loop() {
  // put your main code here, to run repeatedly:
   for ( int i = 0 ; i<uss_num ; i++ ){
     Serial.print(uss[i],2);
     Serial.print(",");
     uss[i] = uss[i] + 0.01 ;
   }
   Serial.print("1.23,");
   Serial.println("");   
   delay(100);
}

////////////////////////

import serial
import time

uss_num = 6
ser = serial.Serial('/dev/ttyUSB0', 115200)
time.sleep(2)
uss = [0 for i in range(uss_num + 1)]
while True :
    if ser.isOpen():
        data = ser.readline()
        data_string_array= data.decode().split(",")
        data_string_array_size = len(data_string_array)
        if data_string_array_size !=  ( uss_num + 2 ) :
            print('data size incorrect data size is {0}'.format(data_string_array_size))
        else:
            for i in range(uss_num+1):
                uss[i] = float(data_string_array[i])
            print('{0},{1},{2},{3},{4},{5},{6}'.format(uss[0], uss[1], uss[2], uss[3], uss[4], uss[5], uss[6]))
            print('{0}'.format(uss[0] + uss[1]))
            if uss[6] != 1.23 :
                print('data is erro')
    else :
        print "there is no port"

ser.close()
