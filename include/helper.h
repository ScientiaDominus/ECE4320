#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>
#include "pins.h"
#include "SR04.h"
#include "Stepper.h"
#include "project2.h"

void monitorUpdate();
void distanceUpdate();
void stepMotor(int motor);
void rvrsMotor(int motor);