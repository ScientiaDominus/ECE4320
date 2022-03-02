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