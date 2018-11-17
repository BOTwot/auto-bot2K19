#include <Servo.h>

#ifdef REFRESH_INTERVAL
#undef REFRESH_INTERVAL
#endif

#define REFRESH_INTERVAL 50000L

Servo myservo[8];   // create servo object to control a servo

#define MIN 1000
#define MAX 2000
#define MID (((MAX-MIN)/2)+MIN)
#define angleTo_us(x) map(x,-90,90,MIN,MAX)
#define writeAngle(e) writeMicroseconds(angleTo_us(e))
#define x 40  //assumes angles for now
#define y 20
#define dly 200
#define initial1 10
#define initial2 0
#define WalkPin 10
int flag = 0;
int corr[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void stand() {
  cycle5();
}

void setup() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].attach( (i + 2) ); //attach servo  2 to 9
  }
  //  Serial.begin(9600);
  pinMode(WalkPin, INPUT_PULLUP);
 // stand();
  //delay(3000);
}

void writeser(int a, int b, int ang1, int ang2)
{
  myservo[a].writeMicroseconds(angleTo_us(ang1 + corr[a]));
  myservo[b].writeMicroseconds(angleTo_us(ang2 + corr[b]));
}

void cycle1()
{
  writeser(1, 0, -x, -y);
  writeser(3, 2, x, initial2);
  writeser(5, 4, initial1, y / 2);
  writeser(7, 6, -initial1, -initial2);
}
void cycle2()
{
  writeser(1, 0, -initial1, -y);
  writeser(3, 2, x, y);
  writeser(5, 4, initial1, initial2);
  writeser(7, 6, -x, -initial2);
}
void cycle3()
{
  writeser(1, 0, -initial1, -y/2);
  writeser(3, 2, initial1, y);
  writeser(5, 4, x, initial2);
  writeser(7, 6, -x, -y);
}
void cycle4()
{
  writeser(1, 0, -initial1, -initial2);
  writeser(3, 2, initial1, y / 2);
  writeser(5, 4, x, y);
  writeser(7, 6, -initial1, -y);
}
void cycle5()//stand
{
  writeser(1, 0, -x, -initial2);
  writeser(3, 2, initial1, initial2);
  writeser(5, 4, initial1, y);
  writeser(7, 6, -initial1, -y / 2);
}
void testcycle()
{
   writeser(1, 0, -initial1, -initial2);
  writeser(3, 2, initial1, initial2);
  writeser(5, 4, initial1, initial2);
  writeser(7, 6, -initial1, -initial2);
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
 // walk();
     // stand();
     testcycle();
     // delay(dly);
}
