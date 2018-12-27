#include "AutoPID.h"

AutoPID::AutoPID(int *input, int *setpoint, int *output1, int *output2, uint8_t outputMin, uint8_t outputMax, double Kp, double Ki, double Kd) {
  _input = input;
  _setpoint = setpoint;
  _output1 = output1;
  _output2 = output2;
  _outputMin = outputMin;
  _outputMax = outputMax;
  setGains(Kp, Ki, Kd);
  _timeStep = 1;
}//AutoPID::AutoPID
void AutoPID::setGains(double Kp, double Ki, double Kd) {
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
}//AutoPID::setControllerParams
void AutoPID::setOutputRange(uint8_t outputMin, uint8_t outputMax) {
  _outputMin = outputMin;
  _outputMax = outputMax;
}//void AutoPID::setOutputRange
void AutoPID::setTimeStep(unsigned long timeStep) {
  _timeStep = timeStep;
}
void AutoPID::run() {
  unsigned long _dT = millis() - _lastStep;   //calculate time since last update
  if (_dT >= _timeStep) {                     //if long enough, do PID calculations
    _lastStep = millis();
    double _error;
    _error = abs(*_setpoint - (*_input));
    _integral += (_error + _previousError) / 2 * _dT / 1000.0;   //Riemann sum integral
    //_integral = constrain(_integral, _outputMin/_Ki, _outputMax/_Ki);
    double _dError = (_error - _previousError) / _dT / 1000.0;   //derivative
    _previousError = _error;
    double PID = (_Kp * _error) + (_Ki * _integral) + (_Kd * _dError);
    //*_output = _outputMin + (constrain(PID, 0, 1) * (_outputMax - _outputMin));
    if (*_setpoint > *_input)
    {
      *_output1 = constrain(PID, _outputMin, _outputMax);
      *_output2 = 0;
    }
    else if (*_setpoint < *_input)
    {
      *_output2 = constrain(PID, _outputMin, _outputMax);
      *_output1 = 0;
    }
  }

  //  else if (*_setpoint < *_input)
  //  {
  //    double _error;
  //    _error = *_input - *_setpoint ;
  //    _integral += (_error + _previousError) / 2 * _dT / 1000.0;   //Riemann sum integral
  //    //_integral = constrain(_integral, _outputMin/_Ki, _outputMax/_Ki);
  //    double _dError = (_error - _previousError) / _dT / 1000.0;   //derivative
  //    _previousError = _error;
  //    double PID = (_Kp * _error) + (_Ki * _integral) + (_Kd * _dError);
  //    //*_output = _outputMin + (constrain(PID, 0, 1) * (_outputMax - _outputMin));
  //    *_output2 = constrain(PID, _outputMin, _outputMax);
  //    *_output1 = 0;
  //  }
}

//void AutoPID::run
void AutoPID::reset() {
  _lastStep = millis();
  _integral = 0;
  _previousError = 0;
}


