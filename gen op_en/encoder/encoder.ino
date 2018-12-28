#include <PinChangeInt.h>

#include "AutoPID.h"
class encoder                 //class definition ends at line 37
{
    int a, b,angle;
  public:
    volatile int op = 0;
    encoder(int, int);
    void doA();
    void doB();
    void updateang();
};
encoder::encoder(int x, int y)
{
  a = x;
  b = y;
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
  angle = map(op,-800,800,-360,360);
}
int a = 2, b = 3, c = 4, d = 5, e = 6, f = 7, g = 8, h = 9;
encoder flleg(a, b), frleg(c, d), blleg(e, f), brleg(g, h);
void setup()
{
  pinMode(a,INPUT_PULLUP);
  pinMode(b,INPUT_PULLUP);
  pinMode(c,INPUT_PULLUP);
  pinMode(d,INPUT_PULLUP);
  pinMode(e,INPUT_PULLUP);
  pinMode(f,INPUT_PULLUP);
  pinMode(g,INPUT_PULLUP);
  pinMode(h,INPUT_PULLUP);
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
  flleg.doA();
}
void fldoB() {
  flleg.doB();
}
void frdoA() {
  frleg.doA();
}
void frdoB() {
  frleg.doB();
}
void bldoA() {
  blleg.doA();
}
void bldoB() {
  blleg.doB();
}
void brdoA() {
  brleg.doA();
}
void brdoB() {
  brleg.doB();
}
void loop()
{
  flleg.updateang();
  frleg.updateang();
  blleg.updateang();
  brleg.updateang();
}
