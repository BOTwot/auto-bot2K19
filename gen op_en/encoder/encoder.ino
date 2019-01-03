#include <PinChangeInt.h>
#include "AutoPID.h"
#include<Servo.h>
int curangle = 0, setangle = 0;
uint8_t stmax = 100, stmin = 0;    //Variables for min and max adjust pwm
double stkp = 14, stki = 0.00017, stkd = 295;    //Kp,Ki,Kd for AutoPID Lib
int out1, out2;
class horse
{
    float corrS, corrE;
    int angle(float x)
    {
      x = map(x, -90, 90, 1000, 2000);
      return x;
    }
  public:
    Servo servoS;
    Servo servoE;
    horse(int pintoS, int pintoE)
    {
      servoS.attach(pintoS);
      servoE.attach(pintoE);
      corrS = 0.0;
      corrE = 0.0;
    }
    horse(int pintoS, int valS, int pintoE, int valE)
    {
      servoS.attach(pintoS);
      servoE.attach(pintoE);
      corrS = valS;
      corrE = valE;
    }
    void setangle(int angleS, int angleE)
    {
      servoS.writeMicroseconds(angle(angleS + corrS));
      servoE.writeMicroseconds(angle(angleE + corrE));
    }
};
class encoder                 //class definition ends at line 37
{
   int a, b, angle;
  public:     
    volatile int op = 0;
    encoder(int, int,AutoPID &mypid);
    void doA();
    void doB();
    void updateang();
};
encoder::encoder(int x, int y, AutoPID &mypid)
{
  a = x;
  b = y;
  mypid.run();
}
void encoder::doA()
{
  if ((digitalRead(a) == HIGH && digitalRead(b) == LOW) || (digitalRead(a) == LOW && digitalRead(b) == HIGH))
    op++;
  else if ((digitalRead(a) == HIGH && digitalRead(b) == HIGH) || (digitalRead(a) == LOW && digitalRead(b) == LOW))
    op--;
}
void encoder::doB()
{
  if ((digitalRead(b) == HIGH && digitalRead(a) == HIGH) || (digitalRead(b) == LOW && digitalRead(a) == LOW))
    op++;
  else if ((digitalRead(b) == LOW && digitalRead(a) == HIGH) || (digitalRead(b) == HIGH && digitalRead(a) == LOW))
    op--;
}
void encoder::updateang()
{
  if (op >= 1600)
    op = 0;
  if (op <= -1600)
    op = 0;
  angle = map(op, -800, 800, -360, 360);
}
int a = 2, b = 3, c = 4, d = 5, e = 6, f = 7, g = 8, h = 9;
AutoPID pid_flknee(&curangle, &setangle, &out1, &out2, stmin, stmax, stkp, stki, stkd); 
AutoPID pid_frknee(&curangle, &setangle, &out1, &out2, stmin, stmax, stkp, stki, stkd); 
AutoPID pid_blknee(&curangle, &setangle, &out1, &out2, stmin, stmax, stkp, stki, stkd); 
AutoPID pid_brknee(&curangle, &setangle, &out1, &out2, stmin, stmax, stkp, stki, stkd); 
encoder flknee(a, b,pid_flknee), frknee(c, d,pid_frknee), blknee(e, f,pid_blknee), brknee(g, h,pid_brknee);
horse flleg(2, 3), frleg(4, 5), blleg(6, 7), brleg(8, 9);
void setup()
{
   
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  pinMode(c, INPUT_PULLUP);
  pinMode(d, INPUT_PULLUP);
  pinMode(e, INPUT_PULLUP);
  pinMode(f, INPUT_PULLUP);
  pinMode(g, INPUT_PULLUP);
  pinMode(h, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(a), fldoA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(b), fldoB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(c), frdoA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(d), frdoB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(e), bldoA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(f), bldoB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(g), brdoA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(h), brdoB, CHANGE);  
  Serial.begin(2000000);
}
void fldoA() {
  flknee.doA();
}
void fldoB() {
  flknee.doB();
}
void frdoA() {
  frknee.doA();
}
void frdoB() {
  frknee.doB();
}
void bldoA() {
  blknee.doA();
}
void bldoB() {
  blknee.doB();
}
void brdoA() {
  brknee.doA();
}
void brdoB() {
  brknee.doB();
}
void loop()
{
  flknee.updateang();
  frknee.updateang();
  blknee.updateang();
  brknee.updateang();
}
