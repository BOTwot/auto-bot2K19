#include <PinChangeInt.h>

#include "AutoPID.h"
#define MYPIN1 A3
#define MYPIN2 A4
int mtr1 = 5;   //motor pins
int mtr2 = 6;   //motor pins

int a = 2, b = 3, c = MYPIN1, d = MYPIN2; //pins for interrupt
//pid variables
int curangle = 0, setangle = 0;
uint8_t stmax = 100, stmin = 0;    //Variables for min and max adjust pwm
double stkp = 14, stki = 0.00017, stkd = 295;    //Kp,Ki,Kd for AutoPID Lib
int out1, out2;
volatile int op = 0, quickop = 0;


AutoPID mypid(&curangle, &setangle, &out1, &out2, stmin, stmax, stkp, stki, stkd);      //AutoPID Obj
void setup() {
  // put your setup code here, to run once:
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  pinMode(mtr1, OUTPUT);
  pinMode(mtr2, OUTPUT);
  pinMode(MYPIN1, INPUT_PULLUP);
  pinMode(MYPIN2, INPUT_PULLUP);
  attachPinChangeInterrupt(MYPIN1, quick0, CHANGE);
  attachPinChangeInterrupt(MYPIN2, quick1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(a), doA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(b), doB, CHANGE);
  Serial.begin(115200);
  Serial.println("Starting now");
  mypid.setTimeStep(5);
}
void quick0()
{
  if ((digitalRead(c) == HIGH && digitalRead(d) == LOW) || (digitalRead(c) == LOW && digitalRead(d) == HIGH))
  {
    quickop++;


  }
  else if ((digitalRead(c) == HIGH && digitalRead(d) == HIGH) || (digitalRead(c) == LOW && digitalRead(d) == LOW))
  {
    quickop--;
  }
}
void quick1()
{
  if ((digitalRead(c) == HIGH && digitalRead(d) == HIGH) || (digitalRead(c) == LOW && digitalRead(d) == LOW))
  {
    quickop++;
  }
  else if ((digitalRead(c) == LOW && digitalRead(d) == HIGH) || (digitalRead(c) == HIGH && digitalRead(d) == LOW))
  {
    quickop--;
  }
}

void doA()
{
  if ((digitalRead(a) == HIGH && digitalRead(b) == LOW) || (digitalRead(a) == LOW && digitalRead(b) == HIGH))
  {
    op++;


  }
  else if ((digitalRead(a) == HIGH && digitalRead(b) == HIGH) || (digitalRead(a) == LOW && digitalRead(b) == LOW))
  {
    op--;
  }
}
void doB()
{
  if ((digitalRead(b) == HIGH && digitalRead(a) == HIGH) || (digitalRead(b) == LOW && digitalRead(a) == LOW))
  {
    op++;
  }
  else if ((digitalRead(b) == LOW && digitalRead(a) == HIGH) || (digitalRead(b) == HIGH && digitalRead(a) == LOW))
  {
    op--;
  }
}
void updateang()
{
  if (quickop >= 1600)
    quickop = 0;
  if (quickop <= -1600)
    quickop = 0;
  curangle = map(quickop, -1600, 1600, -360, 360);
  //Serial.println(angle);
}

void loop() {
  // put your main code here, to run repeatedly:

  //if(curangle>87&&curangle<93)
  setangle = 360;

  Serial.println(curangle);
  Serial.print("Out 1 : ");
  Serial.println(out1);
  Serial.print("Out 2 : ");
  Serial.println(out2);
  mypid.run();
  analogWrite(5, out1);
  analogWrite(6, out2);
  updateang();

}

