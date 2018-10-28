#include <Servo.h>

enum servos {
  leftShoulder1 = 2,
  leftShoulder2 = 3,
  rightShoulder1 = 4,
  rightShoulder2 = 5,
  leftKnee1 = 6,
  leftKnee2 = 7,
  rightKnee1 = 8,
  rightKnee2 = 9
};

Servo myservo[8];  // create servo object to control a servo

void setup() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].attach( (i + 2) ); // attaches the servo on pin 9 to the servo object
  }
}

#define limitlow 1300
#define limithigh 1600
void stand() {
  //1500 as initial position of all servo
  int  low = 1500;
  int  high = 1500;
  for (int i = 0; i < 8 ; i++) {
    myservo[i].writeMicroseconds(low);
  }
  delay(200);
  for (int i = 0; i < 8 ; i++) {
    myservo[i].writeMicroseconds(high);
  }
  delay(200);
}
void diagonal1_up() {
  myservo[1].writeMicroseconds(limitlow);
  myservo[3].writeMicroseconds(1600);
  delay(200);
  myservo[0].writeMicroseconds(limitlow);
  myservo[2].writeMicroseconds(1600);
  delay(200);
}

void diagonal1_low() {
  myservo[1].writeMicroseconds(limithigh);
  myservo[3].writeMicroseconds(1300);
  delay(200);
  myservo[0].writeMicroseconds(limithigh);
  myservo[2].writeMicroseconds(1400);
  delay(200);
}

void diagonal2_up() {
  myservo[5].writeMicroseconds(1600);
  myservo[7].writeMicroseconds(1400);
  delay(200);
  myservo[4].writeMicroseconds(1400);
  myservo[6].writeMicroseconds(1300);
  delay(200);
}

void diagonal2_low() {
  myservo[5].writeMicroseconds(limitlow);
  myservo[7].writeMicroseconds(1600);
  delay(200);
  myservo[4].writeMicroseconds(1600);
  myservo[6].writeMicroseconds(1600);
  delay(200);
}

void loop() {
  //To walk
  diagonal1_up();
  diagonal1_low();
  // delay(500);
  diagonal2_up();
  diagonal2_low();
  //stand();
}
