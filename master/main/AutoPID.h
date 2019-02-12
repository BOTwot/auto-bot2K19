#ifndef AutoPID_H
#define AutoPID_H
#include <Arduino.h>

class AutoPID {

  public:
    AutoPID();
    // Constructor - takes pointer inputs for control variales, so they are updated automatically
    AutoPID(int *input, int *setpoint, double *output, uint8_t outputMin, uint8_t outputMax,
            double Kp, double Ki, double Kd);
    // Allows manual adjustment of gains
    void setGains(double Kp, double Ki, double Kd);
    // Allows manual readjustment of output range
    void setOutputRange(double outputMin, double outputMax);
    // Allows manual adjustment of time step (default 1000ms)
    void setTimeStep(unsigned long timeStep);
    // Returns true when at set point (+-threshold)
    bool atSetPoint(double threshold);
    // Runs PID calculations when needed. Should be called repeatedly in loop.
    // Automatically reads input and sets output via pointers
    void run();
    // Stops PID functionality, output sets to
    void stop();
    void reset();
    bool isStopped();

    double getIntegral();
    void setIntegral(double integral);
    void setParameter(int *input, int *setpoint, double *output, uint8_t outputMin, uint8_t outputMax,
            double Kp, double Ki, double Kd);
  private:
    double _Kp, _Ki, _Kd;
    double _integral, _previousError;
    double _bangOn, _bangOff;
    double  *_output;
    int *_input, *_setpoint;
    int _outputMin, _outputMax;
    unsigned long _timeStep, _lastStep;
    bool _stopped;

};//class AutoPID

class AutoPIDRelay : public AutoPID {
  public:

    AutoPIDRelay(int *input, int *setpoint, bool *relayState, double pulseWidth, double Kp, double Ki, double Kd)
      : AutoPID(input, setpoint, &_pulseValue, 0, 1.0, Kp, Ki, Kd) {
      _relayState = relayState;
      _pulseWidth = pulseWidth;
    };

    void run();

    double getPulseValue();

  private:
    bool * _relayState;
    unsigned long _pulseWidth, _lastPulseTime;
    double _pulseValue;
};//class AutoPIDRelay

#endif
