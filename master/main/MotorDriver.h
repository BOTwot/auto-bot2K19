#define MotorDriver_h
#include "commands.h"
#include <Wire.h>
#include "I2C_Anything.h"
#include <Arduino.h>

//The master datatype for data transfer
typedef union packet {
	struct
	{
		int16_t command;
		float data;
		int16_t ckSum;
	};

	int64_t transfrVal;
};

//datatype def end
class MotorDriver
{
  private:
	packet pktTx, pktRx;
	uint8_t _addr;
	void sendPacket(int16_t cmd, float data);
	void getParam(int16_t param);

  public:
  MotorDriver();
	MotorDriver(uint8_t addr);
  void setadd(uint8_t addr);
	static void begin();
	static void scanBus();
	void setMode(int16_t mode);
	void setPWM(int16_t pwm);
	void setRPM(int16_t rpm);
	void setKP(float kp);
	void setKI(float ki);
	void setKD(float kd);
	void setMAXPWM(uint16_t maxPWM);
	void setCounts(uint32_t counts);
	void setGains(float kp, float ki, float kd);
	void setPosition(int32_t pos);
};
