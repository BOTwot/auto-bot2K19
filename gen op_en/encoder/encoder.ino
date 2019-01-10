#include <PinChangeInt.h>
#include "AutoPID.h"
#include "hardware.h"
#include<Servo.h>
int curangle=0, setangle=0, out1, out2;
uint8_t stmax=100, stmin=0;                               //Variables for min and max adjust pwm
double stkp=14, stki=0.00017, stkd=295; //Kp,Ki,Kd for AutoPID Lib
int a[4]={2,3,4,5};
int b[4]={2,3,4,5};
class knee                                           //class for elbows of legs
{
  public:
    float corrS;
    int angle(float x)                                  //maping angle to pwm output
    {
      x = map(x, -90, 90, 1000, 2000);
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
    int phaseA, phaseB, curangle, out1, out2,mtr1,mtr2;
    AutoPID *mypid;
    volatile int op = 0;
    shoulder(int a, int b,int m1,int m2,double kp,double ki,double kd,  AutoPID &pid)                //attaching pin and pid controller to shoulder
    {
      phaseA = a;
      phaseB = b;
      mtr1=m1;
      mtr2=m2;
      pinMode(phaseA,INPUT);
      pinMode(phaseB,INPUT);
      pinMode(mtr1,OUTPUT);
      pinMode(mtr2,OUTPUT);
      mypid = &pid;                                      //attaching respective pid to the object 
      mypid->setGains(kp, ki, kd);
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
      updateang();
      mypid->_input = &curangle;
      mypid->_setpoint = &x;
      mypid->run();
      analogWrite(mtr1,mypid->_output1);
      analogWrite(mtr2,mypid->_output2);
    }
};
AutoPID pid_flknee(&curangle, &setangle, &out1, &out2, stmin, stmax, stkp, stki, stkd); //pid controller for front left knee
AutoPID pid_frknee(&curangle, &setangle, &out1, &out2, stmin, stmax, stkp, stki, stkd); //pid controller for front right knee
AutoPID pid_blknee(&curangle, &setangle, &out1, &out2, stmin, stmax, stkp, stki, stkd); //pid controller for back left knee
AutoPID pid_brknee(&curangle, &setangle, &out1, &out2, stmin, stmax, stkp, stki, stkd); //pid controller for back right knee
shoulder flleg(flleg_phaseA, flleg_phaseB,flleg_mtr1,flleg_mtr2,flleg_kp,flleg_ki,flleg_kd, pid_flknee), frleg(frleg_phaseA, frleg_phaseB,frleg_mtr1,frleg_mtr2,frleg_kp,frleg_ki,frleg_kd, pid_frknee), blleg(blleg_phaseA, blleg_phaseB,blleg_mtr1,blleg_mtr2,blleg_kp,blleg_ki,blleg_kd,pid_blknee), brleg(brleg_phaseA, brleg_phaseB,brleg_mtr1,brleg_mtr2,brleg_kp,brleg_ki,brleg_kd, pid_brknee); // initiating ogjects for respective knee
knee flknee(flknee_pin), frknee(flknee_pin), blknee(flknee_pin), brknee(flknee_pin);// initiating objects for respective elbows
void setup()
{

  
  attachInterrupt(digitalPinToInterrupt(a[0]), fl_getdir, RISING);      //setting up ISR's
  attachInterrupt(digitalPinToInterrupt(a[1]), fr_getdir, RISING);
  attachInterrupt(digitalPinToInterrupt(a[2]), bl_getdir, RISING);
  attachInterrupt(digitalPinToInterrupt(a[3]), br_getdir, RISING);
  Serial.begin(2000000);
}
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
