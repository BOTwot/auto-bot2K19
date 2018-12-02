#include <Servo.h>
#include "horse.h"
#ifdef REFRESH_INTERVAL
#undef REFRESH_INTERVAL
#endif

#define REFRESH_INTERVAL 50000L

horse flleg(2,0,3,0),frleg(4,0,5,0),blleg(6,0,7,0),brleg(8,0,9,0);   // create leg object to control it; arbitrary pin nos,change acc to bot

#define MIN 1000
#define MAX 2000
#define MID (((MAX-MIN)/2)+MIN)
#define angleTo_us(x) map(x,-90,90,MIN,MAX)
#define writeAngle(e) writeMicroseconds(angleTo_us(e))
#define x 40 //assumes angles for now
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
  
  //  Serial.begin(9600);
  pinMode(WalkPin, INPUT_PULLUP);
 // stand();
  //delay(3000);
}
void cycle1()    //set values for legs as required
{
  flleg.setangle(-x, -y);
  frleg.setangle(x, initial2);
  blleg.setangle(initial1, y / 2);
  brleg.setangle(-initial1, -initial2);
}
void cycle2()
{
  flleg.setangle(-initial1, -y);
  frleg.setangle(x, y);
  blleg.setangle(initial1, initial2);
  brleg.setangle(-x, -initial2);
}
void cycle3()
{
  flleg.setangle(-initial1, -y/2);
  frleg.setangle(initial1, y);
  blleg.setangle(x, initial2);
  brleg.setangle(-x, -y);
}
void cycle4()
{
  flleg.setangle(-initial1, -initial2);
  frleg.setangle(initial1, y / 2);
  blleg.setangle(x, y);
  brleg.setangle(-initial1, -y);
}
void cycle5()//stand
{
  flleg.setangle(-x, -initial2);
  frleg.setangle(initial1, initial2);
  blleg.setangle(initial1, y);
  brleg.setangle(-initial1, -y / 2);
}
void testcycle()
{
  flleg.setangle(-initial1, -initial2);
  frleg.setangle(initial1, initial2);
  blleg.setangle(initial1, initial2);
  brleg.setangle(-initial1, -initial2);
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
