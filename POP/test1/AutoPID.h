#ifndef AUTOPID_H
#define AUTOPID_H
#include <Arduino.h>

class AutoPID {
  private:
   
    double _Kp, _Ki, _Kd;
    double _integral, _previousError;

    int *_setpoint, *_input;
    int  *_output1, *_output2;
    uint8_t _outputMin, _outputMax;

    unsigned long _timeStep, _lastStep;

  public:
    AutoPID();
    AutoPID(int *input, int *setpoint, int *output1, int *output2, uint8_t outputMin, uint8_t outputMax, double Kp, double Ki, double Kd);
    void setGains(double Kp, double Ki, double Kd);
    void setOutputRange(uint8_t outputMin, uint8_t outputMax);
    void setTimeStep(unsigned long timeStep);
    void run();
    void reset();
    void setParameter(int *input, int *setpoint, int *output1, int *output2, uint8_t outputMin, uint8_t outputMax, double Kp, double Ki, double Kd);


};//class AutoPID

#endif
