//www.elegoo.com
//2016.12.08
//#include "project2.h"
#include <Arduino.h>
#include <Stepper.h>
#include "pins.h"
#include "SR04.h"
//#include "Stepper.h"
#include "proj_2_audio.h"

//Define state machine variables that will control the state of the machine
int state = 4, currentMotor = 0, counter = 0, funMode = 0;
int notes[74] = {4,3,2,3,4,0,4,0,4,0,
                 3,0,3,0,3,4,1,1,4,3,
                 2,3,4,0,4,0,4,0,4,0,
                 3,0,3,4,3,2,0,2,4,3,
                 2,3,4,0,4,0,4,0,3,0,
                 3,0,3,4,1,0,1,4,3,2,
                 3,4,0,4,0,4,0,4,3,0,
                 3,4,3,2};

void stateMachine();
void updateState();
void monitorUpdate();
void distanceUpdate();
void runMotors();
void killMotors(int select);
void initializeLEDS();
void clearLEDS();
void button();
void stepMotor(int motor);
void rvrsMotor(int motor);

SR04 sr04_1 = SR04(US1_ECHO_PIN,US1_TRIG_PIN);
SR04 sr04_2 = SR04(US2_ECHO_PIN,US2_TRIG_PIN);
SR04 sr04_3 = SR04(US3_ECHO_PIN,US3_TRIG_PIN);
SR04 sr04_4 = SR04(US4_ECHO_PIN,US4_TRIG_PIN);

//Variables used for sensor arrays
long dist_1, dist_2, dist_3, dist_4;
int steps_1 = 0, steps_2 = 0, steps_3 = 0, steps_4 = 0;
elapsedMillis ledTimer;

const int stepsPerRevolution = 1000;  // change this to fit the number of steps per revolution
const int numSteps = 100;
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

//Stepper Motor Class Definitions
Stepper stepper_1(stepsPerRevolution, M1_PIN_1, M1_PIN_3, M1_PIN_2, M1_PIN_4);
Stepper stepper_2(stepsPerRevolution, M2_PIN_1, M2_PIN_3, M2_PIN_2, M2_PIN_4);
Stepper stepper_3(stepsPerRevolution, M3_PIN_1, M3_PIN_3, M3_PIN_2, M3_PIN_4);
Stepper stepper_4(stepsPerRevolution, M4_PIN_1, M4_PIN_3, M4_PIN_2, M4_PIN_4);

void setup() {
    AudioMemory(20);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON), button, RISING);
    sine1.frequency(noteFreq[NOTE_C6]);
    sine1.amplitude(0);

    sine2.frequency(noteFreq[NOTE_D6]);
    sine2.amplitude(0);

    sine3.frequency(noteFreq[NOTE_E6]);
    sine3.amplitude(0);

    sine4.frequency(noteFreq[NOTE_B5]);
    sine4.amplitude(0);

    stepper_1.setSpeed(rolePerMinute);
    stepper_2.setSpeed(rolePerMinute);
    stepper_3.setSpeed(rolePerMinute);
    stepper_4.setSpeed(rolePerMinute);
    Serial.begin(9600);//Initialization of Serial Port
    initializeLEDS();
    
    digitalWriteFast(LED1_R, HIGH);
    digitalWriteFast(LED1_G, HIGH);
    digitalWriteFast(LED1_B, HIGH);
    digitalWriteFast(LED2_R, HIGH);
    digitalWriteFast(LED2_G, HIGH);
    digitalWriteFast(LED2_B, HIGH);
    digitalWriteFast(LED3_R, HIGH);
    digitalWriteFast(LED3_G, HIGH);
    digitalWriteFast(LED3_B, HIGH);
    digitalWriteFast(LED4_R, HIGH);
    digitalWriteFast(LED4_G, HIGH);
    digitalWriteFast(LED4_B, HIGH);

    delay(1000);

    clearLEDS();
}

void loop() {
    if(ledTimer >= 1000) { // heartbeat led
        digitalWriteFast(LED_BUILTIN, !digitalReadFast(LED_BUILTIN));
        ledTimer = 0;
    }
    //get The distance for the ultrasonic sensors, then print them to the serial monitor
    distanceUpdate();
    monitorUpdate();
    updateState();
    stateMachine();
    runMotors();
    if(funMode == 0){
        sine1.amplitude(steps_1/(float)stepsPerRevolution);
        sine2.amplitude(steps_2/(float)stepsPerRevolution);
        sine3.amplitude(steps_3/(float)stepsPerRevolution);
        sine4.amplitude(steps_4/(float)stepsPerRevolution);
    }
    
}

