#include <Servo.h>

#define limitlow 1300
#define limithigh 1700

Servo myservo[8];  // create servo object to control a servo

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

void leg1X() {
  myservo[0].writeMicroseconds(1200);
  delay(500);
  myservo[1].writeMicroseconds(1700);
  delay(500);
  myservo[0].writeMicroseconds(1700);
  delay(500);
  myservo[1].writeMicroseconds(1200);

}

void stand() {
  //1500 as initial position of all servo
  for (int i = 0; i < 8 ; i++) {
    myservo[i].writeMicroseconds(1500);
  }
}

void setup() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].attach( (i + 2)); // attaches the servo on pin 9 to the servo object
  }
}

void loop() {
  //To walk
  //  stand();
  //  delay(500);
  //  leg1X();
  //  delay(500);

#define MIN 544
#define MAX 2000
#define MID (((MAX-MIN)/2)+MIN)

#define angleTo_us(x) map(x,-90,90,MIN,MAX)


  myservo[3].writeMicroseconds(angleTo_us(-90));
  delay(2000);
  
  myservo[3].writeMicroseconds(angleTo_us(0));
  delay(2000);

  myservo[3].writeMicroseconds(angleTo_us(90));
  delay(2000);
}

