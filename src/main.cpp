//www.elegoo.com
//2016.12.08
#include <Arduino.h>
#include "SR04.h"
#include "Stepper.h"
#define TRIG_PIN 13
#define ECHO_PIN 12 

//Define state machine variables that will control the state of the machine
int state = 0;


SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
int steps;
int pirPin = 7; // Input for HC-S501
int pirValue; // Place to store read PIR Value

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
   myStepper.setSpeed(rolePerMinute);
   pinMode(pirPin, INPUT);
   Serial.begin(9600);//Initialization of Serial Port
   delay(1000);
}

void loop() {
   a=sr04.Distance();
   Serial.print(a);
   Serial.println("cm");//The difference between "Serial.print" and "Serial.println" 
                        //is that "Serial.println" can change lines.
   while(a < 15)
   {
    a=sr04.Distance();
    if(steps < stepsPerRevolution)
    {
      Serial.print(a);
      Serial.println("cm");
      //Serial.println("clockwise");
      myStepper.step(100);
      steps += 100;
    }
   }
   while(a >= 15)
   {
    a=sr04.Distance();
    if(steps > 0)
    {
      Serial.print(a);
      Serial.println("cm");
      //Serial.println("counterclockwise");
      myStepper.step(-100);
      steps -= 100 ;
    }
   }
}
