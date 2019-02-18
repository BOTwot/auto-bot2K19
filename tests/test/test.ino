int A = 2, B =22 ;
int m1 = 6, m2 =7;
volatile int op = 0;
int f = 0;
void getdir()
{
  if (digitalRead(A) == HIGH && digitalRead(B) == LOW)
    op++;
  else if (digitalRead(A) == HIGH && digitalRead(B) == HIGH)
    op--;
  //  Serial.println(op);
}
void setup() {
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(A), getdir , RISING);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  analogWrite(m1, 50);
  Serial.begin(115200);
}

void loop() {
  int a;
  digitalWrite(m1, HIGH);
  a = map(op, -1384, 1384, -360, 360);
  if (op > 1384)
  { op = 0;
  }
  else if (op < -1384)
  { op = 0;
  }
  Serial.println(a);
  

  //Serial.println(op);
}
