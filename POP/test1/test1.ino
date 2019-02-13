#include "AutoPID.h"
int flmtr1 = 4, flmtr2 = 5, frmtr1 = 6, frmtr2 = 7,blmtr1 = 8, blmtr2 = 9,brmtr1 = 10, brmtr2 = 11;
long long last_time;
int phaseflA = 2, phaseflB = 22, curanglefl, sanglefl, output1fl, output2fl, stmax = 500, stmin = 0;
int phasefrA = 3, phasefrB = 23, curanglefr, sanglefr, output1fr, output2fr;
int phaseblA = 18, phaseblB = 24, curanglebl, sanglebl, output1bl, output2bl;
int phasebrA = 19, phasebrB = 25, curanglebr, sanglebr, output1br, output2br;
double kp = 5, ki, kd;
volatile int opfl = 0;
volatile int opfr = 0;
volatile int opbl = 0;
volatile int opbr = 0;
AutoPID myfl(&curanglefl, &sanglefl, &output1fl, &output2fl, stmax, stmin, kp, ki, kd),
        myfr(&curanglefr, &sanglefr, &output1fr, &output2fr, stmax, stmin, kp, ki, kd) ,
        mybl(&curanglebl, &sanglebl, &output1bl, &output2bl, stmax, stmin, kp, ki, kd) ,
        mybr(&curanglebr, &sanglebr, &output1br, &output2br, stmax, stmin, kp, ki, kd);

void get_dirfl()                                    //getting direction of rotation of motor:op++:-CW op--:-CCW
{
  if (digitalRead(phaseflA) == HIGH && digitalRead(phaseflB) == LOW)
    opfl++;
  else if (digitalRead(phaseflA) == HIGH && digitalRead(phaseflB) == HIGH)
    opfl--;
}
void get_dirfr()                                    //getting direction of rotation of motor:op++:-CW op--:-CCW
{
  if (digitalRead(phasefrA) == HIGH && digitalRead(phasefrB) == LOW)
    opfr++;
  else if (digitalRead(phasefrA) == HIGH && digitalRead(phasefrB) == HIGH)
    opfr--;
}
void get_dirbl()                                    //getting direction of rotation of motor:op++:-CW op--:-CCW
{
  if (digitalRead(phaseblA) == HIGH && digitalRead(phaseblB) == LOW)
    opbl++;
  else if (digitalRead(phaseblA) == HIGH && digitalRead(phaseblB) == HIGH)
    opbl--;
}
void get_dirbr()                                    //getting direction of rotation of motor:op++:-CW op--:-CCW
{
  if (digitalRead(phasebrA) == HIGH && digitalRead(phasebrB) == LOW)
    opbr++;
  else if (digitalRead(phasebrA) == HIGH && digitalRead(phasebrB) == HIGH)
    opbr--;
}
void updateangfl()                                  //change angle according to reading from encoder
{
  if (opfl > 22140)
    opfl = 0;
  if (opfl < -22140)
    opfl = 0;
  curanglefl = map(opfl, -22140, 22140, -361, 361);
  //Serial.println(curangle);//maping angle between -360 to +360
}
void updateangfr()                                  //change angle according to reading from encoder
{
  if (opfr > 22140)
    opfr = 0;
  if (opfr < -22140)
    opfr = 0;
  curanglefr = map(opfr, -22140, 22140, -361, 361);
  //Serial.println(curangle);//maping angle between -360 to +360
}
void updateangbl()                                  //change angle according to reading from encoder
{
  if (opbl > 22140)
    opbl = 0;
  if (opbl < -22140)
    opbl = 0;
  curanglebl = map(opbl, -22140, 22140, -361, 361);
  //Serial.println(curangle);//maping angle between -360 to +360
}
void updateangbr()                                  //change angle according to reading from encoder
{
  if (opbr > 22140)
    opbr = 0;
  if (opbr < -22140)
    opbr = 0;
  curanglebr = map(opbr, -22140, 22140, -361, 361);
  //Serial.println(curangle);//maping angle between -360 to +360
}
void setanglefl(int x)                                 //function to write angle to motor
{
  sanglefl = x;
  while (curanglefl != sanglefl)
  {
    updateangfl();

    myfl.run();
    //    Serial.println("writing");
    // Serial.println(output1);
    // Serial.println(output2);
    analogWrite(flmtr1, output1fl);
    analogWrite(flmtr2, output2fl);
  }
}
void setanglefr(int x)                                 //function to write angle to motor
{
  sanglefr = x;
  while (curanglefr != sanglefr)
  {
    updateangfr();

    myfr.run();
    //    Serial.println("writing");
    // Serial.println(output1);
    // Serial.println(output2);
    analogWrite(frmtr1, output1fr);
    analogWrite(frmtr2, output2fr);
  }
}
void setanglebl(int x)                                 //function to write angle to motor
{
  sanglebl = x;
  while (curanglebl != sanglebl)
  {
    updateangbl();

    mybl.run();
    //    Serial.println("writing");
    // Serial.println(output1);
    // Serial.println(output2);
    analogWrite(blmtr1, output1bl);
    analogWrite(blmtr2, output2bl);
  }
}
void setanglebr(int x)                                 //function to write angle to motor
{
  sanglebr = x;
  while (curanglebr != sanglebr)
  {
    updateangbr();

    mybr.run();
    //    Serial.println("writing");
    // Serial.println(output1);
    // Serial.println(output2);
    analogWrite(brmtr1, output1br);
    analogWrite(brmtr2, output2br);
  }
}
void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(phaseflA), get_dirfl, RISING);
  attachInterrupt(digitalPinToInterrupt(phasefrA), get_dirfr, RISING);
  attachInterrupt(digitalPinToInterrupt(phaseblA), get_dirbl, RISING);
  attachInterrupt(digitalPinToInterrupt(phasebrA), get_dirbr, RISING);
  Serial.begin(115200);
}

void loop() {

  // put your main code here, to run repeatedly:
  for (int i = 0; i <= 360; i++)
  {
    setanglefl(i);
    setanglefr(i);
    setanglebl(i);
    setanglebr(i);
  }


}
