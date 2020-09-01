#include <SoftwareSerial.h>

long int bluetoothBaud = 115200;
long int serialBaud = 9600;
int boardT = 4;
int boardR = 6;

SoftwareSerial bluetooth(boardT, boardR);

void serialLog(String message){
  Serial.println(message);
  return;
}

void setupModem(){
  serialLog("Entering command mode");
  bluetooth.print("$");
  bluetooth.print("$");
  bluetooth.print("$");
  
  delay(150); // waiting for response. 150 millisecond "should work"
  bluetooth.print("U,9600,N\n"); // changing to 9600 baud
  
  delay(150);
  bluetooth.begin(serialBaud); // restarting
  serialLog("Switched to 9600 baud");
}

void setup() {
  Serial.begin(serialBaud);
  serialLog("Serial monitor up");
  bluetooth.begin(bluetoothBaud);
  serialLog("Started bluetooth");  

  setupModem();
}

void loop() {
  
  if(bluetooth.available()){
    // Send any characters the bluetooth prints to the serial monitor
    serialLog("Bluetooth modem: ");
    Serial.print((char)bluetooth.read());
  }
  
  if(Serial.available()){
    char toSend = Serial.read();
    
    serialLog("Sending:");
    serialLog((String)toSend);
    
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print(toSend);
  }
}
