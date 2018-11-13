#include <Servo.h>

Servo myservo[8];  // create servo object to control a servo

#define MIN 1000
#define MAX 2000
#define MID (((MAX-MIN)/2)+MIN)
#define angleTo_us(x) map(x,-90,90,MIN,MAX)
#define dly 200
void stand() {
  //1500 as initial position of all servo
  int  low = 00;
  int  high = 00;
  for (int i = 0; i < 8 ; i++) {
    myservo[i].writeMicroseconds(angleTo_us(0));
  }
}

void setup() {
  for (int i = 0; i < 8 ; i++) {
    myservo[i].attach( (i + 2) ); // attaches the servo on pin 9 to the servo object
  }
  stand();
  delay(3000);
}

void diagonal1_up() {
  myservo[1].writeMicroseconds(angleTo_us(0));
  myservo[3].writeMicroseconds(angleTo_us(0));
  delay(dly);
  myservo[0].writeMicroseconds(angleTo_us(0));
  myservo[2].writeMicroseconds(angleTo_us(0));
}

void diagonal1_low() {
  myservo[3].writeMicroseconds(angleTo_us(67));
  myservo[1].writeMicroseconds(angleTo_us(-67));
  delay(dly);
  myservo[0].writeMicroseconds(angleTo_us(-40));
  myservo[2].writeMicroseconds(angleTo_us(40));
  //delay(200);
  myservo[1].writeMicroseconds(angleTo_us(0));
  myservo[3].writeMicroseconds(angleTo_us(0));

}

void diagonal2_up() {
  myservo[5].writeMicroseconds(angleTo_us(0));
  myservo[7].writeMicroseconds(angleTo_us(0));
  delay(dly);
  myservo[4].writeMicroseconds(angleTo_us(0));
  myservo[6].writeMicroseconds(angleTo_us(0));
}

void diagonal2_low() {
  myservo[5].writeMicroseconds(angleTo_us(67));
  myservo[7].writeMicroseconds(angleTo_us(-67));
  delay(dly);
  myservo[4].writeMicroseconds(angleTo_us(40));
  myservo[6].writeMicroseconds(angleTo_us(-40));
  //delay(200);
  myservo[5].writeMicroseconds(angleTo_us(0));
  myservo[7].writeMicroseconds(angleTo_us(0));
}

void loop() {
  //To walk
//  stand();
//  delay(dly);

    diagonal2_low();
    delay(dly);
    diagonal2_up();
    delay(dly);
    diagonal1_low();
    delay(dly);
    diagonal1_up();
    delay(dly);

}
