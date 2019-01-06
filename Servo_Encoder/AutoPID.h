#ifndef AUTOPID_H
#define AUTOPID_H
#include <Arduino.h>

class AutoPID {
  private:

    double _Kp, _Ki, _Kd;
    double _integral, _previousError,_e_old_i;

    int *_input;
    int *_setpoint, *_output1, *_output2;
    uint8_t _outputMin, _outputMax;

    unsigned long _timeStep, _lastStep;

  public:
    AutoPID(int *input, int *setpoint, int *output1, int *output2, uint8_t outputMin, uint8_t outputMax, double Kp, double Ki, double Kd);
    void setGains(double Kp, double Ki, double Kd);
    void setOutputRange(uint8_t outputMin, uint8_t outputMax);
    void setTimeStep(unsigned long timeStep);
    void run();
    void reset();


};//class AutoPID

#endif
