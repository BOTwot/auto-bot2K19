// Libraries Declared here
#include "AutoPID.h"
#include "hardware.h"
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
    int phaseA, phaseB, curangle, sangle, output1, output2, mtr1, mtr2, flag = 0;
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
      sangle = x;                                       //loop needed in function
      updateang();
      my.run();
      analogWrite(mtr1, output1);
      analogWrite(mtr2, output2);
      if (curangle == x)
        flag == 1;
    }

};
shoulder flleg(flleg_phaseA, flleg_phaseB, flleg_mtr1, flleg_mtr2, flleg_kp, flleg_ki, flleg_kd),
         frleg(frleg_phaseA, frleg_phaseB, frleg_mtr1, frleg_mtr2, frleg_kp, frleg_ki, frleg_kd),
         blleg(blleg_phaseA, blleg_phaseB, blleg_mtr1, blleg_mtr2, blleg_kp, blleg_ki, blleg_kd),
         brleg(brleg_phaseA, brleg_phaseB, brleg_mtr1, brleg_mtr2, brleg_kp, brleg_ki, brleg_kd); // initiating ogjects for respective knee
knee flknee(1), frknee(16), blknee(17), brknee(20);                                           // initiating objects for respective elbows

// Setup
void setup()
{
  attachInterrupt(digitalPinToInterrupt(flleg.phaseA), fl_getdir, RISING);      //setting up ISR's
  attachInterrupt(digitalPinToInterrupt(frleg.phaseA), fr_getdir, RISING);
  attachInterrupt(digitalPinToInterrupt(blleg.phaseA), bl_getdir, RISING);
  attachInterrupt(digitalPinToInterrupt(brleg.phaseA), br_getdir, RISING);
  pinMode(activate_pin, INPUT_PULLUP);
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
void servo_initiate()
{
  flknee.setangle(servo_initial_angle);
  frknee.setangle(servo_initial_angle);
  blknee.setangle(servo_initial_angle);
  brknee.setangle(servo_initial_angle);
}
void motor_initiate()
{
  flleg.op = 0;
  frleg.op = 0;
  blleg.op = 0;
  brleg.op = 0;
  flleg.setangle(0);
  frleg.setangle(0);
  blleg.setangle(0);
  brleg.setangle(0);
}
void reset_flags()
{
  flleg.flag = 0;
  frleg.flag = 0;
  blleg.flag = 0;
  brleg.flag = 0;
}
void set_all(int fl_s, int fl_k, int fr_s, int fr_k, int bl_s, int bl_k, int br_s, int br_k)
{
  flknee.setangle(fl_k);
  frknee.setangle(fr_k);
  blknee.setangle(bl_k);
  brknee.setangle(br_k);
  flleg.setangle(fl_s);
  frleg.setangle(fr_s);
  blleg.setangle(bl_s);
  brleg.setangle(br_s);
}
void stand()                               //random test function
{
  reset_flags();
  while (flleg.flag == 1 && frleg.flag == 1 &&  blleg.flag == 1  &&  brleg.flag == 1)
  {
    set_all(10,20,30,40,50,60,70,80);
  }
}
void loop()
{
  if (activate_pin == HIGH)
    servo_initiate();
  else
    motor_initiate();
}