void distanceUpdate() {
    dist_1=sr04_1.Distance();
    dist_2=sr04_2.Distance();
    dist_3=sr04_3.Distance();
    dist_4=sr04_4.Distance();
}

void monitorUpdate() {
    Serial.print("Ultrasonic Sensor 1: ");
    Serial.print(dist_1);
    Serial.println("cm");
    Serial.print("Ultrasonic Sensor 2: ");
    Serial.print(dist_2);
    Serial.println("cm");
    Serial.print("Ultrasonic Sensor 3: ");
    Serial.print(dist_3);
    Serial.println("cm");
    Serial.print("Ultrasonic Sensor 4: ");
    Serial.print(dist_4);
    Serial.println("cm");
}

void stepMotor(int motor) {
    killMotors(motor);
    switch(motor) {
        case 1:
            if(steps_1 < stepsPerRevolution) {
                /*Serial.print("Ultrasonic Sensor 1: ");
                Serial.print(dist_1);
                Serial.println("cm");*/
                //Serial.println("clockwise");
                if(funMode == 1){sine1.amplitude(.9);}
                digitalWriteFast(LED1_G, HIGH);
                stepper_1.step(numSteps);
                steps_1 += numSteps;
            }
            break;
        case 2:
            if(steps_2 < stepsPerRevolution) {
                /*Serial.print("Ultrasonic Sensor 2: ");
                Serial.print(dist_2);
                Serial.println("cm");*/
                //Serial.println("clockwise");
                digitalWriteFast(LED2_G, HIGH);
                if(funMode == 1){sine2.amplitude(.9);}
                stepper_2.step(numSteps);
                steps_2 += numSteps;
            }
            break;
        case 3:
            if(steps_3 < stepsPerRevolution) {
                /*Serial.print("Ultrasonic Sensor 3: ");
                Serial.print(dist_3);
                Serial.println("cm");*/
                //Serial.println("clockwise");
                digitalWriteFast(LED3_G, HIGH);
                if(funMode == 1){sine3.amplitude(.9);}
                stepper_3.step(numSteps);
                steps_3 += numSteps;
            }
            break;
        case 4:
            if(steps_4 < stepsPerRevolution) {
                /*Serial.print("Ultrasonic Sensor 4: ");
                Serial.print(dist_4);
                Serial.println("cm");*/
                //Serial.println("clockwise");
                digitalWriteFast(LED4_G, HIGH);
                if(funMode == 1){sine4.amplitude(.9);}
                stepper_4.step(numSteps);
                steps_4 += numSteps;
            }
            break;
        default:
            break;
    }
}

void rvrsMotor(int motor) {
    killMotors(motor);
    switch(motor) {
        case 1:
            if(steps_1 > 0) {
                /*Serial.print("Ultrasonic Sensor 1: ");
                Serial.print(dist_1);
                Serial.println("cm");
                //Serial.println("counterclockwise");*/
                digitalWriteFast(LED1_R, HIGH);
                if(funMode == 1){sine1.amplitude(0);}
                stepper_1.step(-numSteps);
                steps_1 -= numSteps ;
            }
            break;
        case 2:
            if(steps_2 > 0) {
                /*Serial.print("Ultrasonic Sensor 2: ");
                Serial.print(dist_2);
                Serial.println("cm");
                //Serial.println("counterclockwise");*/
                digitalWriteFast(LED2_R, HIGH);
                if(funMode == 1){sine2.amplitude(0);}
                stepper_2.step(-numSteps);
                steps_2 -= numSteps ;
            }
            break;
        case 3:
            if(steps_3 > 0) {
                /*Serial.print("Ultrasonic Sensor 3: ");
                Serial.print(dist_3);
                Serial.println("cm");
                //Serial.println("counterclockwise");*/
                digitalWriteFast(LED3_R, HIGH);
                if(funMode == 1){sine3.amplitude(0);}
                stepper_3.step(-numSteps);
                steps_3 -= numSteps ;
            }
            break;
        case 4:
            if(steps_4 > 0) {
                /*Serial.print("Ultrasonic Sensor 4: ");
                Serial.print(dist_4);
                Serial.println("cm");
                //Serial.println("counterclockwise");*/
                if(funMode == 1){sine4.amplitude(0);}
                digitalWriteFast(LED4_R, HIGH);
                stepper_4.step(-numSteps);
                steps_4 -= numSteps ;
            }
            break;
        default:
            break;
    }
}

