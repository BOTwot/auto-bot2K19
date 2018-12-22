#include <Servo.h>
#include<Arduino.h>
class horse
{
private:

    float corrS,corrE;
    int angle(float x)
    {
        x=map(x,-90,90,1000,2000);
        return x;
    }
public:
    Servo servoS;
    Servo servoE;
    horse(int pintoS,int pintoE)
    {
        servoS.attach(pintoS);
        servoE.attach(pintoE);
        corrS=0.0;
        corrE=0.0;
    }
    horse(int pintoS,int valS,int pintoE,int valE)
    {
        servoS.attach(pintoS);
        servoE.attach(pintoE);
        corrS=valS;
        corrE=valE;
    }
    void setangle(int angleS,int angleE)
    {
        servoS.writeMicroseconds(angle(angleS+corrS));
        servoE.writeMicroseconds(angle(angleE+corrE));
    }
};
