/**
 * This programis meant to test the connection between two arduino boards using two nRf24l01 transceivers
 * The function of this program would be to turn on led lights connected to both Arduino boards when a button is pressed. 
 * And turn them off when another button is pressed. 
 * This is the tranceiver code
 * 
 */
//include libraries here 
#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"


//constant variables the program 
const int buttonBoardA = 8; // the button acts as a switch 

//defining the CE and CSN pins 
#define CE_PIN 9
#define CSN_PIN 10 

int SentMessage[1] = {000};
RF24 radio(CE_PIN, CSN_PIN);

//location for communicating. Should be that same for both NRF24L01
const uint64_t pipe =0xE6E6E6E6E6E6;


//variables related to this program 
int lastButtonState = 0; 
int currentButtonState = 0;

int ledState = LOW;
int lastLedState = HIGH;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //set the serial monitor to record the button states 
 
  pinMode(buttonBoardA, INPUT_PULLUP);

  radio.begin(); //start the tranceiver 
  radio.openWritingPipe(pipe);  //get it ready to transmit 

}

void loop() {
  // put your main code here, to run repeatedly:
  lastButtonState    = currentButtonState;      // save the last state
  currentButtonState = digitalRead(buttonBoardA); // read new state
  
  if(lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("The button is pressed");


     // toggle state of LED
    if (ledState == LOW){
      SentMessage[0] = 665;
      Serial.println(SentMessage[0]);
      radio.write(SentMessage, 1);
      Serial.println("here"); 
      Serial.println(radio.write(SentMessage, 1));// Send pressed data to NRF24L01
    
     lastLedState = LOW;
     ledState = HIGH;
      
    }
    else{
      SentMessage[0] = 777;
      radio.write(SentMessage, 1);
      Serial.println(SentMessage[0]);
      Serial.println(radio.write(SentMessage, 1));// Send idle data to NRF24L01
      lastLedState = HIGH;
      ledState = LOW;
    }
   

  }}
  

  
