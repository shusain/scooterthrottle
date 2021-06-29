#include <Arduino.h>
#include "Servo.h"

Servo escOuptut;

static int ESC_MIN = 1000;
static int ESC_MAX = 2000;

static int ACCELERATE_HALL_SENSOR_MIN = 540;
static int ACCELERATE_HALL_SENSOR_MAX = 670;

static int BRAKE_HALL_SENSOR_MIN = 507;
static int BRAKE_HALL_SENSOR_MAX = 690;


static int AVG_HALL_SENSOR_MIN = 450;
static int AVG_HALL_SENSOR_MAX = 650;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  escOuptut.attach(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(analogRead(A0));
  int accHallSensorVal = analogRead(A0);
  int brakeHallSensorVal = analogRead(A1);

  int avgHallSensorVal = (accHallSensorVal + (1024-brakeHallSensorVal))/2;
  
  int mappedAccVal = map(accHallSensorVal, ACCELERATE_HALL_SENSOR_MIN, ACCELERATE_HALL_SENSOR_MAX, ESC_MIN, ESC_MAX);
  int mappedBrakeVal = map(brakeHallSensorVal, BRAKE_HALL_SENSOR_MIN, BRAKE_HALL_SENSOR_MAX, ESC_MIN, ESC_MAX);
  int mappedAvgVal = map(avgHallSensorVal, AVG_HALL_SENSOR_MIN, AVG_HALL_SENSOR_MAX, ESC_MIN, ESC_MAX);

  
  Serial.print(mappedAccVal);
  Serial.print("\t");
  
  Serial.print(mappedBrakeVal);
  Serial.print("\t");
  
  Serial.println(mappedAvgVal);
  escOuptut.writeMicroseconds(mappedAvgVal);
  delay(10);
}