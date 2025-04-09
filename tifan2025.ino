#include <Servo.h>

// X axis
#define directionPin 2  //Direction pin
#define stepPin 3       //Pulse pin

// Y axis
#define directionPin2 4  //Direction pin
#define stepPin2 5       //Pulse pin

// Digging Mechanism (NEMA 34)
#define STEP_DIG 6
#define DIR_DIG 7

// 8000 Steps for 5 revolutions
int temp = 7200;
String str;

// No of movement of conveyor
const int rotations_x = 6;   //X axis
const int rotations_y = 7;  //Y axis

Servo ArmServo;
Servo GripperServo;

int armServoPin = 9;
int gripperServoPin = 10;

void setup() {
  Serial.begin(9600);

  // Setting up I/O pins
  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  pinMode(directionPin2, OUTPUT);
  pinMode(stepPin2, OUTPUT);

  pinMode(STEP_DIG, OUTPUT);
  pinMode(DIR_DIG, OUTPUT);

  ArmServo.attach(armServoPin);
  GripperServo.attach(gripperServoPin);

  Serial.println("System Initialized");
}

void loop() {
  if (Serial.available() > 0) {
    temp = Serial.parseInt();
    str = Serial.readStringUntil("\n");
  }
  Serial.print("Current step count: ");
  Serial.println(temp);

  // This loop is for Y axis repetitive 14 Downward movements
  for (int j = 0; j < rotations_y; j++) {
    // This loop is for X axis repetitive 7 Forward movements
    for (int k = 0; k < rotations_x; k++) {
      Serial.println("Moving Arm Forward");
      GripperServo.write(0);
      delay(500);
      ArmServo.write(0);
      delay(500);

      Serial.println("Gripping Plant");
      GripperServo.write(50);
      delay(500);
      ArmServo.write(110);
      delay(500);

      Serial.println("Lifting Plant");
      GripperServo.write(0);
      delay(500);
      ArmServo.write(0);
      delay(500);

      Serial.println("Moving in X Direction");
      for (int i = 0; i < temp; i++) {
        digitalWrite(directionPin, LOW);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(50);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(50);
      }
      delay(500);
    }

    Serial.println("Lowering Plant for Digging");
    GripperServo.write(50);
    delay(500);
    ArmServo.write(110);
    delay(500);
    GripperServo.write(0);
    delay(500);
    ArmServo.write(0);
    delay(500);

    Serial.println("Activating Digging Mechanism");
    moveStepper(STEP_DIG, DIR_DIG, 300, HIGH, 300);
    delay(2000);
    moveStepper(STEP_DIG, DIR_DIG, 300, LOW, 300);
    delay(2000);
    Serial.println("Digging Complete");

    Serial.println("Moving Conveyor in Y Direction");
    for (int i = 0; i < temp; i++) {
      digitalWrite(directionPin2, HIGH);
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(50);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(50);
    }
    delay(500);

    Serial.println("Returning Arm to Initial Position");
    for (int k = 0; k < rotations_x; k++) {
      GripperServo.write(50);
      delay(500);
      ArmServo.write(110);
      delay(500);
      GripperServo.write(0);
      delay(500);
      ArmServo.write(0);
      delay(500);

      Serial.println("Moving in Reverse X Direction");
      for (int i = 0; i < temp; i++) {
        digitalWrite(directionPin, HIGH);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(50);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(50);
      }
      delay(500);
    }

    Serial.println("Moving Conveyor in Y Direction Again");
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

void moveStepper(int stepPinMotor, int dirPinMotor, int steps, int direction, int dly) {
  digitalWrite(dirPinMotor, direction);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPinMotor, HIGH);
    delayMicroseconds(dly);
    digitalWrite(stepPinMotor, LOW);
    delayMicroseconds(dly);
  }
}