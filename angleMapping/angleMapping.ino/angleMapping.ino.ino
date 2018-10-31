#include <Servo.h>

Servo myservo[8];  // create servo object to control a servo

#define limitlow 1300
#define limithigh 1500
void stand() {
  //1500 as initial position of all servo
  int  low = 00;
  int  high = 00;
  for (int i = 0; i < 8 ; i++) {
    myservo[i].writeMicroseconds(1500);
  }
}

void setup() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].attach( (i + 2) ); // attaches the servo on pin 9 to the servo object
  }

}

void diagonal1_up() {
  myservo[1].writeMicroseconds(1500);
  myservo[3].writeMicroseconds(1500);
  delay(200);
  myservo[0].writeMicroseconds(1700);
  myservo[2].writeMicroseconds(1300);
  delay(200);
}

void diagonal1_low() {
  myservo[3].writeMicroseconds(1900);
  myservo[1].writeMicroseconds(1100);
  delay(200);
  myservo[0].writeMicroseconds(1500);
  myservo[2].writeMicroseconds(1500);
  //delay(200);
  myservo[1].writeMicroseconds(1500);
  myservo[3].writeMicroseconds(1500);

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
  stand();
  delay(200);
//  diagonal1_up();
//  delay(200);
//  diagonal1_low();
//  delay(200);
  diagonal2_up();
  delay(200);
  diagonal2_low();
  delay(200);
}
