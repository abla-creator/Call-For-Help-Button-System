/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-switch
 */
//include libraries here
#include <ezButton.h> 
#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

//defining the CE and CSN pins 
#define CE_PIN 9
#define CSN_PIN 10 

int SentMessage[1] = {000};
RF24 radio(CE_PIN, CSN_PIN);

//location for communicating. Should be that same for both NRF24L01
const uint64_t pipe =0xE6E6E6E6E6E6;
ezButton toggleSwitch(7);  // create ezButton object that attach to pin 7;
const int led = 2; //led for pin 2
int ledState = 0; 

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  toggleSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
  radio.begin(); //start the tranceiver 
  radio.openWritingPipe(pipe);  //get it ready to transmit 

}

void loop() {
  toggleSwitch.loop(); // MUST call the loop() function first
 
  if (toggleSwitch.isPressed()){
    Serial.println("The switch: OFF -> ON");
    digitalWrite(led,HIGH);
      delay (50);
    
  }
  if (toggleSwitch.isReleased()){
    Serial.println("The switch: ON -> OFF");
     if (ledState == LOW){
      digitalWrite(led,HIGH);
      delay (50);
      ledState = 1;
      SentMessage[0] = 555;
      Serial.println(SentMessage[0]);
      radio.write(SentMessage, 1);
    }
    else{
      digitalWrite(led,LOW);
      ledState = 0;
      delay (50);
      SentMessage[0] = 444;
      radio.write(SentMessage, 1);
      Serial.println(SentMessage[0]);
    }
  }
}
