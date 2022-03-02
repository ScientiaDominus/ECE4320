//www.elegoo.com
//2016.12.08
#include <Arduino.h>
#include "SR04.h"
#include "Stepper.h"
#include "pins.h"
//#define TRIG_PIN 15
//#define ECHO_PIN 14 

//Define state machine variables that will control the state of the machine
int state = 0;


SR04 sr04_1 = SR04(US1_ECHO_PIN, US1_TRIG_PIN);
SR04 sr04_2 = SR04(US2_ECHO_PIN, US2_TRIG_PIN);
SR04 sr04_3 = SR04(US3_ECHO_PIN, US3_TRIG_PIN);
SR04 sr04_4 = SR04(US4_ECHO_PIN, US4_TRIG_PIN);
long dist_1, dist_2, dist_3, dist_4;
int steps;

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, M1_PIN_1, M1_PIN_2, M1_PIN_3, M1_PIN_4);

void setup() {
   myStepper.setSpeed(rolePerMinute);
   Serial.begin(9600);//Initialization of Serial Port
   delay(1000);
}

void loop() {
   dist_1=sr04_1.Distance();
   dist_2=sr04_2.Distance();
   dist_3=sr04_3.Distance();
   dist_4=sr04_4.Distance();
   Serial.print
   Serial.print(dist_1);
   Serial.println("cm");//The difference between "Serial.print" and "Serial.println" 
                        //is that "Serial.println" can change lines.
   Serial.print(dist_1);
   Serial.println("cm");
   Serial.print(dist_1);
   Serial.println("cm");
   Serial.print(dist_1);
   Serial.println("cm");
   while(a < 15)
   {
     digitalReadFast
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
