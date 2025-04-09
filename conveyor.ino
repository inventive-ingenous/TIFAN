#define directionPin 2
#define stepPin 3

#define directionPin2 4
#define stepPin2 5

int temp = 8000;
String str;


const int rotations_x = 7;
const int rotations_y = 14;

void setup() {
  Serial.begin(9600);
  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin2, OUTPUT);
  pinMode(stepPin2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    temp = Serial.parseInt();
    str = Serial.readStringUntil("\n");
  }
  Serial.print(temp);

  for(int j=0; j<rotations_y; j++){

  for (int k = 0; k < rotations_x; k++) {
    for (int i = 0; i < temp; i++) {
      digitalWrite(directionPin, HIGH);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(100);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(100);
    }
    delay(2000);
  }

  for (int i = 0; i < temp; i++) {
    digitalWrite(directionPin2, HIGH);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(100);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(100);
  }


  delay(2000);



  for (int k = 0; k < rotations_x; k++) {
    for (int i = 0; i < temp; i++) {
      digitalWrite(directionPin, LOW);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(100);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(100);
    }
    delay(2000);
  }
  }
}
