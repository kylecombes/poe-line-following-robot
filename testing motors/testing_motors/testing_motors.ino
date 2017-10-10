// Setting up motors and motor shield
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define leftWheelPin (1)  // this is the M3 pin on motor shield
#define rightWheelPin (2) //M4 on motor shield

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftWheel = AFMS.getMotor(leftWheelPin);
Adafruit_DCMotor *rightWheel = AFMS.getMotor(rightWheelPin);


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  AFMS.begin();  // create with the default frequency 1.6KHz

}

void loop() {
  // put your main code here, to run repeatedly:
 //Drive in a circle (one is forward, one is reverse)
 Serial.input();
 float PWM = 25;
 drive(PWM);
 delay(5000);

//Stop.
 leftWheel->run(RELEASE);
 rightWheel->run(RELEASE);
 delay(2000);

 PWM = 50;
 drive(PWM);
 delay(5000);

//Stop.
 leftWheel->run(RELEASE);
 rightWheel->run(RELEASE);
 delay(2000);
}

void drive(float PWM) {
 leftWheel->setSpeed((int)PWM);
 leftWheel->run(FORWARD);
 
 rightWheel->setSpeed((int)PWM);
 rightWheel->run(BACKWARD);
}



