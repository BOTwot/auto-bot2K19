#define commands_h
enum commands
{ //mode setting
	MODE_PWM = 0x03,
	SET_PWM,
	GET_PWM,

	MODE_RPM,
	SET_RPM,
	GET_RPM,

	MODE_VEL,
	SET_VEL,
	GET_VEL,
	GET_MODE,

	MODE_POSITION,
	SET_POSITION,
	GET_POSITION,

	//PID gains
	SET_KP,
	GET_KP,
	SET_KI,
	GET_KI,
	SET_KD,
	GET_KD,

	//PWM max
	SET_MAXPWM,
	//encoder stuff
	SET_ENCODER_COUNTS,
};
#define NUM_CMD 17 // this has to be done by hand as there is no easy way to get number of elements of a randomly assigned enum

//If we are not randomely assigining stuff,
//we can add "END" at the end of the enum and do (END-MODE_PWM) to get value
//ref: https://stackoverflow.com/questions/712463/number-of-elements-in-an-enum
//this will be done when we sync all commands_h files
//#define NUM_CMD (END-MODE_PWM)

#define CURRENTLIMIT
