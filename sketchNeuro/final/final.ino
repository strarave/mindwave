#include <SoftwareSerial.h>

long int bluetoothBaud = 57600;
long int serialBaud = 57600;
int boardT = 4; // TX on the modem
int boardR = 6; // RX on the modem

SoftwareSerial bluetooth(boardT, boardR);

void serialLog(String message){
  Serial.println(message);
  return;
}

void setup() {
  Serial.begin(serialBaud);
  serialLog("Serial monitor up");
  bluetooth.begin(bluetoothBaud);
  serialLog("Started bluetooth");  
}

void loop() {
  
  if(bluetooth.available()){
    // Send any characters the bluetooth prints to the serial monitor
    Serial.print((char)bluetooth.read());
  }
  
  if(Serial.available()){
    char toSend = Serial.read();
    
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print(toSend);
  }
}
