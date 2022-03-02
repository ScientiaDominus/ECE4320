//www.elegoo.com
//2016.12.08
#include <Arduino.h>
#include "SR04.h"
#include "Stepper.h"
#define TRIG_PIN 13
#define ECHO_PIN 12 

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine4;          //xy=323.00000381469727,563.0000324249268
AudioSynthWaveformSine   sine2;          //xy=327.00000381469727,460
AudioSynthWaveformSine   sine3;          //xy=329.00000381469727,511.00003242492676
AudioSynthWaveformSine   sine1;          //xy=330.00000381469727,405
AudioMixer4              mixer1;         //xy=616.0000076293945,471.00000762939453
AudioOutputMQS           mqs1;           //xy=770.0000114440918,477.4000072479248
AudioConnection          patchCord1(sine4, 0, mixer1, 3);
AudioConnection          patchCord2(sine2, 0, mixer1, 1);
AudioConnection          patchCord3(sine3, 0, mixer1, 2);
AudioConnection          patchCord4(sine1, 0, mixer1, 0);
AudioConnection          patchCord5(mixer1, 0, mqs1, 0);
// GUItool: end automatically generated code


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
    while(a < 15) {
        a=sr04.Distance();
        if(steps < stepsPerRevolution) {
            Serial.print(a);
            Serial.println("cm");
            //Serial.println("clockwise");
            myStepper.step(100);
            steps += 100;
        }
    }
    while(a >= 15) {
        a=sr04.Distance();
        if(steps > 0) {
            Serial.print(a);
            Serial.println("cm");
            //Serial.println("counterclockwise");
            myStepper.step(-100);
            steps -= 100 ;
        }
    }
}
