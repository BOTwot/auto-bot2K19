#include <Servo.h>

//#ifdef REFRESH_INTERVAL
//#undef REFRESH_INTERVAL
//#define REFRESH_INTERVAL 10000L
//#endif

Servo myservo[8];   // create servo object to control a servo

#define MIN 1000
#define MAX 2000
#define MID (((MAX-MIN)/2)+MIN)
#define angleTo_us(x) map(x,-90,90,MIN,MAX)
#define x_len 70  //assumes angles for now
#define y_len 50
#define z 90
#define dly 200
#define init 0

int stan = 10;
int s;
//int corr1[8] = {0, 0, 0, 30, 0, 0, 30, 0}; //stand correction
//int corr[8] = { -20, 30, 0, 0, 0, 0, 0, 0}; //walking correction
int corr1[8] = {0, 0, 20, 30, 0, 0, 0, 0}; //stand correction
int corr[8] = { 0, 0, 0, 0, 0, 0, 0, 0}; //walking correction

void stand() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].writeMicroseconds(angleTo_us(0 + corr1[i]));
  }
}

void servopin(int a, int b , int ang1, int ang2) {
  myservo[a].writeMicroseconds(angleTo_us(ang1 + corr[a]));
  myservo[b].writeMicroseconds(angleTo_us((ang2 + corr[b])));
  delay(dly);
}

void walk(int x, int y) {
  servopin( 3, 1 , x, -x);//sends (servo pin x, servo pin y,  angle)
  servopin(2, 0, y, -y);
  servopin(3, 1, init, -init);
  servopin( 5, 7 , x, -50);
  servopin(2, 0, init, -init);
  servopin(4, 6, y, -y);
  servopin( 5, 7 , init, -init);
  servopin( 3, 1 , 50, -x);
  servopin(4, 6, init, init);
}

void setup() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].attach( (i + 2) ); //attach servo  2 to 9
  }
  //  stand();
  //  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:/
  stand();
  delay(1000);
  //  walk(x_len, y_len);
}
