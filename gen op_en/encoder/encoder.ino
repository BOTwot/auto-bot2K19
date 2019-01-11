// Libraries Declared here
#include "AutoPID.h"
#include<Servo.h>

//Global Variables
uint8_t stmax = 100, stmin = 0;                                      //Variables for min and max adjust pwm

// Class Decalration
class knee                                           //class for elbows of legs
{
  public:
    float corrS;
    int angle(int x)                                  //maping angle to pwm output
    {
      x = map(x, 0, 90, 1000, 2000);
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
    int phaseA, phaseB, curangle, sangle, output1, output2, mtr1, mtr2;
    double kp, ki, kd;
    volatile int op = 0;
    AutoPID my;
    shoulder(int x, int y, int z, int w, int Kp, int Ki, int Kd)           //attaching pin and pid controller to shoulder
    { 
      phaseA = x;
      phaseB = y;
      mtr1 = z;
      mtr2 = w;
      pinMode(phaseA, INPUT_PULLUP);
      pinMode(phaseB, INPUT_PULLUP);
      pinMode(mtr1, OUTPUT);
      pinMode(mtr2, OUTPUT);
      kp = Kp;
      ki = Ki;
      kd = Kd;
      my.setParameter(&curangle, &sangle, &output1, &output2, stmax, stmin, kp, ki, kd);
      my.setTimeStep(50);
    }
    void get_dir()                                    //getting direction of rotation of motor:op++:-CW op--:-CCW
    {
      if (digitalRead(phaseA) == HIGH && digitalRead(phaseB) == LOW)
        op++;
      else if (digitalRead(phaseA) == HIGH && digitalRead(phaseB) == HIGH)
        op--;
    }
    void updateang()                                  //change angle according to reading from encoder
    {
      if (op >= 22140)
        op = 0;
      if (op <= -22140)
        op = 0;
      curangle = map(op, -22140, 22140, -360, 360);        //maping angle between -360 to +360
    }
    void setangle(int x)                                 //function to write angle to motor
    {
      sangle = x;
      while (curangle != x)
      {
        my.run();
        updateang();
        analogWrite(mtr1, output1);
        analogWrite(mtr2, output2);
      }
    }

};
shoulder flleg(2, 4, 5, 6, 100, 100, 100), frleg(3, 7, 8, 9, 100, 100, 100), blleg(18, 10, 11, 12, 100, 100, 100), brleg(19, 13, 14, 15, 100, 100, 100); // initiating ogjects for respective knee
knee flknee(1), frknee(16), blknee(17), brknee(20);// initiating objects for respective elbows

// Setup
void setup()
{
  attachInterrupt(digitalPinToInterrupt(flleg.phaseA), fl_getdir, RISING);      //setting up ISR's
  attachInterrupt(digitalPinToInterrupt(frleg.phaseA), fr_getdir, RISING);
  attachInterrupt(digitalPinToInterrupt(blleg.phaseA), bl_getdir, RISING);
  attachInterrupt(digitalPinToInterrupt(brleg.phaseA), br_getdir, RISING);
  Serial.begin(115200);
}

// Functions
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
void cycle1()                               //random test function
{
  flleg.setangle(23);
}
void loop()
{
  
}
