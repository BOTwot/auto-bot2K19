#include <Servo.h>

Servo myservo[8];   // create servo object to control a servo

#define MIN 1000
#define MAX 2000
#define MID (((MAX-MIN)/2)+MIN)
#define angleTo_us(x) map(x,-90,90,MIN,MAX)
#define x_len 90  //assumes angles for now
#define y_len 50
#define dly 200
#define init 0

void stand() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].writeMicroseconds(angleTo_us(0));
  }
}

void servopin(int a, int b , int d, int ang1, int ang2, int an) {
  myservo[a].writeMicroseconds(angleTo_us(ang1));
  myservo[d].writeMicroseconds(angleTo_us(an));
  delay(dly);
  myservo[b].writeMicroseconds(angleTo_us(ang2));
  myservo[d].writeMicroseconds(angleTo_us(an/2));
  delay(dly);
  myservo[a].writeMicroseconds(angleTo_us(init));
  myservo[d].writeMicroseconds(angleTo_us(init));
  delay(dly);
}

void walk(int x, int y) {
  servopin(1, 0, 2, -x, -y,50);
  servopin(3, 2, 0, x, y,-50);
  // servopin(1, 0, -30, init);
  //  servopin(2, 0, init);  //sends (servo pin x, servo pin y,  angle)
  //  servopin(4, 6 , y);
  //  servopin(5, 7, x);
}

void setup() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].attach( (i + 2) ); //attach servo  2 to 9
  }
  stand();
  delay(30000);
}

void loop() {
  // put your main code here, to run repeatedly:
  walk(x_len, y_len);
  delay(dly);
}