void runMotors() {
    distanceUpdate();
    clearLEDS();
    if(dist_1 < 15) {
        //distanceUpdate();
        currentMotor = 1;
        //play note here
        stepMotor(1);
    }
    else if(dist_1 >= 15) {
        //distanceUpdate();
        //digitalWriteFast(LED1_G, HIGH);
        //play note here
        rvrsMotor(1);
    }

    if(dist_2 < 15) {
        //distanceUpdate();
        currentMotor = 2;
        //play note here
        stepMotor(2);
    }
    else if(dist_2 >= 15) {
        //distanceUpdate();
        //digitalWriteFast(LED2_G, HIGH);
        rvrsMotor(2);
    }

    if(dist_3 < 15) {
        //distanceUpdate();
        currentMotor = 3;
        //play note here
        stepMotor(3);
    }
    else if(dist_3 >= 15) {
        //distanceUpdate();
        //digitalWriteFast(LED3_G, HIGH);
        rvrsMotor(3);
    }

    if(dist_4 < 15) {
        //distanceUpdate();
        currentMotor = 4;
        //play note here
        stepMotor(4);
    }
    else if(dist_4 >= 15) {
        //distanceUpdate();
        //digitalWriteFast(LED4_G, HIGH);
        rvrsMotor(4);
    }
}

void initializeLEDS() {
    pinMode(LED1_R, OUTPUT);
    pinMode(LED1_G, OUTPUT);
    pinMode(LED1_B, OUTPUT);
    pinMode(LED2_R, OUTPUT);
    pinMode(LED2_G, OUTPUT);
    pinMode(LED2_B, OUTPUT);
    pinMode(LED3_R, OUTPUT);
    pinMode(LED3_G, OUTPUT);
    pinMode(LED3_B, OUTPUT);
    pinMode(LED4_R, OUTPUT);
    pinMode(LED4_G, OUTPUT);
    pinMode(LED4_B, OUTPUT);

    clearLEDS();
}

void clearLEDS(){
    switch (state){
        case 1:{
            //digitalWriteFast(LED1_B, LOW);
            digitalWriteFast(LED2_B, LOW);
            digitalWriteFast(LED3_B, LOW);
            digitalWriteFast(LED4_B, LOW);
            break;
        }
        case 2:{
            digitalWriteFast(LED1_B, LOW);
            //digitalWriteFast(LED2_B, LOW);
            digitalWriteFast(LED3_B, LOW);
            digitalWriteFast(LED4_B, LOW);
            break;
        }

        case 3:{
            digitalWriteFast(LED1_B, LOW);
            digitalWriteFast(LED2_B, LOW);
            //digitalWriteFast(LED3_B, LOW);
            digitalWriteFast(LED4_B, LOW);
            break;
        }

        case 4:{
            digitalWriteFast(LED1_B, LOW);
            digitalWriteFast(LED2_B, LOW);
            digitalWriteFast(LED3_B, LOW);
            //digitalWriteFast(LED4_B, LOW);
            break;
        }

        default:{
            digitalWriteFast(LED1_B, LOW);
            digitalWriteFast(LED2_B, LOW);
            digitalWriteFast(LED3_B, LOW);
            digitalWriteFast(LED4_B, LOW);
            break;
        }

    }
    digitalWriteFast(LED1_R, LOW);
    digitalWriteFast(LED1_G, LOW);
    //digitalWriteFast(LED1_B, LOW);
    digitalWriteFast(LED2_R, LOW);
    digitalWriteFast(LED2_G, LOW);
    //digitalWriteFast(LED2_B, LOW);
    digitalWriteFast(LED3_R, LOW);
    digitalWriteFast(LED3_G, LOW);
    //digitalWriteFast(LED3_B, LOW);
    digitalWriteFast(LED4_R, LOW);
    digitalWriteFast(LED4_G, LOW);
    //digitalWriteFast(LED4_B, LOW);
}

