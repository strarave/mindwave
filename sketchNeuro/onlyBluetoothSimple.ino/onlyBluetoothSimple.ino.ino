#include <SoftwareSerial.h>

long int bluetoothBaud = 115200;
long int serialBaud = 9600;
int boardT = 3;
int boardR = 2;

SoftwareSerial bluetooth(boardT, boardR);

void serialLog(String message){
  Serial.println(message);
  return;
}

void setup() {
  Serial.begin(9600);
  serialLog("Serial monitor up");
  bluetooth.begin(115200);
  serialLog("Started bluetooth");  
}

void loop() {
  
  if(bluetooth.available()){
    // Send any characters the bluetooth prints to the serial monitor
    serialLog("Bluetooth modem: ");
    Serial.print((char)bluetooth.read());
    serialLog("");  
  }
  if(Serial.available()){
    char toSend = Serial.read();
    
    serialLog("Sending:");
    serialLog((String)toSend);
    serialLog("");
    
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print(toSend);
  }
}
