#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
char buf;
char command = 'D';
boolean button_state = 0;

void setup() {
  Serial.begin(9600);

  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter

  Serial.println("Digite 'L' para ligar ou 'D' para desligar o led:");
}

void loop() {
  buf = Serial.read();
  
  if(buf == 'L' || buf == 'D')  {
    command = buf;
  }
  
  if(command == 'L')  {
    const char text[] = "Your Button State is HIGH";
    radio.write(&text, sizeof(text));                  //Sending the message to receiver
    button_state = 1;
  }
  
  if(command == 'D')  {
    const char text[] = "Your Button State is LOW";
    radio.write(&text, sizeof(text));                  //Sending the message to receiver 
    button_state = 0;
  }

  radio.write(&button_state, sizeof(button_state));  //Sending the message to receiver 
  delay(1000);
}
