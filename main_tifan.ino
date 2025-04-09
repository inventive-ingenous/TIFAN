#include<Servo.h>

// X axis
#define directionPin 2  //Direction pin
#define stepPin 3       //Pulse pin

// Y axis
#define directionPin2 4  //Direction pin
#define stepPin2 5       //Pulse pin

// 8000 Steps for 5 revolutions
int temp = 7200;
String str;

// No of movement of conveyor
const int rotations_x = 6;   //X axis
const int rotations_y = 7;  //Y axis

Servo Servo1;
Servo Servo2;

int servoPin1 = 9;
int servoPin2 = 10;

// Limit switches
#define limitSwitchX 6   // Limit switch for X axis
#define limitSwitchY 7   // Limit switch for Y axi

void setup() {
  Serial.begin(9600);

  // Setting up I/O pins
  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  pinMode(directionPin2, OUTPUT);
  pinMode(stepPin2, OUTPUT);

  pinMode(limitSwitchX, INPUT_PULLUP);
  pinMode(limitSwitchY, INPUT_PULLUP);

  Servo1.attach(servoPin1);
  Servo2.attach(servoPin2);
}

void loop() {

  if (Serial.available() > 0) {
    temp = Serial.parseInt();
    str = Serial.readStringUntil("\n");
  }
  Serial.print(temp);


  // This loop is for Y axis repitetive 14 Downwords movements
  for (int j = 0; j < rotations_y; j++) {

    // This loop is for X axis repitetive 7 Forword movements
    for (int k = 0; k < rotations_x; k++) {
      Servo2.write(0);
      delay(500);
      Servo1.write(0);
      delay(500);


      Servo2.write(50);
      delay(500);
      Servo1.write(110);

      delay(500);


      Servo2.write(0);
      delay(500);
      Servo1.write(0);
      delay(500);

      //This loop is for 5 revolution of Nema 23 stepper motor of X axis
      for (int i = 0; i < temp; i++) {
        digitalWrite(directionPin, HIGH);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(50);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(50);
      }
      delay(500);
    }
    Servo2.write(50);
    delay(500);
    Servo1.write(110);

    delay(500);

    Servo2.write(0);
    delay(500);
    Servo1.write(0);

    delay(500);

    //This loop is for 1 revolution of Nema 23 stepper motor to move the conveyor Y axis Downword movements
    for (int i = 0; i < temp; i++) {
      digitalWrite(directionPin2, HIGH);
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(50);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(50);
    }


    delay(500);


    // This loop is for X axis repitetive 7 Backword movements
    for (int k = 0; k < rotations_x; k++) {

      Servo2.write(50);
      delay(500);
      Servo1.write(110);

      delay(500);

      Servo2.write(0);
      delay(500);
      Servo1.write(0);
      delay(500);


      //This loop is for 5 revolution of Nema 23 stepper motor of X axis
      for (int i = 0; i < temp; i++) {
        digitalWrite(directionPin, LOW);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(50);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(50);
      }
      delay(500);
    }

    Servo2.write(50);
    delay(500);
    Servo1.write(110);

    delay(500);

    Servo2.write(0);
    delay(500);
    Servo1.write(0);

    delay(200);

    for (int i = 0; i < temp; i++) {
      digitalWrite(directionPin2, HIGH);
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(50);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(50);
    }

    delay(500);
  }
}

//
//void homeConveyor() {
//  // Home X axis
//  digitalWrite(directionPin, LOW);
//  while (digitalRead(limitSwitchX) == HIGH) {
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(250);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(250);
//  }
//
//  // Home Y axis
//  digitalWrite(directionPin2, LOW);
//  while (digitalRead(limitSwitchY) == HIGH) {
//    digitalWrite(stepPin2, HIGH);
//    delayMicroseconds(250);
//    digitalWrite(stepPin2, LOW);
//    delayMicroseconds(250);
//  }
//
//  // For X direction
//  for (int i = 0; i < 37; i++) {
//    for (int j = 0; j < 1600; j++) {
//      digitalWrite(directionPin2, HIGH);
//      digitalWrite(stepPin2, HIGH);
//      delayMicroseconds(50);
//      digitalWrite(stepPin2, LOW);
//      delayMicroseconds(50);
//    }
//  }
//  //For Y directions
//  for (int i = 0; i < 63; i++) {
//    for (int j = 0; j < 1600; j++) {
//      digitalWrite(directionPin2, HIGH);
//      digitalWrite(stepPin2, HIGH);
//      delayMicroseconds(50);
//      digitalWrite(stepPin2, LOW);
//      delayMicroseconds(50);
//    }
//  }
//}
