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
    horse(int pintoS,float valS,int pintoE,float valE)
    {
        servoS.attach(pintoS);
        servoE.attach(pintoE);
        corrS=valS;
        corrE=valE;
    }
    void setangle(float angleS,float angleE)
    {
        servoS.writeMicroseconds(angle(angleS+corrS));
        servoE.writeMicroseconds(angle(angleE+corrE));
    }
};

