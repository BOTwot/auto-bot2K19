#include <PinChangeInt.h>
#include "AutoPID.h"
#include<Servo.h>
int curangle_fl = 0, setangle_fl = 0;                     //pid values for front left
uint8_t stmax_fl = 100, stmin_fl = 0;                     //Variables for min and max adjust pwm
double stkp_fl = 14, stki_fl = 0.00017, stkd_fl = 295;    //Kp,Ki,Kd for AutoPID Lib
int out1_fl, out2_fl;
int curangle_fr = 0, setangle_fr = 0;                   //pid values for front right
uint8_t stmax_fr = 100, stmin_fr = 0;
double stkp_fr = 14, stki_fr = 0.00017, stkd_fr = 295;
int out1_fr, out2_fr;
int curangle_bl = 0, setangle_bl = 0;                   //pid values for back left
uint8_t stmax_bl = 100, stmin_bl = 0;
double stkp_bl = 14, stki_bl = 0.00017, stkd_bl = 295;
int out1_bl, out2_bl;
int curangle_br = 0, setangle_br = 0;                   //pid values for back right
uint8_t stmax_br = 100, stmin_br = 0;
double stkp_br = 14, stki_br = 0.00017, stkd_br = 295;
int out1_br, out2_br;
class shoulder                                            //class for elbows of legs
{
    float corrS;
    int angle(float x)                                  //maping angle to pwm output
    {
      x = map(x, -90, 90, 1000, 2000);
      return x;
    }
  public:
    Servo servoS;
    shoulder(int pintoS)                                //to attach pin to shoulder with zero error
    {
      servoS.attach(pintoS);
      corrS = 0.0;
    }
    shoulder(int pintoS, int valS)                         //to attach pin to shoulder with non-zero error
    {
      servoS.attach(pintoS);
      corrS = valS;
    }
    void setangle(int angleS)                           //providin angle for the servo
    {
      servoS.writeMicroseconds(angle(angleS + corrS));
    }
};
class knee                                             //class for knee of the leg
{
    int a, b, angle;
  public:
    volatile int op = 0;
    knee(int x, int y,  AutoPID &mypid)                //attaching pin and pid controller to knee
    {
      a = x;
      b = y;
    }
    void get_dir()                                    //getting direction of rotation of motor:op++:-CW op--:-CCW
    {
      if ((digitalRead(a) == HIGH && digitalRead(b) == LOW) || (digitalRead(a) == LOW && digitalRead(b) == HIGH))
        op++;
      else if ((digitalRead(a) == HIGH && digitalRead(b) == HIGH) || (digitalRead(a) == LOW && digitalRead(b) == LOW))
        op--;
    }
    void updateang()                                  //change angle according to reading from encoder
    {
      if (op >= 1600)
        op = 0;
      if (op <= -1600)
        op = 0;
      angle = map(op, -1600, 1600, -360, 360);        //maping angle between -360 to +360
    }
};
int fl_a = 2, fl_b = 3, fr_a = 4, fr_b = 5, bl_a = 6, bl_b = 7, br_a = 8, br_b = 9;           //pins for interrupts, b not necessarily be interrupt
AutoPID pid_flknee(&curangle_fl, &setangle_fl, &out1_fl, &out2_fl, stmin_fl, stmax_fl, stkp_fl, stki_fl, stkd_fl); //pid controller for front left knee
AutoPID pid_frknee(&curangle_fr, &setangle_fr, &out1_fr, &out2_fr, stmin_fr, stmax_fr, stkp_fr, stki_fr, stkd_fr); //pid controller for front right knee
AutoPID pid_blknee(&curangle_bl, &setangle_bl, &out1_bl, &out2_bl, stmin_bl, stmax_bl, stkp_bl, stki_bl, stkd_bl); //pid controller for back left knee
AutoPID pid_brknee(&curangle_br, &setangle_br, &out1_br, &out2_br, stmin_br, stmax_br, stkp_br, stki_br, stkd_br); //pid controller for back right knee
knee flknee(fl_a, fl_b, pid_flknee), frknee(fr_a, fr_b, pid_frknee), blknee(bl_a, bl_b, pid_blknee), brknee(br_a, br_b, pid_brknee); // initiating ogjects for respective knee
shoulder flleg(1), frleg(10), blleg(11), brleg(12);// initiating objects for respective elbows
void setup()
{

  pinMode(fl_a, INPUT_PULLUP);                      //initiating pins as input
  pinMode(fl_b, INPUT_PULLUP);
  pinMode(fr_a, INPUT_PULLUP);
  pinMode(fr_b, INPUT_PULLUP);
  pinMode(bl_a, INPUT_PULLUP);
  pinMode(bl_b, INPUT_PULLUP);
  pinMode(br_a, INPUT_PULLUP);
  pinMode(br_b, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(fl_a), fl_getdir, RISING);      //setting up ISR's
  attachInterrupt(digitalPinToInterrupt(fr_a), fr_getdir, RISING);
  attachInterrupt(digitalPinToInterrupt(bl_a), bl_getdir, RISING);
  attachInterrupt(digitalPinToInterrupt(br_a), br_getdir, RISING);
  Serial.begin(2000000);
}
void fl_getdir()                                                        //calling respective ISR's explicitly
{
  flknee.get_dir(); 
}
void fr_getdir() 
{
  frknee.get_dir();
}
void bl_getdir() 
{
  blknee.get_dir();
}
void br_getdir() 
{
  brknee.get_dir();
}
void loop()
{
  
}
