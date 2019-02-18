#include "AutoPID.h"
#include<Servo.h>
Servo knee;
int A=2,B=22,m1=4,m2=5,curangle,sangle,output1,output2,stmax=500,stmin=0;
double kp=5,ki,kd;
volatile int op=0;
AutoPID my(&curangle, &sangle, &output1, &output2, stmax, stmin, kp, ki, kd);
int angle(int x)                                  //maping angle to pwm output
{
  x = map(x, 0, 90, 1000, 2000);
  return x;
}
void setangle(Servo knee,int angleS)                           //providin angle for the servo
{
  knee.writeMicroseconds(angle(angleS));
}
void getdir()
{
  if (digitalRead(A) == HIGH && digitalRead(B) == LOW)
    op++;
  else if (digitalRead(A) == HIGH && digitalRead(B) == HIGH)
    op--;
}
void updateang()
{
  if (op > 1384)
    op = 0;
  if (op < -1384)
    op = 0;
  curangle = map(op, -1384, 1384, -361, 361);
}
void setangle(int x)
{
   sangle = x;
  while (curangle != sangle)
  {
    updateang();
    my.run();
    //    Serial.println("writing");
    // Serial.println(output1);
    // Serial.println(output2);
    analogWrite(m1, output1);
    analogWrite(m2, output2);
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(A,INPUT_PULLUP);
  pinMode(B,INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(A), getdir, RISING);
   pinMode(m1,OUTPUT);
   pinMode(m2,OUTPUT);
   knee.attach(30);
}

void loop() {
  // put your main code here, to run repeatedly:
  
    setangle(0);
    setangle(knee,0);
    setangle(90);
    setangle(knee,45);
    setangle(0);
    setangle(knee,0);
//    setangle(90);
//    setangle(knee,0);
}
