#include "AutoPID.h"
AutoPID::AutoPID()
{
}

AutoPID::AutoPID(int *input, int *setpoint, double *output, uint8_t outputMin, uint8_t outputMax,
                 double Kp, double Ki, double Kd)
{
  _input = input;
  _setpoint = setpoint;
  _output = output;
  _outputMin = outputMin;
  _outputMax = outputMax;
  setGains(Kp, Ki, Kd);
  _timeStep = 1000;
} //AutoPID::AutoPID

void AutoPID::setGains(double Kp, double Ki, double Kd)
{
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
} //AutoPID::setControllerParams
void AutoPID::setOutputRange(double outputMin, double outputMax)
{
  _outputMin = outputMin;
  _outputMax = outputMax;
} //void AutoPID::setOutputRange

void AutoPID::setTimeStep(unsigned long timeStep)
{
  _timeStep = timeStep;
}

bool AutoPID::atSetPoint(double threshold)
{
  return abs(*_setpoint - *_input) <= threshold;
} //bool AutoPID::atSetPoint

void AutoPID::run()
{
  if (_stopped)
  {
    _stopped = false;
    reset();
  }
  unsigned long _dT = millis() - _lastStep; //calculate time since last update
  if (_dT >= _timeStep)
  { //if long enough, do PID calculations
    _lastStep = millis();
    double _error = *_setpoint - *_input;
    _integral += (_error + _previousError) / 2 * _dT / 1000.0; //Riemann sum integral
    //_integral = constrain(_integral, _outputMin/_Ki, _outputMax/_Ki);
    double _dError = (_error - _previousError) / _dT / 1000.0; //derivative
    _previousError = _error;
    double PID = (_Kp * _error) + (_Ki * _integral) + (_Kd * _dError);
    //*_output = _outputMin + (constrain(PID, 0, 1) * (_outputMax - _outputMin));
    *_output = constrain(PID, _outputMin, _outputMax);
  }
} //void AutoPID::run

void AutoPID::stop()
{
  _stopped = true;
  reset();
}
void AutoPID::reset()
{
  _lastStep = millis();
  _integral = 0;
  _previousError = 0;
}

bool AutoPID::isStopped()
{
  return _stopped;
}

double AutoPID::getIntegral()
{
  return _integral;
}

void AutoPID::setIntegral(double integral)
{
  _integral = integral;
}
void AutoPID::setParameter(int *input, int *setpoint, double *output, uint8_t outputMin, uint8_t outputMax,
                  double Kp, double Ki, double Kd)
{
  _input = input;
  _setpoint = setpoint;
  _output = output;
  _outputMin = outputMin;
  _outputMax = outputMax;
  setGains(Kp, Ki, Kd);
  _timeStep = 1000;
}

void AutoPIDRelay::run()
{
  AutoPID::run();
  while ((millis() - _lastPulseTime) > _pulseWidth)
    _lastPulseTime += _pulseWidth;
  *_relayState = ((millis() - _lastPulseTime) < (_pulseValue * _pulseWidth));
}