void updateState(){
    if(counter < 74){
        if(currentMotor == notes[counter]){
            state = notes[counter + 1];
            counter++;
        }
        else if(notes[counter] == 0)
        {
            state = notes[counter + 1];
            counter++;
        }
    }
    else if(counter >= 74){
        counter = 0;
    }
}

void stateMachine(){
    switch(state){
        case 1:{
            digitalWriteFast(LED1_B, HIGH);
            
            if(state != 1){
                digitalWriteFast(LED1_B, LOW);
            }
            break;
        }
        case 2:{
            digitalWriteFast(LED2_B, HIGH);
            
            if(state != 2){
                digitalWriteFast(LED2_B, LOW);
            }
            break;
        }
        case 3:{
            digitalWriteFast(LED3_B, HIGH);
            
            if(state != 3){
                digitalWriteFast(LED3_B, LOW);
            }
            break;
        }
        case 4:{
            digitalWriteFast(LED4_B, HIGH);
            
            if(state != 4){
                digitalWriteFast(LED4_B, LOW);
            }
            break;
        }
        default:{
            //if(funMode == 1){delay(500);}
            break;
        }
    }
}

void killMotors(int select){
    switch(select){
        case 1:{
            digitalWriteFast(M2_PIN_1, LOW);
            digitalWriteFast(M2_PIN_2, LOW);
            digitalWriteFast(M2_PIN_3, LOW);
            digitalWriteFast(M2_PIN_4, LOW);
            digitalWriteFast(M3_PIN_1, LOW);
            digitalWriteFast(M3_PIN_2, LOW);
            digitalWriteFast(M3_PIN_3, LOW);
            digitalWriteFast(M3_PIN_4, LOW);
            digitalWriteFast(M4_PIN_1, LOW);
            digitalWriteFast(M4_PIN_2, LOW);
            digitalWriteFast(M4_PIN_3, LOW);
            digitalWriteFast(M4_PIN_4, LOW);
            break;
        }
        case 2:{
            digitalWriteFast(M1_PIN_1, LOW);
            digitalWriteFast(M1_PIN_2, LOW);
            digitalWriteFast(M1_PIN_3, LOW);
            digitalWriteFast(M1_PIN_4, LOW);
            digitalWriteFast(M3_PIN_1, LOW);
            digitalWriteFast(M3_PIN_2, LOW);
            digitalWriteFast(M3_PIN_3, LOW);
            digitalWriteFast(M3_PIN_4, LOW);
            digitalWriteFast(M4_PIN_1, LOW);
            digitalWriteFast(M4_PIN_2, LOW);
            digitalWriteFast(M4_PIN_3, LOW);
            digitalWriteFast(M4_PIN_4, LOW);
            break;
        }
        case 3:{
            digitalWriteFast(M2_PIN_1, LOW);
            digitalWriteFast(M2_PIN_2, LOW);
            digitalWriteFast(M2_PIN_3, LOW);
            digitalWriteFast(M2_PIN_4, LOW);
            digitalWriteFast(M1_PIN_1, LOW);
            digitalWriteFast(M1_PIN_2, LOW);
            digitalWriteFast(M1_PIN_3, LOW);
            digitalWriteFast(M1_PIN_4, LOW);
            digitalWriteFast(M4_PIN_1, LOW);
            digitalWriteFast(M4_PIN_2, LOW);
            digitalWriteFast(M4_PIN_3, LOW);
            digitalWriteFast(M4_PIN_4, LOW);
            break;
        }
        case 4:{
            digitalWriteFast(M2_PIN_1, LOW);
            digitalWriteFast(M2_PIN_2, LOW);
            digitalWriteFast(M2_PIN_3, LOW);
            digitalWriteFast(M2_PIN_4, LOW);
            digitalWriteFast(M3_PIN_1, LOW);
            digitalWriteFast(M3_PIN_2, LOW);
            digitalWriteFast(M3_PIN_3, LOW);
            digitalWriteFast(M3_PIN_4, LOW);
            digitalWriteFast(M1_PIN_1, LOW);
            digitalWriteFast(M1_PIN_2, LOW);
            digitalWriteFast(M1_PIN_3, LOW);
            digitalWriteFast(M1_PIN_4, LOW);
            break;
        }
        default:{
            break;
        }
    }
}

void button(){
    funMode = !funMode;
}