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

#define limitlow 1400
#define limithigh 1700
#define limitlow1 1600
#define limithigh1 1300
void stand() {
  //1500 as initial position of all servo
  int  low = 1500;
  int  high = 1500;
  for (int i = 0; i < 8 ; i++) {
    myservo[i].writeMicroseconds(low);
  }
  delay(300);

  for (int i = 0; i < 8 ; i++) {
    myservo[i].writeMicroseconds(high);
  }
  delay(300);
}

void fashion() {

  myservo[3].writeMicroseconds(1580);
  myservo[7].writeMicroseconds(1580);
  delay(200);
}
void fashion1() {
  myservo[1].writeMicroseconds(1400);
  myservo[5].writeMicroseconds(1400);
  delay(200);
}
void loop() {
  //      for (int i = 0; i < 8 ; i++) {
  //        myservo[i].writeMicroseconds(1500);
  //      }
  //      delay(1000);
  //
  //      for (int i = 0; i < 8 ; i++) {
  //        myservo[i].writeMicroseconds(1500);
  //      }
  //      delay(1000);

  //////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////
  //To walk//
  stand();
  delay(200);
  //  fashion();
  //  delay(500);
  for (int i = 0; i < 2; i++) {
    //   myservo[1].writeMicroseconds(1200);
    myservo[i].writeMicroseconds(limithigh);
    delay(200);
  }
  for (int i = 0; i < 2; i++) {
    myservo[i].writeMicroseconds(limitlow);
    delay(200);
  }
  delay(200);
  stand();
  delay(200);
  //  fashion1();
  //  delay(500);

  for (int i = 2; i < 4; i++) {
    myservo[3].writeMicroseconds(1700);
    myservo[i].writeMicroseconds(limithigh1);
    delay(200);
  }
  for (int i = 2; i < 4; i++) {
    myservo[i].writeMicroseconds(limitlow1);
    delay(200);
  }
  delay(200);
  stand();
  delay(200);
  //  fashion();
  //  delay(500);
  /////////////////////////////
  for (int i = 4; i < 6; i++) {
    myservo[5].writeMicroseconds(1200);
    myservo[i].writeMicroseconds(limithigh);
    delay(200);
  }
  for (int i = 4; i < 6; i++) {
    myservo[i].writeMicroseconds(limitlow);
    delay(200);
  }
  delay(200);
  stand();
  //  delay(500);
  //  fashion1();
  delay(200);
  for (int i = 6; i < 8; i++) {
    myservo[7].writeMicroseconds(1700);
    myservo[i].writeMicroseconds(limithigh1);
    delay(200);
  }
  for (int i = 6; i < 8; i++) {
    myservo[i].writeMicroseconds(limitlow1);
    delay(200);
  }
}
