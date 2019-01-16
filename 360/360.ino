//testing purpose
int a = 2, b = 5;
volatile long int op = 0;
void setup() {
  // put your setup code here, to run once:
  void doA();
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(a), doA, RISING);
  
  Serial.begin(115200);
  Serial.println("Starting now");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(op);
//  int angle;
//  Serial.println(op);
//    if (op >= 22140)
//      op = 0;
//    if (op <= -22140)
//      op = 0;
//    angle = map(op,-22140,22140,-360,360);
//    Serial.println(angle);
}
void doA()
{
  op++;
//  if ((digitalRead(a) == HIGH && digitalRead(b) == LOW))
//    op++;
//  else if ((digitalRead(a) == HIGH && digitalRead(b) == HIGH))
//    op--;
}
