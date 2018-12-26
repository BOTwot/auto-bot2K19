int a = 2, b = 3;
int op = 0, pos;
void setup() {
  // put your setup code here, to run once:
  void doA();
  void doB();
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), doA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), doB, CHANGE);
  Serial.begin(2000000);
  Serial.println("Starting now");
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = digitalRead(a);
  int y = digitalRead(b);
}
void doA()
{
  if ((digitalRead(a) == HIGH && digitalRead(b) == LOW) || (digitalRead(a) == LOW && digitalRead(b) == HIGH))
  {
    op++;
//    Serial.println("CW");
    pos = map(op, -400,400, 70, -360, 360) / 2;
    if (pos >= -360 && pos <= 360)
      Serial.println(pos);
  }
  else if ((digitalRead(a) == HIGH && digitalRead(b) == HIGH) || (digitalRead(a) == LOW && digitalRead(b) == LOW))
  {
    op--;
//    Serial.println("CCCCW");
    pos = map(op, -400, 400, -360, 360) / 2;
    if (pos >= -360 && pos <= 360)
      Serial.println(pos);
  }
}
void doB()
{
  if ((digitalRead(b) == HIGH && digitalRead(a) == HIGH) || (digitalRead(b) == LOW && digitalRead(a) == LOW))
  {
//    Serial.println("CW");
  }
  else if ((digitalRead(b) == LOW && digitalRead(a) == HIGH) || (digitalRead(b) == HIGH && digitalRead(a) == LOW))
  {
//    Serial.println("CCCCW");
  }
}
