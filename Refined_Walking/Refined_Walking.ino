#include <Servo.h>

Servo myservo[8];   // create servo object to control a servo

#define MIN 1000
#define MAX 2000
#define MID (((MAX-MIN)/2)+MIN)
#define angleTo_us(x) map(x,-90,90,MIN,MAX)
#define x 50  //assumes angles for now
#define y 20
#define dly 200
#define initial 0
#define WalkPin 10
int flag = 0;

void setup() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].attach( (i + 2) ); //attach servo  2 to 9
  }
  Serial.begin(9600);
  pinMode(WalkPin, INPUT_PULLUP);
}
void writeser(int a, int b, int ang1, int ang2)
{
  myservo[a].writeMicroseconds(angleTo_us(ang1));
  myservo[b].writeMicroseconds(angleTo_us(ang2));
}

void cycle1()
{
  writeser(1, 0, -x, -y);
  writeser(3, 2, x, initial);
  writeser(5, 4, initial, y / 2);
  writeser(7, 6, -initial, -initial);
}
void cycle2()
{
  writeser(1, 0, -initial, -y);
  writeser(3, 2, x, y);
  writeser(5, 4, initial, initial);
  writeser(7, 6, -x, -initial);
}
void cycle3()
{
  writeser(1, 0, -initial, -y / 2);
  writeser(3, 2, initial, y);
  writeser(5, 4, x, initial);
  writeser(7, 6, -x, -y);
}
void cycle4()
{
  writeser(1, 0, -initial, -initial);
  writeser(3, 2, initial, y / 2);
  writeser(5, 4, x, y);
  writeser(7, 6, -initial, -y);
}
void cycle5()//stand
{
  writeser(1, 0, -x, -initial);
  writeser(3, 2, initial, initial);
  writeser(5, 4, initial, y);
  writeser(7, 6, -initial, -y / 2);
}
void walk() {
  cycle1();
  delay(dly);
  cycle2();
  delay(dly);
  cycle3();
  delay(dly);
  cycle4();
  delay(dly);
  cycle5();
  delay(dly);
}
void loop() {
  // put your main code here, to run repeatedly:
//  if (digitalRead(WalkPin) == LOW)
//  {
//    if (flag == 1)
//      {
//        delay(4000);
//        flag=0;
//      }
//      walk();
//  }
//  else
//  {
//    cycle5();
//    flag=1;
//  }
walk();
}
