#include <PinChangeInt.h>
#include "AutoPID.h"
#include<Servo.h>
int curangle[4], setangle[4], out1[4], out2[4];
uint8_t stmax[4], stmin[4];                               //Variables for min and max adjust pwm
double stkp[4], stki[4], stkd[4];                         //Kp,Ki,Kd for AutoPID Lib
int a[4]={10,11,12,13}, b[4]={14,15,16,17};                   //pins for interrupts, b not necessarily be interrupt
int mtr1[4]={2,3,4,5},mtr2[4]={6,7,8,9};                  //pins for analog write
class knee                                           //class for elbows of legs
{
  public:
    float corrS;
    int angle(float x)                                  //maping angle to pwm output
    {
      x = map(x, -90, 90, 1000, 2000);
      return x;
    }
    Servo servoS;
    knee(int pintoS)                                //to attach pin to knee with zero error
    {
      servoS.attach(pintoS);
      corrS = 0.0;
    }
    shoulder(int pintoS, int valS)                         //to attach pin to knee with non-zero error
    {
      servoS.attach(pintoS);
      corrS = valS;
    }
    void setangle(int angleS)                           //providin angle for the servo
    {
      servoS.writeMicroseconds(angle(angleS + corrS));
    }
};
class shoulder                                             //class for shoulder of the leg
{
  public:
    int a, b, angle;
    volatile int op = 0;
    shoulder(int x, int y,  AutoPID &mypid)                //attaching pin and pid controller to shoulder
    {
      a = x;
      b = y;
    }
    void get_dir()                                    //getting direction of rotation of motor:op++:-CW op--:-CCW
    {
      if (digitalRead(a) == HIGH && digitalRead(b) == LOW)
        op++;
      else if (digitalRead(a) == HIGH && digitalRead(b) == HIGH)
        op--;
    }
    void updateang()                                  //change angle according to reading from encoder
    {
      if (op >= 22140)
        op = 0;
      if (op <= -22140)
        op = 0;
      angle = map(op, -22140, 22140, -360, 360);        //maping angle between -360 to +360
    }
};
AutoPID pid_flknee(&curangle[0], &setangle[0], &out1[0], &out2[0], stmin[0], stmax[0], stkp[0], stki[0], stkd[0]); //pid controller for front left knee
AutoPID pid_frknee(&curangle[1], &setangle[1], &out1[1], &out2[1], stmin[1], stmax[1], stkp[1], stki[1], stkd[1]); //pid controller for front right knee
AutoPID pid_blknee(&curangle[2], &setangle[2], &out1[2], &out2[2], stmin[2], stmax[2], stkp[2], stki[2], stkd[2]); //pid controller for back left knee
AutoPID pid_brknee(&curangle[3], &setangle[3], &out1[3], &out2[3], stmin[3], stmax[3], stkp[3], stki[3], stkd[3]); //pid controller for back right knee
shoulder flleg(a[0], b[0], pid_flknee), frleg(a[1], b[1], pid_frknee), blleg(a[2], b[2], pid_blknee), brleg(a[3], b[3], pid_brknee); // initiating ogjects for respective knee
knee flknee(1), frknee(18), blknee(19), brknee(20);// initiating objects for respective elbows
void setup()
{
  for (int i = 0; i < 4; i++)
  {
    curangle[i] = 0, setangle[i] = 0;                     //pid values for legs
    stmax[i] = 100, stmin[i] = 0;                         //front left->0,front right->1
    stkp[i] = 14, stki[i] = 0.00017, stkd[i] = 295;       //back left->2,back right->3
    pinMode(mtr1[i],OUTPUT);
    pinMode(mtr1[i],OUTPUT);
  }
  for (int i = 0; i < 3; i++)
  {
    pinMode(a[i], INPUT_PULLUP);                      //initiating pins as input
    pinMode(b[i], INPUT_PULLUP);
  }
  attachInterrupt(digitalPinToInterrupt(a[0]), fl_getdir, RISING);      //setting up ISR's
  attachInterrupt(digitalPinToInterrupt(a[1]), fr_getdir, RISING);
  attachInterrupt(digitalPinToInterrupt(a[2]), bl_getdir, RISING);
  attachInterrupt(digitalPinToInterrupt(a[3]), br_getdir, RISING);
  Serial.begin(2000000);
}
void fl_getdir()                                                        //calling respective ISR's explicitly
{
  flleg.get_dir();
}
void fr_getdir()
{
  frleg.get_dir();
}
void bl_getdir()
{
  blleg.get_dir();
}
void br_getdir()
{
  brleg.get_dir();
}
void loop()
{
  for(int i=0; i<4;i++)
  {
  analogWrite(mtr1[i], out1[i]);
  analogWrite(mtr2[i], out2[i]);
  }
  flleg.updateang();
  frleg.updateang();
  blleg.updateang();
  brleg.updateang();
}
