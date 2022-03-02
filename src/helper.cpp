#include "helper.h"

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

void stepMotor(int motor)
{
    switch(motor)
    {
        case 1:
            if(steps_1 < stepsPerRevolution) {
                    Serial.print("Ultrasonic Sensor 1: ");
                    Serial.print(dist_1);
                    Serial.println("cm");
                    //Serial.println("clockwise");
                    stepper_1.step(100);
                    steps_1 += 100;
            }
            break;
        case 2:
            if(steps_2 < stepsPerRevolution) {
                    Serial.print("Ultrasonic Sensor 2: ");
                    Serial.print(dist_2);
                    Serial.println("cm");
                    //Serial.println("clockwise");
                    stepper_2.step(100);
                    steps_2 += 100;
            }
            break;
        case 3:
            if(steps_3 < stepsPerRevolution) {
                Serial.print("Ultrasonic Sensor 3: ");
                Serial.print(dist_3);
                Serial.println("cm");
                //Serial.println("clockwise");
                stepper_3.step(100);
                steps_3 += 100;
            }
            break;
        case 4:
            if(steps_4 < stepsPerRevolution) {
                Serial.print("Ultrasonic Sensor 4: ");
                Serial.print(dist_4);
                Serial.println("cm");
                //Serial.println("clockwise");
                stepper_4.step(100);
                steps_4 += 100;
            }
            break;
        default:
            break;
    }
}

void rvrsMotor(int motor)
{
    switch(motor)
    {
        case 1:
            if(steps_1 > 0) {
                Serial.print("Ultrasonic Sensor 1: ");
                Serial.print(dist_1);
                Serial.println("cm");
                //Serial.println("counterclockwise");
                stepper_1.step(-100);
                steps_1 -= 100 ;
            }
            break;
        case 2:
            if(steps_2 > 0) {
                Serial.print("Ultrasonic Sensor 2: ");
                Serial.print(dist_2);
                Serial.println("cm");
                //Serial.println("counterclockwise");
                stepper_2.step(-100);
                steps_2 -= 100 ;
            }
            break;
        case 3:
            if(steps_3 > 0) {
                Serial.print("Ultrasonic Sensor 3: ");
                Serial.print(dist_3);
                Serial.println("cm");
                //Serial.println("counterclockwise");
                stepper_3.step(-100);
                steps_3 -= 100 ;
            }
            break;
        case 4:
            if(steps_4 > 0) {
                Serial.print("Ultrasonic Sensor 4: ");
                Serial.print(dist_4);
                Serial.println("cm");
                //Serial.println("counterclockwise");
                stepper_4.step(-100);
                steps_4 -= 100 ;
            }
            break;
        default:
            break;
    }
}