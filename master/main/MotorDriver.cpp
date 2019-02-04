#include "MotorDriver.h"
MotorDriver ::MotorDriver()
{
}

MotorDriver ::MotorDriver(uint8_t addr)
{
  _addr = addr;
}

void MotorDriver::setadd(uint8_t addr)
{
  _addr = addr;
}
void MotorDriver ::sendPacket(int16_t cmd, float data)
{
  pktTx.command = cmd;
  pktTx.data = data;

  Wire.beginTransmission(_addr);
  I2C_writeAnything(pktTx.transfrVal);
  Wire.endTransmission();
}

void MotorDriver ::getParam(int16_t param)
{
  sendPacket(param, 0);
  Wire.beginTransmission(_addr);
  Wire.requestFrom(_addr, 8, true); //true stops the transmission and releases the bus
  I2C_readAnything(pktRx.transfrVal);

} //Still need to be checked for WIRE logic to RX from

static void MotorDriver ::begin()
{
  Wire.begin();
}

static void MotorDriver::scanBus()
{
  Serial.begin(9600);
  Serial.println("I2C scanner. Scanning ...");
  byte count = 0;

  Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0)
    {
      Serial.print("Found address: ");
      Serial.print(i, DEC);
      Serial.print(" (0x");
      Serial.print(i, HEX);
      Serial.println(")");
      count++;
      delay(1); // maybe unneeded?
    }           // end of good response
  }             // end of for loop
  Serial.println("Done.");
  Serial.print("Found ");
  Serial.print(count, DEC);
  Serial.println(" device(s).");
}

void MotorDriver ::setMode(int16_t mode)
{
  if ((mode == MODE_PWM) || (mode == MODE_RPM))
  {
    sendPacket(mode, 1);
  }
}

void MotorDriver ::setPWM(int16_t pwm)
{
  sendPacket(SET_PWM, pwm);
}

void MotorDriver ::setRPM(int16_t rpm)
{
  sendPacket(SET_RPM, rpm);
}

void MotorDriver ::setPosition(int32_t pos)
{
  sendPacket(SET_POSITION, pos);
}

void MotorDriver ::setKP(float kp)
{
  sendPacket(SET_KP, kp);
}
void MotorDriver ::setKI(float ki)
{
  sendPacket(SET_KI, ki);
}
void MotorDriver ::setKD(float kd)
{
  sendPacket(SET_KD, kd);
}

void MotorDriver ::setMAXPWM(uint16_t maxPWM)
{
  sendPacket(SET_MAXPWM, maxPWM);
}
void MotorDriver ::setCounts(uint32_t counts)
{
  sendPacket(SET_ENCODER_COUNTS, counts);
}
void MotorDriver ::setGains(float kp, float ki, float kd)
{
  void setKP(float kp);
  void setKI(float ki);
  void setKD(float kd);
}

// #define commands_h
// enum commands { //mode setting
// 	MODE_PWM = 0x03,
// 	SET_PWM,
// 	GET_PWM,

// 	MODE_RPM,
// 	SET_RPM,
// 	GET_RPM,

// 	MODE_VEL,
// 	SET_VEL,
// 	GET_VEL,
// 	GET_MODE,

// 	//PID gains
// 	SET_KP,
// 	GET_KP,
// 	SET_KI,
// 	GET_KI,
// 	SET_KD,
// 	GET_KD,

// 	//encoder stuff
// 	SET_ENCODER_COUNTS,
// };
// #define NUM_CMD 17 // this has to be done by hand as there is no easy way to get number of elements of a randomly assigned enum

// //If we are not randomely assigining stuff,
// //we can add "END" at the end of the enum and do (END-MODE_PWM) to get value
// //ref: https://stackoverflow.com/questions/712463/number-of-elements-in-an-enum
// //this will be done when we sync all commands_h files
// //#define NUM_CMD ( (END) - (MODE_PWM) )

// #define CURRENTLIMIT
