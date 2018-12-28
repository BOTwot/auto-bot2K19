

#include <PinChangeInt.h>

// Modify these at your leisure.
#define MYPIN1 4
#define MYPIN2 5

// Don't change these.
//#define FIRST_ANALOG_PIN 14
//#define TOTAL_PINS 19
// Notice that anything that gets modified inside an interrupt, that I wish to access
// outside the interrupt, is marked "volatile". That tells the compiler not to optimize
// them.
volatile int a=0;

// Do not use any Serial.print() in interrupt subroutines. Serial.print() uses interrupts,
// and by default interrupts are off in interrupt subroutines.
// Here we update a counter corresponding to whichever pin interrupted.
void quicfunc0() {
  a++;
};



// Attach the interrupts in setup()
void setup() {
  pinMode(MYPIN1, INPUT_PULLUP);
  attachPinChangeInterrupt(MYPIN1, quicfunc0, CHANGE);
  pinMode(MYPIN2, INPUT_PULLUP);
  attachPinChangeInterrupt(MYPIN2, quicfunc0, CHANGE);
  Serial.begin(115200);
  Serial.println("---------------------------------------");
}


void loop() {
                               // every second,
  Serial.println(a);
}

