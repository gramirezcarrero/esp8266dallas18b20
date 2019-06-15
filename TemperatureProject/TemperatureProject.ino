#include <SoftwareSerial.h>
#include "Config.h";
// arduino Rx (pin 2) ---- ESP8266 Tx
// arduino Tx (pin 3) ---- ESP8266 Rx
SoftwareSerial esp8266(2,3);

void setup() {
  Serial.begin(9600);
  
  esp8266.begin(115200);
  sendData("AT+CWMODE=1\r\n", 5000);
  sendData("AT+CWJAP=\"TP-LINK_AC75A3\",\"Alink514\"\r\n",8000); 
}
int getSensorData(){
  return random(100); // Replace with 
}
void loop() {
Serial.println(SSID);
testGetApi();
}
void testGetApi(){
  Serial.print("test");
  valSensor = getSensorData();
  String getData = "GET /?"+ field +"="+String(valSensor);
  sendData("AT+CIPMUX=1\r\n",100);
  sendData("AT+CIPSTART=4,\"TCP\",\"192.168.0.150\",8080\r\n", 1000);
  printResponse();
  sendData("AT+CIPSEND=0," +String(getData.length()+4)+"\r\n",100);
  esp8266.println(getData);delay(500);countTrueCommand++;
  sendData("AT+CIPCLOSE=0\r\n",1000);
}
void sendData(String comando, const int timeout)
{
 long int time = millis(); // medir el tiempo actual para verificar timeout
 
 esp8266.print(comando); // enviar el comando al ESP8266
 
 while( (time+timeout) > millis()) //mientras no haya timeout
 {
 while(esp8266.available()) //mientras haya datos por leer
 { 
 // Leer los datos disponibles
 char c = esp8266.read(); // leer el siguiente caracter
 Serial.print(c);
 }
 } 
 return;
}
void printResponse() {
  while (esp8266.available()) {
    Serial.println(esp8266.readStringUntil('\n')); 
  }
}
