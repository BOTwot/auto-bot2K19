int a = 2, b = 3;
volatile int op = 0;
void setup() {
  // put your setup code here, to run once:
  void doA();
  void doB();
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(a), doA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(b), doB, CHANGE);
  Serial.begin(2000000);
  Serial.println("Starting now");
}

void loop() {
  // put your main code here, to run repeatedly:
  int angle;
//  Serial.println(op);
  if (op >= 1600)
    op = 0;
  if (op <= -1600)
    op = 0;
  angle = map(op,-1600,1600,-360,360);
  Serial.println(angle);

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
