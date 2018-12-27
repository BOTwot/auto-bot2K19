#include "AutoPID.h"

int mtr1 = 5;   //motor pins
int mtr2 = 6;   //motor pins

int a = 2, b = 3, pwml = 0, pwmr = 0; //pins for interrupt
//pid variables
int curangle = 0, setangle = 0;
uint8_t stmax = 100, stmin = 0;    //Variables for min and max adjust pwm
double stkp = 14, stki = 0.00017, stkd = 295;    //Kp,Ki,Kd for AutoPID Lib
volatile int op = 0;


AutoPID mypid(&curangle, &setangle, &pwml, &pwmr, stmin, stmax, stkp, stki, stkd);      //AutoPID Obj
void setup() {
  // put your setup code here, to run once:
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  pinMode(mtr1, OUTPUT);
  pinMode(mtr2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(a), doA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(b), doB, CHANGE);
  Serial.begin(115200);
  Serial.println("Starting now");
  mypid.setTimeStep(5);
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
  if (op >= 1600)
    op = 0;
  if (op <= -1600)
    op = 0;
  curangle = map(op, -1600, 1600, -360, 360);
  //Serial.println(angle);
}
void motor()
{

}

void loop() {
  // put your main code here, to run repeatedly:

  //if(curangle>87&&curangle<93)
  setangle = 60;
  motor();
  Serial.println(curangle);
  Serial.println(pwml);
    mypid.run();
  analogWrite(5, pwml);
  analogWrite(6, pwmr);
  updateang();

}

