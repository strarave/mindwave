/*
  Example Bluetooth Serial Passthrough Sketch
 by: Jim Lindblom
 SparkFun Electronics
 date: February 26, 2013
 license: Public domain

 This example sketch converts an RN-42 bluetooth module to
 communicate at 9600 bps (from 115200), and passes any serial
 data between Serial Monitor and bluetooth module.
 */
#include <SoftwareSerial.h>  

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

long int bluetoothBaudRate = 9600; 
long int serialBaudRate = 9600;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  delay(1000);
  Serial.begin(serialBaudRate);
  Serial.println("Serial monitor up, starting bluetooth serial");
  
  bluetooth.begin(bluetoothBaudRate);  
  
  delay(150);
  bluetooth.print("$");  
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  delay(1000);  // Short delay, wait for the Mate to send back CMD*/
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(serialBaudRate);  // Start bluetooth serial at 9600
  
  Serial.print("Bluetooth up, baud ");
  Serial.println(serialBaudRate);
  
}

void loop()
{

  if(bluetooth.available()){
    // Send any characters the bluetooth prints to the serial monitor
    Serial.print("Bluetooth modem: ");
    Serial.print((char)bluetooth.read());
    Serial.println();  
  }
  if(Serial.available()){
    char toSend = Serial.read();
    
    Serial.print("Sending: \"");
    Serial.print(toSend);
    Serial.print("\"");
    Serial.println();
    
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print(toSend);
  }
  // and loop forever and ever!
}
