//www.elegoo.com
//2016.12.08
#include <Arduino.h>
#include "pins.h"
#include "SR04.h"
#include "Stepper.h"
#include "project2.h"
#include "helper.h"
 

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

void setup() {
    stepper_1.setSpeed(rolePerMinute);
    stepper_2.setSpeed(rolePerMinute);
    stepper_3.setSpeed(rolePerMinute);
    stepper_4.setSpeed(rolePerMinute);
    Serial.begin(9600);//Initialization of Serial Port
    delay(1000);
}

void loop() {
    
    //get The distance for the ultrasonic sensors, then print them to the serial monitor
    distanceUpdate();
    monitorUpdate();

    while(dist_1 < 15) {
        distanceUpdate();
        if(steps_1 < stepsPerRevolution) {
            Serial.print("Ultrasonic Sensor 1: ");
            Serial.print(dist_1);
            Serial.println("cm");
            //Serial.println("clockwise");
            stepper_1.step(100);
            steps_1 += 100;
        }
    }
    while(dist_1 >= 15) {
        distanceUpdate();
        if(steps_1 > 0) {
            Serial.print("Ultrasonic Sensor 1: ");
            Serial.print(dist_1);
            Serial.println("cm");
            //Serial.println("counterclockwise");
            stepper_1.step(-100);
            steps_1 -= 100 ;
        }
    }
}

