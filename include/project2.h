#ifndef PROJECT2_H
#define PROJECT2_H

#include <Arduino.h>
#include "pins.h"
#include "SR04.h"
#include "Stepper.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

SR04 sr04_1 = SR04(US1_ECHO_PIN,US1_TRIG_PIN);
SR04 sr04_2 = SR04(US2_ECHO_PIN,US2_TRIG_PIN);
SR04 sr04_3 = SR04(US3_ECHO_PIN,US3_TRIG_PIN);
SR04 sr04_4 = SR04(US4_ECHO_PIN,US4_TRIG_PIN);

//Define state machine variables that will control the state of the machine
int state = 0;

//Variables used for sensor arrays
long dist_1, dist_2, dist_3, dist_4;
int steps_1, steps_2, steps_3, steps_4;
int pirValue; // Place to store read PIR Value

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

//Stepper Motor Class Definitions
Stepper stepper_1(stepsPerRevolution, M1_PIN_1, M1_PIN_2, M1_PIN_3, M1_PIN_4);
Stepper stepper_2(stepsPerRevolution, M2_PIN_1, M2_PIN_2, M2_PIN_3, M2_PIN_4);
Stepper stepper_3(stepsPerRevolution, M3_PIN_1, M3_PIN_2, M3_PIN_3, M3_PIN_4);
Stepper stepper_4(stepsPerRevolution, M4_PIN_1, M4_PIN_2, M4_PIN_3, M4_PIN_4);

#endif