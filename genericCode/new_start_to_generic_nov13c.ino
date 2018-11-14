#include <Servo.h>

Servo myservo[8];   // create servo object to control a servo

#define MIN 1000
#define MAX 2000
#define MID (((MAX-MIN)/2)+MIN)
#define angleTo_us(x) map(x,-90,90,MIN,MAX)
#define dly 200

void stand() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].writeMicroseconds(angleTo_us(0));
  }
}

void leg1() {
  myservo[1].writeMicroseconds(angleTo_us(-50));
  delay(dly);
  myservo[0].writeMicroseconds(angleTo_us(-50));
  delay(dly);
  myservo[1].writeMicroseconds(angleTo_us(0));
  delay(dly);
  myservo[0].writeMicroseconds(angleTo_us(0));
  delay(dly);
  myservo[3].writeMicroseconds(angleTo_us(50));
  delay(dly);
  myservo[2].writeMicroseconds(angleTo_us(50));
  delay(dly);
  myservo[3].writeMicroseconds(angleTo_us(0));
  delay(dly);
  myservo[2].writeMicroseconds(angleTo_us(0));
  delay(dly);

}

void leg2() {
  myservo[3].writeMicroseconds(angleTo_us(50));
  delay(dly);
  myservo[2].writeMicroseconds(angleTo_us(50));
  delay(dly);
  myservo[3].writeMicroseconds(angleTo_us(0));
  delay(dly);
  myservo[2].writeMicroseconds(angleTo_us(0));
  delay(dly);
}

void setup() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].attach( (i + 2) ); //attach servo  2 to 9
  }
  stand();
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  leg1();
//  leg2();
}
