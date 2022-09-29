//include libraries here 
#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

const int ledPinB = 6; //led on board B
const int ledPinA = 5;
const int ledPin4 = 4;
const int ledPin3 = 3;

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01
//defining the CE and CSN pins 
#define CE_PIN 9
#define CSN_PIN 10 
int table1;
int table2;
int table3;
int table4;

RF24 radio(CE_PIN, CSN_PIN);

const uint64_t pipe =0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin(); //starts the NRF24L01
  radio.openReadingPipe(1, pipe); //getting the NRF24L01
  radio.startListening();
  pinMode (ledPinB, OUTPUT);
  pinMode (ledPinA, OUTPUT);
  pinMode (ledPin3, OUTPUT);
  pinMode (ledPin4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (radio.available())
  {
   radio.read(ReceivedMessage, 1); // Read information from the NRF24L01
   if (ReceivedMessage[0] == 222 || ReceivedMessage[0] == 77){
    table2 = ReceivedMessage[0];
   }
   else if (ReceivedMessage[0] == 0 || ReceivedMessage[0] == 111){
    table1 = ReceivedMessage[0];
   }
   else if (ReceivedMessage[0] == 43 || ReceivedMessage[0] == 188){
    table3 = ReceivedMessage[0];
   }
   else if (ReceivedMessage[0] == 153 || ReceivedMessage[0] == 9){
    table4 = ReceivedMessage[0];
   }
Serial.println(table4);

    //check table 1
    if (table1 == 111) // Indicates switch is pressed
    {
      digitalWrite(ledPinB, HIGH); //turn on lights
    }
    else
    {
       digitalWrite(ledPinB, LOW); //else turn it off
    }
    
    //check the second table
    if (table2 == 222) // Indicates switch is pressed
    {
      digitalWrite(ledPinA, HIGH); //turn on lights
    }
    else
    {
       digitalWrite(ledPinA, LOW); //else turn it off
    }
   
   //check table3
   if (table3 == 43) // Indicates switch is pressed
    {
      digitalWrite(ledPin3, HIGH); //turn on lights
    }
    else
    {
       digitalWrite(ledPin3, LOW); //else turn it off
    }
    //check table 4
    if (table4 == 9) // Indicates switch is pressed
    {
      digitalWrite(ledPin4, HIGH); //turn on lights
    }
    else
    {
       digitalWrite(ledPin4, LOW); //else turn it off
    }
    delay(2);
  }
   

   
  


}
