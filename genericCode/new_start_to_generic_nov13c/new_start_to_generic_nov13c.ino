#include <Servo.h>

Servo myservo[8];   // create servo object to control a servo

#define MIN 1000
#define MAX 2000
#define MID (((MAX-MIN)/2)+MIN)
#define angleTo_us(x) map(x,0,180,MIN,MAX)
#define x_len 150  //assumes angles for now
#define y_len 50
#define z 20
#define dly 100
#define init 100

void stand() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].writeMicroseconds(angleTo_us(100));
  }
}

void servopin(int a, int b , int ang1, int ang2 ) {
  myservo[a].writeMicroseconds(angleTo_us(ang1));
  myservo[b].writeMicroseconds(angleTo_us(ang2));
  delay(dly);
}

void walk(int x, int y) {
  servopin(3, 1, x, y);
  servopin(2, 0, x, y);
  servopin(3, 1, init, init);
  servopin(2, 0, init, init);
  servopin(5, 7, x, y);
  servopin(4, 6, x, y);
  servopin(5, 7, init, init);
  servopin(4, 6, init, init);
  //servopin(1, 0, 2, 3, init, init);
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
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //walk(x_len, y_len);
    stand();
  delay(dly);
}
