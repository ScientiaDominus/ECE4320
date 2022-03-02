//www.elegoo.com
//2016.12.08
#include <Arduino.h>
#include "pins.h"
#include "SR04.h"
#include "Stepper.h"
#include "project2.h"
#include "helper.h"
#include "proj_2_audio.h"
 

void setup() {
    AudioMemory(20);

    sine1.frequency(noteFreq[NOTE_C6]);
    sine1.amplitude(1);

    sine2.frequency(noteFreq[NOTE_D6]);
    sine2.amplitude(1);

    sine3.frequency(noteFreq[NOTE_E6]);
    sine3.amplitude(1);

    sine4.frequency(noteFreq[NOTE_B5]);
    sine4.amplitude(1);

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

