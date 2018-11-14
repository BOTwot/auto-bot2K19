#include <Servo.h>

Servo myservo[8];   // create servo object to control a servo

#define MIN 1000
#define MAX 2000
#define MID (((MAX-MIN)/2)+MIN)
#define angleTo_us(x) map(x,-90,90,MIN,MAX)
#define x_len 50                           //assumes angles for now
#define y_len 50
#define dly 200
#define init 0

void stand() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].writeMicroseconds(angleTo_us(0));
  }
}

void servopin(int a, int b , int x) {
  myservo[a].writeMicroseconds(angleTo_us(x));
  myservo[b].writeMicroseconds(angleTo_us(-x));
  delay(dly);
  myservo[a].writeMicroseconds(angleTo_us(init));
  myservo[b].writeMicroseconds(angleTo_us(init));

}

void diagonal1(int x, int y) {
  //  myservo[3].writeMicroseconds(angleTo_us(-y));
  //  //delay(dly);
  //  myservo[1].writeMicroseconds(angleTo_us(y));
  //  delay(dly);
  servopin(2, 0, x);                                //sends (servo pin x, servo pin y,  angle)
  //  myservo[2].writeMicroseconds(angleTo_us(-x));
  //  //delay(dly);
  //  myservo[0].writeMicroseconds(angleTo_us(x));
  //  delay(dly);
  //  myservo[3].writeMicroseconds(angleTo_us(init));
  //  //delay(dly);
  //  myservo[1].writeMicroseconds(angleTo_us(init));
  //  delay(dly);
  //  myservo[2].writeMicroseconds(angleTo_us(init));
  //  //delay(dly);
  //  myservo[0].writeMicroseconds(angleTo_us(init));
  //  delay(dly);
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
  diagonal1(x_len, y_len);
  delay(dly);
}
